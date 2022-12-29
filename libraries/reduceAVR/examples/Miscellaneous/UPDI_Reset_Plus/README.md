# UPDI_Reset_Plus.ino

このサンプルスケッチは以下について記述している；

- __[reduceAVR]__ “UPDI Reset Plus” Firmware

## 対象AVR

- reduceAVR
  - ATtiny4/5/9/10

## 解説

これは
__[[Multix Zinnia “UPDI Reset Plus” Snap-On Circuit]](https://askn37.github.io/product/URP)__
で使われているファームウェアだ。
ハードウェア専用RESET端子が
UPDI端子と共用の tinyAVR-0/1/2 を、
FUSE書換せずとも
UPDI端子経由でリセット可能にするスナップオン基板として動作する。

同梱の`<UPDI_Reset_Plus.ino>`は内容を持たない空ファイルだが、
Arduino IDEにプログラム本体`<UPDI_Reset_Plus.cpp>`を認識させるために存在する。

プログラムの内容は単純で、
外部端子`PIN_PB2`ボタン割込によって`ATtiny10`が休止状態から起動すると、
その押し下げ状態に応じた`UPDI`命令塊を
外部端子`PIN_PB0`で送信する。
これは単純な BitBang で実装され、
それが適切な通信速度になるよう、
プログラム冒頭で`CLK_PER`を十分低い周波数速度に設定している。

> 具体的には`WDT`用128kHz発振器を主動作クロック元に選択している。

`PIN_PB0`端子の駆動はオープンドレイン動作で、
`LOW`は通常の電流引き込み動作だが
`HIGH`の電流吐き出し動作は
内蔵プルアップ抵抗を介して行われる。

`UPDI`命令塊を送信したら CPUは休止状態に戻る。
1回のボタン操作で
2回の割込が発生するため、それぞれを
`RESET状態移行`と`RESET状態解除`に使用する。

> ボタンを押し下げているあいだは両者の間隔がひらくため、
その間のターゲットはリセット状態が維持されつづける。

## 著作表示

Twitter: [@askn37](https://twitter.com/askn37) \
GitHub: [https://github.com/askn37/](https://github.com/askn37/) \
Product: [https://askn37.github.io/](https://askn37.github.io/)

Copyright (c) askn (K.Sato) multix.jp \
Released under the MIT license \
[https://opensource.org/licenses/mit-license.php](https://opensource.org/licenses/mit-license.php) \
[https://www.oshwa.org/](https://www.oshwa.org/)
