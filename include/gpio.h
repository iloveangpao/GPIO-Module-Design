#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <stdbool.h>

// Define GPIO pins for LEDs and Push Buttons
#define GREEN_LED_PIN 0
#define RED_LED_PIN 1
#define PUSH_BUTTON_1_PIN 2
#define PUSH_BUTTON_2_PIN 3

// Set active low/high configuration before compilation
#define GREEN_LED_ACTIVE_LOW false
#define RED_LED_ACTIVE_LOW false
#define PUSH_BUTTON_1_ACTIVE_LOW false
#define PUSH_BUTTON_2_ACTIVE_LOW false

// LED identifiers
enum LED {
    GREEN,
    RED,
};

// Push button identifiers
enum PUSH_BUTTON {
    PB_1, // Toggle Green LED
    PB_2, // Cycle through Red LED blink intervals
};

// Blink intervals for Red LED
#define RED_LED_FAST_BLINK_INTERVAL 500  // Fast blink (500 ms)
#define RED_LED_MEDIUM_BLINK_INTERVAL 1000  // Medium blink (1000 ms)
#define RED_LED_SLOW_BLINK_INTERVAL 2000  // Slow blink (2000 ms)

// LED states for Green LED
typedef enum {
    LED_OFF,
    LED_ON
} green_led_state_t;

// LED states for Red LED
typedef enum {
    RED_LED_OFF,
    RED_LED_BLINK_FAST,
    RED_LED_BLINK_MEDIUM,
    RED_LED_BLINK_SLOW
} red_led_state_t;

// Function prototypes
int set_led(enum LED led_number, uint32_t interval);
int set_push_button(enum PUSH_BUTTON push_button, void (*callback_func)(void));
void led_app(void);
void push_button_app(void);

// Helper function prototypes
void green_led_on(void);
void green_led_off(void);
void red_led_on(void);
void red_led_off(void);

#endif // GPIO_H



