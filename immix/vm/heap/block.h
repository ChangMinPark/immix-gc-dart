#ifndef RUNTIME_VM_HEAP_BLOCK_H_
#define RUNTIME_VM_HEAP_BLOCK_H_

#define BLOCK_SIZE 32768 // in bytes.
#define MAX_OBJECT_SIZE BLOCK_SIZE/2 

#include "vm/heap/line.h"

namespace dart{

class Block {

    Block();

}; 
}

#endif  // RUNTIME_VM_HEAP_BLOCK_H_
