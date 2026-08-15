//
//  TypeAliases.swift
//  RetroTransistorOrgan
//
//  Created by Yugen on 2026/06/28.
//

import CoreMIDI
import AudioToolbox

#if os(iOS) || os(visionOS)
import UIKit

public typealias ViewController = UIViewController
#elseif os(macOS)
import AppKit

public typealias KitView = NSView
public typealias ViewController = NSViewController
#endif
