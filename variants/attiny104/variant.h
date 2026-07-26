/**
 * @file variant.h
 * @author askn (K.Sato) multix.jp
 * @brief ATtiny102/104 Macro/MicroAPI
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
#if !defined(__AVR_ATtiny102__)
#define AVR_TPI14     1
#else
#define AVR_TPI8      1
#endif

#include "variant_io.h"
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>
#include <api/CLKCTRL_reduceAVR.h>

/* GPIO x6 or x12 (other VDD,GND) */
#define PIN_PA0 192
#define PIN_PA1 193
#define PIN_PA2 194
#if !defined(__AVR_ATtiny102__)
#define PIN_PA3 195
#define PIN_PA4 196
#define PIN_PA5 197
#define PIN_PA6 198
#define PIN_PA7 199

#define PIN_PB0 224
#endif
#define PIN_PB1 225
#define PIN_PB2 226
#define PIN_PB3 227

#define NOT_A_PIN   255
#define PIN_RST     PIN_PA2

#ifndef LED_BUILTIN
#define LED_BUILTIN PIN_PA5   /* PWM Channel TCB0_WO1_ALT Pin */
#endif
/* #define LED_BUILTIN_INVERT */ /* implementation dependent */

/* peripheral ports */
#define PIN_RESET         PIN_PA2
#define PIN_TPIDATA       PIN_PA1
#define PIN_TPICLK        PIN_PA0

#define PIN_OC0A          PIN_PB1
#define PIN_OC0B          PIN_PA1
#define PIN_ICP0          PIN_PB2
#define PIN_T0            PIN_PA0

#define PIN_WOA           PIN_PB1
#define PIN_WOB           PIN_PA1
#define PIN_TCB0_WOA      PIN_PB1
#define PIN_TCB0_WOB      PIN_PA1
#define PIN_TCB0_CAP      PIN_PB2
#define PIN_TCB0_CLKI     PIN_PA0

#if !defined(__AVR_ATtiny102__)
#define PIN_OC0A_ALT      PIN_PA3
#define PIN_OC0B_ALT      PIN_PA5
#define PIN_ICP0_ALT      PIN_PA4
#endif
#define PIN_T0_ALT        PIN_PB3

#if !defined(__AVR_ATtiny102__)
#define PIN_WOA_ALT       PIN_PA3
#define PIN_WOB_ALT       PIN_PA5
#define PIN_TCB0_WOA_ALT  PIN_PA3
#define PIN_TCB0_WOB_ALT  PIN_PA5
#define PIN_TCB0_CAP_ALT  PIN_PA4
#endif
#define PIN_TCB0_CLKI_ALT PIN_PB3

#define PIN_ADC0          PIN_PA0
#define PIN_ADC1          PIN_PA1
#if !defined(__AVR_ATtiny102__)
#define PIN_ADC2          PIN_PA5
#define PIN_ADC3          PIN_PA6
#define PIN_ADC4          PIN_PB0
#endif
#define PIN_ADC5          PIN_PB1
#define PIN_ADC6          PIN_PB2
#define PIN_ADC7          PIN_PB3

#define PIN_ADC0_AIN0     PIN_PA0
#define PIN_ADC0_AIN1     PIN_PA1
#if !defined(__AVR_ATtiny102__)
#define PIN_ADC0_AIN2     PIN_PA5
#define PIN_ADC0_AIN3     PIN_PA6
#define PIN_ADC0_AIN4     PIN_PB0
#endif
#define PIN_ADC0_AIN5     PIN_PB1
#define PIN_ADC0_AIN6     PIN_PB2
#define PIN_ADC0_AIN7     PIN_PB3

#define PIN_ACO           PIN_PB3
#define PIN_AIN0          PIN_PA0
#define PIN_AIN1          PIN_PA1

#define PIN_AC0_OUT       PIN_PB3
#define PIN_AC0_AINN      PIN_PA0
#define PIN_AC0_AINP      PIN_PA1

#define PIN_XCK           PIN_PB1
#define PIN_TXD           PIN_PB2
#define PIN_RXD           PIN_PB3

#define PIN_USART0_XCK    PIN_PB1
#define PIN_USART0_TXD    PIN_PB2
#define PIN_USART0_RXD    PIN_PB3

#define PIN_CLKI          PIN_PA0
#define PIN_CLKO          PIN_PB1
#define PIN_INT0          PIN_PB1

/* peripheral symbols */

#define HAVE_AC0          ANA_COMP_vect_num
#define HAVE_ADC0         ADC_vect_num
#define HAVE_INT0         INT0_vect_num
#define HAVE_PORTA        PCINT0_vect_num
#define HAVE_PORTB        PCINT1_vect_num
#define HAVE_TCB0         TIM0_CAPT_vect_num
#define HAVE_USART0       USART_RXS_vect_num
#define HAVE_VLM          VLM_vect_num
#define HAVE_WDT          WDT_vect_num

#ifdef __cplusplus
extern "C" {
#endif

inline void initVariant (void) {
  _CLKCTRL_SETUP();
  PORTCTRL_CTRLB = PORTCTRL_DID0_gm;  /* Digital Input Disable all pin */
}

#ifdef __cplusplus
} /* extern "C" */
#endif

/* end of code */
