#include "vm/heap/line.h"

namespace dart{

intptr_t Line::calculateLinesNeeded(intptr_t size) {
    intptr_t result = size / LINE_SIZE;
    if (size % LINE_SIZE != 0) result++;
    return result;
}

void Line::markLine(intptr_t lineTableIndex, uint8_t markState) {
    uint8_t* mark = (uint8_t*) lineTableIndex;
    *mark = markState;
}

uint8_t Line::getLineMark(intptr_t lineTableIndex) {
    uint8_t* mark = (uint8_t*) lineTableIndex;
    return *mark;
}

}
