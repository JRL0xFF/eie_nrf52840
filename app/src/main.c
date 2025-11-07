/*
 * main.c
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>

#include "BTN.h"
#include "LED.h"

#define BUTTON1 BTN0
#define BUTTON2 BTN1
#define BUTTON3 BTN2
#define BUTTON4 BTN3

#define SLEEP_TIME_MS 1
#define SW0_NODE DT_ALIAS(sw0)

#if 0 /* ISR-based example code */
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(SW0_NODE, gpios);

static struct gpio_callback sButtonIsrData;

void button_isr(const struct device *pcsDev, 
                struct gpio_callback *pfCallback, 
                uint32_t pins)
{
  printk("Button 0 pressed says the ISR!\n");
}
#endif /* ISR-based example code */

int main(void) 
{
  int ret;

  ret = BTN_init();
  ret |= LED_init();

  if (0 > ret)
  {
    return 0;
  }

  #if 0 /* ISR-based example code */
  if(!gpio_is_ready_dt(&button))
  {
    return 0;
  }

  ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
  ret |= gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_TO_ACTIVE);
  if(0 > ret)
  {
    return 0;
  }

  gpio_init_callback(&sButtonIsrData, button_isr, BIT(button.pin));
  gpio_add_callback(button.port, &sButtonIsrData);
  #endif /* ISR-based example code */

  while(1)
  {
    /* Button API-based button checking */
    if(BTN_check_clear_pressed(BUTTON1))
    {
      LED_toggle(LED0);
      printk("BUTTON1 was pressed via the EIE API!\n");
    }

    k_msleep(SLEEP_MS);

    #if 0 /* Polling-based solution */
    ret = gpio_pin_get_dt(&button);
    if(0 < ret)
    {
      printk("Pressed!\n");
    }
    k_msleep(SLEEP_TIME_MS);
    #endif /* Polling-based solution */
  }
 
	return 0;
}
