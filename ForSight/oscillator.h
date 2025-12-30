#pragma once
#include <chrono>

class oscillator {
public:
    // Constructor
    oscillator(std::chrono::steady_clock::time_point _start, float _a);

    // Member function to read current value
    float read_val();

private:
    std::chrono::steady_clock::time_point start;
    float a;
};
