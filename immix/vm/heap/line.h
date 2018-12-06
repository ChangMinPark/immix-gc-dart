#ifndef RUNTIME_VM_HEAP_LINE_H_
#define RUNTIME_VM_HEAP_LINE_H_

#define LINE_SIZE 256   // in bytes.

#define LINE_MARK_UNUSED 0
#define LINE_MARK_USED 1
#define LINE_MARK_IMPLICIT 2

#include <stdint.h>

namespace dart{

class Line{
    public:
    /* Helper methods  */    
    static intptr_t calculateLinesNeeded(intptr_t size);
    static void markLine(intptr_t lineTableIndex, uint8_t markState);
    static uint8_t getLineMark(intptr_t lineTableIndex);
};
}
#endif // RUNTIME_VM_HEAP_LINE_H_
