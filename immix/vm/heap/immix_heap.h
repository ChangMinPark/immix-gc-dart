#ifndef RUNTIME_VM_HEAP_IMMIX_HEAP_H_
#define RUNTIME_VM_HEAP_IMMIX_HEAP_H_

#include "vm/isolate.h"
#include "vm/globals.h"
#include "vm/heap/block.h"

#define BLOCK_NUM 10

namespace dart {
class ImmixHeap {
    public:
    ImmixHeap(Isolate* isolate);
    ~ImmixHeap();

    static void Init(Isolate* isolate, intptr_t max_words);
    
    intptr_t getFirstFreeBlock();
    intptr_t getNextRecyclableBlock(intptr_t current_block);

    bool isAllocatableSize(intptr_t size);

    Isolate* isolate() const { return isolate_; };
    Isolate* isolate_;

    /* Types does not matter here since it is just for requesting a space. */
    char* space_;

    intptr_t start_;
    intptr_t end_;

    static void initializeBlocks(intptr_t start);
    uword Allocate(intptr_t size);

    /* For Testing */
    void printBlocksAndLines();


};
}
#endif // RUNTIME_VM_HEAP_IMMIX_HEAP_H_
