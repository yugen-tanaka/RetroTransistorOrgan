#pragma once
#include <cmath>

class StaircaseOscillator {
private:
    static inline double poly_blep(double t, double dt) {
        if (t < dt) {
            t /= dt;
            return t + t - t * t - 1.0;
        }
        else if (t > 1.0 - dt) {
            t = (t - 1.0) / dt;
            return t * t + t + t + 1.0;
        }
        return 0.0;
    }

public:
    static inline double process(double phase, double dt) {
        // phase is [0, 1.0)
        double sq1 = (phase < 0.5) ? 1.0 : -1.0;
        sq1 += poly_blep(phase, dt);
        double p1_shifted = phase + 0.5;
        if (p1_shifted >= 1.0) p1_shifted -= 1.0;
        sq1 -= poly_blep(p1_shifted, dt);
        
        double phase2 = phase * 2.0;
        if (phase2 >= 1.0) phase2 -= 1.0;
        double dt2 = dt * 2.0;
        
        double sq2 = (phase2 < 0.5) ? 1.0 : -1.0;
        if (dt2 < 1.0) { // Only blep if frequency is below nyquist
            sq2 += poly_blep(phase2, dt2);
            double p2_shifted = phase2 + 0.5;
            if (p2_shifted >= 1.0) p2_shifted -= 1.0;
            sq2 -= poly_blep(p2_shifted, dt2);
        }
        
        // Sum fundamental and 1 octave up
        return (sq1 + sq2) * 0.5;
    }
};
