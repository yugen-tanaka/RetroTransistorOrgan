import SwiftUI

struct TabletButton: View {
    let tablet: Tablet
    
    @Binding var isOn: Bool
    let action: () -> Void
    
    private let width: CGFloat = 56
    private let height: CGFloat = 150
    private let cornerRadius: CGFloat = 6
    
    var body: some View {
        ZStack {
            RoundedRectangle(cornerRadius: cornerRadius)
                .fill(
                    LinearGradient(
                        gradient: Gradient(colors: [
                            isOn ? tablet.theme.color.opacity(0.98) : tablet.theme.color,
                            isOn ? tablet.theme.color.opacity(0.82) : tablet.theme.color,
                            isOn ? tablet.theme.color.opacity(0.6) : tablet.theme.color.opacity(1.1)
                        ]),
                        startPoint: .top,
                        endPoint: .bottom
                    )
                )
                .overlay(
                    RoundedRectangle(cornerRadius: cornerRadius)
                        .strokeBorder(Color.white.opacity(0.25), lineWidth: 1)
                )
                .shadow(
                    color: Color.black.opacity(0.5),
                    radius: isOn ? 2 : 6,
                    x: 0,
                    y: isOn ? 2 : 10
                )
           
            VStack(spacing: 4) {
                Spacer()
                Text(tablet.voiceName)
                    .multilineTextAlignment(.center)
                    .kerning(-0.8)
                    .font(.system(size: 10, weight: .bold, design: .default))
                    .foregroundColor(tablet.theme.textColor)
                    .padding(.bottom, 20)
                Spacer()
            }
            if let ft = tablet.footage {
                VStack {
                    Spacer()
                    Text(ft)
                        .font(.system(size: ft == "FAST" ? 10 : 20, weight: .regular, design: .default))
                        .foregroundColor(tablet.theme.textColor)
                        .padding(.bottom, 22)
                }
            }
        }
        .frame(width: width, height: height)
        .rotation3DEffect(
            .degrees(isOn ? -12 : 0),
            axis: (x: 1.0, y: 0.0, z: 0.0),
            anchor: UnitPoint(x: 0.5, y: 0.25),
            perspective: 0.6
        )
        .animation(.spring(response: 0.3, dampingFraction: 0.55), value: isOn)
        .onTapGesture {
            action()
        }
    }
}
