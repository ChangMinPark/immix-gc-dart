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
    ASSERT(isAllocatableSize(size));
    if(size < LINE_SIZE) {      // Can fit into a single line
        // TODO: Look for recyclable lines.

    } else {                    // Requires multiple lines
        // intptr_t lines_needed = Line::calculateLinesNeeded(size);
        
        // TODO: Calculate how many contiguous lines.
        //

    }
    //TODO: If size is less than a line size, use IMPLICIT MARKING 
    
    //isolate()->AssertCurrentThreadIsMutator();
    //Thread* thread = Thread::Current();
    return 0;
}

intptr_t ImmixHeap::getFirstFreeBlock(){
    return 0;

}

intptr_t ImmixHeap::getNextRecyclableBlock(intptr_t current_block){
    return 0;

}

bool ImmixHeap::isAllocatableSize(intptr_t size_) {
    return size_ < MAX_OBJECT_SIZE;
}

void ImmixHeap::initializeBlocks() {
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
    for(int i = 0; i < (int) blockNum_; i++) {
        
        // printf(" - printing %dth block...\n", i);
        intptr_t block = (intptr_t) blockAddresses_[i];
        uint8_t* state = (uint8_t*) Block::getBlockState(block);
        switch (*state) {
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

}
}   // Close namespace



