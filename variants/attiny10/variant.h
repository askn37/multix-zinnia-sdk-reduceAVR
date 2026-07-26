/**
 * @file variant.h
 * @author askn (K.Sato) multix.jp
 * @brief ATtiny4/5/9/10 Macro/MicroAPI
 * @version 0.4.2
 * @date 2026-07-20
 *
 * @copyright Copyright (c) 2026 askn37 at github.com
 *
 */
/* MIT License : https://askn37.github.io/LICENSE.html */

#pragma once
#include <avr/io.h>

#define AVR_REDUCEAVR 1
#define AVR_TPI       1
#define AVR_TPI6      1

#include "variant_io.h"
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>
#include <api/CLKCTRL_reduceAVR.h>

/* GPIO x4 (other VDD,GND) */
#define PIN_PB0 224
#define PIN_PB1 225
#define PIN_PB2 226
#define PIN_PB3 227

#define NOT_A_PIN   255
#define PIN_RST     PIN_PB3

#ifndef LED_BUILTIN
#define LED_BUILTIN PIN_PB1   /* PWM Channel TCB0_WOA Pin */
#endif
/* #define LED_BUILTIN_INVERT */ /* implementation dependent */

/* peripheral ports */
#define PIN_RESET         PIN_PB3
#define PIN_TPIDATA       PIN_PB0
#define PIN_TPICLK        PIN_PB1

#define PIN_OC0A          PIN_PB0
#define PIN_OC0B          PIN_PB1
#define PIN_ICP0          PIN_PB1
#define PIN_T0            PIN_PB2

#define PIN_WOA           PIN_PB0
#define PIN_WOB           PIN_PB1
#define PIN_TCB0_WOA      PIN_PB0
#define PIN_TCB0_WOB      PIN_PB1
#define PIN_TCB0_CAP      PIN_PB1
#define PIN_TCB0_CLKI     PIN_PB2

#if !defined(__AVR_ATtiny4__) && !defined(__AVR_ATtiny9__)
#define PIN_ADC0          PIN_PB0
#define PIN_ADC1          PIN_PB1
#define PIN_ADC2          PIN_PB2
#define PIN_ADC3          PIN_PB3
#define PIN_ADC0_AIN0     PIN_PB0
#define PIN_ADC0_AIN1     PIN_PB1
#define PIN_ADC0_AIN2     PIN_PB2
#define PIN_ADC0_AIN3     PIN_PB3
#endif

#define PIN_AIN0          PIN_PB0
#define PIN_AIN1          PIN_PB1
#define PIN_AC0_AINN      PIN_PB0
#define PIN_AC0_AINP      PIN_PB1

#define PIN_CLKI          PIN_PB1
#define PIN_CLKO          PIN_PB2
#define PIN_INT0          PIN_PB2

/* peripheral symbols */

#define HAVE_AC0          ANA_COMP_vect_num
#if !defined(__AVR_ATtiny4__) && !defined(__AVR_ATtiny9__)
#define HAVE_ADC0         ADC_vect_num
#endif
#define HAVE_INT0         INT0_vect_num
#define HAVE_PORTA        PCINT0_vect_num
#define HAVE_TCB0         TIM0_CAPT_vect_num
#define HAVE_VLM          VLM_vect_num
#define HAVE_WDT          WDT_vect_num

#ifdef __cplusplus
extern "C" {
#endif

#if !defined (__ASSEMBLER__)
inline void initVariant (void) {
  _CLKCTRL_SETUP();
  PORTCTRL_CTRLB = PORTCTRL_DID0_gm;  /* Digital Input Disable all pin */
}
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

/* end of code */
