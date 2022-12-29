/**
 * @file Blink_04_Interrupt_PFM.ino
 * @author askn (K.Sato) multix.jp
 * @brief Blink using delay timer sketch code
 * @version 0.1
 * @date 2022-09-29
 *
 * @copyright Copyright (c) 2022
 *
 */

/* Using Macro/Micro API */

void setup (void) {
  pinModeMacro(LED_BUILTIN, OUTPUT);

  TIM0_INTCTRL = TIM_CMPA_EN_bm;
  TIM0_CMPA = F_CPU / 3910;
  TIM0_CTRLA = TIM_WGMODE_CTC_CMPA_L_gc;
  TIM0_CTRLB = TIM_WGMODE_CTC_CMPA_H_gc | TIM_CLKSEL_CLKDIV64_gc;

  _PROTECTED_WRITE(WDT_CTRLA, WDT_IE_bm| WDT_PERIOD_2CLK_gc);
  set_sleep_mode(SLEEP_MODE_IDLE);
  sleep_enable();
}

ISR(TIM0_COMPA_vect) {
  digitalWriteMacro(LED_BUILTIN, TOGGLE);
}

ISR_ALIAS(WDT_vect, TIM0_COMPA_vect);

void loop (void) {
  sleep_cpu();
}

// end of code
