#ifndef RUNTIME_VM_HEAP_BLOCK_H_
#define RUNTIME_VM_HEAP_BLOCK_H_

#include "vm/heap/line.h"
#include <stdint.h>

#define NUM_LINE_IN_BLOCK 11                   // First line is for meta data.
#define BLOCK_SIZE NUM_LINE_IN_BLOCK*LINE_SIZE   // in bytes.
#define MAX_OBJECT_SIZE BLOCK_SIZE/2 
#define BLOCK_STATE_OFFSET NUM_LINE_IN_BLOCK-1


#define BLOCK_STATE_FREE 0
#define BLOCK_STATE_RECYCLABLE 1
#define BLOCK_STATE_UNAVAILABLE 2



namespace dart{

class Block {

    public:
    static void init(intptr_t block);
    static void initLineTable(intptr_t lineTable);

    /* Beginning of a block is a line table. */
    static intptr_t getLineTable(intptr_t block) { return block; };
    static intptr_t getBlockState(intptr_t block) { return block+BLOCK_STATE_OFFSET; };

}; 
}

#endif  // RUNTIME_VM_HEAP_BLOCK_H_
