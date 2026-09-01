//
//  RetroTransistorOrganExtensionMainView.swift
//  RetroTransistorOrganExtension
//
//  Created by Yugen on 2026/06/28.
//

import SwiftUI

struct RetroTransistorOrganExtensionMainView: View {
    var parameterTree: ObservableAUParameterGroup
    
    var body: some View {
            VStack(spacing: 20) {
                HStack(alignment: .top, spacing: 25) {
                    VStack {
                        Text("Effects Tablet").font(.headline)
                        HStack(spacing: 8) {
                            StopLeverParameterView(param: parameterTree.global.vibrato, tablet: Tablet(voiceName: "VIBRATO", footage: nil, theme: .green))
                            StopLeverParameterView(param: parameterTree.global.ensemble, tablet: Tablet(voiceName: "ENSEMBLE", footage: nil, theme: .blue))
                        }
                        .padding(18)
                        .background(Color.gray.opacity(0.1))
                        .cornerRadius(12)
                    }
                    VStack {
                        Text("Upper (Ch 1)").font(.headline)
                        HStack(spacing: 8) {
                            StopLeverParameterView(param: parameterTree.upper.upperTibia16, tablet: Tablet(voiceName: "TIBIA", footage: "16", theme: .white))
                            StopLeverParameterView(param: parameterTree.upper.upperTibia8, tablet: Tablet(voiceName: "TIBIA", footage: "8", theme: .white))
                            StopLeverParameterView(param: parameterTree.upper.upperTibia4, tablet: Tablet(voiceName: "TIBIA", footage: "4", theme: .white))
                            StopLeverParameterView(param: parameterTree.upper.upperTibia2_2_3, tablet: Tablet(voiceName: "TIBIA", footage: "2 2/3", theme: .white))
                            StopLeverParameterView(param: parameterTree.upper.upperString16, tablet: Tablet(voiceName: "STRING", footage: "16", theme: .yellow))
                            StopLeverParameterView(param: parameterTree.upper.upperDiapason8, tablet: Tablet(voiceName: "DIAPASON", footage: "8", theme: .white))
                            StopLeverParameterView(param: parameterTree.upper.upperString8, tablet: Tablet(voiceName: "STRING", footage: "8", theme: .yellow))
                            StopLeverParameterView(param: parameterTree.upper.upperClarinet, tablet: Tablet(voiceName: "CLARINET", footage: "8", theme: .red))
                            StopLeverParameterView(param: parameterTree.upper.upperOboe, tablet: Tablet(voiceName: "OBOE", footage: "8", theme: .red))
                            StopLeverParameterView(param: parameterTree.upper.upperString4, tablet: Tablet(voiceName: "STRING", footage: "4", theme: .yellow))
                        }
                        .padding(18)
                        .background(Color.gray.opacity(0.1))
                        .cornerRadius(12)
                    }
                }
                
                HStack(alignment: .top, spacing: 25) {
                    VStack {
                        Text("Lower (Ch 4)").font(.headline)
                        HStack(spacing: 8) {
                            StopLeverParameterView(param: parameterTree.lower.lowerTibia8, tablet: Tablet(voiceName: "TIBIA", footage: "8", theme: .white))
                            StopLeverParameterView(param: parameterTree.lower.lowerTibia4, tablet: Tablet(voiceName: "TIBIA", footage: "4", theme: .white))
                            StopLeverParameterView(param: parameterTree.lower.lowerDiapason8, tablet: Tablet(voiceName: "DIAPASON", footage: "8", theme: .white))
                            StopLeverParameterView(param: parameterTree.lower.lowerString8, tablet: Tablet(voiceName: "STRING", footage: "8", theme: .yellow))
                            StopLeverParameterView(param: parameterTree.lower.lowerHorn, tablet: Tablet(voiceName: "HORN", footage: "8", theme: .red))
                            StopLeverParameterView(param: parameterTree.lower.lowerString4, tablet: Tablet(voiceName: "STRING", footage: "4", theme: .yellow))
                            Spacer().frame(width: 24)
                            BlackKnobVerticalSliderParameterView(param: parameterTree.lower.lowerVolume, title: "VOLUME", unit: "", formatString: "%.1f", showMarks: false)
                                .frame(height: 130)
                        }
                        .padding(18)
                        .background(Color.gray.opacity(0.1))
                        .cornerRadius(12)
                    }
                    
                    VStack {
                        Text("Pedal (Ch 5)").font(.headline)
                        HStack(spacing: 8) {
                            StopLeverParameterView(param: parameterTree.pedal.pedalBourdon16, tablet: Tablet(voiceName: "BOURDON", footage: "16", theme: .white))
                            StopLeverParameterView(param: parameterTree.pedal.pedalMajorFlute8, tablet: Tablet(voiceName: "MAJOR FLUTE", footage: "8", theme: .white))
                            StopLeverParameterView(param: parameterTree.pedal.pedalSustain, tablet: Tablet(voiceName: "SUSTAIN", footage: nil, theme: .black))
                            Spacer().frame(width: 24)
                            BlackKnobVerticalSliderParameterView(param: parameterTree.pedal.pedalSustainLength, title: "SUSTAIN", unit: "s", formatString: "%.1f", showMarks: false)
                                .frame(height: 130)
                            BlackKnobVerticalSliderParameterView(param: parameterTree.pedal.pedalVolume, title: "VOLUME", unit: "", formatString: "%.1f", showMarks: false)
                                .frame(height: 130)
                        }
                        .padding(18)
                        .background(Color.gray.opacity(0.1))
                        .cornerRadius(12)
                    }
                    VStack {
                        Text("Master").font(.headline)
                        HStack(spacing: 16) {
                            ParameterSlider(param: parameterTree.global.gain)
                                .frame(width: 200, height: 44)
                                .fixedSize(horizontal: true, vertical: true)
                                .rotationEffect(.degrees(-90.0), anchor: .center)
                                .frame(width: 44, height: 200)
                            
                            BlackKnobVerticalSliderParameterView(param: parameterTree.global.expressionMin, title: "EXPR MIN")
                                .frame(height: 200)
                        }
                        .padding(18)
                        .background(Color.gray.opacity(0.1))
                        .cornerRadius(12)
                    }
                }
                
            }
            .padding(30)
            
            #if os(macOS)
            .background(Color(NSColor.windowBackgroundColor))
            #endif
        
    }
}
