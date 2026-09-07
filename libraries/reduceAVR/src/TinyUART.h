/**
 * @file TinyUART.h
 * @author askn (K.Sato) multix.jp
 * @brief Asynchronous Serial Class Dedicated to ATtiny102/104.
 * @version 0.1
 * @date 2026-09-05
 * @copyright Copyright (c) 2026 askn37 at github.com
 * @link Product Potal : https://askn37.github.io/
 *         MIT License : https://askn37.github.io/LICENSE.html
 */

#pragma once
#include <api/macro_api.h>

#if defined(__AVR_TINY__) && defined(__AVR_ATtiny102__) || defined(__AVR_ATtiny104__)

#include <api/Print.h>

class TinyUART_Class : public Print {
public:
  uint8_t _stat;

  TinyUART_Class (void) {};
  inline TinyUART_Class& begin (const uint32_t _baudrate) {
    return initiate((uint16_t)(F_CPU / _baudrate - 1));
  }
  TinyUART_Class& initiate (const uint16_t _baud);

  void end (void);

  size_t write (const uint8_t _c);
  using Print::write; // pull in write(str) and write(buf, size) from Print

  int read (void);

  void flush (void) {
    loop_until_bit_is_set(USART0_STATUS, USART_TXCIF_bp);
  }

  size_t available (void) {
    return bit_is_set(USART0_STATUS, USART_RXCIF_bp) ? 1 : 0;
  }

  size_t availableForWrite (void) {
    return bit_is_set(USART0_STATUS, USART_DREIF_bp) ? 1 : 0;
  }

  /* unsupported int peek() */
  inline int peek (void) { return ~0; }

  inline uint16_t is_baud (void) { return USART0_BAUD; }
  inline uint8_t status (void) { return _stat; }

  size_t readBytes (void* _buffer, size_t _limit, char _terminate = 0, uint8_t _swevent = 0);

  explicit operator bool (void) { return true; }
};

extern TinyUART_Class Serial0;

#endif

// end of code
