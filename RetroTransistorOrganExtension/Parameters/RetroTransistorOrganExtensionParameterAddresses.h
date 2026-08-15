//
//  RetroTransistorOrganExtensionParameterAddresses.h
//  RetroTransistorOrganExtension
//
//  Created by Yugen on 2026/06/28.
//

#pragma once

#include <AudioToolbox/AUParameters.h>

typedef NS_ENUM(AUParameterAddress, RetroTransistorOrganExtensionParameterAddress) {
    gain = 0,
    upperTibia16, upperTibia8, upperTibia4, upperTibia2_2_3,
    upperDiapason8,
    upperString16, upperString8, upperClarinet, upperOboe, upperString4,
    lowerTibia8, lowerTibia4,
    lowerDiapason8,
    lowerHorn,
    lowerString8, lowerString4,
    lowerVolume,
    pedalBourdon16, pedalMajorFlute8,
    pedalVolume,
    pedalSustain, pedalSustainLength,
    vibrato, ensemble
};
