#include "vm/heap/immix_heap.h"

#include "vm/isolate.h"
#include "vm/object.h"
#include "vm/object_set.h"
#include "vm/raw_object.h"

namespace dart{

ImmixHeap::ImmixHeap(Isolate* isolate)
    : isolate_(isolate) {
    initializeBlocks();
}

ImmixHeap::~ImmixHeap() {
    //TODO: delete everything created.
}

void ImmixHeap::init(Isolate* isolate) {
    ASSERT(isolate->immixHeap() == NULL);
    ImmixHeap* immixHeap = new ImmixHeap(isolate);
    isolate->set_immixHeap(immixHeap);
}

uword ImmixHeap::allocate(intptr_t size) {
    ASSERT(Thread::Current()->no_safepoint_scope_depth() == 0);

    /* Whether it's allocatable or not */
    if(!isAllocatableSize(size)) {
        printf(" - Cannot allocate an object (%ld bytes)\n", size);
        return 0;
    }

    if(size < LINE_SIZE) {      // Can fit into a single line
        printf(" - Allocate an object (%ld bytes): 1 Line\n", size);

        /* Look for implicitly marked line */
        for(int i = 0; i < blockNum_; i++) {
            intptr_t block = blockAddresses_[i];
            intptr_t line = Block::findFirstRecyclableLine(block);
            if (line != 0) {             
                Line::markLine(Block::getIndexFromLine(block, line), LINE_MARK_USED);
                Block::updateBlockState(block);
                return line;
            }
        }

        /* Look for available line */
        for(int i = 0; i < blockNum_; i++) {
            intptr_t block = blockAddresses_[i];
            intptr_t line = Block::findFirstAvailableLine(block);
            if (line != 0) {
                // TODO: Currently it marks UNUSED, should be IMPLICIT in future.
                Line::markLine(Block::getIndexFromLine(block, line), LINE_MARK_USED);
                Block::updateBlockState(block);
                return line;
            }
        }

        /* Get new free block */
        intptr_t block = getFreeBlock();
        intptr_t line = Block::findFirstAvailableLine(block);
        // TODO: Currently it marks UNUSED, should be IMPLICIT in future.
        Line::markLine(Block::getIndexFromLine(block, line), LINE_MARK_USED);
        Block::updateBlockState(block);
        return line;

    } else {    // Requires multiple lines
        intptr_t linesNeeded = Line::calculateLinesNeeded(size);
        printf(" - Allocate an object (%ld bytes): %ld lines\n", size, linesNeeded);
       
        /* Look for availabe contiguous lines in existing blocks */
        for(int i = 0; i < blockNum_; i++) {
            intptr_t block = blockAddresses_[i];
            intptr_t firstLine = Block::findContiguousAvailableLines(block, linesNeeded);
            if(firstLine != 0) {
                intptr_t lineIndex = Block::getIndexFromLine(block, firstLine);
                for(intptr_t j = 0; j < linesNeeded; j++) {
                    Line::markLine(lineIndex + j, LINE_MARK_USED);
                }
                Block::updateBlockState(block);
                return firstLine;
            } 
        }

        /* Get new free block */
        intptr_t block = getFreeBlock();
        intptr_t firstLine = Block::findContiguousAvailableLines(block, linesNeeded);
        intptr_t lineIndex = Block::getIndexFromLine(block, firstLine);
        for(intptr_t j = 0; j < linesNeeded; j++) {
            Line::markLine(lineIndex + j, LINE_MARK_USED);
        }
        Block::updateBlockState(block);
        return firstLine;            

    }
    
    return 0;
}

intptr_t ImmixHeap::getFreeBlock(){
    printf(" --> ImmixHeap::getFreeBlock() \n");
    char* block = (char*) malloc(BLOCK_SIZE);
    Block::init((intptr_t) block);

    blockNum_++;
    intptr_t* new_blockAddresses_ = (intptr_t*) malloc(sizeof(intptr_t) * blockNum_);
    for(int i = 0; 0 < blockNum_; i++) {
        if (i == blockNum_ - 1) {
            new_blockAddresses_[i] = (intptr_t) block; 
            break;
        }
        new_blockAddresses_[i] = blockAddresses_[i];       
    }
    blockAddresses_ = new_blockAddresses_;

    return (intptr_t) block;
}

bool ImmixHeap::isAllocatableSize(intptr_t size_) {
    return size_ < MAX_OBJECT_SIZE;
}

void ImmixHeap::initializeBlocks() {
    printf(" - Initialized %d blocks.\n",BLOCK_NUM);
    blockAddresses_ = (intptr_t*) malloc(sizeof(intptr_t) * BLOCK_NUM);
    blockNum_ = BLOCK_NUM;
    for(int i = 0; i < BLOCK_NUM; i++) {
        // printf(" - initializing %dth block...\n", i);
        char* block = (char*) malloc(BLOCK_SIZE);
        Block::init((intptr_t) block);
        blockAddresses_[i] = (intptr_t) block; 
    }
}


/* These methods are for debugging. Recommend to use with small number of blocks and lines */
void ImmixHeap::printBlocksAndLines() {
    // printf("blockNum_: %d\n", blockNum_);
    printf("\n----- Printing Blocks & Lines -----\n");
    for(int i = 0; i < (int) blockNum_; i++) {
        
        // printf(" - printing %dth block...\n", i);
        intptr_t block = (intptr_t) blockAddresses_[i];
        uint8_t state = Block::getBlockState(block);
        switch (state) {
            case BLOCK_STATE_FREE:
                printf("[.]");
                break;
            case BLOCK_STATE_RECYCLABLE:
                printf("[*]");
                break;
            case BLOCK_STATE_UNAVAILABLE:
                printf("[#]");             
                break;
        }

        for(int j = 0; j < NUM_LINE_IN_BLOCK - 1; j++) {
            uint8_t* line_mark = (uint8_t*) block+j;
            switch (*line_mark) {
                case LINE_MARK_UNUSED:
                    printf(" .");
                    break;
                case LINE_MARK_USED:
                    printf(" #");
                    break;
                case LINE_MARK_IMPLICIT:
                    printf(" *");
                    break;
            }    
        }
        printf("\n");
    }
    printf("\n");

}
}   // Close namespace



