#pragma once
#include <cmath>

class GlobalPhaseTracker {
public:
    GlobalPhaseTracker(double sampleRate = 44100.0) {
        setSampleRate(sampleRate);
    }

    void setSampleRate(double sampleRate) {
        mSampleRate = sampleRate;
        mVibratoPhaseInc = 6.0 / mSampleRate; // 6 Hz vibrato default
    }
    
    void setVibrato(bool enabled, double depth = 0.015) {
        mVibratoEnabled = enabled;
        mVibratoDepth = depth;
    }

    // Call this once per sample
    void process() {
        if (mVibratoEnabled) {
            double lfo = std::sin(mVibratoPhase * 2.0 * M_PI);
            mVibratoPhase += mVibratoPhaseInc;
            if (mVibratoPhase >= 1.0) mVibratoPhase -= 1.0;
            
            // Advance master time with LFO modulation
            mMasterTime += (1.0 + lfo * mVibratoDepth) / mSampleRate;
        } else {
            mMasterTime += 1.0 / mSampleRate;
        }
    }

    // Get the phase [0, 1) for a specific frequency
    double getPhase(double frequency) const {
        double phase = std::fmod(mMasterTime * frequency, 1.0);
        if (phase < 0) phase += 1.0;
        return phase;
    }

private:
    double mSampleRate = 44100.0;
    double mMasterTime = 0.0;
    
    bool mVibratoEnabled = false;
    double mVibratoDepth = 0.015;
    double mVibratoPhase = 0.0;
    double mVibratoPhaseInc = 0.0;
};
