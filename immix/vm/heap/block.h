#ifndef RUNTIME_VM_HEAP_BLOCK_H_
#define RUNTIME_VM_HEAP_BLOCK_H_

#include "vm/heap/line.h"
#include <stdint.h>

#define NUM_LINE_IN_BLOCK 11                    // First line is for meta data.
                                                // Default: 128
#define BLOCK_SIZE NUM_LINE_IN_BLOCK*LINE_SIZE   // in bytes.
#define MAX_OBJECT_SIZE BLOCK_SIZE/2 
#define BLOCK_STATE_OFFSET NUM_LINE_IN_BLOCK-1


#define BLOCK_STATE_FREE 0
#define BLOCK_STATE_RECYCLABLE 1
#define BLOCK_STATE_UNAVAILABLE 2



namespace dart{

class Block {

    public:
    /* Initializing methods */
    static void init(intptr_t block);
    static void initLineTable(intptr_t lineTable);

    /* Beginning of a block is a line table. */
    static intptr_t getLineTable(intptr_t block) { return block; };
    static uint8_t getBlockState(intptr_t block); 
    static void updateBlockState(intptr_t block);

    /* Helper methods */
    static intptr_t getLineFromIndex(intptr_t block, intptr_t lineIndex);
    static intptr_t getIndexFromLine(intptr_t block, intptr_t line);
    static intptr_t findFirstAvailableLine(intptr_t block);
    static intptr_t findFirstRecyclableLine(intptr_t block);
    static intptr_t findContiguousAvailableLines(intptr_t block, intptr_t numLines);

}; 
}

#endif  // RUNTIME_VM_HEAP_BLOCK_H_
