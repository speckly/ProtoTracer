<<<<<<< Updated upstream
#include "Examples\UserConfiguration.h"

#ifdef TESTHARDWARE
#include "Examples\Protogen\ProtogenHardwareTest.h"
#endif
=======

#define HUB75
//#define HUB75Split
//#define HUB75Square
//#define WS35
//#define WS35SPLIT
// #define ESP32HUB75
//#define CUSTOMHUB75
//#define CUSTOMWS35
//#define CUSTOMBETAWS35

// #define PRINTINFO 

//#define NEOTRELLISMENU

#include <Arduino.h>
// #include <FastLED.h>//temporary

// CRGB testleds[50];
uint8_t maxBrightness = 255;
uint8_t maxAccentBrightness = 255;
// unsigned long startTime;

#if defined(HUB75)
#include "Controllers\SmartMatrixHUB75.h"
#include "Animation\HUB75Animation.h"
// #include "Controllers\SpeckWS2812B.h"
//#include "Animation\BetaAnimation.h"
SmartMatrixHUB75 controller = SmartMatrixHUB75(maxBrightness, maxAccentBrightness);
HUB75Animation animation = HUB75Animation();
// SpeckWS2812B leds = SpeckWS2812B();
//BetaAnimation animation = BetaAnimation();
#endif
// #else
//Define your own here
//--------------- ANIMATIONS ---------------
//#include "Animation\Test\FullScreenAnimation.h"
//#include "Animation\VectorFieldAnimation.h"
//#include "Animation\CoelaBonkAnimation.h"
//#include "Animation\SpyroAnimation.h"
//#include "Animation\SpyroRotateAnimation.h"
//#include "Animation\Commissions\AphoriAnimation.h"
//#include "Animation\Commissions\GalaxyAnimation.h"

//--------------- CONTROLLERS ---------------
//#include "Controllers\KaiborgV1Controller.h"
// #include "Controllers\KaiborgV1D1Controller.h"
//#include "Controllers\ProtoDRController.h"
//#include "Controllers\SmartMatrixHUB75.h"
//#include "Controllers\SmartMatrixHUB75Split.h"
//#define HUB75
// #endif
>>>>>>> Stashed changes

#include "Examples\Protogen\ProtogenHUB75Project.h"
//#include "Examples\Protogen\ProtogenWS35Project.h"
//#include "Examples\VerifyEngine.h"

ProtogenHUB75Project project;

void setup() {
    Serial.begin(115200);
    Serial.println("\nStarting...");
    
    #ifndef TESTHARDWARE
    project.Initialize();
    delay(100);
<<<<<<< Updated upstream
    #else
    while(true){
        HardwareTest::ScanDevices();
        HardwareTest::TestNeoTrellis();
        HardwareTest::TestBoopSensor();
        HardwareTest::TestHUD();
    }
    #endif
=======

    // leds.initializeLED(); //const int ledcount = 197, const int brightness = 190
>>>>>>> Stashed changes
}

void loop() {
    float ratio = (float)(millis() % 5000) / 5000.0f;
<<<<<<< Updated upstream

    project.Animate(ratio); 

    project.Render();

    project.Display();

    project.PrintStats();
=======
    #if defined(HUB75)
    controller.SetAccentBrightness(animation.GetAccentBrightness() * 25 + 5);
    controller.SetBrightness(animation.GetBrightness() * 25 + 5);

    animation.UpdateTime(ratio);
    controller.Render(animation.GetScene());
    #else
    Serial.print("not defined");
    #endif
    
    //controller.

    controller.Display();

    #ifdef PRINTINFO
    Serial.print("Animated in ");
    Serial.print(animation.GetAnimationTime(), 4);

    Serial.print("s, Rendered in ");
    Serial.print(controller.GetRenderTime(), 4);

    
    Serial.print("s, Free memory ");
    Serial.print(FreeMem(),3);

    Serial.println("Kb");
    #endif
>>>>>>> Stashed changes
}