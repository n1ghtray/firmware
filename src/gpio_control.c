#include "gpio_control.h"
#include "hardware/gpio.h"
#include "config.h"

void initialize_gpio()
{
    for (int gpio_pin = 1; gpio_pin <= 46; gpio_pin++) // Set as input pins by default
        gpio_init(gpio_pin);

    for (int gpio_pin = 1; gpio_pin <= 22; gpio_pin++) // A pins
    {
        gpio_set_dir(gpio_pin, 1);
        gpio_pull_down(gpio_pin);
    }

    for (int gpio_pin = 24; gpio_pin <= 39; gpio_pin++) // P pins
    {
        gpio_set_dir(gpio_pin, 1);
        gpio_pull_down(gpio_pin);
    }

    for (int gpio_pin = 41; gpio_pin <= 44; gpio_pin++) // Control pins
    {
        gpio_set_dir(gpio_pin, 1);
        gpio_pull_down(gpio_pin);
    }

    gpio_pull_up(BUTTON_PIN); // WeAct RP2350B button
    gpio_pull_down(FIRE_PIN); // FIRE pin
}