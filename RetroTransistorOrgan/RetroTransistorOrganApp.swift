//
//  RetroTransistorOrganApp.swift
//  RetroTransistorOrgan
//
//  Created by Yugen on 2026/06/28.
//

import SwiftUI

@main
struct RetroTransistorOrganApp: App {
    private let hostModel = AudioUnitHostModel()

    var body: some Scene {
        WindowGroup {
            ContentView(hostModel: hostModel)
        }
    }
}
