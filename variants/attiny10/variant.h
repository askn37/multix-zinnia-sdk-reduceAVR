/**
 * @file variant.h
 * @author askn (K.Sato) multix.jp
 * @brief
 * @version 0.1
 * @date 2022-12-12
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>
#include <variant_io.h>
#include <api/CLKCTRL_reduceAVR.h>

#define AVR_REDUCEAVR 1
#define AVR_TPI       1
#define AVR_TPI6      1

/* GPIO x4 (other VDD,GND) */
#define PIN_PB0 224
#define PIN_PB1 225
#define PIN_PB2 226
#define PIN_PB3 227

#define NOT_A_PIN   255
#define PIN_RST     PIN_PB3

#ifndef LED_BUILTIN
#define LED_BUILTIN PIN_PB1   /* PWM Channel OC0B Pin */
#endif
/* #define LED_BUILTIN_INVERT */ /* implementation dependent */

#ifdef __cplusplus
extern "C" {
#endif

inline void initVariant (void) {
  PORTCTRL_DIDIS = ~0;  /* Digital Input Disable all pin */
  _CLKCTRL_SETUP();
}

#ifdef __cplusplus
} // extern "C"
#endif

// end of code
