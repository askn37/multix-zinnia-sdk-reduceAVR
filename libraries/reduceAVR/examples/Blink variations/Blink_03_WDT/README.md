# Blink_03_WDT.ino

このサンプルスケッチは以下について記述している；

- __[reduceAVR]__ WDT周期割込による"Blink"実演

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
```

## 解説

ここでは`ATtiny10`系列の`WDT`周期割込機能を使って"Lチカ"を実演する。

`ATtiny10`の場合、時間を生成できる計時器は`TIM0`と`WDT`のふたつだ。
`WDT`本来の役割は CPUの死活監視だが、それに使わないのであれば汎用の
周期割込計時機として使用できる。
かつ、この機能は CPU休止状態に関わらず動作し続ける。

> `SLEEP_MODE_PWR_DOWN`であっても周期割込動作を続ける。

`WDT`は`CLK_PER`とは別の独自の周波数発振器で動作しており、周期割込の基準周波数は`約128Hz`だ。
これに分周比を`(0|2|4|8|16|32|64|128|256|512|1024)`から選ぶことができるため、
約16ミリ秒から約8秒の割込周期が得られる。

> `WDT`動作周波数は`CLK_PER`とは別でかつ個体差や動作温度による誤差変動が大きい。
周期割込時間はおおよその目安である。

ここでは割込周期が1秒になる`WDT_PERIOD_128CLK_gc`を選択し、
割込動作許可指定`WDT_IE_bm`と共に`WDT_CTRLA`レジスタに書くことで、
割込ハンドラ内で`LED_BUILTIN`出力を`TOGGLE`させている。

## 著作表示

Copyright (c) 2020 Kazuhiko Sato (askn) \
Released under the MIT license \
[https://opensource.org/licenses/mit-license.php](https://opensource.org/licenses/mit-license.php) \
[https://www.oshwa.org/](https://www.oshwa.org/)
