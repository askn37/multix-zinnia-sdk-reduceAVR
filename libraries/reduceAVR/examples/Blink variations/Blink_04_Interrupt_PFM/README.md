# Blink_04_Interrupt_PFM.ino

このサンプルスケッチは以下について記述している；

- __[reduceAVR]__ 2種の周期割込による"Blink"実演（ホタル明滅）

## 対象AVR

- reduceAVR
  - ATtiny4/5/9/10/20/102/104 (ATtiny40以外)

## Blinkの要件

- 約1秒経過毎に出力信号を正負反転（Duty比50%の 0.5Hz周波数信号出力）
- 出力信号で LEDを消灯・点灯
- 以上を継続動作

## スケッチ記述

```c
/* Using Macro/Micro API */

void setup (void) {
  pinModeMacro(LED_BUILTIN, OUTPUT);

  TCB0_INTCTRL = TCB_CMPA_EN_bm;
  TCB0_CMPA = F_CPU / 3490; /* 数値は個体差に応じて要調整 */
  TCB0_CTRLA = (TCB_WGMODE_CTC_CMPA_gc & TCB_WGMODE_LOW_gm);
  TCB0_CTRLB = (TCB_WGMODE_CTC_CMPA_gc & TCB_WGMODE_HIGH_gm) | TCB_CLKSEL_CLKDIV64_gc;

  _PROTECTED_WRITE(WDT_CTRLA, WDT_IE_bm | WDT_PERIOD_2CLK_gc);
  set_sleep_mode(SLEEP_MODE_IDLE);
  sleep_enable();
}

ISR(TCB0_CMPA_vect) {
  digitalWriteMacro(LED_BUILTIN, TOGGLE);
}

ISR_ALIAS(WDT_vect, TCB0_CMPA_vect);

void loop (void) {
  sleep_cpu();
}
```

## 解説

ここでは`ATtiny4/5/9/10/20/102/104`系列の2種類の周期割込機能を使ってハートビート"Lチカ"を実演する。

周期割込には`TCB0`計時器によるものと`WDT`周期割込によるものとが使えるので、これを両方使って微妙に位相差のある割込間隔を作り、それを合成することで擬似的に`PFM`信号を生成している。

`WDT`周期割込の最短間隔は`約64Hz`なので`TCB0`の設定もこれに合わせて調整する。動作モードは`TCB_WGMODE_CTC_CMPA`とし、`TCB0_CMPA`の比較一致で`TCB0_COMPA_vect`割込ハンドラが起動するように`TCB_CMPA_EN_bm`フラグを`TCB0_INTCTRL`レジスタに与えている。

ふたつの割込ハンドラ`TCB0_COMPA_vect`と`WDT_vect`の動作内容は同じなので、`ISR_ALIAS`マクロを使って両者がおなじになるようにしている。

> `ISR_ALIAS`を使うことで割込ハンドラを個別に書くよりも生成コード量を節約している。

## 著作表示

Twitter: [@askn37](https://twitter.com/askn37) \
GitHub: [https://github.com/askn37/](https://github.com/askn37/) \
Product: [https://askn37.github.io/](https://askn37.github.io/)

Copyright (c) askn (K.Sato) multix.jp \
Released under the MIT license \
[https://opensource.org/licenses/mit-license.php](https://opensource.org/licenses/mit-license.php) \
[https://www.oshwa.org/](https://www.oshwa.org/)
