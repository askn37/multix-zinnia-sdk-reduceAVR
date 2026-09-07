/**
 * @file TinyUART.cpp
 * @author askn (K.Sato) multix.jp
 * @brief Asynchronous Serial Class Dedicated to ATtiny102/104.
 * @version 0.1
 * @date 2026-09-05
 * @copyright Copyright (c) 2026 askn37 at github.com
 * @link Product Potal : https://askn37.github.io/
 *         MIT License : https://askn37.github.io/LICENSE.html
 */

#include "../TinyUART.h"

#if defined(__AVR_TINY__) && defined(__AVR_ATtiny102__) || defined(__AVR_ATtiny104__)

TinyUART_Class& TinyUART_Class::initiate (const uint16_t _baud) {
  uint8_t _temp = 4;
  if (_baud <= 64) {
    _temp = 3;
    USART0_CTRLA = USART_CLK2X_bm;
  }
  pinMode(PIN_TXD, OUTPUT);
  pinMode(PIN_RXD, INPUT_PULLUP);
  USART0_BAUD = _baud >> _temp;
  USART0_CTRLC = USART_CHSIZE_8BIT_gc
                /* Data corruption is likely to occur when STOP=1 bit. */
               | USART_SBMODE_2BIT_gc
               | USART_PMODE_DISABLED_gc
               | USART_CMODE_ASYNCHRONOUS_gc;
  USART0_CTRLB = USART_TXEN_bm | USART_RXEN_bm;
  // while (bit_is_set(USART0_STATUS, USART_RXCIF_bp)) _temp = USART0_DATA;
  return *this;
}

void TinyUART_Class::end (void) {
  flush();
  USART0_CTRLB =
  USART0_CTRLA = 0;
}

size_t TinyUART_Class::write (const uint8_t _c) {
  loop_until_bit_is_set(USART0_STATUS, USART_DREIF_bp);
  USART0_DATA = _c;
  return 1;
}

int TinyUART_Class::read (void) {
  int _rxd = ~0;
  do {
    _stat = USART0_STATUS;
    if (bit_is_set(_stat, USART_RXCIF_bp)) {
      char _data = USART0_DATA;
      if (!(_stat & (USART_FERR_bm | USART_BUFOVF_bm | USART_PERR_bm ))) _rxd = _data;
      return _rxd;
    }
  } while (true);
}

size_t TinyUART_Class::readBytes (void* _buffer, size_t _limit, char _terminate, uint8_t /* unused */) {
  size_t _length = 0;
  do {
    uint16_t _busy = USART0_BAUD;
    while (bit_is_clear(USART0_STATUS, USART_RXCIF_bp)) {
      if (--_busy == 0) return _length;
    }
    int _c = read();
    if (_c >= 0) {
      ((uint8_t*)_buffer)[_length++] = (uint8_t)_c;
      if (_terminate == (uint8_t)_c) break;
    }
    else break;
  } while (_length < _limit);
  return _length;
}

TinyUART_Class Serial0;

#endif

// end of code
