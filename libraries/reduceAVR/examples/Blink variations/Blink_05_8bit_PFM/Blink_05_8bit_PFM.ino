/**
 * @file Blink_05_8bit_PFM.ino
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

#if !defined(HAVE_TCA0)
#error 8-bit timer is not implemented
#include BUILDSTOP
#endif

void setup (void) {
  pinModeMacro(LED_BUILTIN, OUTPUT);

  TCA0_INTCTRL = TCA_CMPA_bm;
  TCA0_CTRLA = (TCA_WGMODE_CTC_CMPA_gc & TCA_WGMODE_A_gm);
  TCA0_CTRLB = (TCA_WGMODE_CTC_CMPA_gc & TCA_WGMODE_B_gm) | TCA_CLKSEL_CLKDIV1024_gc;

  _PROTECTED_WRITE(WDT_CTRLA, WDT_IE_bm | WDT_PERIOD_2CLK_gc);
  set_sleep_mode(SLEEP_MODE_IDLE);
  sleep_enable();
}

ISR(TCA0_CMPA_vect) {
  digitalWriteMacro(LED_BUILTIN, TOGGLE);
  if (TCA0_CMPA == 0) {
    TCA0_CMPA = TCA0_CNT - (TCA0_CNT >> 6);
  }
}

ISR_ALIAS(WDT_vect, TCA0_CMPA_vect);

void loop (void) {
  sleep_cpu();
}

// end of code
