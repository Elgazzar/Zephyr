/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
#define BUTTON_NODE DT_ALIAS(sw0)

#define TIMER_MS 1000

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);
static const struct gpio_dt_spec btn = GPIO_DT_SPEC_GET(BUTTON_NODE, gpios);

static struct k_timer my_timer;

k_timeout_t duration_ms = {.ticks = TIMER_MS};
k_timeout_t period_ms = {.ticks = TIMER_MS};


void timer_callback(struct k_timer *timer)
{
	if(timer == &my_timer)
	{
		//printk("Esraa & Mahmoud!\r\n");
	}
}
int main(void)
{
	bool led_state = true;
	bool button_state = false;

	k_timer_init(&my_timer,timer_callback,NULL);

	k_timer_start(&my_timer,duration_ms,period_ms);

	/*Configure Pins as inputs or outputs*/
	gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
	gpio_pin_configure_dt(&led2, GPIO_OUTPUT_ACTIVE);
	gpio_pin_configure_dt(&btn, GPIO_INPUT);

	printk("Button Specs flags: 0x%x\r\n", btn.dt_flags);
	while (1) 
	{
		/*Toggle LEDS*/
		gpio_pin_toggle_dt(&led);
		gpio_pin_toggle_dt(&led1);
		gpio_pin_toggle_dt(&led2);

		/*Get Button state*/
		button_state = gpio_pin_get_dt(&btn);
		if( button_state == 1)
		{
			/*Toggle LEDS*/
			gpio_pin_toggle_dt(&led);
			gpio_pin_toggle_dt(&led1);
			gpio_pin_toggle_dt(&led2);
			/*Update led state*/
			led_state = !led_state;
		}
		/*Print Button state*/
		printf("Button state: %s\n", button_state ? "Not Pressed" : "Pressed");
		/*Print led state to the console*/
		printf("LED state: %s\n", led_state ? "ON" : "OFF");
		/*sleep for 1 sec*/
		k_msleep(SLEEP_TIME_MS);
	}
	return 0;
}
