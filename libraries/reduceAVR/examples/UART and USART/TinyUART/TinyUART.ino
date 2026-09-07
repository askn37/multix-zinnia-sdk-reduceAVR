/**
 * @file TinyUART.ino
 * @author askn (K.Sato) multix.jp
 * @brief
 * @version 0.1
 * @date 2026-09-05
 * @copyright Copyright (c) 2026 askn37 at github.com
 * @link Product Potal : https://askn37.github.io/
 *         MIT License : https://askn37.github.io/LICENSE.html
 */

#include <TinyUART.h> /* Serial0 にセットアップされる */
#include <reboot.h>   /* WDT RESET の制御補助 */

void setup (void) {

#if defined(SW_BUILTIN) && (SW_BUILTIN == PIN_INT0)
  /* SW_BUILTIN があるなら、RESETに利用する */
  pinMode(SW_BUILTIN, INPUT_PULLUP);
  EXTINT_CTRLA = EXTINT_EDGE_FALLING_gc;
  EXTINT_INTCTRL = EXTINT_INT0_bm;
#endif

  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);

  /* 基本的に write/puts 系しか使えない */
  Serial.begin(CONSOLE_BAUD);
  Serial.println(F("\n<startup>"));
  Serial.print(F("_AVR_IOXXX_H_=")).println(_AVR_IOXXX_H_);
  Serial.flush();
}

void loop (void) {
  if (Serial.available() > 0) {
    char _data = Serial.read();
    if (_data == '\n') digitalWrite(LED_BUILTIN, TOGGLE);
    Serial.write(_data);
  }
}

#if defined(SW_BUILTIN) && (SW_BUILTIN == PIN_INT0)
/* SW_BUILTIN を押したら再起動 */
ISR(INT0_vect, ISR_NAKED) {
  reboot();
}
#endif

// end of code
