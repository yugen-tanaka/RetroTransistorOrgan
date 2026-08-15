//
//  AudioUnitViewModel.swift
//  RetroTransistorOrgan
//
//  Created by Yugen on 2026/06/28.
//

import SwiftUI
import AudioToolbox
import CoreAudioKit

struct AudioUnitViewModel {
    var showAudioControls: Bool = false
    var showMIDIContols: Bool = false
    var title: String = "-"
    var message: String = "No Audio Unit loaded.."
    var viewController: ViewController?
}
