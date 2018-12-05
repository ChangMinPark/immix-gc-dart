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
    static intptr_t calculateLinesNeeded(intptr_t size) {
        intptr_t result = size / LINE_SIZE;
        if (size % LINE_SIZE != 0) result++;
        return result;
    }
};
}
#endif // RUNTIME_VM_HEAP_LINE_H_
