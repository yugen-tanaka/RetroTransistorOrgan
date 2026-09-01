//
//  BlackKnobVerticalSlider.swift
//  RetroTransistorOrganExtension
//
//  Created by Yugen on 2026/08/18.
//

import SwiftUI

struct BlackKnobVerticalSlider: View {
    let title: String
    @Binding var value: Double
    var range: ClosedRange<Double> = -60.0...(-20.0)
    var unit: String = "dB"
    var formatString: String = "%.0f"
    var marks: [String]? = nil
    var showMarks: Bool = true
    
    private let trackHeight: CGFloat = 130
    private let trackWidth: CGFloat = 8
    private let knobWidth: CGFloat = 34
    private let knobHeight: CGFloat = 20
    
    @State private var dragStartValue: Double? = nil
    
    var body: some View {
        VStack(spacing: 8) {
            Text(title)
                .font(.system(size: 10, weight: .bold))
                .multilineTextAlignment(.center)
                .frame(maxWidth: 70)
            
            let normalizedValue = (value - range.lowerBound) / (range.upperBound - range.lowerBound)
            // Inverted for vertical slider: top is max (upperBound), bottom is min (lowerBound)
            let travelDistance = trackHeight - knobHeight
            let knobYOffset = (1.0 - CGFloat(normalizedValue)) * travelDistance
            
            HStack(spacing: 6) {
                // Scale marks on left
                if showMarks {
                    VStack(alignment: .trailing) {
                        if let customMarks = marks, customMarks.count >= 3 {
                            Text(customMarks[0])
                                .font(.system(size: 8, weight: .semibold, design: .monospaced))
                                .foregroundColor(.secondary)
                            Spacer()
                            Text(customMarks[1])
                                .font(.system(size: 8, weight: .semibold, design: .monospaced))
                                .foregroundColor(.secondary)
                            Spacer()
                            Text(customMarks[2])
                                .font(.system(size: 8, weight: .semibold, design: .monospaced))
                                .foregroundColor(.secondary)
                        } else {
                            Text(String(format: formatString, range.upperBound))
                                .font(.system(size: 8, weight: .semibold, design: .monospaced))
                                .foregroundColor(.secondary)
                            Spacer()
                            Text(String(format: formatString, (range.upperBound + range.lowerBound) / 2))
                                .font(.system(size: 8, weight: .semibold, design: .monospaced))
                                .foregroundColor(.secondary)
                            Spacer()
                            Text(String(format: formatString, range.lowerBound))
                                .font(.system(size: 8, weight: .semibold, design: .monospaced))
                                .foregroundColor(.secondary)
                        }
                    }
                    .frame(height: trackHeight)
                }
                
                // Track and Black Knob Thumb
                ZStack(alignment: .top) {
                    // Track slot
                    RoundedRectangle(cornerRadius: trackWidth / 2)
                        .fill(
                            LinearGradient(
                                colors: [Color.black.opacity(0.8), Color(white: 0.12)],
                                startPoint: .top,
                                endPoint: .bottom
                            )
                        )
                        .overlay(
                            RoundedRectangle(cornerRadius: trackWidth / 2)
                                .stroke(Color.black.opacity(0.4), lineWidth: 1)
                        )
                        .frame(width: trackWidth, height: trackHeight)
                    
                    // Black Knob Cap (Fader Thumb)
                    ZStack {
                        // Knob Body
                        RoundedRectangle(cornerRadius: 3)
                            .fill(
                                LinearGradient(
                                    colors: [Color(white: 0.28), Color(white: 0.12), Color(white: 0.08)],
                                    startPoint: .top,
                                    endPoint: .bottom
                                )
                            )
                            .overlay(
                                RoundedRectangle(cornerRadius: 3)
                                    .stroke(Color(white: 0.35), lineWidth: 0.5)
                            )
                            .shadow(color: .black.opacity(0.6), radius: 3, x: 0, y: 2)
                        
                        // Ribbed grip texture
                        HStack(spacing: 2) {
                            ForEach(0..<4) { _ in
                                Rectangle()
                                    .fill(Color(white: 0.18))
                                    .frame(width: 1, height: 10)
                            }
                        }
                        
                        // Center white indicator line
                        Rectangle()
                            .fill(Color.white.opacity(0.95))
                            .frame(width: knobWidth - 8, height: 2)
                            .shadow(color: .white.opacity(0.5), radius: 1, x: 0, y: 0)
                    }
                    .frame(width: knobWidth, height: knobHeight)
                    .offset(y: knobYOffset)
                }
                .frame(width: knobWidth, height: trackHeight)
                .contentShape(Rectangle())
                .gesture(
                    DragGesture(minimumDistance: 0)
                        .onChanged { gesture in
                            if dragStartValue == nil {
                                dragStartValue = value
                            }
                            let deltaY = -Double(gesture.translation.height)
                            let deltaRatio = deltaY / Double(travelDistance)
                            let newValue = dragStartValue! + deltaRatio * (range.upperBound - range.lowerBound)
                            value = max(range.lowerBound, min(range.upperBound, newValue))
                        }
                        .onEnded { _ in
                            dragStartValue = nil
                        }
                )
            }
            
            // Value display
            Text(String(format: formatString, value) + (unit.isEmpty ? "" : " \(unit)"))
                .font(.system(size: 10, weight: .bold, design: .monospaced))
                .foregroundColor(.primary)
                .padding(.horizontal, 6)
                .padding(.vertical, 2)
                .background(Color.black.opacity(0.1))
                .cornerRadius(4)
        }
    }
}
