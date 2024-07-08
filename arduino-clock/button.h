#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

// Class which objects represents buttons and accommodates switch bouncing
// it also sets proper pin mode in constructor.
class Button {
private:
    const byte pin;

    // button timer used to accommodate switch bouncing
    byte timer;

public:
    static inline byte set_timer_to = 125;

    Button(int pin);

    bool is_clicked();
    void decrement_timer();
};

#endif /* BUTTON_H */
