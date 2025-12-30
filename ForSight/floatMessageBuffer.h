#pragma once
#include <mutex>

class floatMessageBuffer {
public:
    floatMessageBuffer();

    void write(float val);
    bool read(float *val);

private:
    float msg;
    bool newMsg;
    std::mutex msgMutex;
};

