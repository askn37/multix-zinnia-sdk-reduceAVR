/**
 * @file Blink_01_Basic.ino
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
}

void loop (void) {
  digitalWriteMacro(LED_BUILTIN, TOGGLE);
  delay_millis(1000);
}

// end of code
