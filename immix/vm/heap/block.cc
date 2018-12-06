#include "vm/heap/block.h"


namespace dart{

void Block::init(intptr_t block) {

    /* Initialize Block State */    
    uint8_t* state = (uint8_t*) block + BLOCK_STATE_OFFSET;
    *state = BLOCK_STATE_FREE;

    /* Initilize Line Table */
    intptr_t lineTable_ = Block::getLineTable(block);
    Block::initLineTable(lineTable_);

}

void Block::initLineTable(intptr_t lineTable) {
    /* Initialize all lines as UNUSED */
    for(intptr_t i = 0; i < NUM_LINE_IN_BLOCK - 1; i++) {
        intptr_t lineIndex = lineTable + i;
        Line::markLine(lineIndex, LINE_MARK_UNUSED);
    }
}

uint8_t Block::getBlockState(intptr_t block) {
    uint8_t* blockState = (uint8_t*) block + BLOCK_STATE_OFFSET;
    return *blockState;
}

void Block::updateBlockState(intptr_t block) {
    int lineUsed = 0;
    for(intptr_t i = 0; i < NUM_LINE_IN_BLOCK - 1; i++) {
        intptr_t lineIndex = block + i;
        uint8_t* lineState = (uint8_t*) lineIndex;
        switch(*lineState){
            case LINE_MARK_UNUSED: break;
            case LINE_MARK_IMPLICIT: break;
            case LINE_MARK_USED: lineUsed++;
        }
    }

    uint8_t* blockState = (uint8_t*) block + BLOCK_STATE_OFFSET;
    if(lineUsed == 0) *blockState = BLOCK_STATE_FREE;
    else if(lineUsed == NUM_LINE_IN_BLOCK - 1) *blockState = BLOCK_STATE_UNAVAILABLE;
    else *blockState = BLOCK_STATE_RECYCLABLE;
}

intptr_t Block::getLineFromIndex(intptr_t block, intptr_t lineIndex) {
    intptr_t indexNum = lineIndex - block + 1;
    return block + (LINE_SIZE * indexNum);
}

intptr_t Block::getIndexFromLine(intptr_t block, intptr_t line) {
    intptr_t indexNum = (line - block) / LINE_SIZE;
    return block + indexNum - 1;
}

intptr_t Block::findFirstAvailableLine(intptr_t block) {
    for(intptr_t i = 0; i < NUM_LINE_IN_BLOCK - 1; i++) {
        intptr_t lineIndex = block + i;
        if (Line::getLineMark(lineIndex) == LINE_MARK_UNUSED) {
            /* Return a line address */
            return getLineFromIndex(block, lineIndex);
        }
    }
    /* Available line not found */
    return 0;
}

intptr_t Block::findFirstRecyclableLine(intptr_t block) {
    for(intptr_t i = 0; i < NUM_LINE_IN_BLOCK - 1; i++) {
        intptr_t lineIndex = block + i;
        if (Line::getLineMark(lineIndex) == LINE_MARK_IMPLICIT) {
            /* Return a line address */
            return getLineFromIndex(block, lineIndex);                                     
        }
    }
    /* Recyclable line not found */
    return 0;
}

intptr_t Block::findContiguousAvailableLines(intptr_t block, intptr_t numLines) {
    int foundLines = 0;
    intptr_t firstLine = 0;
    for(intptr_t i = 0; i < NUM_LINE_IN_BLOCK - 1; i++) {
        intptr_t lineIndex = block + i;
        if (Line::getLineMark(lineIndex) == LINE_MARK_UNUSED) {
            if (foundLines == 0) firstLine = getLineFromIndex(block, lineIndex);
            foundLines++;
            if (foundLines == numLines) return firstLine;
        }
        else {
            foundLines = 0;
            firstLine = 0;
        }
    }
    /* Contiguous line not found */
    return 0;
}


}
