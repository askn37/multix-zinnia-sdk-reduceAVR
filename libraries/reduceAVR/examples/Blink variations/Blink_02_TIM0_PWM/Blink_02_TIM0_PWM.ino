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

void setup (void) {
  /* Enable OC0B = PIN_PB1 */
  pinModeMacro(PIN_PB1, OUTPUT);

  /* Enable TIM0 output OC0B Divider 1024 */
  TIM0_CMPA = F_CPU / 1024 - 1;
  TIM0_CTRLA = TIM_WGMODE_CTC_CMPA_L_gc | TIM_CPMODE_OC0B_TOGGLE_gc;
  TIM0_CTRLB = TIM_WGMODE_CTC_CMPA_H_gc | TIM_CLKSEL_CLKDIV1024_gc;

  set_sleep_mode(SLEEP_MODE_IDLE);
  sleep_enable();
}

void loop (void) {
  sleep_cpu();
}

// end of code
