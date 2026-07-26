/**
 * @file variant.h
 * @author askn (K.Sato) multix.jp
 * @brief ATtiny40 Macro/MicroAPI
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
#define AVR_TPI20     1

#include "variant_io.h"
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>
#include <api/CLKCTRL_reduceAVR.h>

/* GPIO x18 (other VDD,GND) */
#define PIN_PA0 192
#define PIN_PA1 193
#define PIN_PA2 194
#define PIN_PA3 195
#define PIN_PA4 196
#define PIN_PA5 197
#define PIN_PA6 198
#define PIN_PA7 199

#define PIN_PB0 200
#define PIN_PB1 201
#define PIN_PB2 202
#define PIN_PB3 202

#define PIN_PC0 208
#define PIN_PC1 209
#define PIN_PC2 210
#define PIN_PC3 211
#define PIN_PC4 212
#define PIN_PC5 213

#define NOT_A_PIN   255
#define PIN_RST     PIN_PC3


#ifndef LED_BUILTIN
#define LED_BUILTIN PIN_PC0   /* PWM Channel OC0A Pin */
#endif
/* #define LED_BUILTIN_INVERT */ /* implementation dependent */

#ifndef SW_BUILTIN
#define SW_BUILTIN  PIN_PC2   /* INT0/PCINT14/MISO */
#endif

/* peripheral ports */
#define PIN_RESET         PIN_PC3
#define PIN_TPIDATA       PIN_PC4
#define PIN_TPICLK        PIN_PC5

#define PIN_OC0A          PIN_PC0
#define PIN_OC0B          PIN_PA5
#define PIN_ICP1          PIN_PC1
#define PIN_T0            PIN_PA4
#define PIN_T1            PIN_PC1

#define PIN_WOA           PIN_PC0
#define PIN_WOB           PIN_PA5
#define PIN_TCA0_WOA      PIN_PC0
#define PIN_TCA0_WOB      PIN_PA5
#define PIN_TCC0_CAP      PIN_PC1
#define PIN_TCA0_CLKI     PIN_PA4
#define PIN_TCC0_CLKI     PIN_PC1

#define PIN_ADC0          PIN_PA0
#define PIN_ADC1          PIN_PA1
#define PIN_ADC2          PIN_PA5
#define PIN_ADC3          PIN_PA6
#define PIN_ADC4          PIN_PB0
#define PIN_ADC5          PIN_PB1
#define PIN_ADC6          PIN_PB2
#define PIN_ADC7          PIN_PB3
#define PIN_ADC8          PIN_PB4
#define PIN_ADC9          PIN_PB5
#define PIN_ADC10         PIN_PB6
#define PIN_ADC11         PIN_PB7

#define PIN_ADC0_AIN0     PIN_PA0
#define PIN_ADC0_AIN1     PIN_PA1
#define PIN_ADC0_AIN2     PIN_PA5
#define PIN_ADC0_AIN3     PIN_PA6
#define PIN_ADC0_AIN4     PIN_PB0
#define PIN_ADC0_AIN5     PIN_PB1
#define PIN_ADC0_AIN6     PIN_PB2
#define PIN_ADC0_AIN7     PIN_PB3
#define PIN_ADC0_AIN8     PIN_PB4
#define PIN_ADC0_AIN9     PIN_PB5
#define PIN_ADC0_AIN10    PIN_PB6
#define PIN_ADC0_AIN11    PIN_PB7

#define PIN_AIN0          PIN_PA1
#define PIN_AIN1          PIN_PA2

#define PIN_AC0_AINN      PIN_PA1
#define PIN_AC0_AINP      PIN_PA2

#define PIN_SS            PIN_PC0
#define PIN_SCK           PIN_PC1
#define PIN_MISO          PIN_PC2
#define PIN_MOSI          PIN_PC4
#define PIN_SDI0_SS       PIN_PC0
#define PIN_SDI0_SCK      PIN_PC1
#define PIN_SDI0_MISO     PIN_PC2
#define PIN_SDI0_MOSI     PIN_PC4

#define PIN_SCL           PIN_PC1
#define PIN_SDA           PIN_PC4
#define PIN_TWI0_SCL      PIN_PC1
#define PIN_TWI0_SDA      PIN_PC4

#define PIN_CLKI          PIN_PC5
#define PIN_CLKO          PIN_PC2
#define PIN_INT0          PIN_PC2

/* peripheral symbols */

#define HAVE_AC0          ANA_COMP_vect_num
#define HAVE_ADC0         ADC_vect_num
#define HAVE_INT0         INT0_vect_num
#define HAVE_PORTA        PCINT0_vect_num
#define HAVE_PORTB        PCINT1_vect_num
#define HAVE_PORTC        PCINT2_vect_num
/* #define HAVE_QTRIP         QTRIP_vect_num */
#define HAVE_SPI0         SPI_vect_num
#define HAVE_TCA0         TIM0_OVF_vect_num
#define HAVE_TCA1         TIM1_CAPT_vect_num
#define HAVE_TWI0         TWI_SLAVE_vect_num
#define HAVE_WDT          WDT_vect_num

#ifdef __cplusplus
extern "C" {
#endif

#if !defined (__ASSEMBLER__)
inline void initVariant (void) {
  _CLKCTRL_SETUP();
  PORTCTRL_CTRLA = PORTCTRL_DID1_gm;  /* Digital Input Disable all pin */
  PORTCTRL_CTRLB = PORTCTRL_DID0_gm;  /* Digital Input Disable all pin */
}
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

/* end of code */
