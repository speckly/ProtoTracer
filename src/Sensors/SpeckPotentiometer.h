#include <Arduino.h>

class SpeckPotentiometer {
private:
    uint8_t pinNumber;
    uint8_t modeNumber;
    int potValue;

public:
    // Define the constructor here
    SpeckPotentiometer(uint8_t pin, uint8_t mode) : pinNumber(pin), modeNumber(mode) {
        pinMode(pinNumber, INPUT);
    }

    int read() {
        potValue = analogRead(pinNumber);
        return (potValue * modeNumber) / 1023;
    }
};
