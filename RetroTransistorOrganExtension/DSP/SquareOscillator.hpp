#pragma once
#include <cmath>

class SquareOscillator {
public:
    static inline double process(double phase, double dt) {
        // Simple square wave: +1.0 for [0, 0.5), -1.0 for [0.5, 1.0)
        // No poly-BLEP, just a basic square oscillator
        return (phase < 0.5) ? 1.0 : -1.0;
    }
};
