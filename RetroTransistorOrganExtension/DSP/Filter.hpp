#pragma once
#include <cmath>

class OnePoleLPF {
public:
    void setCutoff(double cutoff, double sampleRate) {
        mAlpha = std::exp(-2.0 * M_PI * cutoff / sampleRate);
    }

    void reset() {
        mOut1 = 0.0;
        mOut2 = 0.0;
    }
    
    double process(double input) {
        // Cascade 2 poles for 12dB/octave slope (deeper filter)
        mOut1 = input + mAlpha * (mOut1 - input);
        mOut2 = mOut1 + mAlpha * (mOut2 - mOut1);
        return mOut2;
    }
private:
    double mAlpha = 0.0;
    double mOut1 = 0.0;
    double mOut2 = 0.0;
};

class BiquadLowPass {
public:
    void setCutoff(double cutoff, double q, double sampleRate) {
        if (!std::isfinite(sampleRate) || sampleRate <= 0.0) {
            sampleRate = 44100.0;
        }
        if (!std::isfinite(q) || q < 0.01) {
            q = 0.01;
        }
        if (!std::isfinite(cutoff)) {
            cutoff = 10.0;
        }

        const double maxCutoff = sampleRate * 0.45;
        if (cutoff < 10.0) {
            cutoff = 10.0;
        } else if (cutoff > maxCutoff) {
            cutoff = maxCutoff;
        }

        const double omega = 2.0 * M_PI * cutoff / sampleRate;
        const double sinw = std::sin(omega);
        const double cosw = std::cos(omega);
        const double alpha = sinw / (2.0 * q);
        const double a0 = 1.0 + alpha;

        const double b0 = (1.0 - cosw) * 0.5;
        const double b1 = 1.0 - cosw;
        const double b2 = b0;

        const double safeA0 = (a0 == 0.0 || !std::isfinite(a0)) ? 1.0 : a0;
        mB0 = b0 / safeA0;
        mB1 = b1 / safeA0;
        mB2 = b2 / safeA0;
        mA1 = -2.0 * cosw / safeA0;
        mA2 = (1.0 - alpha) / safeA0;
    }

    void reset() {
        mw1 = 0.0;
        mw2 = 0.0;
    }
    
    double process(double input) {
        const double output = mB0 * input + mw1;
        if (!std::isfinite(output)) {
            reset();
            return 0.0;
        }
        const double w1 = mB1 * input + mw2 - mA1 * output;
        const double w2 = mB2 * input - mA2 * output;
        mw1 = std::isfinite(w1) ? w1 : 0.0;
        mw2 = std::isfinite(w2) ? w2 : 0.0;
        return output;
    }
private:
    double mB0 = 0.0;
    double mB1 = 0.0;
    double mB2 = 0.0;
    double mA1 = 0.0;
    double mA2 = 0.0;
    double mw1 = 0.0;
    double mw2 = 0.0;
};

class BiquadBandPass {
public:
    void setCutoff(double centerFreq, double q, double sampleRate) {
        if (!std::isfinite(sampleRate) || sampleRate <= 0.0) {
            sampleRate = 44100.0;
        }
        if (!std::isfinite(q) || q < 0.01) {
            q = 0.01;
        }
        if (!std::isfinite(centerFreq)) {
            centerFreq = 1000.0;
        }

        const double maxCutoff = sampleRate * 0.45;
        if (centerFreq < 10.0) {
            centerFreq = 10.0;
        } else if (centerFreq > maxCutoff) {
            centerFreq = maxCutoff;
        }

        const double omega = 2.0 * M_PI * centerFreq / sampleRate;
        const double sinw = std::sin(omega);
        const double cosw = std::cos(omega);
        const double alpha = sinw / (2.0 * q);
        const double a0 = 1.0 + alpha;

        // Bandpass coefficients
        const double b0 = alpha;
        const double b1 = 0.0;
        const double b2 = -alpha;

        const double safeA0 = (a0 == 0.0 || !std::isfinite(a0)) ? 1.0 : a0;
        mB0 = b0 / safeA0;
        mB1 = b1 / safeA0;
        mB2 = b2 / safeA0;
        mA1 = -2.0 * cosw / safeA0;
        mA2 = (1.0 - alpha) / safeA0;
    }

    void reset() {
        mw1 = 0.0;
        mw2 = 0.0;
    }
    
    double process(double input) {
        const double output = mB0 * input + mw1;
        if (!std::isfinite(output)) {
            reset();
            return 0.0;
        }
        const double w1 = mB1 * input + mw2 - mA1 * output;
        const double w2 = mB2 * input - mA2 * output;
        mw1 = std::isfinite(w1) ? w1 : 0.0;
        mw2 = std::isfinite(w2) ? w2 : 0.0;
        return output;
    }
private:
    double mB0 = 0.0;
    double mB1 = 0.0;
    double mB2 = 0.0;
    double mA1 = 0.0;
    double mA2 = 0.0;
    double mw1 = 0.0;
    double mw2 = 0.0;
};
