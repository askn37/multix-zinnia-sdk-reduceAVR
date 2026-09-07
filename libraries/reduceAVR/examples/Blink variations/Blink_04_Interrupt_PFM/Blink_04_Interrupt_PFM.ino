/**
 * @file Blink_04_Interrupt_PFM.ino
 * @author askn (K.Sato) multix.jp
 * @brief Blink using delay timer sketch code
 * @version 0.4.2
 * @date 2026-07-26
 *
 * @copyright Copyright (c) 2026 askn37 at github.com
 *
 */
/* MIT License : https://askn37.github.io/LICENSE.html */

/* Using Macro/Micro API */

#if !defined(HAVE_TCB0)
#error 16-bit timer is not implemented
#include BUILDSTOP
#endif

volatile bool cmp_init = true;

void setup (void) {
  pinModeMacro(LED_BUILTIN, OUTPUT);

  TCB0_INTCTRL = TCB_CCMPA_bm;
  TCB0_CTRLA = (TCB_WGMODE_CTC_CCMPA_gc & TCB_WGMODE_A_gm);
  TCB0_CTRLB = (TCB_WGMODE_CTC_CCMPA_gc & TCB_WGMODE_B_gm) | TCB_CLKSEL_CLKDIV64_gc;

  _PROTECTED_WRITE(WDT_CTRLA, WDT_IE_bm | WDT_PERIOD_2CLK_gc);
  set_sleep_mode(SLEEP_MODE_IDLE);
  sleep_enable();
}

ISR(TCB0_CCMPA_vect) {
  digitalWriteMacro(LED_BUILTIN, TOGGLE);
  if (cmp_init) {
    cmp_init = false;
    uint16_t _temp = TCB0_CNT;
    _temp -= _temp >> 6;
    TCB0_CCMPA = _temp;
  }
}

ISR_ALIAS(WDT_vect, TCB0_CCMPA_vect);

void loop (void) {
  sleep_cpu();
}

// end of code
