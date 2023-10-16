# MultiX Zinnia Product SDK [reduceAVR]

このソフトウェア開発キットは、
主に __Atmel ATtiny10__ について
Arduino IDEでの開発を支援するために構成されている。
AVR-GCC/AVR-LIBC を用いて書かれた C/C++/アセンブラ プログラムを
avrdude を用いて対象MCUにアップロードするまでの作業フローを提供する。

## 概要

- Arduino互換APIは提供されない。
  - ごく限られた互換性は配慮されており Blinkスケッチ（標準Lチカ）はそのままビルドできる。
  - 原則として割込や計数器/計時器周辺機能を専有せず、利用者が自由に使える。
- 安価なプログラムライタ（書込器）の利用を想定。
  - 記憶容量もピン数も極端に少ないので、外部ロジックアナライザ解析はほぼ必須。
- makeコマンドによる高度なビルド進行は提供されない。
  - Arduino IDE自体が makeコマンドに対応していない。
  - Arduino IDEによる自動ビルド進行は提供される。
  - 大規模開発には不向き。
  - むしろMakefileを書かなくて良いから割り切れて簡単。
  - 単機能テスト、スクラッチビルド、先行検証、各種実験に好適。
- 現状、ブートローダーは提供されない。
  - 対象に現在ブートローダー支援機能を持つ品種がない。
- 新規構築・再構築が簡単。
  - セットアップは数分で済む。公式IDEのように何GBも大量ダウンロードすることはない。
  - セミナー講習等での一斉大量導入に向く。

## 対応AVRアーキテクチャ

現在この SDK は複数の異なる対象アーキテクチャ向けにリポジトリを分けて提供される。

- __MultiX Zinnia Product SDK [megaAVR]__
  - megaAVR-0 と tinyAVR-0/1/2 系統。（Atmelブランド世代）
- __MultiX Zinnia Product SDK [modernAVR]__
  - AVR_DA/DB/DD/EA 系統。（Microchipブランド世代）
- __MultiX Zinnia Product SDK [reduceAVR]__
  - 旧世代AVRのうち TPI方式に対応した系統。（Atmelブランド世代）
  - ATtiny4/5/9/10

> この分割は NVM書換プロトコルおよび/すなわちブートローダーの相互共有性による。\
> 共通基盤の AVR-GCC/AVR-LIBC toolchain は既知の AVR 8bit 系全種に対応している。

## AVRrc 一覧

- __reduceAVR__ が対応するのは ATtiny4/5/9/10 のみ

|Code|ATtiny4|ATtiny5|ATtiny9|ATtiny10|ATtiny20|ATtiny40|ATtiny102|ATtiny104|
|-|-|-|-|-|-|-|-|-|
|Pkg|SOT23-6|SOT23-6|SOT23-6|SOT23-6|SOIC14|SOIC20|SOIC8|SOIC14
||UDFN8|UDFN8|UDFN8|UDFN8|TSSOP14|TSSOP20|UDFN8
||||||VQFN20|VQFN20
|Flash|512B|512B|1024B|1024B|1024B|2048B|1024B|1024B
|SRAM|32B|32B|32B|32B|128B|256B|32B|32B
|CLK|8M/12M|8M/12M|8M/12M|8M/12M|8M/12M|8M/12M|8M/12M|8M/12M
|PCINT|3(4)|3(4)|3(4)|3(4)|11(12)|17(18)|5(6)|11(12)
|INT|1|1|1|1|1|1|1|1
|TIM/TC|1|1|1|1|2|2|1|1
|PWM|2|2|2|2|2|2|2|2
|ADC|-|3(4)|-|3(4)|8|8|5|8
|AC|1+1|1+1|1+1|1+1|1+1|1+1|1+1|1+1
|WDT|1|1|1|1|1|1|1|1
|USART|-|-|-|-|-|-|1|1
|SPI|-|-|-|-|1|1|1|1
|TWI|-|-|-|-|1|1|1|1
|ICSP|TPI|TPI|TPI|TPI|TPI|TPI|TPI|TPI

- `TPI`書込 Vcc=4.5V〜5.5V
- `CLKI`入力定格最大`12MHz`（Vcc=4.5V）
- 内蔵発振器定格`8MHz`（Vcc=4.5V）または`4MHz`（Vcc=1.8V）

## 対応するホストOS

- Windows (32bit/64bit)
- macOS (64bit)
- Linux (主にintel系64bit)

## 対応する主なプログラムライタ

- [__TPI4AVR__](https://github.com/askn37/TPI4AVR) -- このSDKでの既定書込装置。
  - __HV書込__ に対応。（要外部回路）
- PICkit4 -- 公式のプログラム書込装置兼 ~~デバッグトレース~~ 装置。
  - 使用開始前に MPLAB X によるFWアップデートが要求される。購入状態での対応範囲不明。
  - フルスペックの公式開発環境が別途必須なのでエンドユーザーのPC環境によっては難がある。\
    Arduino IDEの動作スペックより数倍大きなディスク空容量やハードウェア性能とIDE操作習熟が必要。
  - reduceAVR系MCUはデバッグトレース不可能。（マシン語レベルで BREAK命令非実装）

## 導入方法

- Arduino IDE の「環境設定」「追加のボードマネージャーのURL」に以下のリンクを追加
  - [`https://askn37.github.io/package_multix_zinnia_index.json`](https://askn37.github.io/package_multix_zinnia_index.json)
- 「ボードマネージャー」ダイアログパネルを開き、検索欄に "multix" と入力
- 目的のアーキテクチャを選択して「インストール」\
  `reduceAVR`

### Developer Preview

- 上記リンクは更新がある程度まとまってから差し替えられるため、公開リポジトリより古い場合がある。
なる早で Arduino IDE に更新を取り込みたい場合は、下記リンクを使用されたい。
  - [`https://askn37.github.io/package_multix_zinnia_index_preview.json`](https://askn37.github.io/package_multix_zinnia_index_preview.json)

## ボード選択メニュー

SDK種別と対象ブートローダー使用の有無をここで選ぶ。

- __MultiX Zinnia Product SDK [reduceAVR]__
  - ATtiny4/5/9/10

## ボード選択サブメニュー

Arduino IDE でこのSDKを選択すると、
サブメニューでは以下のオプションが選択可能となる；

> FUSE設定の変更は 書換器使用時に反映。ブートローダー書込時は変更不能。

- __Variant__ -- 具体的な製品型番を選択。（必須）
  - 外囲器ピン数＋型番＋フラッシュメモリ量＋SRAM量別になっている。
- __Clock__ -- 主装置動作基準周波数選択（F_CPUマクロ初期値） -- 既定値は定格内最高速度
  - F_CPUマクロを参照しないプログラムでは効果なし
  - __FUSE無関係に常時どれでも変更可能__
  - 内蔵発振器による 8MHz〜1MHz
  - WDT用副発振器による 125kHz〜500Hz
- __FUSE PB3__ -- リセットピン用途変更（FUSE設定）
  - __原則、既定値からの変更禁止（復元にはHV対応書換器が必須）__
- __Build Option__ -- DEBUGマクロ有無（任意選択）
  - Build Release -- 既定値（NDEBUG設定）
  - Build DEBUG=1
  - Build DEBUG=2
- __Build API__ -- API拡張（任意選択）
  - Macro API Enable -- 既定値
  - Macro API Disable -- 無効
    - Arduino互換APIの導入は要外部支援（本SDKサポート外）
  - Standard Library All Disable
    - フルアセンブラ記述/純粋C言語環境（LIBC無効）
- __LED_BUILTIN Select__ -- 既定LED選択
  - PIN_PB1 -- TPI4AVRの TCLK 信号端子インジケータ（既定）
  - PIN_PB2 -- TPI書込時の未使用端子（兼INT0割込端子）
- __シリアルポート選択__
  - 環境依存
- __書込装置選択__
  - TPI4AVR over UART (Standard)
  - TPI4AVR over UART (HV Recomended) -- __HV書込対応__
  - PICkit4
  - USBasp
  - AVRISP mkII

> `FUSE PB3` -> `PB3 pin=Reset`選択以外に書換えた場合の復元は __HV対応書込器が必須。__\
> `Build API{} -> `Standard Library All Disable`選択は、一切の既定コンパイル前提を除去する。
__AVRrc では単純な加減算以外はC/C++言語で計算不能になることに注意。__

## プログラム書込

### LED_BUILTIN

既定値では`PIN_PB1`となっている。
これはこの端子が`TPI`書込時の`TCLK`信号であり、書込器のインジケータLEDをユーザー制御で利用可能なことを期待している。
そうでない書込器の場合は、ボードメニューの`LED_BUILTIN Select`を操作することで`PIN_PB2`に変更できる。

### 書込器でのスケッチ書込 ```Ctrl+U``` ```⌘+U```

FUSEも同時に更新される。
Arduino IDE のシリアルコンソールを閉じる必要はない。

以下のサブメニュー設定が必須；

- シリアルポート選択（over UART 書込器の場合）
- 書込装置選択
- すべてのFUSE関連

reduceAVR系統では任意の Clock 選択が有効となる。

### ビルド出力確認 ```Ctrl+Alt+S``` ```⌘+Alt+S```

（書込み可能な場合の）スケッチフォルダに、
スケッチがビルドされた HEX ファイル、
ブートローダーも一体に結合された HEX ファイル、
逆アセンブルコードリスト、
EEPROM 初期化用 HEX ファイル
が出力される。

> スケッチがビルドエラーになる場合は何も出力されない。

### ブートローダー

reduceAVR系統は ブートローダーが支援されない。

## 更新履歴

- v0.2.6 (23/10/16)
  - `7.2-arduino.1`に更新。
  - `7.3.0-avr8-gnu-toolchain-231004`に更新。

- v0.2.4 (23/09/09)
  - `7.3.0-avr8-gnu-toolchain-230831`に更新。

- v0.2.3 (23/07/09)
  - `7.3.0-avr8-gnu-toolchain-230628`に更新。

- v0.2.2 (23/05/23)
  - `7.1-arduino.1`に更新。

- v0.2.1 (23/05/08)
  - `7.3.0-avr8-gnu-toolchain-230418`に更新。

- v0.2.0 (23/04/08)
  - `modernAVR`で`AVR_EA`対応。これに伴う`MicroAPI`の修正反映。

## 許諾

各構成要素はそれぞれ異なる配布ライセンスに属する。条件はそれぞれの規約に従う。

- BSD License
  - avr-libc
- GNU General Public License v2.0
  - avr-gcc
  - avrdude
- MIT License
  - other original document and code

## 著作表示

Twitter: [@askn37](https://twitter.com/askn37) \
GitHub: [https://github.com/askn37/](https://github.com/askn37/) \
Product: [https://askn37.github.io/](https://askn37.github.io/)

Copyright (c) askn (K.Sato) multix.jp \
Released under the MIT license \
[https://opensource.org/licenses/mit-license.php](https://opensource.org/licenses/mit-license.php) \
[https://www.oshwa.org/](https://www.oshwa.org/)
