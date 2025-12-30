#include "oscillator.h"
#include <chrono>
using namespace std::chrono;

oscillator::oscillator(steady_clock::time_point _start, float _a)
    : start(_start), a(_a) {}

float oscillator::read_val() {
    constexpr float SLOPE = 4.0f;
    constexpr float HALF_PERIOD = 0.5f;

    auto now = steady_clock::now();        
    long long total_ms = duration_cast<milliseconds>(now - start).count();
    long long ms_only = total_ms % 1000;
    float t_now = float(ms_only) / 1000;

    int sign = 1;
    float t = t_now;
    if (t_now > HALF_PERIOD) {
        t -= HALF_PERIOD;
        sign = -1;
    }

    return sign * a * (-1 + SLOPE * t);
}
