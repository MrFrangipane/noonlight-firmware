#ifndef V02_RELEASE_DIP_SWITCH_H
#define V02_RELEASE_DIP_SWITCH_H

void dipInitPins(uint8_t startPin, uint8_t endPin) {

}

uint16_t dipGetValue(uint8_t startPin, uint8_t endPin) {
    uint16_t value = !digitalRead(startPin);

    for (uint8_t pin = startPin + 1; pin < endPin + 1; pin++) {
        value += !digitalRead(pin) * (2 << pin - 2);
    }

    return min(value, 512);
}

#endif //V02_RELEASE_DIP_SWITCH_H
