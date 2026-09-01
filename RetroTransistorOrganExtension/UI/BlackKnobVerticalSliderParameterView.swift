//
//  BlackKnobVerticalSliderParameterView.swift
//  RetroTransistorOrganExtension
//
//  Created by Yugen on 2026/08/18.
//

import SwiftUI

struct BlackKnobVerticalSliderParameterView: View {
    @State var param: ObservableAUParameter
    let title: String
    var unit: String = "dB"
    var formatString: String = "%.0f"
    var marks: [String]? = nil
    var showMarks: Bool = true
    
    var body: some View {
        let binding = Binding<Double>(
            get: { Double(self.param.value) },
            set: { newValue in
                self.param.value = Float(newValue)
                self.param.onEditingChanged(true)
            }
        )
        
        BlackKnobVerticalSlider(
            title: title,
            value: binding,
            range: Double(param.min)...Double(param.max),
            unit: unit,
            formatString: formatString,
            marks: marks,
            showMarks: showMarks
        )
    }
}
