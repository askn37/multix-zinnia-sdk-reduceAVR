/**
 * @file Blink_02_TIM0_PWM.ino
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

void setup (void) {
#if (PIN_TCB0_WOB == LED_BUILTIN)
  pinModeMacro(PIN_TCB0_WOB, OUTPUT);
#elif (PIN_TCB0_WOB_ALT == LED_BUILTIN)
  pinModeMacro(PIN_TCB0_WOB_ALT, OUTPUT);
  TCB0_CTRLD |= TCB_IO_ALT_bm;
#endif

  TCB0_CCMPA = F_CPU / 1024 - 1;
  TCB0_CTRLA = (TCB_WGMODE_CTC_CCMPA_gc & TCB_WGMODE_A_gm) | TCB_WOB_TOGGLE_gc;
  TCB0_CTRLB = (TCB_WGMODE_CTC_CCMPA_gc & TCB_WGMODE_B_gm) | TCB_CLKSEL_CLKDIV1024_gc;

  set_sleep_mode(SLEEP_MODE_IDLE);
  sleep_enable();
}

void loop (void) {
  sleep_cpu();
}

// end of code
