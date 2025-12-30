#include "floatMessageBuffer.h"

floatMessageBuffer::floatMessageBuffer()
    : msg(0), newMsg(false) {
}

void floatMessageBuffer::write(float val) {
    std::lock_guard<std::mutex> lock(msgMutex);  // safer than manual lock/unlock
    msg = val;
    newMsg = true;
}

bool floatMessageBuffer::read(float *val) {
    std::lock_guard<std::mutex> lock(msgMutex);
    if (newMsg) {
        *val = msg;
        newMsg = false;
        return true;
    }
    return false;
}

