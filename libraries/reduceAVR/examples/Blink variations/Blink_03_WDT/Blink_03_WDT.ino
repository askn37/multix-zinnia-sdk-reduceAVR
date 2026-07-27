/**
 * @file Blink_03_WDT.ino
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

void setup (void) {
  pinModeMacro(LED_BUILTIN, OUTPUT);

  _PROTECTED_WRITE(WDT_CTRLA, WDT_IE_bm | WDT_PERIOD_128CLK_gc);

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
}

ISR(WDT_vect) {
  digitalWriteMacro(LED_BUILTIN, TOGGLE);
}

void loop (void) {
  sleep_cpu();
}

// end of code
