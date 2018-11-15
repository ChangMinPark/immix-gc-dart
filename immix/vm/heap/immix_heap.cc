#include "vm/heap/immix_heap.h"

#include "vm/isolate.h"
#include "vm/object.h"
#include "vm/object_set.h"
#include "vm/raw_object.h"

namespace dart{

ImmixHeap::ImmixHeap(Isolate* isolate)
    : isolate_(isolate) {
  printf("ImmixHeap::ImmixHeap(...)\n");
        // TODO: UpdateGlobalMaxUsed();
        // TODO: Initialize heap. 
}

ImmixHeap::~ImmixHeap() {
    printf("ImmixHeap::~ImmixHeap(...)\n");
    //TODO: delete everything created.

}

void ImmixHeap::Init(Isolate* isolate, intptr_t max_words) {
    ASSERT(isolate->immixHeap() == NULL);
    printf(" ---- immix_heap.cc: Init(...)\n");
    ImmixHeap* immixHeap = new ImmixHeap(isolate);
    // TODO: Printing out heap sizes.
    // immixHeap->PrintSizes();
    isolate->set_immixHeap(immixHeap);

}

uword ImmixHeap::Allocate(intptr_t size) {
    ASSERT(Thread::Current()->no_safepoint_scope_depth() == 0);
//isolate()->AssertCurrentThreadIsMutator();
    //Thread* thread = Thread::Current();
    // TODO: allocate to space <- need to implement it.
    return 0;
}

}   // Close namespace



