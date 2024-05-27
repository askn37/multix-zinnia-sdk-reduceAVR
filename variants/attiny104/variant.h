/**
 * @file variant.h
 * @author askn (K.Sato) multix.jp
 * @brief
 * @version 0.1
 * @date 2024-05-27
 *
 * @copyright Copyright (c) 2024 askn37 at github.com
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
#define AVR_TPI14     1

/* GPIO x12 (other VDD,GND) */
#define PIN_PA0 192
#define PIN_PA1 193
#define PIN_PA2 194
#define PIN_PA3 195
#define PIN_PA4 196
#define PIN_PA5 197
#define PIN_PA6 198
#define PIN_PA7 199

#define PIN_PB0 224
#define PIN_PB1 225
#define PIN_PB2 226
#define PIN_PB3 227

#define NOT_A_PIN   255
#define PIN_RST     PIN_PA2

#ifndef LED_BUILTIN
#define LED_BUILTIN PIN_PA5   /* PWM Channel OC0B* Pin */
#endif
/* #define LED_BUILTIN_INVERT */ /* implementation dependent */

#ifndef SW_BUILTIN
#define SW_BUILTIN  PIN_PB1
#endif

#ifdef __cplusplus
extern "C" {
#endif

inline void initVariant (void) {
  _CLKCTRL_SETUP();
  PORTCTRL_DIDIS = ~0;  /* Digital Input Disable all pin */
}

#ifdef __cplusplus
} // extern "C"
#endif

// end of code
