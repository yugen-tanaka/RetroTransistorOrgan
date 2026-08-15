import SwiftUI

struct RotaryKnobView: View {
    let title: String
    @Binding var value: Double
    var range: ClosedRange<Double>
    
    private let minAngle = -150.0
    private let maxAngle = 150.0
    
    @State private var dragStartValue: Double? = nil
    
    var body: some View {
        VStack(spacing: 8) {
            Text(title)
                .font(.system(size: 10, weight: .bold))
                .multilineTextAlignment(.center)
                .frame(maxWidth: 60)
            
            let normalizedValue = (value - range.lowerBound) / (range.upperBound - range.lowerBound)
            let currentAngle = minAngle + normalizedValue * (maxAngle - minAngle)
            
            ZStack {
                Circle()
                    .fill(Color(white: 0.15))
                    .shadow(color: .black.opacity(0.4), radius: 3, x: 0, y: 2)
                
                Capsule()
                    .fill(Color.white)
                    .frame(width: 4, height: 16)
                    .offset(y: -10)
                    .rotationEffect(.degrees(currentAngle))
            }
            .frame(width: 44, height: 44)
            .gesture(
                DragGesture(minimumDistance: 0)
                    .onChanged { gesture in
                        if dragStartValue == nil {
                            dragStartValue = value
                        }
                        let sensitivity: Double = 0.005
                        let delta = -Double(gesture.translation.height) * sensitivity
                        let newValue = dragStartValue! + delta * (range.upperBound - range.lowerBound)
                        value = max(range.lowerBound, min(range.upperBound, newValue))
                    }
                    .onEnded { _ in
                        dragStartValue = nil
                    }
            )
        }
    }
}
