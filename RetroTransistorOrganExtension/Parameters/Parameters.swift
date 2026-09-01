//
//  Parameters.swift
//  RetroTransistorOrganExtension
//
//  Created by Yugen on 2026/06/28.
//

import Foundation
import AudioToolbox

let RetroTransistorOrganExtensionParameterSpecs = ParameterTreeSpec {
    ParameterGroupSpec(identifier: "global", name: "Global") {
        ParameterSpec(address: .gain, identifier: "gain", name: "Output Gain", units: .linearGain, valueRange: 0.0...1.0, defaultValue: 0.25)
        ParameterSpec(address: .vibrato, identifier: "vibrato", name: "Vibrato", units: .boolean, valueRange: 0.0...1.0, defaultValue: 0.0)
        ParameterSpec(address: .ensemble, identifier: "ensemble", name: "Ensemble", units: .boolean, valueRange: 0.0...1.0, defaultValue: 0.0)
        ParameterSpec(address: .expressionMin, identifier: "expressionMin", name: "Expression Min", units: .decibels, valueRange: -60.0...(-20.0), defaultValue: -40.0)
    }
    ParameterGroupSpec(identifier: "upper", name: "Upper") {
        ParameterSpec(address: .upperTibia16, identifier: "upperTibia16", name: "Tibia 16'", units: .boolean, valueRange: 0.0...1.0, defaultValue: 0.0)
        ParameterSpec(address: .upperTibia8, identifier: "upperTibia8", name: "Tibia 8'", units: .boolean, valueRange: 0.0...1.0, defaultValue: 0.0)
        ParameterSpec(address: .upperTibia4, identifier: "upperTibia4", name: "Tibia 4'", units: .boolean, valueRange: 0.0...1.0, defaultValue: 0.0)
        ParameterSpec(address: .upperTibia2_2_3, identifier: "upperTibia2_2_3", name: "Tibia 2 2/3'", units: .boolean, valueRange: 0.0...1.0, defaultValue: 0.0)
        ParameterSpec(address: .upperString16, identifier: "upperString16", name: "String 16'", units: .boolean, valueRange: 0.0...1.0, defaultValue: 0.0)
        ParameterSpec(address: .upperDiapason8, identifier: "upperDiapason8", name: "Diapason 8'", units: .boolean, valueRange: 0.0...1.0, defaultValue: 0.0)
        ParameterSpec(address: .upperString8, identifier: "upperString8", name: "String 8'", units: .boolean, valueRange: 0.0...1.0, defaultValue: 0.0)
        ParameterSpec(address: .upperClarinet, identifier: "upperClarinet", name: "Clarinet 8'", units: .boolean, valueRange: 0.0...1.0, defaultValue: 0.0)
        ParameterSpec(address: .upperOboe, identifier: "upperOboe", name: "Oboe 8'", units: .boolean, valueRange: 0.0...1.0, defaultValue: 0.0)
        ParameterSpec(address: .upperString4, identifier: "upperString4", name: "String 4'", units: .boolean, valueRange: 0.0...1.0, defaultValue: 0.0)
    }
    ParameterGroupSpec(identifier: "lower", name: "Lower") {
        ParameterSpec(address: .lowerTibia8, identifier: "lowerTibia8", name: "Tibia 8'", units: .boolean, valueRange: 0.0...1.0, defaultValue: 0.0)
        ParameterSpec(address: .lowerTibia4, identifier: "lowerTibia4", name: "Tibia 4'", units: .boolean, valueRange: 0.0...1.0, defaultValue: 0.0)
        ParameterSpec(address: .lowerDiapason8, identifier: "lowerDiapason8", name: "Diapason 8'", units: .boolean, valueRange: 0.0...1.0, defaultValue: 0.0)
        ParameterSpec(address: .lowerString8, identifier: "lowerString8", name: "String 8'", units: .boolean, valueRange: 0.0...1.0, defaultValue: 0.0)
        ParameterSpec(address: .lowerHorn, identifier: "lowerHorn", name: "Horn 8'", units: .boolean, valueRange: 0.0...1.0, defaultValue: 0.0)
        ParameterSpec(address: .lowerString4, identifier: "lowerString4", name: "String 4'", units: .boolean, valueRange: 0.0...1.0, defaultValue: 0.0)
        ParameterSpec(address: .lowerVolume, identifier: "lowerVolume", name: "Lower Volume", units: .linearGain, valueRange: 0.5...1.5, defaultValue: 1.0)
    }
    ParameterGroupSpec(identifier: "pedal", name: "Pedal") {
        ParameterSpec(address: .pedalBourdon16, identifier: "pedalBourdon16", name: "Bourdon 16'", units: .boolean, valueRange: 0.0...1.0, defaultValue: 0.0)
        ParameterSpec(address: .pedalMajorFlute8, identifier: "pedalMajorFlute8", name: "Major Flute 8'", units: .boolean, valueRange: 0.0...1.0, defaultValue: 0.0)
        ParameterSpec(address: .pedalVolume, identifier: "pedalVolume", name: "Pedal Volume", units: .linearGain, valueRange: 0.5...4.0, defaultValue: 2.0)
        ParameterSpec(address: .pedalSustain, identifier: "pedalSustain", name: "Pedal Sustain", units: .boolean, valueRange: 0.0...1.0, defaultValue: 0.0)
        ParameterSpec(address: .pedalSustainLength, identifier: "pedalSustainLength", name: "Pedal Sustain Length", units: .seconds, valueRange: 0.1...2.0, defaultValue: 0.3)
    }
}

extension ParameterSpec {
    init(
        address: RetroTransistorOrganExtensionParameterAddress,
        identifier: String,
        name: String,
        units: AudioUnitParameterUnit,
        valueRange: ClosedRange<AUValue>,
        defaultValue: AUValue,
        unitName: String? = nil,
        flags: AudioUnitParameterOptions = [AudioUnitParameterOptions.flag_IsWritable, AudioUnitParameterOptions.flag_IsReadable],
        valueStrings: [String]? = nil,
        dependentParameters: [NSNumber]? = nil
    ) {
        self.init(address: address.rawValue,
                  identifier: identifier,
                  name: name,
                  units: units,
                  valueRange: valueRange,
                  defaultValue: defaultValue,
                  unitName: unitName,
                  flags: flags,
                  valueStrings: valueStrings,
                  dependentParameters: dependentParameters)
    }
}
