#pragma once
#include <chrono>
#include "INode.h"

class oscillator: public INode {
public:
    // Constructor
    oscillator(std::chrono::steady_clock::time_point _start, float _a):
        start(_start), a(_a) {};

    virtual void write(float val){
        return;
    };
    
    virtual bool read(float& out){
        constexpr float SLOPE = 4.0f;
        constexpr float HALF_PERIOD = 0.5f;

        auto now = std::chrono::steady_clock::now();        
        long long total_ms = 
            std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
        long long ms_only = total_ms % 1000;
        float t_now = float(ms_only) / 1000;

        int sign = 1;
        float t = t_now;
        if (t_now > HALF_PERIOD) {
            t -= HALF_PERIOD;
            sign = -1;
        }

        out = sign * a * (-1 + SLOPE * t);
        return true;
    };
private:
    std::chrono::steady_clock::time_point start;
    float a;
};










