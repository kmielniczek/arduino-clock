#include <Arduino.h>
#include "datetime.h"

DateTime::DateTime() : day(28), month(5), year(2024), hour(23), minute(59), second(40) {}

void DateTime::increment_day() {
    day++;

    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            if (day > 31) {
                day = 1;
                increment_month();
            }
            break;

        case 4: case 6: case 9: case 11:
            if (day > 30) {
                day = 1;
                increment_month();
            }
            break;

        case 2:
            if (day > (((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) ? 29 : 28)) {
                day = 1;
                increment_month();
            }
            break;
    }
}

void DateTime::decrement_day() {
    if (--day == 0) {
        switch (month) {
            case 1: case 2: case 4: case 6: case 8: case 9: case 11:
                day = 31;
                decrement_month();
                break;

            case 5: case 7: case 10: case 12:
                day = 30;
                decrement_month();
                break;

            case 3:
                day = (((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) ? 29 : 28);
                decrement_month();
                break;
        }
    }
}

void DateTime::increment_month() {
    if (++month > 12) {
        month = 1;
        year++;
    }
}

void DateTime::decrement_month() {
    if (--month == 0) {
        month = 12;
        year--;
    }
}

void DateTime::increment_year() {
    year++;
}

void DateTime::decrement_year() {
    year--;
}

void DateTime::adjust_day_after_change() {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            break;

        case 4: case 6: case 9: case 11:
            if (day > 30) day = 30;
            break;

        case 2:
            byte days_in_feb = (((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) ? 29 : 28);
            if (day > days_in_feb) {
                day = days_in_feb;
            }
            break;
    }
}

void DateTime::increment_seconds() {
    if (++second >= 60) {
        second = 0;
        increment_minutes();
    }
}

void DateTime::decrement_seconds() {
    if (second > 0) {
        second--;
    }
    else {
        second = 59;
        decrement_minutes();
    }
}

void DateTime::increment_minutes() {
    if (++minute >= 60) {
        minute = 0;
        increment_hours();
    }
}

void DateTime::decrement_minutes() {
    if (minute > 0) {
        minute--;
    }
    else {
        minute = 59;
        decrement_hours();
    }
}

void DateTime::increment_hours() {
    if (++hour >= 24) {
        hour = 0;
        increment_day();
    }
}

void DateTime::decrement_hours() {
    if (hour > 0) {
        hour--;
    }
    else {
        hour = 23;
        decrement_day();
    }
}
