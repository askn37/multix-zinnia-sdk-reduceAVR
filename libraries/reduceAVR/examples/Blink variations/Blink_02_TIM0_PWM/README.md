# Blink_02_TIM0_PWM.ino

このサンプルスケッチは以下について記述している；

- __[reduceAVR]__ タイマー出力による"Blink"実演

## 対象AVR

- reduceAVR
  - ATtiny4/5/9/10

## Blinkの要件

- 1秒経過毎に出力信号を正負反転（Duty比50%の 0.5Hz周波数信号出力）
- 出力信号で LEDを消灯・点灯
- 以上を継続動作

## スケッチ記述

```c
/* Using Macro/Micro API */
void setup (void) {
  pinModeMacro(PIN_PB1, OUTPUT);

  TIM0_CMPA = F_CPU / 1024 - 1;
  TIM0_CTRLA = TIM_WGMODE_CTC_CMPA_L_gc | TIM_CPMODE_OC0B_TOGGLE_gc;
  TIM0_CTRLB = TIM_WGMODE_CTC_CMPA_H_gc | TIM_CLKSEL_CLKDIV1024_gc;

  set_sleep_mode(SLEEP_MODE_IDLE);
  sleep_enable();
}

void loop (void) {
  sleep_cpu();
}
```

## 解説

ここでは`ATtiny10`系列の 16bit計数器`TIM0`の比較一致機能を使って"Lチカ"を実演する。
`TIM0`は`OC0A`と`OC0B`の2種類の生成信号を直接
外部端子`PIN_PB0`と`PIN_PB1`に出力する機能があるので、これを利用する。

> `LED_BUILTIN`が`PIN_PB[01]`以外を指している場合、これは使えないことに注意。

`TIM0`の動作モードは、その設定値の下位／上位値を
`TIM0_CTRLA`と`TIM0_CTRLB`の
ふたつのレジスタに別けて指定しなければならない。
比較一致値に`TIM0_CMPA`レジスタを選んだ場合、
該当する比較一致モードは`TIM_WGMODE_CTC_CMPA_[HL]_gc`なので、
これをそれぞれに書く。

出力外部端子は`TIM0_CTRLA`に`TIM_CPMODE_OC0[AB]_*`を書くことで指定できる。
該当する外部端子は別途、出力方向に指定されていなければならない。
ここでは`OC0B=PIN_PB1`出力を選び、比較一致毎に`TOGGLE`動作をさせる。

`TIM0`の分周比は`(0|1|8|64|256|1024)`から指定でき、
これを`TIM0_CTRLB`に書くことで計数動作が開始される。

> `ATTiny10`系列の場合他品種のような`EN`ビットではなく、
分周比指定フィールドに`0`を書くことで`TIM0`動作を`OFF`にする。

ここでは分周比`DIV1024`を選んだ。
信号出力は`TOGGLE`なので、比較一致は1秒に1回発生すれば良いのだから
`(F_CPU / 1024 - 1)`を`TIM0_CMPA`に書くものとする。

以上で動作を始めた`TIM0`計数器はもはや CPUに依存しないので、
このコードの最後では必要なくなった CPU動作を`IDLE`休止状態として休眠させている。

> `STANDBY`休止状態では`TIM0`の動作も休眠する。

## 著作表示

Twitter: [@askn37](https://twitter.com/askn37) \
GitHub: [https://github.com/askn37/](https://github.com/askn37/) \
Product: [https://askn37.github.io/](https://askn37.github.io/)

Copyright (c) askn (K.Sato) multix.jp \
Released under the MIT license \
[https://opensource.org/licenses/mit-license.php](https://opensource.org/licenses/mit-license.php) \
[https://www.oshwa.org/](https://www.oshwa.org/)
