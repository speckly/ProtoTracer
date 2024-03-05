//Author: Andrew Higgins 
//https://github.com/speckly

#include <Arduino.h>
// #include <Adafruit_NeoPixel.h>

class SpeckWS2812B {
    private:
        int hue = 0;
        const int LED_PIN = 8;
        const int NUM_PIXELS = 75;
        Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
        //The Wheel() function converts a color value from 0 to 255 into a rainbow color.
        uint32_t Wheel(byte WheelPos) {
            WheelPos = 255 - WheelPos;
            if (WheelPos < 85) {
                return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
            }
            if (WheelPos < 170) {
                WheelPos -= 85;
                return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
            }
            WheelPos -= 170;
            return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
        }

    public:
        void initializeLED(const int ledcount=50, const int brightness=100);
        void updateRainbow();
    };

//The parameters are pretty useless for now but im going to keep it here just for future self
void SpeckWS2812B::updateRainbow() {
    // colorWipe(strip.Color(255, 0, 0));
    for (int i = 0; i < NUM_PIXELS; i++) {
        strip.setPixelColor(i, Wheel((i + hue) & 255));
    }
    hue++;
    if (hue == 256) {
        hue = 0;
    }
    strip.show();
}

void SpeckWS2812B::initializeLED(const int ledcount, const int brightness) {
    // this->ledcount = ledcount; // Set the private member ledcount to the parameter ledcount
    // if (matrixleds) {
    //     delete[] matrixleds;
    // }
    // Allocate memory for matrixleds based on the new ledcount
    // matrixleds = new CRGB[ledcount];
    strip.begin();
    strip.show();  // Initialize all pixels to 'off'
}

