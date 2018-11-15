#ifndef RUNTIME_VM_HEAP_IMMIX_HEAP_H_
#define RUNTIME_VM_HEAP_IMMIX_HEAP_H_

#include "vm/isolate.h"
#include "vm/globals.h"
#include "vm/heap/block.h"

namespace dart {
class ImmixHeap {
    public:
    ImmixHeap(Isolate* isolate);
    ~ImmixHeap();

    static void Init(Isolate* isolate, intptr_t max_words);
    uword Allocate(intptr_t size);
            

    Isolate* isolate() const { return isolate_; };

    Isolate* isolate_;

    /* Types does not matter here since it is just for requesting a space. */
    char* space_;

};
}
#endif // RUNTIME_VM_HEAP_IMMIX_HEAP_H_
