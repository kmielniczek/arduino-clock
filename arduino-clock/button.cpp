#include <Arduino.h>
#include "button.h"

Button::Button(int pin) : pin(pin), timer(0) {
    pinMode(pin, INPUT_PULLUP);
}

bool Button::is_clicked() {
    if (timer == 0 && digitalRead(pin) == LOW) {
        timer = set_timer_to;
        return true;
    }

    return false;
}

void Button::decrement_timer() {
    if (timer > 0) timer--;
}
