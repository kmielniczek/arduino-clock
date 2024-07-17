#ifndef DATETIME_H
#define DATETIME_H

#include <Arduino.h>

struct DateTime {
public:
    byte day;
    byte month;
    unsigned int year;

    byte hour;
    byte minute;
    byte second;

    DateTime();

    void tick();

    void increment_day();
    void decrement_day();

    void increment_month();
    void decrement_month();

    void increment_year();
    void decrement_year();

    void adjust_day_after_change();

    void increment_seconds();
    void decrement_seconds();

    void increment_minutes();
    void decrement_minutes();

    void increment_hours();
    void decrement_hours();
};

#endif /* DATETIME_H */
