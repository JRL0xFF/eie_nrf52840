/**
 * @file main.c
 */

#include <inttypes.h>

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include "BTN.h"
#include "LED.h"

#define SLEEP_MS 10

#define LED_BLU LED0
#define LED_RED LED1
#define LED_GRN LED2
#define LED_YEL LED3

uint8_t u8DutyCycle = 0;

int main(void) 
{
  if (0 > BTN_init()) 
  {
    return 0;
  }
  if (0 > LED_init()) 
  {
    return 0;
  }

  /* Turn on LEDs and figure out which color is which (step through this) */
  LED_blink(LED_BLU, LED_2HZ); // Blue
  LED_set(LED_GRN, LED_ON); // Red
  //LED_set(LED_GRN, LED_ON); // Green
  //LED_set(LED_YEL, LED_ON); // Yellow

  while (1) 
  {
    LED_pwm(LED_YEL, u8DutyCycle);

    if(u8DutyCycle == 100)
    {
      u8DutyCycle = 0;
      LED_toggle(LED_RED);
    }
    else
    {
      u8DutyCycle++;
    }

    k_msleep(SLEEP_MS);
  }
  return 0;
} // end main()
