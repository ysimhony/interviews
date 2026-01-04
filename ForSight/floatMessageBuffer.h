#pragma once
#include <mutex>
#include "INode.h"


class floatMessageBuffer : public INode {
public:
    floatMessageBuffer() : msg(0), newMsg(false) {}

    void write(float val) {
        std::lock_guard<std::mutex> lock(msgMutex);
        msg = val;
        newMsg = true;
    }

    bool read(float &val) {
        std::lock_guard<std::mutex> lock(msgMutex);
        if (newMsg) {
            val = msg;
            newMsg = false;
            return true;
        }
        return false;
    }

private:
    float msg;
    bool newMsg;
    std::mutex msgMutex;
};
