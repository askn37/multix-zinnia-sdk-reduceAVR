/**
 * @file Blink_04_Interrupt_PFM.ino
 * @author askn (K.Sato) multix.jp
 * @brief Blink using delay timer sketch code
 * @version 0.1
 * @date 2022-12-29
 *
 * @copyright Copyright (c) 2022
 *
 */

/* Using Macro/Micro API */

#if !defined(HAVE_TCB0)
#error 16-bit timer is not implemented
#include BUILDSTOP
#endif

void setup (void) {
  pinModeMacro(LED_BUILTIN, OUTPUT);

  TCB0_INTCTRL = TCB_CMPA_bm;
  TCB0_CMPA = F_CPU / 3490;
  TCB0_CTRLA = (TCB_WGMODE_CTC_CMPA_gc & TCB_WGMODE_A_gm);
  TCB0_CTRLB = (TCB_WGMODE_CTC_CMPA_gc & TCB_WGMODE_B_gm) | TCB_CLKSEL_CLKDIV64_gc;

  _PROTECTED_WRITE(WDT_CTRLA, WDT_IE_bm | WDT_PERIOD_2CLK_gc);
  set_sleep_mode(SLEEP_MODE_IDLE);
  sleep_enable();
}

ISR(TCB0_CMPA_vect) {
  digitalWriteMacro(LED_BUILTIN, TOGGLE);
}

ISR_ALIAS(WDT_vect, TCB0_CMPA_vect);

void loop (void) {
  sleep_cpu();
}

// end of code
