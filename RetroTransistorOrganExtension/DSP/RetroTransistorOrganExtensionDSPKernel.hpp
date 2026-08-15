//
//  RetroTransistorOrganExtensionDSPKernel.hpp
//  RetroTransistorOrganExtension
//
//  Created by Yugen on 2026/06/28.
//

#pragma once

#import <AudioToolbox/AudioToolbox.h>
#import <CoreMIDI/CoreMIDI.h>
#import <algorithm>
#import <vector>
#import <span>
#import <array>

#import "RetroTransistorOrganExtensionParameterAddresses.h"
#import "GlobalPhaseTracker.hpp"
#import "StaircaseOscillator.hpp"
#import "SquareOscillator.hpp"
#import "Voice.hpp"
#import "Filter.hpp"

class RetroTransistorOrganExtensionDSPKernel {
public:
    void initialize(int channelCount, double inSampleRate) {
        mSampleRate = inSampleRate;
        mPhaseTracker.setSampleRate(inSampleRate);
        // 単一のTIBIAフィルタを初期化（カットオフ: 500Hz）
        mTibiaFilter.setCutoff(517.0, 0.6, inSampleRate);
        // DIAPASONフィルタを初期化（カットオフ: 1000Hz）
        mDiapasonFilter.setCutoff(1000.0, inSampleRate);
        // STRING音色のエイリアシングを和らげるアナログ風LPF（6000Hz）
        mStringFilter.setCutoff(8000.0, inSampleRate);
        // CLARINETの12dB/octローパスフィルタ（2300Hz, Q=1.40）
        mClarinetFilter.setCutoff(2300.0, 1.40, inSampleRate);
        mClarinetFilter.reset();
        // OBOEの2次バンドパスフィルタ（2000Hz, Q=3.3）
        mOboeFilter.setCutoff(2000.0, 3.3, inSampleRate);
        mOboeFilter.reset();
        mHornFilter.setCutoff(2700.0, 1.8, inSampleRate);
        mHornFilter.reset();
        
        // ペダル用フィルタ「MAJOR FLUTE」の初期化（LPF, カットオフ: 158Hz, Q: 0.1）
        mPedalFilter.setCutoff(158.0, 0.1, inSampleRate);
        mPedalFilter.reset();
        
        // ペダル用ボイスおよび状態の初期化
        mPedalVoice.initialize(0, 4, inSampleRate);
        mPedalVoice.terminate();
        mHeldPedalNotes.fill(false);
        mActivePedalNote = -1;
    }
    
    void deInitialize() {
    }
    
    bool isBypassed() { return mBypassed; }
    void setBypass(bool shouldBypass) { mBypassed = shouldBypass; }
    
    void setParameter(AUParameterAddress address, AUValue value) {
        bool isOn = value > 0.5f;
        switch (address) {
            case gain: mGain = value; break;
            
            case upperTibia16: mUpperTibia16 = isOn; break;
            case upperTibia8:  mUpperTibia8  = isOn; break;
            case upperTibia4:  mUpperTibia4  = isOn; break;
            case upperTibia2_2_3: mUpperTibia2_2_3 = isOn; break;
            case upperDiapason8:  mUpperDiapason8 = isOn; break;
            case upperString16:mUpperString16= isOn; break;
            case upperString8: mUpperString8 = isOn; break;
            case upperClarinet:
                mUpperClarinet = isOn;
                mClarinetFilter.reset();
                break;
            case upperOboe:
                mUpperOboe = isOn;
                mOboeFilter.reset();
                break;
            case upperString4: mUpperString4 = isOn; break;
                
            case lowerTibia8:  mLowerTibia8  = isOn; break;
            case lowerTibia4:  mLowerTibia4  = isOn; break;
            case lowerDiapason8: mLowerDiapason8 = isOn; break;
            case lowerString8: mLowerString8 = isOn; break;
            case lowerHorn:
                mLowerHorn = isOn;
                mHornFilter.reset();
                break;
            case lowerString4: mLowerString4 = isOn; break;
            case lowerVolume:  mLowerVolume = value; break;
                
            case pedalBourdon16: mPedalBourdon16 = isOn; break;
            case pedalMajorFlute8: mPedalMajorFlute8 = isOn; break;
            case pedalVolume:  mPedalVolume = value; break;
            case pedalSustain: mPedalSustain = isOn; break;
            case pedalSustainLength: mPedalSustainLength = value; break;
                
            case vibrato:
                mVibrato = isOn;
                mPhaseTracker.setVibrato(mVibrato);
                break;
            case ensemble: mEnsemble = isOn; break;
        }
    }
    
    AUValue getParameter(AUParameterAddress address) {
        switch (address) {
            case gain: return mGain;
            case upperTibia16: return mUpperTibia16 ? 1.0f : 0.0f;
            case upperTibia8:  return mUpperTibia8 ? 1.0f : 0.0f;
            case upperTibia4:  return mUpperTibia4 ? 1.0f : 0.0f;
            case upperTibia2_2_3: return mUpperTibia2_2_3 ? 1.0f : 0.0f;
            case upperDiapason8:  return mUpperDiapason8 ? 1.0f : 0.0f;
            case upperString16:return mUpperString16 ? 1.0f : 0.0f;
            case upperString8: return mUpperString8 ? 1.0f : 0.0f;
            case upperClarinet: return mUpperClarinet ? 1.0f : 0.0f;
            case upperString4: return mUpperString4 ? 1.0f : 0.0f;
            case lowerTibia8:  return mLowerTibia8 ? 1.0f : 0.0f;
            case lowerTibia4:  return mLowerTibia4 ? 1.0f : 0.0f;
            case lowerDiapason8: return mLowerDiapason8 ? 1.0f : 0.0f;
            case lowerString8: return mLowerString8 ? 1.0f : 0.0f;
            case lowerHorn: return mLowerHorn ? 1.0f : 0.0f;
            case lowerString4: return mLowerString4 ? 1.0f : 0.0f;
            case lowerVolume:  return mLowerVolume;
            case pedalBourdon16: return mPedalBourdon16 ? 1.0f : 0.0f;
            case pedalMajorFlute8: return mPedalMajorFlute8 ? 1.0f : 0.0f;
            case pedalVolume:  return mPedalVolume;
            case pedalSustain: return mPedalSustain ? 1.0f : 0.0f;
            case pedalSustainLength: return mPedalSustainLength;
            case vibrato:      return mVibrato ? 1.0f : 0.0f;
            case ensemble:     return mEnsemble ? 1.0f : 0.0f;
            default: return 0.f;
        }
    }
    
    AUAudioFrameCount maximumFramesToRender() const { return mMaxFramesToRender; }
    void setMaximumFramesToRender(const AUAudioFrameCount &maxFrames) { mMaxFramesToRender = maxFrames; }
    void setMusicalContextBlock(AUHostMusicalContextBlock contextBlock) { mMusicalContextBlock = contextBlock; }
    MIDIProtocolID AudioUnitMIDIProtocol() const { return kMIDIProtocol_2_0; }
    
    void process(std::span<float *> outputBuffers, AUEventSampleTime bufferStartTime, AUAudioFrameCount frameCount) {
        if (mBypassed) {
            for (UInt32 channel = 0; channel < outputBuffers.size(); ++channel) {
                std::fill_n(outputBuffers[channel], frameCount, 0.f);
            }
            return;
        }
        
        for (UInt32 frameIndex = 0; frameIndex < frameCount; ++frameIndex) {
            mPhaseTracker.process();
            
            double tibiaSum = 0.0;
            double diapasonSum = 0.0;
            double stringSum = 0.0;
            double clarinetSum = 0.0;
            double oboeSum = 0.0;
            double hornSum = 0.0;
            
            for (int i = 0; i < kMaxPolyphony; ++i) {
                if (mVoices[i].isActive() || mVoices[i].getEnvelope() > 0.0) {
                    double env = mVoices[i].getEnvelope();
                    if (env == 0.0) continue;
                    
                    int ch = mVoices[i].getChannel();
                    double freq = mVoices[i].getFrequency();
                    
                    double voiceString = 0.0;
                    double voiceClarinet = 0.0;
                    double voiceOboe = 0.0;
                    double voiceHorn = 0.0;
                    
                    // フォールドバック（高音域制限）：6300Hzを超える場合はオクターブを下げる
                    auto foldback = [](double f) {
                        while (f > 6300.0) f *= 0.5;
                        return f;
                    };
                    
                    auto addTibia = [&](double f, double amp = 1.0) {
                        f = foldback(f);
                        const double relativeBoostDB = 4.821636 * std::log2(f / 130.81);
                        double comp = std::pow(10.0, relativeBoostDB / 20.0);
                        tibiaSum += StaircaseOscillator::process(mPhaseTracker.getPhase(f), f / mSampleRate) * env * comp * amp;
                    };
                    
                    auto addDiapason = [&](double f, double amp = 1.0) {
                        f = foldback(f);
                        // カットオフ1000Hzによる高音減衰を補正するプレゲイン（1.0 + (f / 1000)^2）
                        double comp = 1.0 + (f / 1000.0) * (f / 1000.0);
                        diapasonSum += StaircaseOscillator::process(mPhaseTracker.getPhase(f), f / mSampleRate) * env * comp * amp;
                    };
                    
                    auto addString = [&](double f, double amp = 1.0) {
                        f = foldback(f);
                        voiceString += StaircaseOscillator::process(mPhaseTracker.getPhase(f), f / mSampleRate) * amp;
                    };
                    auto addClarinet = [&](double f, double amp = 1.0) {
                        f = foldback(f);
                        voiceClarinet += SquareOscillator::process(mPhaseTracker.getPhase(f), f / mSampleRate) * amp;
                    };
                    auto addOboe = [&](double f, double amp = 1.0) {
                        f = foldback(f);
                        voiceOboe += StaircaseOscillator::process(mPhaseTracker.getPhase(f), f / mSampleRate) * amp;
                    };
                    
                    auto addHorn = [&](double f, double amp = 1.0) {
                        f = foldback(f);
                        voiceHorn += StaircaseOscillator::process(mPhaseTracker.getPhase(f), f / mSampleRate) * amp;
                    };
                    
                    if (ch == 0) { // Upper
                        if (mUpperTibia16)  addTibia(freq * 0.5);
                        if (mUpperTibia8)   addTibia(freq);
                        if (mUpperTibia4)   addTibia(freq * 2.0);
                        if (mUpperTibia2_2_3) addTibia(freq * std::pow(2.0, 19.0 / 12.0)); // 1オクターブ＋完全5度上 (平均律)
                        
                        if (mUpperDiapason8) addDiapason(freq);
                        if (mUpperString16) addString(freq * 0.5);
                        if (mUpperString8)  addString(freq);
                        if (mUpperClarinet) addClarinet(freq);
                        if (mUpperOboe)     addOboe(freq);
                        if (mUpperString4)  addString(freq * 2.0);
                        clarinetSum += voiceClarinet * env;
                        oboeSum += voiceOboe * env;
                    }
                    else if (ch == 3) { // Lower
                        if (mLowerTibia8)   addTibia(freq, mLowerVolume);
                        if (mLowerTibia4)   addTibia(freq * 2.0, mLowerVolume);
                        
                        if (mLowerDiapason8) addDiapason(freq, mLowerVolume);
                        if (mLowerString8)  addString(freq, mLowerVolume);
                        if (mLowerHorn) addHorn(freq, mLowerVolume);
                        if (mLowerString4)  addString(freq * 2.0, mLowerVolume);
                        hornSum += voiceHorn * env;
                    }
                    stringSum += voiceString * env;
                }
            }
            
            // Pedal音源の合成（モノフォニック・独立処理）
            double pedalSum = 0.0;
            if (mPedalVoice.isActive() || mPedalVoice.getEnvelope() > 0.0) {
                double env = mPedalVoice.getEnvelope();
                if (env > 0.0) {
                    double freq = mPedalVoice.getFrequency();
                    
                    auto foldback = [](double f) {
                        while (f > 6300.0) f *= 0.5;
                        return f;
                    };
                    
                    auto addPedalTone = [&](double f, double amp = 1.0) {
                        f = foldback(f);
                        const double relativeBoostDB = 4.821636 * std::log2(f / 130.81);
                        double comp = std::pow(10.0, relativeBoostDB / 20.0);
                        pedalSum += StaircaseOscillator::process(mPhaseTracker.getPhase(f), f / mSampleRate) * env * comp * amp;
                    };
                    
                    if (mPedalBourdon16) {
                        addPedalTone(freq * 0.5, mPedalVolume);
                    }
                    if (mPedalMajorFlute8) {
                        addPedalTone(freq, mPedalVolume);
                    }
                }
            }
            
            // TIBIAの単一グローバルLPF
            tibiaSum = mTibiaFilter.process(tibiaSum);
            
            // Pedalの専用グローバルLPF（MAJOR FLUTE / BOURDON共用: 158Hz, Q=0.1）
            pedalSum = mPedalFilter.process(pedalSum);
            
            // DIAPASONの単一グローバルLPF
            diapasonSum = mDiapasonFilter.process(diapasonSum);
            
            // アナログ回路を模したSTRINGのグローバルLPF
            stringSum = mStringFilter.process(stringSum);
            clarinetSum = mClarinetFilter.process(clarinetSum);
            oboeSum = mOboeFilter.process(oboeSum);
            hornSum = mHornFilter.process(hornSum);
            
            // Adjust gain, divided to prevent clipping with many notes
            // フィルタ減衰を考慮し、TIBIAは0.15、PEDALは大きめの0.30に設定
            tibiaSum *= 0.15 * mGain;
            pedalSum *= 0.90 * mGain;
            diapasonSum *= 0.10 * mGain;
            stringSum *= 0.07 * mGain;
            clarinetSum *= 0.07 * mGain;
            oboeSum *= 0.15 * mGain;
            hornSum *= 0.05 * mGain;
            
            double outL = tibiaSum + pedalSum;
            double outR = stringSum + diapasonSum + clarinetSum + oboeSum + hornSum;
            
            if (mEnsemble) {
                outL += stringSum + diapasonSum + clarinetSum + oboeSum + hornSum;
                outR = 0.0; // Stationary（R）からの出力をミュート
            }
            
            if (outputBuffers.size() > 0) outputBuffers[0][frameIndex] = outL;
            if (outputBuffers.size() > 1) outputBuffers[1][frameIndex] = outR;
        }
    }
    
    void handleOneEvent(AUEventSampleTime now, AURenderEvent const *event) {
        switch (event->head.eventType) {
            case AURenderEventParameter:
                handleParameterEvent(now, event->parameter);
                break;
            case AURenderEventMIDIEventList:
                handleMIDIEventList(now, &event->MIDIEventsList);
                break;
            default:
                break;
        }
    }
    
    void handleParameterEvent(AUEventSampleTime now, AUParameterEvent const& parameterEvent) {
        setParameter(parameterEvent.parameterAddress, parameterEvent.value);
    }
    
    void handleMIDIEventList(AUEventSampleTime now, AUMIDIEventList const* midiEvent) {
        auto visitor = [] (void* context, MIDITimeStamp timeStamp, MIDIUniversalMessage message) {
            auto thisObject = static_cast<RetroTransistorOrganExtensionDSPKernel *>(context);
            if (message.type == kMIDIMessageTypeChannelVoice2) {
                thisObject->handleMIDI2VoiceMessage(message);
            }
        };
        MIDIEventListForEachEvent(&midiEvent->eventList, visitor, this);
    }
    
    void handlePedalMIDI(const struct MIDIUniversalMessage& message) {
        const auto& note = message.channelVoice2.note;
        switch (message.channelVoice2.status) {
            case kMIDICVStatusNoteOff: {
                if (note.number >= 0 && note.number < 128) {
                    mHeldPedalNotes[note.number] = false;
                }
                
                if (mActivePedalNote == note.number) {
                    int lowestNote = -1;
                    for (int i = 0; i < 128; ++i) {
                        if (mHeldPedalNotes[i]) {
                            lowestNote = i;
                            break;
                        }
                    }
                    if (lowestNote != -1) {
                        handlePedalNoteOn(lowestNote);
                    } else {
                        handlePedalNoteOff(note.number);
                        mActivePedalNote = -1;
                    }
                }
                break;
            }
            case kMIDICVStatusNoteOn: {
                if (message.channelVoice2.note.velocity == 0) {
                    if (note.number >= 0 && note.number < 128) {
                        mHeldPedalNotes[note.number] = false;
                    }
                    if (mActivePedalNote == note.number) {
                        int lowestNote = -1;
                        for (int i = 0; i < 128; ++i) {
                            if (mHeldPedalNotes[i]) {
                                lowestNote = i;
                                break;
                            }
                        }
                        if (lowestNote != -1) {
                            handlePedalNoteOn(lowestNote);
                        } else {
                            handlePedalNoteOff(note.number);
                            mActivePedalNote = -1;
                        }
                    }
                    break;
                }
                
                if (note.number >= 0 && note.number < 128) {
                    mHeldPedalNotes[note.number] = true;
                }
                
                handlePedalNoteOn(note.number);
                break;
            }
            default:
                break;
        }
    }

    void handlePedalNoteOn(int noteNumber) {
        mPedalVoice.terminate();
        mPedalVoice.initialize(noteNumber, 4, mSampleRate);
        mPedalVoice.noteOn();
        mActivePedalNote = noteNumber;
    }

    void handlePedalNoteOff(int noteNumber) {
        mPedalVoice.noteOff(mPedalSustain, mPedalSustainLength, mSampleRate);
    }

    void handleMIDI2VoiceMessage(const struct MIDIUniversalMessage& message) {
        const auto& note = message.channelVoice2.note;
        int ch = message.channelVoice2.channel;
        
        if (ch == 4) { // Pedal
            handlePedalMIDI(message);
            return;
        }
        
        if (ch != 0 && ch != 3) {
            return;
        }
        
        switch (message.channelVoice2.status) {
            case kMIDICVStatusNoteOff: {
                for (int i = 0; i < kMaxPolyphony; ++i) {
                    if (mVoices[i].isActive() && mVoices[i].getNote() == note.number && mVoices[i].getChannel() == ch) {
                        mVoices[i].noteOff();
                    }
                }
                break;
            }
            case kMIDICVStatusNoteOn: {
                if (message.channelVoice2.note.velocity == 0) {
                    for (int i = 0; i < kMaxPolyphony; ++i) {
                        if (mVoices[i].isActive() && mVoices[i].getNote() == note.number && mVoices[i].getChannel() == ch) {
                            mVoices[i].noteOff();
                        }
                    }
                    break;
                }
                
                for (int i = 0; i < kMaxPolyphony; ++i) {
                    if (!mVoices[i].isActive()) {
                        mVoices[i].initialize(note.number, ch, mSampleRate);
                        mVoices[i].noteOn();
                        break;
                    }
                }
                break;
            }
            default:
                break;
        }
    }
    
private:
    AUHostMusicalContextBlock mMusicalContextBlock;
    
    double mSampleRate = 44100.0;
    double mGain = 0.25;
    double mLowerVolume = 1.0;
    double mPedalVolume = 1.0;
    bool mBypassed = false;
    AUAudioFrameCount mMaxFramesToRender = 1024;
    
    static constexpr int kMaxPolyphony = 64;
    Voice mVoices[kMaxPolyphony];
    
    GlobalPhaseTracker mPhaseTracker;
    BiquadLowPass mTibiaFilter;
    OnePoleLPF mDiapasonFilter;
    OnePoleLPF mStringFilter;
    BiquadLowPass mClarinetFilter;
    BiquadBandPass mOboeFilter;
    BiquadLowPass mHornFilter;
    BiquadLowPass mPedalFilter;
    
    Voice mPedalVoice;
    std::array<bool, 128> mHeldPedalNotes;
    int mActivePedalNote = -1;
    
    bool mUpperTibia16 = false, mUpperTibia8 = false, mUpperTibia4 = false, mUpperTibia2_2_3 = false;
    bool mUpperDiapason8 = false;
    bool mUpperString16 = false, mUpperString8 = false, mUpperClarinet = false, mUpperOboe = false, mUpperString4 = false;
    bool mLowerTibia8 = false, mLowerTibia4 = false;
    bool mLowerDiapason8 = false;
    bool mLowerHorn = false;
    bool mLowerString8 = false, mLowerString4 = false;
    bool mPedalBourdon16 = false, mPedalMajorFlute8 = false;
    bool mPedalSustain = false;
    double mPedalSustainLength = 1.0;
    bool mVibrato = false, mEnsemble = false;
};
