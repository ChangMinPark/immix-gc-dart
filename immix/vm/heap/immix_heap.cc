#include "vm/heap/immix_heap.h"

#include "vm/isolate.h"
#include "vm/object.h"
#include "vm/object_set.h"
#include "vm/raw_object.h"

namespace dart{

ImmixHeap::ImmixHeap(Isolate* isolate)
    : isolate_(isolate) {
  // printf("ImmixHeap::ImmixHeap(...)\n");
  space_ = (char*) malloc(BLOCK_SIZE * BLOCK_NUM);

  start_ = (intptr_t) space_;
  end_ = (intptr_t) (space_ + (BLOCK_SIZE * BLOCK_NUM));

  ImmixHeap::initializeBlocks(start_);

}

ImmixHeap::~ImmixHeap() {
    // printf("ImmixHeap::~ImmixHeap(...)\n");
    //TODO: delete everything created.

}

void ImmixHeap::Init(Isolate* isolate, intptr_t max_words) {
    ASSERT(isolate->immixHeap() == NULL);
    // printf(" ---- immix_heap.cc: Init(...)\n");
    ImmixHeap* immixHeap = new ImmixHeap(isolate);
    isolate->set_immixHeap(immixHeap);

}

uword ImmixHeap::Allocate(intptr_t size) {
    ASSERT(Thread::Current()->no_safepoint_scope_depth() == 0);

    //TODO: If size is less than a line size, use IMPLICIT MARKING 
    
    //isolate()->AssertCurrentThreadIsMutator();
    //Thread* thread = Thread::Current();
    return 0;
}

intptr_t getFirstFreeBlock(){
    return 0;

}

intptr_t getNextRecyclableBlock(intptr_t current_block){
    return 0;

}

bool isAllocatableSize(intptr_t size_) {
    return size_ < MAX_OBJECT_SIZE;
}

void ImmixHeap::initializeBlocks(intptr_t start) {
    for(intptr_t i = 0; i < BLOCK_NUM; i++) {
        intptr_t block = start + (i * BLOCK_SIZE);
        Block::init(block);
    }
}



/* These methods are for debugging. Recommend to use with small number of blocks and lines */
void ImmixHeap::printBlocksAndLines() {
    for(int i = 0; i < BLOCK_NUM; i++) {
        intptr_t block = (intptr_t) start_ + (i*BLOCK_SIZE);
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



