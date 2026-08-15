import SwiftUI

struct StopLeverParameterView: View {
    @State var param: ObservableAUParameter
    let tablet: Tablet
    
    init(param: ObservableAUParameter, tablet: Tablet) {
        self._param = State(initialValue: param)
        self.tablet = tablet
    }
    
    var body: some View {
        let binding = Binding<Bool>(
            get: { self.param.value > 0.5 },
            set: { newValue in
                self.param.value = newValue ? 1.0 : 0.0
                self.param.onEditingChanged(true)
            }
        )
        
        TabletButton(tablet: tablet, isOn: binding) {
            binding.wrappedValue.toggle()
        }
    }
}
