#define DATE_ADJ_BUTTON_PIN 11
#define TIME_ADJ_BUTTON_PIN 10
#define INCREASE_BUTTON_PIN 9
#define DECREASE_BUTTON_PIN 8

#define LCD_RS 18
#define LCD_EN 19
#define LCD_0 14
#define LCD_1 15
#define LCD_2 16
#define LCD_3 17


#include <Arduino.h>
#include <LiquidCrystal.h>
#include "button.h"
#include "clock.h"

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_0, LCD_1, LCD_2, LCD_3);

Clock clock(new Working);

Button date_btn(DATE_ADJ_BUTTON_PIN);
Button time_btn(TIME_ADJ_BUTTON_PIN);
Button up_btn(INCREASE_BUTTON_PIN);
Button down_btn(DECREASE_BUTTON_PIN);

// called every 2ms
ISR(TIMER0_COMPA_vect) {
    clock.tick();

    if (up_btn.is_clicked()) clock.up();
    if (down_btn.is_clicked()) clock.down();
    if (date_btn.is_clicked()) clock.date();
    if (time_btn.is_clicked()) clock.time();

    up_btn.decrement_timer();
    down_btn.decrement_timer();
    date_btn.decrement_timer();
    time_btn.decrement_timer();
}

void setup() {
    lcd.begin(16, 2);
    lcd.clear();

    TCCR0A = bit(WGM01);
    TCCR0B = bit(CS02);
    OCR0A = 125 - 1; // indexing starts from 0
    TIMSK0 = bit(OCIE0A) | bit(TOIE0);

    sei();
}

void loop() {
    if (clock.has_buf_changed()) {
        lcd.setCursor(7, 0);
        lcd.print(clock.time_buf);
        lcd.setCursor(6, 1);
        lcd.print(clock.date_buf);
    }
}
