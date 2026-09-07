/**
 * @file reboot.c
 * @author askn (K.Sato) multix.jp
 * @brief
 * @version 0.1
 * @date 2026-09-05
 * @copyright Copyright (c) 2026 askn37 at github.com
 * @link Product Potal : https://askn37.github.io/
 *         MIT License : https://askn37.github.io/LICENSE.html
 */

#include "reboot.h"

#if defined(__AVR_TINY__)

__attribute__((used, naked, section(".init1")))
void _DISABLE_WDT_ (void) {
  bit_clear(RSTCTRL_RSTFR, RSTCTRL_WDRF_bp);
  _PROTECTED_WRITE(WDT_CTRLA, 0);
}

void reboot (void) {
  _PROTECTED_WRITE(WDT_CTRLA, WDT_SREN_bm | WDT_PERIOD_2CLK_gc);
  for (;;);
}

#endif

// end of code
