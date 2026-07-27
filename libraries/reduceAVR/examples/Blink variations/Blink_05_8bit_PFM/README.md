# Blink_05_8bit_PFM.ino

このサンプルスケッチは以下について記述している；

- __[reduceAVR]__ 2種の周期割込による"Blink"実演（ホタル明滅）Rev.B

## 対象AVR

- reduceAVR
  - ATtiny20/40

## Blinkの要件

- 1秒経過毎に出力信号を正負反転（Duty比50%の 0.5Hz周波数信号出力）
- 出力信号で LEDを消灯・点灯
- 以上を継続動作

## スケッチ記述

```c
/* Using Macro/Micro API */

void setup (void) {
  pinModeMacro(LED_BUILTIN, OUTPUT);

  TCA0_INTCTRL = TCA_CMPA_bm;
  TCA0_CTRLA = (TCA_WGMODE_CTC_CMPA_gc & TCA_WGMODE_A_gm);
  TCA0_CTRLB = (TCA_WGMODE_CTC_CMPA_gc & TCA_WGMODE_B_gm) | TCA_CLKSEL_CLKDIV1024_gc;

  _PROTECTED_WRITE(WDT_CTRLA, WDT_IE_bm | WDT_PERIOD_2CLK_gc);
  set_sleep_mode(SLEEP_MODE_IDLE);
  sleep_enable();
}

ISR(TCA0_CMPA_vect) {
  digitalWriteMacro(LED_BUILTIN, TOGGLE);
  if (TCA0_CMPA == 0) {
    TCA0_CMPA = TCA0_CNT - (TCA0_CNT >> 6);
  }
}

ISR_ALIAS(WDT_vect, TCA0_CMPA_vect);

void loop (void) {
  sleep_cpu();
}
```

## 解説

これは[[reduceAVR] 2種の周期割込による"Blink"実演（ホタル明滅）](https://github.com/askn37/multix-zinnia-sdk-reduceAVR/tree/main/libraries/reduceAVR/examples/Blink%20variations/Blink_04_Interrupt_PFM)を __ATTiny20/40__ 用に変形した 8-bitタイマー版だ。記述および動作内容は`TCA0`を使用する以外の差異は殆どない。

8-bitタイマーの場合、最大計数カウントは 256でかつ分解能は最大 1024であるから`F_CPU=8MHz`時の計時周波数は`約30.5Hz`となる。これは`WDT`の最大計時周波数`約64Hz`よりは長いので 8-bitカウンターでも桁溢れせずに擬似PFM信号を生成できるに足る。

比較一致レジスタ`TCA0_CMPA`（`TIM0->OCR0A`）は 8-bit幅であり 16-bit幅レジスタの読み書き順序制約を意識した記述は不要のため、初期化フラグは省略して直接のゼロ比較、さらに係数演算式も 1行で記述している。

## 著作表示

Twitter: [@askn37](https://twitter.com/askn37) \
GitHub: [https://github.com/askn37/](https://github.com/askn37/) \
Product: [https://askn37.github.io/](https://askn37.github.io/)

Copyright (c) askn (K.Sato) multix.jp \
Released under the MIT license \
[https://opensource.org/licenses/mit-license.php](https://opensource.org/licenses/mit-license.php) \
[https://www.oshwa.org/](https://www.oshwa.org/)
