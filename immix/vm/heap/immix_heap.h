#ifndef RUNTIME_VM_HEAP_IMMIX_HEAP_H_
#define RUNTIME_VM_HEAP_IMMIX_HEAP_H_

#include "vm/isolate.h"
#include "vm/globals.h"
#include "vm/heap/block.h"

#define BLOCK_NUM 3

namespace dart {
class ImmixHeap {
    public:
    ImmixHeap(Isolate* isolate);
    ~ImmixHeap();

    void init(Isolate* isolate);
    
    intptr_t getFreeBlock();

    bool isAllocatableSize(intptr_t size);

    Isolate* isolate() const { return isolate_; };
    Isolate* isolate_;

    intptr_t* blockAddresses_;
    int blockNum_;

    void initializeBlocks();
    
    uword allocate(intptr_t size);

    /* For Testing */
    void printBlocksAndLines();

};
}
#endif // RUNTIME_VM_HEAP_IMMIX_HEAP_H_
