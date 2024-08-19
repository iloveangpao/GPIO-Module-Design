#include "gpio.h"
#include <stdio.h>
#include <stdint.h>

// Callback function for toggling Green LED
void toggle_green_led(void) {
    static green_led_state_t green_led_state = LED_ON;
    green_led_state = (green_led_state == LED_ON) ? LED_OFF : LED_ON;
    set_led(GREEN, green_led_state == LED_ON ? 0 : 1);  // Toggle between ON and OFF
}

// Callback function for cycling through Red LED blink intervals
void cycle_red_led_blink(void) {
    static uint32_t interval = RED_LED_FAST_BLINK_INTERVAL;

    if (interval == RED_LED_FAST_BLINK_INTERVAL) {
        interval = RED_LED_MEDIUM_BLINK_INTERVAL;
    } else if (interval == RED_LED_MEDIUM_BLINK_INTERVAL) {
        interval = RED_LED_SLOW_BLINK_INTERVAL;
    } else if (interval == RED_LED_MEDIUM_BLINK_INTERVAL) {
        interval = RED_LED_SLOW_BLINK_INTERVAL;
    } else {
        interval = 0; // Turn off Red LED
    }

    set_led(RED, interval);
}

int main(void) {
    // Initialize LEDs and Push Buttons
    set_led(GREEN, 0);
    set_led(RED, RED_LED_FAST_BLINK_INTERVAL);

    set_push_button(PB_1, toggle_green_led);
    set_push_button(PB_2, cycle_red_led_blink);

    // Main loop
    while (1) {
        led_app();
        push_button_app();
    }

    return 0;
}
