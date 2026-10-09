/**
 * @file main.c
 */

#include <inttypes.h>

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include "BTN.h"
#include "LED.h"

#define SLEEP_MS 1

uint32_t u32Counter = 0;
uint32_t u32Bar = 0;

int main(void) {
  if (0 > BTN_init()) {
    return 0;
  }
  if (0 > LED_init()) {
    return 0;
  }

  while (1) 
  {
    u32Counter++;
    if(u32Counter == 1000)
    {
      printk("Counter 1000 test message: %d",u32Bar);
    }

    if(u32Counter == 2000)
    {
      printk("Counter 2000 test message\n\r");
      u32Counter = 0;
    }

    k_msleep(SLEEP_MS);
  }
  return 0;
}
