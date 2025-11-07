/*
* main.c
*/

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#include "typedefs.h"

#define LED0_NODE DT_ALIAS(led0)

static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

int main(void)
{
  /* Initiatialization */
  s32 s32Return;

  if(!gpio_is_ready_dt(&led0))
  {
    return -1;
  }

  s32Return = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
  if(s32Return < 0)
  {
    return s32Return;
  }

  while(1)
  {

  }

  return 0;
}