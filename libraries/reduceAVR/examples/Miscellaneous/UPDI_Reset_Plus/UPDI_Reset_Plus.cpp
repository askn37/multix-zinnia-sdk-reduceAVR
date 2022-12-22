/**
 * @file UPDI_Reset_Plus.cpp
 * @author askn (K.Sato) multix.jp
 * @brief
 * @version 0.1
 * @date 2022-12-12
 *
 * @copyright Copyright (c) 2022
 *
 */
// #include <variant.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#define CLKPSR_CLKDIV1_bm 0

// Prototypes
namespace {
/*****
 * UPDI Reset sequence
 *
 * BREAK            ($000)
 * BREAK            ($000)
 * IDLE             ($FFF)
 * SYNCH            ($55)
 * STCS|ASI_RST_REQ ($C8)
 * RSTREQ           ($59/$00)
 * STCS|CTRLB       ($C3)
 * UPDIDIS          ($04)
 */
  const uint8_t bitmap[2][12] = {{  /* 12 * 8 == 8 * 12 == 96 bit, LSB first */
  /* RESET Enable */
  /* |BREAK          |BREAK              |IDLE           |$55              */
    0b00000000, 0b00000000, 0b00000000, 0b11111111, 0b11110101, 0b01010011,
  /* |$C8            |$59                |$C3            |$04              */
    0b00001001, 0b11110100, 0b11010011, 0b01100001, 0b10110001, 0b00000111
  },{
  /* RESET Disable */
  /* |BREAK          |BREAK              |IDLE           |$55              */
    0b00000000, 0b00000000, 0b00000000, 0b11111111, 0b11110101, 0b01010011,
  /* |$C8            |$00                |$C3            |$04              */
    0b00001001, 0b11110000, 0b00000011, 0b01100001, 0b10110001, 0b00000111
  }};
  void setup (void);
  void loop (void);
  void updi_reset (bool mode);
}

namespace {
  inline void setup (void) {
    /* Master clock is 128 kHz setup */
    CCP = 0xD8; CLKMSR = _BV(CLKMS0);
    CCP = 0xD8; CLKPSR = CLKPSR_CLKDIV1_bm;

    /* PORTB2 is INPUT and pullup and interrupt */
    PUEB  = _BV(PUEB0) | _BV(PUEB1) | _BV(PUEB2) | _BV(PUEB3);
    EICRA = _BV(ISC00);
    EIMSK = _BV(INT0);

    /* sleep settings */
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
  }

/* main loop */
  inline void loop (void) {
    /* interrupt input pin check */
    updi_reset(PINB & _BV(PINB2));

    /* sleep */
    sei();
    sleep_cpu();
    cli();
  }

  /* output squence */
  inline void updi_reset (bool mode) {
    for (uint8_t i = 0; i < 96; i++) {
        uint8_t d = (bitmap[mode][i >> 3]) << (i & 7);
        if (d & 0x80) PORTB |=   _BV(PORTB0);
        else          PORTB &= ~(_BV(PORTB0));
    }
  }
}

/* interrupt vector is empty */
EMPTY_INTERRUPT(INT0_vect);

/* main function */
// __attribute__((used,naked,section(".init9")))
int main (void) {
  setup();
  for (;;) loop();
}

// end of code

