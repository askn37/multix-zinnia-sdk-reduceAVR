/**
 * @file Blink_02_TIM0_PWM.ino
 * @author askn (K.Sato) multix.jp
 * @brief Blink using delay timer sketch code
 * @version 0.1
 * @date 2022-09-29
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
  pinModeMacro(PIN_TCB0_WOB, OUTPUT);

  TCB0_CMPA = F_CPU / 1024 - 1;
  TCB0_CTRLA = (TCB_WGMODE_CTC_CMPA_gc & TCB_WGMODE_A_gm) | TCB_WOB_TOGGLE_gc;
  TCB0_CTRLB = (TCB_WGMODE_CTC_CMPA_gc & TCB_WGMODE_B_gm) | TCB_CLKSEL_CLKDIV1024_gc;

  set_sleep_mode(SLEEP_MODE_IDLE);
  sleep_enable();
}

void loop (void) {
  sleep_cpu();
}

// end of code
