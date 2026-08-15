import SwiftUI

enum TabletTheme: CaseIterable {
    case white, black, yellow, red, blue, green, purple, whiteBlue
    var color: Color {
        switch self {
        case .white, .whiteBlue:
            return Color(red: 0.95, green: 0.93, blue: 0.88)
        case .black:
            return Color(red: 0.08, green: 0.08, blue: 0.08)
        case .yellow:
            return Color(red: 1.0, green: 0.8, blue: 0.0)
        case .red:
            return Color(red: 0.85, green: 0.05, blue: 0.1)
        case .blue:
            return Color(red: 0.15, green: 0.05, blue: 0.95)
        case .green:
            return Color(red: 0.05, green: 0.65, blue: 0.4)
        case .purple:
            return Color(red: 0.35, green: 0.05, blue: 0.75)
        }
    }
    var textColor: Color {
        switch self {
        case .white, .yellow:
            return .black
        case .black, .red, .blue, .green, .purple:
            return .white
        case .whiteBlue:
            return Color(red: 0.15, green: 0.05, blue: 0.95)
        }
    }
}
