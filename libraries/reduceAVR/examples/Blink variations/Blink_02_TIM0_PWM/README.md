# Blink_02_TIM0_PWM.ino

このサンプルスケッチは以下について記述している；

- __[reduceAVR]__ タイマー出力による、糖衣構文を用いた"Blink"実演

## 対象AVR

- reduceAVR
  - ATtiny4/5/9/10/20/102/104 (ATtiny40以外)

## Blinkの要件

- 1秒経過毎に出力信号を正負反転（Duty比50%の 0.5Hz周波数信号出力）
- 出力信号で LEDを消灯・点灯
- 以上を継続動作

## スケッチ記述

```c
/* Using Macro/Micro API */

#if !defined(HAVE_TCB0)
#error 16-bit timer is not implemented
#include BUILDSTOP
#endif

void setup (void) {
  pinModeMacro(PIN_TCB0_WOB, OUTPUT);

  TCB0_CMPA = F_CPU / 1024 - 1;
  TCB0_CTRLA = (TCB_WGMODE_CTC_CMPA_gc & TCB_WGMODE_A_gm) | TCB_CMPB_TOGGLE_gc;
  TCB0_CTRLB = (TCB_WGMODE_CTC_CMPA_gc & TCB_WGMODE_B_gm) | TCB_CLKSEL_CLKDIV1024_gc;

  set_sleep_mode(SLEEP_MODE_IDLE);
  sleep_enable();
}

void loop (void) {
  sleep_cpu();
}
```

## 解説

ここでは **reduceAVR** 系列の内、16-bitタイマーを持つ品種の比較一致機能を使って"Lチカ"を実演する。対象となるのは以下の7品種3系統だが、**Macro/MicroAPI** の糖衣構文によって機能差が吸収され、ただ一通りのプログラム表現に帰結する。

|ATtiny|4/5/9/10|20|102/104|糖衣構文
|-|-|-|-|-|
|タイマー|TIM0|TIM1|TIM0|TCB0
|出力信号|OC0B|OC1B|OC0B|TCB0_WOB
|出力ピン|PB1|PB2|PA1|PIN_TCB0_WOB

> [!TIP]
> **reduceAVR** 用糖衣構文の多くは、**modernAVR** 世代の新しい`<avr/io.h>`記法に準じている。従って後者を既に学習しているならば前者への応用は比較的容易い。

16-bitタイマーの実態は品種によって`TIM0`または`TIM1`いずれかのモジュールだが、レジスタ設定の構造は変わらないため、糖衣構文（マクロ）により`TCB0`の代表名で利用できる。同様にタイマー出力信号名`OC0B`または`OC1B`の違いも代表名`TCB0_WOB`となる。

> [!TIP]
> 代表名`TCB0`が使用可能なら`HAVE_TCB0`マクロが定義されるので、これを判定すればコンパイルを早期中断することができる。

一方で糖衣構文の守備範囲は物理ピン配置までは及ばない。出力ピン名を表す代表名`PIN_TCB0_WOB`は`PB1`、`PB2`、`PA1`の何れかを表すのみである。故に LED への配線先は品種によって個別に対応しなければならない。

以下は Macro/MicroAPI 糖衣構文の使用可否による ATtiny10 でのコード記述の比較を示す。`-Os`最適化によるコンパイル結果は **いずれも同じ** になる。しかし`<avr/io.h>` *のみでの正しい記法* はアセンブラコードをそのまま引き写した表現になるのに対し、`<api/macro_api.h>` では記述が冗長になる一方で *成そうとしていることの意味* が明瞭になる。

```diff
- #include <avr/io.h>
+ #include <api/macro_api.h>

- PORTCR |= _BV(BBMB); DDRB |= _BV(PINB1); DIDR0 &= ~_BV(ADC1D);
+ pinModeMacro(PIN_TCB0_WOB, OUTPUT);

- OCR0A = F_CPU / 1024 - 1;
+ TCB0_CMPA = F_CPU / 1024 - 1;

- TCCR0A = /* _BV(WGM01) | */ /* _BV(WGM00) | */ _BV(COM0B0);
+ TCB0_CTRLA = (TCB_WGMODE_CTC_CMPA_gc & TCB_WGMODE_LOW_gm)  | TCB_WOB_TOGGLE_gc;

- TCCR0B = /* _BV(WGM03) | */ _BV(WGM02) | _BV(CS02) | /* _BV(CS01) | */ _BV(CS00);
+ TCB0_CTRLB = (TCB_WGMODE_CTC_CMPA_gc & TCB_WGMODE_HIGH_gm) | TCB_CLKSEL_CLKDIV1024_gc;
```

タイマーの出力波形設定`WGMODE`ビット群はふたつの設定レジスタに分割して記述するため、`<avr/io.h>`構文では設定変更の際の個別ビットのコメントイン／アウトも煩雑だ。糖衣構文ではこれを機能名で表す定数とANDマスクの組に置き換えることができる。

ここで`WGMODE`は`CTC_CMPA`つまり「`CNT`値は`CMPA`値と一致するまでカウントし、のちゼロクリア(CTC)されて再カウント継続」モードを選択した。その比較一致が成立するのと同期して`WOB`出力をトグル反転させたいので`WOB_TOGGLE`定数を設定する。

タイマーの分解能（主クロック`F_CPU`に対する分周比）は`CLKSEL_CLKDIV*`定数で与えられる。ここでは`1/1024`を選択した。よってカウント比較レジスタ`CMPA`には`F_CPU/1024-1`をセットする。これにより1秒に1回の比較割込要求要件を満たす。

以上で動作を始めた`TCB0`計数器はもはや MPUの走行に依存せず自律的に動作するため、最後では必要なくなった MPU動作を`IDLE`休止状態（`STANDBY`でも`PWR_DOWN`でもない）として休眠させている。

## 著作表示

Twitter: [@askn37](https://twitter.com/askn37) \
GitHub: [https://github.com/askn37/](https://github.com/askn37/) \
Product: [https://askn37.github.io/](https://askn37.github.io/)

Copyright (c) askn (K.Sato) multix.jp \
Released under the MIT license \
[https://opensource.org/licenses/mit-license.php](https://opensource.org/licenses/mit-license.php) \
[https://www.oshwa.org/](https://www.oshwa.org/)
