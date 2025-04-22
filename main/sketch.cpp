// SPDX-License-Identifier: Apache-2.0
// Copyright 2021 Ricardo Quesada
// http://retro.moe/unijoysticle2

#include "sdkconfig.h"

#include <Arduino.h>
#include <Bluepad32.h>

#include <LovyanGFX.hpp>
#include "lgfx_config.h"

static LGFX tft;

void setup() {
    delay(5000);

    if (psramInit()) {
        Console.println("✅ PSRAM is enabled!");
        Console.printf("Total PSRAM: %d bytes\n", ESP.getPsramSize());
    } else {
        Console.println("❌ PSRAM init failed!");
    }

    // Comment out the tft lines below and there won't be a crash
    tft.begin();
    tft.setRotation(1);
    tft.setBrightness(128);
    tft.fillScreen(TFT_BLACK);
    tft.drawString("Hello", 10, 10);
}

void loop() {
    delay(5000);
    Console.println("Heartbeat...");
}
