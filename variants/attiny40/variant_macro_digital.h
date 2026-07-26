/**
 * @file variant_macro_digital.h
 * @author askn (K.Sato) multix.jp
 * @brief Macro/Micro API digital pin control
 * @version 0.1
 * @date 2024-05-27
 *
 * @copyright Copyright (c) 2024 askn37 at github.com
 *
 */
// MIT License : https://askn37.github.io/LICENSE.html

#pragma once

#define ENABLE_MACRO_DIGITAL 1

/* MACRO API */

#ifndef __CONCAT
#define __CONCAT(A,B) A##B
#endif

#ifndef __CONCAT3
#define __CONCAT3(A,B,C) A##B##C
#endif

#ifndef __CONCAT4
#define __CONCAT4(A,B,C,D) A##B##C##D
#endif

/* CONCAT macro parameter */

#define LOW           0
#define INPUT_PULLUP  250
#define TOGGLE        251
#define OUTPUT        252
#define INPUT         253
#define HIGH          254
#define NOT_A_PIN     255

/*
 * pinModeMacroMacro(PIN,INPUT|OUTPUT|INPUT_PULLUP) macro
 */
#define pinModeMacro(PIN,DIR) __CONCAT4(VPORTDIR_,PIN,_,DIR)

// pinModeMacro(PIN,INPUT) -> CBI VPORTx.DIR, y
#define VPORTDIR_192_253 do { __asm__ volatile ("CBI 0x01, 0\nCBI 0x0D, 0"); } while (0)
#define VPORTDIR_193_253 do { __asm__ volatile ("CBI 0x01, 1\nCBI 0x0D, 1"); } while (0)
#define VPORTDIR_194_253 do { __asm__ volatile ("CBI 0x01, 2\nCBI 0x0D, 2"); } while (0)
#define VPORTDIR_195_253 do { __asm__ volatile ("CBI 0x01, 3\nCBI 0x0D, 3"); } while (0)
#define VPORTDIR_196_253 do { __asm__ volatile ("CBI 0x01, 4\nCBI 0x0D, 4"); } while (0)
#define VPORTDIR_197_253 do { __asm__ volatile ("CBI 0x01, 5\nCBI 0x0D, 5"); } while (0)
#define VPORTDIR_198_253 do { __asm__ volatile ("CBI 0x01, 6\nCBI 0x0D, 6"); } while (0)
#define VPORTDIR_199_253 do { __asm__ volatile ("CBI 0x01, 7\nCBI 0x0D, 7"); } while (0)

#define VPORTDIR_200_253 do { __asm__ volatile ("CBI 0x05, 0\nCBI 0x08, 4"); } while (0)
#define VPORTDIR_201_253 do { __asm__ volatile ("CBI 0x05, 1\nCBI 0x08, 5"); } while (0)
#define VPORTDIR_202_253 do { __asm__ volatile ("CBI 0x05, 2\nCBI 0x08, 6"); } while (0)
#define VPORTDIR_203_253 do { __asm__ volatile ("CBI 0x05, 3\nCBI 0x08, 7"); } while (0)

#define VPORTDIR_208_253 do { __asm__ volatile ("CBI 0x1C, 0");              } while (0)
#define VPORTDIR_209_253 do { __asm__ volatile ("CBI 0x1C, 1");              } while (0)
#define VPORTDIR_210_253 do { __asm__ volatile ("CBI 0x1C, 2");              } while (0)
#define VPORTDIR_211_253 do { __asm__ volatile ("CBI 0x1C, 3");              } while (0)
#define VPORTDIR_212_253 do { __asm__ volatile ("CBI 0x1C, 4");              } while (0)
#define VPORTDIR_213_253 do { __asm__ volatile ("CBI 0x1C, 5");              } while (0)

#define VPORTDIR__
#define VPORTDIR__253
#define VPORTDIR_255_
#define VPORTDIR_255_253

// pinModeMacro(PIN,OUTPUT) -> Break-Before-Make Mode Enable -> SBI VPORTx.DIR, y
#define VPORTDIR_192_252 do { __asm__ volatile ("SBI 0x08, 0\nSBI 0x01, 0\nCBI 0x0D, 0"); } while (0)
#define VPORTDIR_193_252 do { __asm__ volatile ("SBI 0x08, 0\nSBI 0x01, 1\nCBI 0x0D, 1"); } while (0)
#define VPORTDIR_194_252 do { __asm__ volatile ("SBI 0x08, 0\nSBI 0x01, 2\nCBI 0x0D, 2"); } while (0)
#define VPORTDIR_195_252 do { __asm__ volatile ("SBI 0x08, 0\nSBI 0x01, 3\nCBI 0x0D, 3"); } while (0)
#define VPORTDIR_196_252 do { __asm__ volatile ("SBI 0x08, 0\nSBI 0x01, 4\nCBI 0x0D, 4"); } while (0)
#define VPORTDIR_197_252 do { __asm__ volatile ("SBI 0x08, 0\nSBI 0x01, 5\nCBI 0x0D, 5"); } while (0)
#define VPORTDIR_198_252 do { __asm__ volatile ("SBI 0x08, 0\nSBI 0x01, 6\nCBI 0x0D, 6"); } while (0)
#define VPORTDIR_199_252 do { __asm__ volatile ("SBI 0x08, 0\nSBI 0x01, 7\nCBI 0x0D, 7"); } while (0)

#define VPORTDIR_200_252 do { __asm__ volatile ("SBI 0x08, 1\nSBI 0x05, 0\nCBI 0x08, 4"); } while (0)
#define VPORTDIR_201_252 do { __asm__ volatile ("SBI 0x08, 1\nSBI 0x05, 1\nCBI 0x08, 5"); } while (0)
#define VPORTDIR_202_252 do { __asm__ volatile ("SBI 0x08, 1\nSBI 0x05, 2\nCBI 0x08, 6"); } while (0)
#define VPORTDIR_203_252 do { __asm__ volatile ("SBI 0x08, 1\nSBI 0x05, 3\nCBI 0x08, 7"); } while (0)

#define VPORTDIR_208_252 do { __asm__ volatile ("SBI 0x08, 2\nSBI 0x1C, 0"); } while (0)
#define VPORTDIR_209_252 do { __asm__ volatile ("SBI 0x08, 2\nSBI 0x1C, 1"); } while (0)
#define VPORTDIR_210_252 do { __asm__ volatile ("SBI 0x08, 2\nSBI 0x1C, 2"); } while (0)
#define VPORTDIR_211_252 do { __asm__ volatile ("SBI 0x08, 2\nSBI 0x1C, 3"); } while (0)
#define VPORTDIR_212_252 do { __asm__ volatile ("SBI 0x08, 2\nSBI 0x1C, 4"); } while (0)
#define VPORTDIR_213_252 do { __asm__ volatile ("SBI 0x08, 2\nSBI 0x1C, 5"); } while (0)

// pinModeMacro(PIN,INPUT_PULLUP) -> CBI VPORTx.DIR, y
#define VPORTDIR_192_250 do { __asm__ volatile ("CBI 0x01, 0\nSBI 0x03, 0\nCBI 0x0D, 0"); } while (0)
#define VPORTDIR_193_250 do { __asm__ volatile ("CBI 0x01, 1\nSBI 0x03, 1\nCBI 0x0D, 1"); } while (0)
#define VPORTDIR_194_250 do { __asm__ volatile ("CBI 0x01, 2\nSBI 0x03, 2\nCBI 0x0D, 2"); } while (0)
#define VPORTDIR_195_250 do { __asm__ volatile ("CBI 0x01, 3\nSBI 0x03, 3\nCBI 0x0D, 3"); } while (0)
#define VPORTDIR_196_250 do { __asm__ volatile ("CBI 0x01, 4\nSBI 0x03, 4\nCBI 0x0D, 4"); } while (0)
#define VPORTDIR_197_250 do { __asm__ volatile ("CBI 0x01, 5\nSBI 0x03, 5\nCBI 0x0D, 5"); } while (0)
#define VPORTDIR_198_250 do { __asm__ volatile ("CBI 0x01, 6\nSBI 0x03, 6\nCBI 0x0D, 6"); } while (0)
#define VPORTDIR_199_250 do { __asm__ volatile ("CBI 0x01, 7\nSBI 0x03, 7\nCBI 0x0D, 7"); } while (0)

#define VPORTDIR_200_250 do { __asm__ volatile ("CBI 0x05, 0\nSBI 0x07, 0\nCBI 0x08, 4"); } while (0)
#define VPORTDIR_201_250 do { __asm__ volatile ("CBI 0x05, 1\nSBI 0x07, 1\nCBI 0x08, 5"); } while (0)
#define VPORTDIR_202_250 do { __asm__ volatile ("CBI 0x05, 2\nSBI 0x07, 2\nCBI 0x08, 6"); } while (0)
#define VPORTDIR_203_250 do { __asm__ volatile ("CBI 0x05, 3\nSBI 0x07, 3\nCBI 0x08, 7"); } while (0)

#define VPORTDIR_208_250 do { __asm__ volatile ("CBI 0x1C, 0\nSBI 0x1E, 0"); } while (0)
#define VPORTDIR_209_250 do { __asm__ volatile ("CBI 0x1C, 1\nSBI 0x1E, 1"); } while (0)
#define VPORTDIR_210_250 do { __asm__ volatile ("CBI 0x1C, 2\nSBI 0x1E, 2"); } while (0)
#define VPORTDIR_211_250 do { __asm__ volatile ("CBI 0x1C, 3\nSBI 0x1E, 3"); } while (0)
#define VPORTDIR_212_250 do { __asm__ volatile ("CBI 0x1C, 4\nSBI 0x1E, 4"); } while (0)
#define VPORTDIR_213_250 do { __asm__ volatile ("CBI 0x1C, 5\nSBI 0x1E, 5"); } while (0)

#define VPORTDIR__
#define VPORTDIR__252
#define VPORTDIR__250
#define VPORTDIR_255_
#define VPORTDIR_255_252
#define VPORTDIR_255_250

/*
 * digitalWriteMacro(PIN,LOW|HIGH|TOGGLE) macro
 */
#define digitalWriteMacro(PIN,OUT) __CONCAT4(VPORTOUT_,PIN,_,OUT)

// digitalWriteMacro(PIN,LOW) -> CBI VPORTx.OUT, y
#define VPORTOUT_192_0 do { __asm__ volatile ("CBI 0x02, 0"); } while (0)
#define VPORTOUT_193_0 do { __asm__ volatile ("CBI 0x02, 1"); } while (0)
#define VPORTOUT_194_0 do { __asm__ volatile ("CBI 0x02, 2"); } while (0)
#define VPORTOUT_195_0 do { __asm__ volatile ("CBI 0x02, 3"); } while (0)
#define VPORTOUT_196_0 do { __asm__ volatile ("CBI 0x02, 4"); } while (0)
#define VPORTOUT_197_0 do { __asm__ volatile ("CBI 0x02, 5"); } while (0)
#define VPORTOUT_198_0 do { __asm__ volatile ("CBI 0x02, 6"); } while (0)
#define VPORTOUT_199_0 do { __asm__ volatile ("CBI 0x02, 7"); } while (0)

#define VPORTOUT_200_0 do { __asm__ volatile ("CBI 0x06, 0"); } while (0)
#define VPORTOUT_201_0 do { __asm__ volatile ("CBI 0x06, 1"); } while (0)
#define VPORTOUT_202_0 do { __asm__ volatile ("CBI 0x06, 2"); } while (0)
#define VPORTOUT_203_0 do { __asm__ volatile ("CBI 0x06, 3"); } while (0)

#define VPORTOUT_208_0 do { __asm__ volatile ("CBI 0x1D, 0"); } while (0)
#define VPORTOUT_209_0 do { __asm__ volatile ("CBI 0x1D, 1"); } while (0)
#define VPORTOUT_210_0 do { __asm__ volatile ("CBI 0x1D, 2"); } while (0)
#define VPORTOUT_211_0 do { __asm__ volatile ("CBI 0x1D, 3"); } while (0)
#define VPORTOUT_212_0 do { __asm__ volatile ("CBI 0x1D, 4"); } while (0)
#define VPORTOUT_213_0 do { __asm__ volatile ("CBI 0x1D, 5"); } while (0)

// digitalWriteMacro(PIN,HIGH) -> SBI VPORTx.OUT, y
#define VPORTOUT_192_254 do { __asm__ volatile ("SBI 0x02, 0"); } while (0)
#define VPORTOUT_193_254 do { __asm__ volatile ("SBI 0x02, 1"); } while (0)
#define VPORTOUT_194_254 do { __asm__ volatile ("SBI 0x02, 2"); } while (0)
#define VPORTOUT_195_254 do { __asm__ volatile ("SBI 0x02, 3"); } while (0)
#define VPORTOUT_196_254 do { __asm__ volatile ("SBI 0x02, 4"); } while (0)
#define VPORTOUT_197_254 do { __asm__ volatile ("SBI 0x02, 5"); } while (0)
#define VPORTOUT_198_254 do { __asm__ volatile ("SBI 0x02, 6"); } while (0)
#define VPORTOUT_199_254 do { __asm__ volatile ("SBI 0x02, 7"); } while (0)

#define VPORTOUT_200_254 do { __asm__ volatile ("SBI 0x06, 0"); } while (0)
#define VPORTOUT_201_254 do { __asm__ volatile ("SBI 0x06, 1"); } while (0)
#define VPORTOUT_202_254 do { __asm__ volatile ("SBI 0x06, 2"); } while (0)
#define VPORTOUT_203_254 do { __asm__ volatile ("SBI 0x06, 3"); } while (0)

#define VPORTOUT_208_254 do { __asm__ volatile ("SBI 0x1D, 0"); } while (0)
#define VPORTOUT_209_254 do { __asm__ volatile ("SBI 0x1D, 1"); } while (0)
#define VPORTOUT_210_254 do { __asm__ volatile ("SBI 0x1D, 2"); } while (0)
#define VPORTOUT_211_254 do { __asm__ volatile ("SBI 0x1D, 3"); } while (0)
#define VPORTOUT_212_254 do { __asm__ volatile ("SBI 0x1D, 4"); } while (0)
#define VPORTOUT_213_254 do { __asm__ volatile ("SBI 0x1D, 1"); } while (0)

// digitalWriteMacro(PIN,TOGGLE) -> SBI VPORTx.IN, y
#define VPORTOUT_192_251 do { __asm__ volatile ("SBI 0x00, 0"); } while (0)
#define VPORTOUT_193_251 do { __asm__ volatile ("SBI 0x00, 1"); } while (0)
#define VPORTOUT_194_251 do { __asm__ volatile ("SBI 0x00, 2"); } while (0)
#define VPORTOUT_195_251 do { __asm__ volatile ("SBI 0x00, 3"); } while (0)
#define VPORTOUT_196_251 do { __asm__ volatile ("SBI 0x00, 4"); } while (0)
#define VPORTOUT_197_251 do { __asm__ volatile ("SBI 0x00, 5"); } while (0)
#define VPORTOUT_198_251 do { __asm__ volatile ("SBI 0x00, 6"); } while (0)
#define VPORTOUT_199_251 do { __asm__ volatile ("SBI 0x00, 7"); } while (0)

#define VPORTOUT_200_251 do { __asm__ volatile ("SBI 0x04, 0"); } while (0)
#define VPORTOUT_201_251 do { __asm__ volatile ("SBI 0x04, 1"); } while (0)
#define VPORTOUT_202_251 do { __asm__ volatile ("SBI 0x04, 2"); } while (0)
#define VPORTOUT_203_251 do { __asm__ volatile ("SBI 0x04, 3"); } while (0)

#define VPORTOUT_208_251 do { __asm__ volatile ("SBI 0x1B, 0"); } while (0)
#define VPORTOUT_209_251 do { __asm__ volatile ("SBI 0x1B, 1"); } while (0)
#define VPORTOUT_210_251 do { __asm__ volatile ("SBI 0x1B, 2"); } while (0)
#define VPORTOUT_211_251 do { __asm__ volatile ("SBI 0x1B, 3"); } while (0)
#define VPORTOUT_212_251 do { __asm__ volatile ("SBI 0x1B, 4"); } while (0)
#define VPORTOUT_213_251 do { __asm__ volatile ("SBI 0x1B, 5"); } while (0)

#define VPORTOUT__
#define VPORTOUT__0
#define VPORTOUT__254
#define VPORTOUT__251
#define VPORTOUT_255_
#define VPORTOUT_255_0
#define VPORTOUT_255_254
#define VPORTOUT_255_251

/*
 * digitalReadMacro(PIN) macro
 */
#define digitalReadMacro(PIN) __CONCAT(VPORTIN_,PIN)

// digitalReadMacro(PIN) -> VPORTx.IN & PINn_bm; } while (0)
#define VPORTIN_192 (PINA & 1)
#define VPORTIN_193 (PINA & 2)
#define VPORTIN_194 (PINA & 4)
#define VPORTIN_195 (PINA & 8)
#define VPORTIN_196 (PINA & 16)
#define VPORTIN_197 (PINA & 32)
#define VPORTIN_198 (PINA & 64)
#define VPORTIN_199 (PINA & 128)

#define VPORTIN_200 (PINB & 1)
#define VPORTIN_201 (PINB & 2)
#define VPORTIN_202 (PINB & 4)
#define VPORTIN_203 (PINB & 8)

#define VPORTIN_208 (PINC & 1)
#define VPORTIN_209 (PINC & 2)
#define VPORTIN_210 (PINC & 4)
#define VPORTIN_211 (PINC & 8)
#define VPORTIN_212 (PINC & 16)
#define VPORTIN_213 (PINC & 32)

#define VPORTIN_
#define VPORTIN_255

/*
 * openDrainWriteMacro(PIN,LOW|HIGH|TOGGLE) macro
 */
#define openDrainWriteMacro(PIN,OUT) __CONCAT4(VPORTCHG_,PIN,_,OUT)

// openDrainWriteMacro(PIN,LOW) -> pinModeMacro(PIN,OUTPUT) -> SBI VPORTx.DIR, y
#define VPORTCHG_192_0 do { __asm__ volatile ("SBI 0x01, 0"); } while (0)
#define VPORTCHG_193_0 do { __asm__ volatile ("SBI 0x01, 1"); } while (0)
#define VPORTCHG_194_0 do { __asm__ volatile ("SBI 0x01, 2"); } while (0)
#define VPORTCHG_195_0 do { __asm__ volatile ("SBI 0x01, 3"); } while (0)
#define VPORTCHG_196_0 do { __asm__ volatile ("SBI 0x01, 4"); } while (0)
#define VPORTCHG_197_0 do { __asm__ volatile ("SBI 0x01, 5"); } while (0)
#define VPORTCHG_198_0 do { __asm__ volatile ("SBI 0x01, 6"); } while (0)
#define VPORTCHG_199_0 do { __asm__ volatile ("SBI 0x01, 7"); } while (0)

#define VPORTCHG_200_0 do { __asm__ volatile ("SBI 0x05, 0"); } while (0)
#define VPORTCHG_201_0 do { __asm__ volatile ("SBI 0x05, 1"); } while (0)
#define VPORTCHG_202_0 do { __asm__ volatile ("SBI 0x05, 2"); } while (0)
#define VPORTCHG_203_0 do { __asm__ volatile ("SBI 0x05, 3"); } while (0)

#define VPORTCHG_208_0 do { __asm__ volatile ("SBI 0x1C, 0"); } while (0)
#define VPORTCHG_209_0 do { __asm__ volatile ("SBI 0x1C, 1"); } while (0)
#define VPORTCHG_210_0 do { __asm__ volatile ("SBI 0x1C, 2"); } while (0)
#define VPORTCHG_211_0 do { __asm__ volatile ("SBI 0x1C, 3"); } while (0)
#define VPORTCHG_212_0 do { __asm__ volatile ("SBI 0x1C, 4"); } while (0)
#define VPORTCHG_213_0 do { __asm__ volatile ("SBI 0x1C, 5"); } while (0)

#define VPORTCHG__
#define VPORTCHG__0
#define VPORTCHG_255_
#define VPORTCHG_255_0

// openDrainWriteMacro(PIN,HIGH) -> pinModeMacro(PIN,INPUT) -> CBI VPORTx.DIR, y
#define VPORTCHG_192_254 do { __asm__ volatile ("CBI 0x01, 0"); } while (0)
#define VPORTCHG_193_254 do { __asm__ volatile ("CBI 0x01, 1"); } while (0)
#define VPORTCHG_194_254 do { __asm__ volatile ("CBI 0x01, 2"); } while (0)
#define VPORTCHG_195_254 do { __asm__ volatile ("CBI 0x01, 3"); } while (0)
#define VPORTCHG_196_254 do { __asm__ volatile ("CBI 0x01, 4"); } while (0)
#define VPORTCHG_197_254 do { __asm__ volatile ("CBI 0x01, 5"); } while (0)
#define VPORTCHG_198_254 do { __asm__ volatile ("CBI 0x01, 6"); } while (0)
#define VPORTCHG_199_254 do { __asm__ volatile ("CBI 0x01, 7"); } while (0)

#define VPORTCHG_200_254 do { __asm__ volatile ("CBI 0x05, 0"); } while (0)
#define VPORTCHG_201_254 do { __asm__ volatile ("CBI 0x05, 1"); } while (0)
#define VPORTCHG_202_254 do { __asm__ volatile ("CBI 0x05, 2"); } while (0)
#define VPORTCHG_203_254 do { __asm__ volatile ("CBI 0x05, 3"); } while (0)

#define VPORTCHG_208_254 do { __asm__ volatile ("CBI 0x1C, 0"); } while (0)
#define VPORTCHG_209_254 do { __asm__ volatile ("CBI 0x1C, 1"); } while (0)
#define VPORTCHG_210_254 do { __asm__ volatile ("CBI 0x1C, 2"); } while (0)
#define VPORTCHG_211_254 do { __asm__ volatile ("CBI 0x1C, 3"); } while (0)
#define VPORTCHG_212_254 do { __asm__ volatile ("CBI 0x1C, 4"); } while (0)
#define VPORTCHG_213_254 do { __asm__ volatile ("CBI 0x1C, 5"); } while (0)

#define VPORTCHG__
#define VPORTCHG__254
#define VPORTCHG_255_254

// openDrainWriteMacro(PIN,TOGGLE) -> MISSING
#define VPORTCHG_192_251 do {} while (0)
#define VPORTCHG_193_251 do {} while (0)
#define VPORTCHG_194_251 do {} while (0)
#define VPORTCHG_195_251 do {} while (0)
#define VPORTCHG_196_251 do {} while (0)
#define VPORTCHG_197_251 do {} while (0)
#define VPORTCHG_198_251 do {} while (0)
#define VPORTCHG_199_251 do {} while (0)

#define VPORTCHG_200_251 do {} while (0)
#define VPORTCHG_201_251 do {} while (0)
#define VPORTCHG_202_251 do {} while (0)
#define VPORTCHG_203_251 do {} while (0)

#define VPORTCHG_208_251 do {} while (0)
#define VPORTCHG_209_251 do {} while (0)
#define VPORTCHG_210_251 do {} while (0)
#define VPORTCHG_211_251 do {} while (0)
#define VPORTCHG_212_251 do {} while (0)
#define VPORTCHG_213_251 do {} while (0)

#define VPORTCHG__
#define VPORTCHG__251
#define VPORTCHG_255_251

// end of code
