/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/adc.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
#define BUTTON_NODE DT_ALIAS(sw0)
#define MY_ADC_CH DT_ALIAS(my_adc_channel)

#define TIMER_MS 100

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);
static const struct gpio_dt_spec btn = GPIO_DT_SPEC_GET(BUTTON_NODE, gpios);

static const struct device *adc_dev = DEVICE_DT_GET(DT_ALIAS(my_adc));
static const struct adc_channel_cfg adc_ch = ADC_CHANNEL_CFG_DT(MY_ADC_CH);

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
	int ret;
	bool led_state = true;
	bool button_state = false;

	uint16_t buf;
	uint32_t val_mv;
	
	if (!device_is_ready(adc_dev)) {
		printk("ADC device not ready\n");
		return 0;
	}

	struct adc_sequence seq = {
		.channels = BIT(adc_ch.channel_id),
		.buffer = &buf,
		.buffer_size = sizeof(buf),
		.resolution = DT_PROP(MY_ADC_CH, zephyr_resolution)
	};

	ret = adc_channel_setup(adc_dev, &adc_ch);
	if (ret < 0) {
		printk("Could not setup channel (%d)\n", ret);
		return 0;
	}

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
		/*Get Button state*/
		button_state = gpio_pin_get_dt(&btn);

		ret = adc_read(adc_dev, &seq);
		if (ret < 0) {
			printk("Could not read (%d)\n", ret);
			continue;
		}
		/*Calculate ADC value mv*/
		val_mv = (uint32_t)buf * DT_PROP(MY_ADC_CH, zephyr_vref_mv) / (1 << seq.resolution);
		
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
		/*Print ADC Conversion value*/
		printf("Raw: %u, mv: %u\r\n", buf, val_mv);
		/*sleep for 1 sec*/
		k_msleep(SLEEP_TIME_MS);
	}
	return 0;
}
