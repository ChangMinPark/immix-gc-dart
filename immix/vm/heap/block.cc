#include "vm/heap/block.h"


namespace dart{

void Block::init(intptr_t block) {

    /* Initialize Block State */    
    uint8_t* state_ = (uint8_t*) block + BLOCK_STATE_OFFSET;
    *state_ = BLOCK_STATE_FREE;

    /* Initilize Line Table */
    intptr_t lineTable_ = Block::getLineTable(block);
    Block::initLineTable(lineTable_);

}

void Block::initLineTable(intptr_t lineTable) {
    for(intptr_t i = 0; i < NUM_LINE_IN_BLOCK; i++) {
        uint8_t* mark_ = (uint8_t*) lineTable + i;
        *mark_ = LINE_MARK_UNUSED;
    }
}

}
