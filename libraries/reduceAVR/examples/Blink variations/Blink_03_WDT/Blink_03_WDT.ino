/**
 * @file Blink_03_WDT.ino
 * @author askn (K.Sato) multix.jp
 * @brief Blink using delay timer sketch code
 * @version 0.1
 * @date 2022-12-29
 *
 * @copyright Copyright (c) 2022
 *
 */

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
