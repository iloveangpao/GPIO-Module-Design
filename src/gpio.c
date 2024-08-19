#include "gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define DEBOUNCE_TIME_MS 50

// Internal structure to hold LED states
typedef struct {
    green_led_state_t green_state;
    red_led_state_t red_state;
    uint32_t red_interval;
    struct timeval last_toggle_time;
} led_control_t;

// Internal structure to hold Push Button states
typedef struct {
    struct timeval last_press_time;
    void (*callback_func)(void);
} button_control_t;

// LED control variables
static led_control_t leds = { LED_OFF, RED_LED_OFF, 0, {0, 0} };

// Push Button control variables
static button_control_t buttons[2];

// Mock functions for GPIO manipulation (to simulate GPIO hardware)
static void gpio_write(int pin, bool state, bool active_low) {
    bool output_state = active_low ? !state : state;
    printf("GPIO %d: %s\n", pin, output_state ? "HIGH" : "LOW");
}

static bool gpio_read(int pin) {
    int input;
    printf("GPIO %d read value (0/1): ", pin);
    scanf("%d", &input);
    return (input == 1);
}

// Helper function to turn the Green LED on
void green_led_on(void) {
    gpio_write(GREEN_LED_PIN, true, GREEN_LED_ACTIVE_LOW);
}

// Helper function to turn the Green LED off
void green_led_off(void) {
    gpio_write(GREEN_LED_PIN, false, GREEN_LED_ACTIVE_LOW);
}

// Helper function to turn the Red LED on
void red_led_on(void) {
    gpio_write(RED_LED_PIN, true, RED_LED_ACTIVE_LOW);
}

// Helper function to turn the Red LED off
void red_led_off(void) {
    gpio_write(RED_LED_PIN, false, RED_LED_ACTIVE_LOW);
}

// Function to set LED state and blink interval
int set_led(enum LED led_number, uint32_t interval) {
    if (led_number == GREEN) {
        if (interval == 0) {
            leds.green_state = LED_ON;
        } else {
            leds.green_state = LED_OFF;
        }
    } else if (led_number == RED) {
        if (interval == 0) {
            leds.red_state = RED_LED_OFF;
            leds.red_interval = 0;
        } else {
            leds.red_interval = interval;
            if (interval == RED_LED_FAST_BLINK_INTERVAL) {
                leds.red_state = RED_LED_BLINK_FAST;
            } else if (interval == RED_LED_MEDIUM_BLINK_INTERVAL) {
                leds.red_state = RED_LED_BLINK_MEDIUM;
            } else if (interval == RED_LED_SLOW_BLINK_INTERVAL) {
                leds.red_state = RED_LED_BLINK_SLOW;
            }
        }
    } else {
        return -1; // Invalid LED number
    }
    return 0;
}

// LED application logic (this is where GPIO operations occur)
void led_app(void) {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);

    if(leds.green_state == LED_OFF) green_led_on();
    else green_led_off();

    // Red LED control (blinking logic)
    if (leds.red_state != RED_LED_OFF && leds.red_interval > 0) {
        if ((current_time.tv_sec - leds.last_toggle_time.tv_sec) * 1000 +
            (current_time.tv_usec - leds.last_toggle_time.tv_usec) / 1000 >= leds.red_interval) {
            if(leds.red_state == RED_LED_OFF) red_led_on();
            else red_led_off();
            gettimeofday(&leds.last_toggle_time, NULL);
        }
    }
}

// Push Button application logic
void push_button_app(void) {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);

    for (int i = 0; i < 2; i++) {
        int pin = (i == 0) ? PUSH_BUTTON_1_PIN : PUSH_BUTTON_2_PIN;
        if (gpio_read(pin) == (i == 0 ? PUSH_BUTTON_1_ACTIVE_LOW : PUSH_BUTTON_2_ACTIVE_LOW)) {
            if ((current_time.tv_sec - buttons[i].last_press_time.tv_sec) * 1000 +
                (current_time.tv_usec - buttons[i].last_press_time.tv_usec) / 1000 >= DEBOUNCE_TIME_MS) {
                buttons[i].callback_func();
                gettimeofday(&buttons[i].last_press_time, NULL);
            }
        }
    }
}





