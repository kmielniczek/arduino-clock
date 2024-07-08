#ifndef CLOCK_H
#define CLOCK_H

#include <Arduino.h>
#include "datetime.h"

// Basically a big switch where each case is a separate object

class Clock;

class State {
protected:
    Clock *cnt;
    int counter;

public:
    State() : counter(0) {};
    virtual ~State() {};

    void set_context(Clock *context) { cnt = context; }

    virtual void tick() = 0;
    virtual void up() = 0;
    virtual void down() = 0;
    virtual void date() = 0;
    virtual void time() = 0;
};


class Clock {
private:
    State *state;

public:
    DateTime date_time;
    char date_buf[11];
    char time_buf[9];
    volatile bool buf_changed;

    Clock(State *st) : state(st) {
        state->set_context(this);
        refresh_bufs();
    }

    ~Clock() {
        if (state != nullptr) delete state;
    }

    void change_state(State *st) {
        if (state != nullptr) delete state;
        state = st;
        state->set_context(this);

        refresh_bufs();
    }

    void tick() { state->tick(); }
    void up() { state->up(); }
    void down() { state->down(); }
    void date() { state->date(); }
    void time() { state->time(); }

    bool has_buf_changed() {
        if (!buf_changed) return false;

        buf_changed = false;
        return true;
    }

    void refresh_bufs() {
        snprintf(time_buf, 9, "%02d:%02d:%02d",
            date_time.hour, date_time.minute, date_time.second);

        snprintf(date_buf, 11, "%02d.%02d.%04d",
            date_time.day, date_time.month, date_time.year);
        buf_changed = true;
    }
};


class ChangeSeconds : public State {
private:
    bool displayed = true;

public:
    void tick() {
        if (++counter == 200) {
            counter = 0;
            if (displayed) {
                strncpy(cnt->time_buf + 6, "  ", 2);
                cnt->buf_changed = true;
            }
            else cnt->refresh_bufs();

            displayed = !displayed;
        }
    }
    void up() {
        cnt->date_time.increment_seconds();
        cnt->refresh_bufs();
    }
    void down() {
        cnt->date_time.decrement_seconds();
        cnt->refresh_bufs();
    }
    void date() {
        return;
    }
    void time();
};


class ChangeMinutes : public State {
private:
    bool displayed = true;

public:
    void tick() {
        if (++counter == 200) {
            counter = 0;
            if (displayed) {
                strncpy(cnt->time_buf + 3, "  ", 2);
                cnt->buf_changed = true;
            }
            else cnt->refresh_bufs();

            displayed = !displayed;
        }
    }
    void up() {
        cnt->date_time.increment_minutes();
        cnt->refresh_bufs();
    }
    void down() {
        cnt->date_time.decrement_minutes();
        cnt->refresh_bufs();
    }
    void date() {
        return;
    }
    void time() {
        cnt->change_state(new ChangeSeconds);
    }
};


class ChangeHours : public State {
private:
    bool displayed = true;

public:
    void tick() {
        if (++counter == 200) {
            counter = 0;
            if (displayed) {
                strncpy(cnt->time_buf, "  ", 2);
                cnt->buf_changed = true;
            }
            else cnt->refresh_bufs();

            displayed = !displayed;
        }
    }
    void up() {
        cnt->date_time.increment_hours();
        cnt->refresh_bufs();
    }
    void down() {
        cnt->date_time.decrement_hours();
        cnt->refresh_bufs();
    }
    void date() {
        return;
    }
    void time() {
        cnt->change_state(new ChangeMinutes);
    }
};


class ChangeYear : public State {
private:
    bool displayed = true;

public:
    void tick() {
        if (++counter == 200) {
            counter = 0;
            if (displayed) {
                strncpy(cnt->date_buf + 6, "    ", 4);
                cnt->buf_changed = true;
            }
            else cnt->refresh_bufs();

            displayed = !displayed;
        }
    }
    void up() {
        cnt->date_time.increment_year();
        cnt->refresh_bufs();
    }
    void down() {
        cnt->date_time.decrement_year();
        cnt->refresh_bufs();
    }
    void date();
    void time() {
        return;
    }
};


class ChangeMonth : public State {
private:
    bool displayed = true;

public:
    void tick() {
        if (++counter == 200) {
            counter = 0;
            if (displayed) {
                strncpy(cnt->date_buf + 3, "  ", 2);
                cnt->buf_changed = true;
            }
            else cnt->refresh_bufs();

            displayed = !displayed;
        }
    }
    void up() {
        cnt->date_time.increment_month();
        cnt->refresh_bufs();
    }
    void down() {
        cnt->date_time.decrement_month();
        cnt->refresh_bufs();
    }
    void date() {
        cnt->change_state(new ChangeYear);
    }
    void time() {
        return;
    }
};


class ChangeDay : public State {
private:
    bool displayed = true;

public:
    void tick() {
        if (++counter == 200) {
            counter = 0;
            if (displayed) {
                strncpy(cnt->date_buf, "  ", 2);
                cnt->buf_changed = true;
            }
            else cnt->refresh_bufs();
            displayed = !displayed;
        }
    }
    void up() {
        cnt->date_time.increment_day();
        cnt->refresh_bufs();
    }
    void down() {
        cnt->date_time.decrement_day();
        cnt->refresh_bufs();
    }
    void date() {
        cnt->change_state(new ChangeMonth);
    }
    void time() {
        return;
    }
};


class Working : public State {
public:
    void tick() {
        if (++counter == 500) {
            counter = 0;
            cnt->date_time.increment_seconds();
            cnt->refresh_bufs();
        }
    };
    void up() {
        return;
    }
    void down() {
        return;
    }
    void date() {
        cnt->change_state(new ChangeDay);
    }
    void time() {
        cnt->change_state(new ChangeHours);
    }
};


void ChangeSeconds::time() {
    cnt->date_time.adjust_day_after_change();
    cnt->change_state(new Working);
}

void ChangeYear::date() {
    cnt->date_time.adjust_day_after_change();
    cnt->change_state(new Working);
}

#endif /* CLOCK_H */