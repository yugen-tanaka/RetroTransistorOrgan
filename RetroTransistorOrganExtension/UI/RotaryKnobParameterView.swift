import SwiftUI

struct RotaryKnobParameterView: View {
    @State var param: ObservableAUParameter
    let title: String
    
    var body: some View {
        let binding = Binding<Double>(
            get: { Double(self.param.value) },
            set: { newValue in
                self.param.value = Float(newValue)
                self.param.onEditingChanged(true)
            }
        )
        
        RotaryKnobView(
            title: title,
            value: binding,
            range: Double(param.min)...Double(param.max)
        )
    }
}
