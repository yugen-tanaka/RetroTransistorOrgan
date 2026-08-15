struct Tablet: Identifiable {
    let id = UUID()
    let voiceName: String
    let footage: String?
    let theme: TabletTheme
    var isOn = false
}
