
#include <iostream>
#include "IO.h"


int main() {
    GPIO* testPin = new GPIO(3, PinState::OUTPUT);
    testPin->write(PinState::HIGH);
    sleep(1);
    testPin->write(PinState::LOW);

    delete testPin;
}