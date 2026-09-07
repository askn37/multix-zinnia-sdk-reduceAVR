# TinyUART.ino

このサンプルスケッチは以下について記述している；

- __[reduceAVR]__ 単純な組込ハードウェア実装UARTの実演（ATtiny102/104専用）

## 対象AVR

- reduceAVR
  - ATtiny102/104

## 用例

以下は ATtiny102/104 の組込ハードウェア実装 UARTを用いて入力された文字列を送信元に送り返すだけの、単純なエコーバック実演例だ。

```c
#include <TinyUART.h> /* Serial <- Serial0 でセットアップされる */
void setup (void) {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(CONSOLE_BAUD);
}
void loop (void) {
  if (Serial.available() > 0) {
    char _data = Serial.read();
    if (_data == '\n') digitalWrite(LED_BUILTIN, TOGGLE);
    Serial.write(_data);
  }
}
```

対象品種は __Macro/MicoroAPI__ が有効な場合、スケッチ冒頭で`#include <TinyUART.h>`を記述することで、`Serial`インスタンスが利用可能になる。
この機能は割込ベクターも蓄積バッファも使用しない。`write/read` が呼ばれた際に 1バイトずつのポーリングで ホストPC とのデータ送受信を行う。

それでも、Flashコード空間は 約 400バイトを消費する。つまり 1KiB の全 Flash空間の、4割を占める。

## ATtiny102/104 での制約と注意点

これらの品種は SRAM を 32バイトしか有していない。

このため、使用可能なメソッドは以下に限られる。

- `begin` `end` `status`
- `write` `read` `puts` `flush` `available` `availableForWrite`
- `puts` のエイリアスとしての `print` `println` `ln`

実装はされているが、事実上、使用できない。

- `readBytes` `peek` `initiate`

`F()`および`P()`マクロは何もしない。全ての Flashメモリ空間は直接、一般データ空間の一角（`.data`中の`.rodata`セクション）に見えている。

`begin`に与える`CONSOLE_BAUD`定数値は最大`500000L`まで許されるが、内蔵発信機の精度／安定性に強く依存し、実用的に選択できる定義値は少ない。一般的使用範囲では、ほぼ`9600L`一択となる。

`initiate`に与える定数値の定義精度は、modernAVR系と異なる。故に`Portmux.h`で定義されている`UART_*`定数値は直接指定できない。

## 著作表示

Twitter: [@askn37](https://twitter.com/askn37) \
BlueSky Social: [@multix.jp](https://bsky.app/profile/multix.jp) \
GitHub: [https://github.com/askn37/](https://github.com/askn37/) \
Product: [https://askn37.github.io/](https://askn37.github.io/)

Copyright (c) askn (K.Sato) multix.jp \
Released under the MIT license \
[https://opensource.org/licenses/mit-license.php](https://opensource.org/licenses/mit-license.php) \
[https://www.oshwa.org/](https://www.oshwa.org/)
