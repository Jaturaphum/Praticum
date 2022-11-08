#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

float light;
const uint RED_PIN = 12;
const uint YELLOW_PIN = 13;
const uint GREEN_PIN = 14;
const uint SW_PIN = 15;
uint light_color[]= {RED_PIN, YELLOW_PIN, GREEN_PIN};
int logic = 1, secound = 1000000, delay = 1, sw_delay = 0;

void set_io() {
    stdio_init_all();
    adc_init();
    adc_gpio_init(28);
    adc_select_input(2);
    gpio_pull_up(SW_PIN); 
    for(int i=0; i<3; i++) {
        gpio_init(light_color[i]);
        gpio_set_dir(light_color[i], GPIO_OUT);
    }
}

void led_red() {
    gpio_put(RED_PIN, 1);
}
void led_yellow() {
    gpio_put(YELLOW_PIN, 1);
}
void led_green() {
    gpio_put(GREEN_PIN, 1);
}
void clear_all() {
    for (int i=0; i<3; i++) {
        gpio_put (light_color[i], 0);
    }
}
void clear_led_light() {
    gpio_put(light_color[0], 0);
    gpio_put(light_color[1], 0);
}
void clear_led_green() {
    gpio_put(light_color[2], 0);
}
float get_light(float conversion_factor) {
    uint16_t result = adc_read();
    uint16_t light = result * conversion_factor;
    return light;
}
void gpio_callback_press(uint gpio, uint32_t events) {
    gpio_acknowledge_irq(gpio, events);
    printf("Press");
    logic = 1; }
void gpio_callback_release(uint gpio, uint32_t events) {
    gpio_acknowledge_irq(gpio, events);
    printf("Release");
    logic = 2; }
void gpio_callback_delay(uint gpio, uint32_t events) {
    gpio_acknowledge_irq(gpio, events);
    sw_delay = 1;
    if (delay > 2) { delay = 1; }
    else { delay += 1; } 
}
void sw_test() {
        if (logic == 1) {
          gpio_set_irq_enabled_with_callback(SW_PIN, GPIO_IRQ_EDGE_RISE, true, &gpio_callback_release);
        } else { 
        gpio_set_irq_enabled_with_callback(SW_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_callback_press);
        }
}

void test_hw(int old_time) {
    int old_time_light = old_time;
    while (true) {
    const float conversion_factor = 100.0f / (1 << 12);
    sw_test();
    light = get_light(conversion_factor);
    if (time_us_64() - old_time >= 5* secound)
    { break;
    } else {
        if(time_us_64() - old_time_light > 1* secound) {
        old_time_light = time_us_64();
        printf("%f", light); 
        } if(time_us_64() - old_time > 3* secound) {
        led_green();
        clear_all();
        } else if (time_us_64() - old_time > 2* secound) {
        led_yellow();
        clear_all();
        } else if (time_us_64() - old_time > 1* secound) {
        led_red();
        } else { clear_all();}
        }
    }
}

void run(int old_time) {
    while (true) 
    {
        const float conversion_factor = 100.0f / (1 << 12);
        light = get_light(conversion_factor);
        if(light < 30) {
        clear_led_light();
        led_red(); 
        } else if (light < 60) {
        clear_led_light();
        led_red();
        led_yellow();
        } else {
        clear_led_light();
        led_yellow();
        }
        gpio_set_irq_enabled_with_callback(SW_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_callback_delay);
        if (time_us_64() - old_time > delay * secound) {
            led_green();
            old_time = time_us_64();
            printf("LDR value: %d", delay);
        } if (time_us_64() - old_time > delay* secound/2) {
        clear_led_green();
        }
    }
}

int main() {
    int old_time = time_us_64();
    set_io();
    test_hw(old_time);
    logic = 0;
    sleep_ms(3000);
    old_time = time_us_64();
    run(old_time);
    return 1;
}
