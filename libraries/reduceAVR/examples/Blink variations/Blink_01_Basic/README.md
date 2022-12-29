# Blink_01_Basic.ino

このサンプルスケッチは以下について記述している；

- __[reduceAVR]__ 遅延ループ時間待機による"Blink"実演

## 対象AVR

- megaAVR世代
  - megaAVR-0系統
  - tinyAVR-0/1系統
- modernAVR世代
  - AVR Dx系統
  - tinyAVR-2系統
- reduceAVR
  - ATtiny4/5/9/10

## Blinkの要件

- 1秒経過毎に出力信号を正負反転（Duty比50%の 0.5Hz周波数信号出力）
- 出力信号で LEDを消灯・点灯
- 以上を継続動作

## スケッチ記述

```c
void setup (void) {
  pinModeMacro(LED_BUILTIN, OUTPUT);
}

void loop (void) {
  digitalWriteMacro(LED_BUILTIN, TOGGLE);
  delay_millis(1000);
}
```

## 解説

通常のArduino互換APIでの```delay()```機能は（ほとんどの場合）
計時器と割込よるマイクロ秒/ミリ秒計数で実装されている。

ここではもっと原始的な遅延ループを使用する。
この実装は次のようなものだ。

```c
void delay_millis (uint32_t _ms) {
  __builtin_avr_delay_cycles((F_CPU * _ms) / 1000L);
}
```

```__builtin_avr_delay_cycles(uint32_t)```は
AVR-GCC固有のAVR関数で、指定した数量のCPUサイクルを単に消費するコードを生成する。

遅延ループは制御されているものの、CPUは他に何をするでもなく時間だけを消費する。
その代わり他にいかなるメカニズムも必要としない単純作業なので、
ATtiny10 のような機能制約の多い MCUでも簡単かつ問題なく使用できる。

## 著作表示

Copyright (c) 2020 Kazuhiko Sato (askn) \
Released under the MIT license \
[https://opensource.org/licenses/mit-license.php](https://opensource.org/licenses/mit-license.php) \
[https://www.oshwa.org/](https://www.oshwa.org/)
