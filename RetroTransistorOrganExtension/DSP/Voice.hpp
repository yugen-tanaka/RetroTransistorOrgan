#pragma once
#include <cmath>
#include <algorithm>

class Voice {
public:
    Voice() = default;

    void initialize(int noteNumber, int channel, double sampleRate) {
        mNoteNumber = noteNumber;
        mChannel = channel;
        mFrequency = MIDINoteToFrequency(noteNumber);
        
        // Envelope: 5ms fade
        mFadeInc = 1.0 / (0.005 * sampleRate);
    }
    
    void noteOn() {
        mTargetEnv = 1.0;
        mState = State::Attack;
        mIsActive = true;
    }
    
    void noteOff(bool useSustain = false, double sustainTime = 0.005, double sampleRate = 44100.0) {
        mTargetEnv = 0.0;
        mState = State::Release;
        double releaseTime = 0.005;
        if (useSustain) {
            releaseTime = std::max(0.005, sustainTime);
        }
        mFadeInc = 1.0 / (releaseTime * sampleRate);
    }

    void terminate() {
        mCurrentEnv = 0.0;
        mTargetEnv = 0.0;
        mState = State::Idle;
        mIsActive = false;
    }
    
    bool isActive() const { return mIsActive; }
    int getNote() const { return mNoteNumber; }
    int getChannel() const { return mChannel; }
    double getFrequency() const { return mFrequency; }
    
    double getEnvelope() {
        if (mState == State::Attack) {
            mCurrentEnv += mFadeInc;
            if (mCurrentEnv >= mTargetEnv) {
                mCurrentEnv = mTargetEnv;
                mState = State::Sustain;
            }
        } else if (mState == State::Release) {
            mCurrentEnv -= mFadeInc;
            if (mCurrentEnv <= 0.0) {
                mCurrentEnv = 0.0;
                mState = State::Idle;
                mIsActive = false;
            }
        }
        return mCurrentEnv;
    }

private:
    inline double MIDINoteToFrequency(int note) {
        constexpr auto kMiddleA = 440.0;
        return (kMiddleA / 32.0) * std::pow(2.0, ((note - 9) / 12.0));
    }

    enum class State { Idle, Attack, Sustain, Release };
    State mState = State::Idle;

    int mNoteNumber = 0;
    int mChannel = 0;
    double mFrequency = 0.0;
    
    double mCurrentEnv = 0.0;
    double mTargetEnv = 0.0;
    double mFadeInc = 0.0;
    bool mIsActive = false;
};
