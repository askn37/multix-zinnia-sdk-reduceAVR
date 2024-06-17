/**
 * @file variant_io.h
 * @author askn (K.Sato) multix.jp
 * @brief
 * @version 0.1
 * @date 2022-12-12
 *
 * @copyright Copyright (c) 2024 askn37 at github.com
 *
 */
// MIT License : https://askn37.github.io/LICENSE.html

#pragma once
#include <avr/io.h>
#define AVR_MODERNAVR_LIKE_REDUCEAVR

/* [ defined ioXXX.h ] */
// #define CCP                         _SFR_IO8(0x3C)
// #define SPL                         _SFR_IO8(0x3D)
// #define SPH                         _SFR_IO8(0x3E)
// #define SREG                        _SFR_IO8(0x3F)


/* C Language Only */
#if !defined (__ASSEMBLER__)

#include <stdint.h>

typedef volatile uint8_t register8_t;
typedef volatile uint16_t register16_t;

#ifdef _WORDREGISTER
#undef _WORDREGISTER
#endif
#define _WORDREGISTER(regname)        \
    __extension__ union {             \
        register16_t regname;         \
        struct {                      \
            register8_t regname ## L; \
            register8_t regname ## H; \
        };                            \
    }

#ifdef _PROTECTED_WRITE
#undef _PROTECTED_WRITE
#endif
#define _PROTECTED_WRITE(reg, value)                \
    __asm__ volatile (                              \
        "out %[ccp], %[ccp_ioreg] \n"               \
        "out %[ioreg], %[val]       "               \
        :                                           \
        : [ccp] "I" (_SFR_IO_ADDR(CCP)),            \
          [ccp_ioreg] "d" ((uint8_t)CCP_IOREG_gc),  \
          [ioreg] "n" (_SFR_IO_ADDR(reg)),          \
          [val] "r" ((uint8_t)value)                \
    )


/*
==========================================================================
IO Module Structures
==========================================================================
*/


/*
--------------------------------------------------------------------------
AC - Analog Comparator
--------------------------------------------------------------------------
*/

/* Analog Comparator */
typedef struct AC_struct
{
    register8_t CTRLA;          /* $1F ACSR : Analog Comparator Control and Status Register */
} AC_t;

/* Interrupt Mode select */
typedef enum AC_INTMODE_enum
{
    AC_INTMODE_BOTHEDGE_gc      = (0x00<<4),    /* Any Edge */
    AC_INTMODE_NEGEDGE_gc       = (0x02<<4),    /* Negative Edge */
    AC_INTMODE_POSEDGE_gc       = (0x03<<4)     /* Positive Edge */
} AC_INTMODE_t;

#if defined(__AVR_ATtiny10__) || defined(__AVR_ATtiny5__)

/*
--------------------------------------------------------------------------
ADC - Analog to Digital Converter
--------------------------------------------------------------------------
*/

/* Analog to Digital Converter */
typedef struct ADC_struct
{
    register8_t RES;            /* $19 ADCL : */
    register8_t reserved_1[1];
    register8_t MUXPOS;         /* $1B ADMUX : */
    register8_t CTRLB;          /* $1C ADCSRB : */
    register8_t CTRLA;          /* $1D ADCSRA : */
} ADC_t;

/* Analog Channel Selection Bits */
typedef enum ADC_MUX_enum
{
    ADC_MUXPOS_AIN0_gc          = (0<<0),       /* Multiplexer Select PB0 */
    ADC_MUXPOS_AIN1_gc          = (1<<0),       /* Multiplexer Select PB1 */
    ADC_MUXPOS_AIN2_gc          = (2<<0),       /* Multiplexer Select PB2 */
    ADC_MUXPOS_AIN3_gc          = (3<<0)        /* Multiplexer Select PB3 */
} ADC_MUX_t;

/* Clock Pre-scaler select */
typedef enum ADC_PRESC_enum
{
    ADC_PRESC_DIVN_gc           = (0x00<<0),    /* CLK_PER divided by 2 */
    ADC_PRESC_DIV2_gc           = (0x01<<0),    /* CLK_PER divided by 2 */
    ADC_PRESC_DIV4_gc           = (0x02<<0),    /* CLK_PER divided by 4 */
    ADC_PRESC_DIV8_gc           = (0x03<<0),    /* CLK_PER divided by 8 */
    ADC_PRESC_DIV16_gc          = (0x04<<0),    /* CLK_PER divided by 16 */
    ADC_PRESC_DIV32_gc          = (0x05<<0),    /* CLK_PER divided by 32 */
    ADC_PRESC_DIV64_gc          = (0x06<<0),    /* CLK_PER divided by 64 */
    ADC_PRESC_DIV128_gc         = (0x07<<0)     /* CLK_PER divided by 128 */
} ADC_PRESC_t;

/* Automatic Trigger Source select */
typedef enum ADC_ADTS_enum
{
    ADC_ATMODE_0_gc             = (0<<0),       /* Free Running mode */
    ADC_ATMODE_1_gc             = (1<<0),       /* Analog Comparator */
    ADC_ATMODE_2_gc             = (2<<0),       /* External Interrupt Flag 0 */
    ADC_ATMODE_3_gc             = (3<<0),       /* Timer/Counter 0 Compare Match A */
    ADC_ATMODE_4_gc             = (4<<0),       /* Timer/Counter 0 Overflow */
    ADC_ATMODE_5_gc             = (5<<0),       /* Timer/Counter 0 Compare Match B */
    ADC_ATMODE_6_gc             = (6<<0),       /* Pin Change Interrupt 0 Request */
    ADC_ATMODE_7_gc             = (7<<0)        /* Timer/Counter 0 Capture Event */
} ADC_ADTS_t;

#endif

/*
--------------------------------------------------------------------------
BOD (VLMCTRL) - Brownout Detector
--------------------------------------------------------------------------
*/

typedef struct BOD_struct
{
    register8_t CTRLA;          /* $34 VLMCSR : VCC Monitoring Control and Status Register */
} BOD_t;

/* Clock select */
typedef enum BOD_LEVEL_enum
{
    BOD_LEVEL_0_gc              = (0x00<<0),    /* Dsiable */
    BOD_LEVEL_1_gc              = (0x01<<0),    /* 1.4 V */
    BOD_LEVEL_2_gc              = (0x02<<0),    /* 1.6 V */
    BOD_LEVEL_3_gc              = (0x03<<0),    /* 2.5 V */
    BOD_LEVEL_4_gc              = (0x04<<0)     /* 3.7 V */
} BOD_LEVEL_t;


/*
--------------------------------------------------------------------------
CLKCTRL - Clock controller
--------------------------------------------------------------------------
*/

/* Clock controller */
typedef struct CLKCTRL_struct
{
    register8_t MCLKCTRLB;      /* $36 CLKPSR : Clock Prescale Register */
    register8_t MCLKCTRLA;      /* $37 CLKMSR : Clock Main Settings Register */
    register8_t reserved_1[1];
    register8_t OSCCALIB;       /* $39 OSCCAL : Oscillator Calibration Register */
} CLKCTRL_t;

/* Clock select */
typedef enum CLKCTRL_CLKSEL_enum
{
    CLKCTRL_CLKSEL_OSC8M_gc     = (0x00<<0),    /* 8MHz oscillator */
    CLKCTRL_CLKSEL_OSC128K_gc   = (0x01<<0),    /* 128KHz oscillator */
    CLKCTRL_CLKSEL_EXTCLK_gc    = (0x02<<0)     /* External clock */
} CLKCTRL_CLKSEL_t;

/* Prescaler division select */
typedef enum CLKCTRL_PDIV_enum
{
    CLKCTRL_PDIV_1X_gc          = (0x00<<0),    /* 1X */
    CLKCTRL_PDIV_2X_gc          = (0x01<<0),    /* 2X */
    CLKCTRL_PDIV_4X_gc          = (0x02<<0),    /* 4X */
    CLKCTRL_PDIV_8X_gc          = (0x03<<0),    /* 8X */
    CLKCTRL_PDIV_16X_gc         = (0x04<<0),    /* 16X */
    CLKCTRL_PDIV_32X_gc         = (0x05<<0),    /* 32X */
    CLKCTRL_PDIV_64X_gc         = (0x06<<0),    /* 64X */
    CLKCTRL_PDIV_128X_gc        = (0x07<<0),    /* 128X */
    CLKCTRL_PDIV_256X_gc        = (0x08<<0)     /* 256X */
} CLKCTRL_PDIV_t;


/*
--------------------------------------------------------------------------
EXTINT - External Interrupt Controller
--------------------------------------------------------------------------
*/

/* External Interrupt Controller */
typedef struct EXTINT_struct
{
    register8_t INTFLAGS;       /* $13 EIFR : External Interrupt Flag Register */
    register8_t INTCTRL;        /* $14 EIMSK : External Interrupt Mask Register */
    register8_t CTRLA;          /* $15 EICRA : External Interrupt Control Register A */
} EXTINT_t;

/* Input/Sense Configuration select */
typedef enum EXTINT_ISC0_enum
{
    EXTINT_ISC0_LEVEL_gc        = (0x00<<0),    /* Sense low Level */
    EXTINT_ISC0_BOTHEDGES_gc    = (0x01<<0),    /* Sense Both Edges */
    EXTINT_ISC0_FALLING_gc      = (0x02<<0),    /* Sense Falling Edge */
    EXTINT_ISC0_RISING_gc       = (0x03<<0)     /* Sense Rising Edge */
} EXTINT_ISC0_t;


/*
--------------------------------------------------------------------------
NVMCTRL - Non-volatile Memory Controller
--------------------------------------------------------------------------
*/

/* Non-volatile Memory Controller */
typedef struct NVMCTRL_struct
{
    register8_t STATUS;         /* $32 NVMCSR : Non-Volatile Memory Status Register */
    register8_t CTRLA;          /* #33 NVMCMD : Non-Volatile Memory Command Register */
} NVMCTRL_t;

/* Command select */
typedef enum NVMCTRL_CMD_enum
{
    NVMCTRL_CMD_NONE_gc         = (0x00<<0),    /* No command */
    NVMCTRL_CMD_CHIPERASE_gc    = (0x10<<0),    /* Chip erase */
    NVMCTRL_CMD_PAGEERASE_gc    = (0x14<<0),    /* Section erase */
    NVMCTRL_CMD_WORDWRITE_gc    = (0x1D<<0)     /* Word write */
} NVMCTRL_CMD_t;


/*
--------------------------------------------------------------------------
PCINT - Pin Change Interrupt Controller
--------------------------------------------------------------------------
*/

typedef struct PCINT_struct
{
    register8_t INTFLAGS;       /* $10 PCMSK : Pin Change Mask Register */
    register8_t INTCTRL;        /* $11 PCIFR : Pin Change Interrupt Flag Register */
    register8_t CTRLA;          /* $12 PCICR : Pin Change Interrupt Control Register */
} PCINT_t;


/*
--------------------------------------------------------------------------
PORTx - Ports controller
--------------------------------------------------------------------------
*/

/* Ports */
typedef struct PORT_struct
{
    register8_t IN;             /* $00 INx : Input Value */
    register8_t DIR;            /* $01 DDRx : Data Direction */
    register8_t OUT;            /* $02 PORTx : Output Value */
    register8_t PUE;            /* $03 PUEx : Pullup Enable Value */
} PORT_t;

/* Port Control */
typedef struct PORTCTRL_struct
{
    register8_t CTRLA;          /* $0C PORTCR : Port Control Register */
    register8_t reserved_1[10];
    register8_t DIDIS;          /* $17 DIDR0 : Digital Input Disable Register 0 */
} PORTCTRL_t;


/*
--------------------------------------------------------------------------
SLPCTRL - Sleep controller
--------------------------------------------------------------------------
*/

/* Sleep controller */
typedef struct SLPCTRL_struct
{
    register8_t CTRLB;          /* $35 PRR : Power Reduction Register */
    register8_t reserved_1[4];
    register8_t CTRLA;          /* $3A SMCR : Sleep Mode Control Register */
} SLPCTRL_t;

/* Sleep mode select */
typedef enum SLPCTRL_SMODE_enum
{
    SLPCTRL_SMODE_IDLE_gc       = (0x00<<1),    /* Idle mode */
    SLPCTRL_SMODE_ADC_gc        = (0x01<<1),    /* Power-down Mode */
    SLPCTRL_SMODE_PDOWN_gc      = (0x02<<1),    /* Power-down Mode */
    SLPCTRL_SMODE_STDBY_gc      = (0x04<<1)     /* Standby Mode */
} SLPCTRL_SMODE_t;


/*
--------------------------------------------------------------------------
TIM - Timer/Counter controller
--------------------------------------------------------------------------
*/

/* 16-bit Timer 0 ($22-2F) */
typedef struct TIM_struct
{
    _WORDREGISTER(CAPT);        /* $22 ICR0 : Input Capture Register */
    _WORDREGISTER(CMPB);        /* $24 OCR0B : Output Compare Register B */
    _WORDREGISTER(CMPA);        /* $26 OCR0A : Output Compare Register A */
    _WORDREGISTER(CNT);         /* $28 TCNT0 : Count */
    register8_t INTFLAGS;       /* $2A TIFR0 : Interrupt Flag Register */
    register8_t INTCTRL;        /* $2B TIMSK0 : Interrupt Mask Register */
    register8_t CTRLC;          /* $2C TCCR0C : Control Register C */
    register8_t CTRLB;          /* $2D TCCR0B : Control Register B */
    register8_t CTRLA;          /* $2E TCCR0A : Control Register A */
    register8_t GTCC;           /* $2F GTCCR : General Timer/Counter Control Register */
} TIM_t;

/* Compare Output Mode Channel A */
typedef enum TIM_CPMODE_A_enum
{
    TIM_CPMODE_OC0A_OFF_gc      = (0x00<<6),    /* Normal port operation: OC0A/OC0B disconnected */
    TIM_CPMODE_OC0A_TOGGLE_gc   = (0x01<<6),
    TIM_CPMODE_OC0A_LOW_gc      = (0x01<<6),
    TIM_CPMODE_OC0A_HIGH_gc     = (0x01<<6)
} TIM_CPMODE_A_t;

/* Compare Output Mode Channel B */
typedef enum TIM_CPMODE_B_enum
{
    TIM_CPMODE_OC0B_OFF_gc      = (0x00<<4),    /* Normal port operation: OC0A/OC0B disconnected */
    TIM_CPMODE_OC0B_TOGGLE_gc   = (0x01<<4),
    TIM_CPMODE_OC0B_LOW_gc      = (0x01<<4),
    TIM_CPMODE_OC0B_HIGH_gc     = (0x01<<4)
} TIM_CPMODE_B_t;

/* Wave Generation */
typedef enum TIM_WGMODE_L_enum
{
    TIM_WGMODE_NORMAL_L_gc      = (0x00<<0),    /* Normal Mode                  0xFFFF-Imd----MAX */
    TIM_WGMODE_PWM8_BTM_L_gc    = (0x01<<0),    /* PWM, Phase Correct, 8-bit    0x00FF-TOP----BOTTOM */
    TIM_WGMODE_PWM9_BTM_L_gc    = (0x02<<0),    /* PWM, Phase Correct, 9-bit    0x01FF-TOP----BOTTOM */
    TIM_WGMODE_PWM10_BTM_L_gc   = (0x03<<0),    /* PWM, Phase Correct, 10-bit   0x03FF-TOP----BOTTOM */
    TIM_WGMODE_CTC_CMPA_L_gc    = (0x00<<0),    /* CTC (Clear Timer on Compare) OCR0A--Imd----MAX */
    TIM_WGMODE_PWM8_TOP_L_gc    = (0x01<<0),    /* Fast PWM, 8-bit              0x00FF-TOP----TOP */
    TIM_WGMODE_PWM9_TOP_L_gc    = (0x02<<0),    /* Fast PWM, 9-bit              0x01FF-TOP----TOP */
    TIM_WGMODE_PWM10_TOP_L_gc   = (0x03<<0),    /* Fast PWM, 10-bit             0x03FF-TOP----TOP */
    TIM_WGMODE_PWFQ_CAPT_L_gc   = (0x00<<0),    /* PWM, Phase & Freq. Correct   ICR0---BOTTOM-BOTTOM */
    TIM_WGMODE_PWFQ_CMPA_L_gc   = (0x01<<0),    /* PWM, Phase & Freq. Correct   OCR0A--BOTTOM-BOTTOM */
    TIM_WGMODE_PWPH_CAPT_L_gc   = (0x02<<0),    /* PWM, Phase Correct           ICR0---TOP----BOTTOM */
    TIM_WGMODE_PWPH_CMPA_L_gc   = (0x03<<0),    /* PWM, Phase Correct           OCR0A--TOP----BOTOM */
    TIM_WGMODE_CTC_CAPT_L_gc    = (0x00<<0),    /* CTC (Clear Timer on Compare) ICR0---Imd----MAX */
    TIM_WGMODE_13_L_gc          = (0x01<<0),    /* (Reserved) */
    TIM_WGMODE_PWM_CAPT_L_gc    = (0x02<<0),    /* Fast PWM                     ICR0---TOP----TOP */
    TIM_WGMODE_PWM_CMPA_L_gc    = (0x03<<0)     /* Fast PWM                     OCR0A--TOP----TOP */
} TIM_WGMODE_L_t;

typedef enum TIM_WGMODE_H_enum
{
    TIM_WGMODE_NORMAL_H_gc      = (0x00<<3),    /* Normal Mode                  0xFFFF-Imd----MAX */
    TIM_WGMODE_PWM8_BTM_H_gc    = (0x00<<3),    /* PWM, Phase Correct, 8-bit    0x00FF-TOP----BOTTOM */
    TIM_WGMODE_PWM9_BTM_H_gc    = (0x00<<3),    /* PWM, Phase Correct, 9-bit    0x01FF-TOP----BOTTOM */
    TIM_WGMODE_PWM10_BTM_H_gc   = (0x00<<3),    /* PWM, Phase Correct, 10-bit   0x03FF-TOP----BOTTOM */
    TIM_WGMODE_CTC_CMPA_H_gc    = (0x01<<3),    /* CTC (Clear Timer on Compare) OCR0A--Imd----MAX */
    TIM_WGMODE_PWM8_TOP_H_gc    = (0x01<<3),    /* Fast PWM, 8-bit              0x00FF-TOP----TOP */
    TIM_WGMODE_PWM9_TOP_H_gc    = (0x01<<3),    /* Fast PWM, 9-bit              0x01FF-TOP----TOP */
    TIM_WGMODE_PWM10_TOP_H_gc   = (0x01<<3),    /* Fast PWM, 10-bit             0x03FF-TOP----TOP */
    TIM_WGMODE_PWFQ_CAPT_H_gc   = (0x02<<3),    /* PWM, Phase & Freq. Correct   ICR0---BOTTOM-BOTTOM */
    TIM_WGMODE_PWFQ_CMPA_H_gc   = (0x02<<3),    /* PWM, Phase & Freq. Correct   OCR0A--BOTTOM-BOTTOM */
    TIM_WGMODE_PWPH_CAPT_H_gc   = (0x02<<3),    /* PWM, Phase Correct           ICR0---TOP----BOTTOM */
    TIM_WGMODE_PWPH_CMPA_H_gc   = (0x02<<3),    /* PWM, Phase Correct           OCR0A--TOP----BOTOM */
    TIM_WGMODE_CTC_CAPT_H_gc    = (0x03<<3),    /* CTC (Clear Timer on Compare) ICR0---Imd----MAX */
    TIM_WGMODE_13_H_gc          = (0x03<<3),    /* (Reserved) */
    TIM_WGMODE_PWM_CAPT_H_gc    = (0x03<<3),    /* Fast PWM                     ICR0---TOP----TOP */
    TIM_WGMODE_PWM_CMPA_H_gc    = (0x03<<3)     /* Fast PWM                     OCR0A--TOP----TOP */
} TIM_WGMODE_H_t;

/* Clock Select */
typedef enum TIM_CLKSEL_enum
{
    TIM_CLKSEL_CLKSTOP_gc       = (0x00<<0),    /* No clock */
    TIM_CLKSEL_CLKDIV1_gc       = (0x01<<0),    /* CLK_PER (No Prescaling)  */
    TIM_CLKSEL_CLKDIV8_gc       = (0x02<<0),    /* CLK_PER/8 (From Prescaler) */
    TIM_CLKSEL_CLKDIV64_gc      = (0x03<<0),    /* CLK_PER/64 (From Prescaler) */
    TIM_CLKSEL_CLKDIV256_gc     = (0x04<<0),    /* CLK_PER/256 (From Prescaler) */
    TIM_CLKSEL_CLKDIV1024_gc    = (0x05<<0),    /* CLK_PER/256 (From Prescaler) */
    TIM_CLKSEL_T0_FALLING_gc    = (0x06<<0),    /* T0 pin edge falling (T0 == PB2) */
    TIM_CLKSEL_T0_RISING_gc     = (0x07<<0),    /* T0 pin edge rising (T0 == PB2) */
} TCB_CLKSEL_t;

/*
--------------------------------------------------------------------------
WDT - Watch-Dog Timer
--------------------------------------------------------------------------
*/

/* Watch-Dog Timer */
typedef struct WDT_struct
{
    register8_t CTRLA;          /* $31 WDTCSR : Watchdog Timer Control and Status Register */
} WDT_t;

/* Period select */
typedef enum WDT_PERIOD_enum
{
    WDT_PERIOD_2CLK_gc          = (0x00<<0),    /* 2 cycles (64Hz) */
    WDT_PERIOD_4CLK_gc          = (0x01<<0),    /* 4 cycles (32Hz) */
    WDT_PERIOD_8CLK_gc          = (0x02<<0),    /* 8 cycles (16Hz) */
    WDT_PERIOD_16CLK_gc         = (0x03<<0),    /* 16 cycles (8Hz) */
    WDT_PERIOD_32CLK_gc         = (0x04<<0),    /* 32 cycles (4Hz) */
    WDT_PERIOD_64CLK_gc         = (0x05<<0),    /* 64 cycles (2Hz) */
    WDT_PERIOD_128CLK_gc        = (0x06<<0),    /* 128 cycles (1.0s) */
    WDT_PERIOD_256CLK_gc        = (0x07<<0),    /* 256 cycles (2.0s) */
    WDT_PERIOD_512CLK_gc        = (0x20<<0),    /* 512 cycles (4.0s) */
    WDT_PERIOD_1KCLK_gc         = (0x21<<0)     /* 1K cycles (8.0s) */
} WDT_PERIOD_t;


/*
--------------------------------------------------------------------------
CPU - CPU
--------------------------------------------------------------------------
*/

/* CCP signature select */
typedef enum CCP_enum {
  CCP_IOREG_gc                  = (0xD8<<0)     /* IO Register Protection */
} CCP_t;


/*
==========================================================================
IO Module Instances. Mapped to memory.
==========================================================================
*/
// #define PORTB                       (*(PORT_t *)    0x00)
#define IOPORTB                     (*(PORT_t *)    0x00) /* Alias */
#define PORTCTRL                    (*(PORTCTRL_t*) 0x0C)
#define PCINT                       (*(PIINT_t *)   0x10)
#define EXTINT                      (*(EXTINT_t *)  0x13)
// #define ADC0                        (*(ADC_t *)     0x19)
#if defined(__AVR_ATtiny10__) || defined(__AVR_ATtiny5__)
#define AD0                         (*(ADC_t *)     0x19) /* Alias */
#endif
#define AC0                         (*(AC_t *)      0x1F)
#define TIM0                        (*(TIM_t *)     0x22)
#define WDT                         (*(WDT_t *)     0x31)
#define NVMCTRL                     (*(NVMCTRL_t *) 0x32)
#define VLMCTRL                     (*(BOD_t *)     0x34)
#define BOD                         (*(BOD_t *)     0x34) /* Alias */
#define SLPCTRL                     (*(SLPCTRL_t *) 0x35)
#define CLKCTRL                     (*(CLKCTRL_t *) 0x36)

#endif /* !defined (__ASSEMBLER__) */

/* ========== Flattened fully qualified IO register names ========== */


/* AC0 - Analog Comparator */
#define AC0_CTRLA                   _SFR_IO8(0x1F)  /* ACSR */

/* AC0.CTRLA  bit masks and bit positions */
#define AC_INTMODE_gm               (3<<0)      /* Interrupt Mode Select group mask. */
#define AC_INTMODE_gp               0           /* Interrupt Mode Select group position. */
#define AC_INTMODE_0_bm             (1<<0)      /* Interrupt Mode Select bit 0 mask. */
#define AC_INTMODE_0_bp             0           /* Interrupt Mode Select bit 0 position. */
#define AC_INTMODE_1_bm             (1<<1)      /* Interrupt Mode Select bit 1 mask. */
#define AC_INTMODE_1_bp             1           /* Interrupt Mode Select bit 1 position. */
#define AC_ICE_bm                   (1<<2)      /* Input Capture Enable bit mask. */ /* ACO -> TIM0 ICIE */
#define AC_ICE_bp                   2           /* Input Capture Enable bit position. */
#define AC_IE_bm                    (1<<3)      /* Interrupt Enable bit mask. */
#define AC_IE_bp                    3           /* Interrupt Enable bit position. */
#define AC_IF_bm                    (1<<4)      /* Interrupt Flag bit mask. */
#define AC_IF_bp                    4           /* Interrupt Flag bit position. */
#define AC_OUT_bm                   (1<<5)      /* Output bit mask. */
#define AC_OUT_bp                   5           /* Output bit position. */
#define AC_DIS_bm                   (1<<7)      /* Disable bit mask. */
#define AC_DIS_bp                   7           /* Disable bit position. */


#if defined(__AVR_ATtiny10__) || defined(__AVR_ATtiny5__)

/* ADC0 - Analog Digital Converter */
#define ADC0_RES                    _SFR_IO8(0x19)  /* ADCL */
#define ADC0_MUXPOS                 _SFR_IO8(0x1B)  /* ADMUX */
#define ADC0_CTRLB                  _SFR_IO8(0x1C)  /* ADCSRB */
#define ADC0_CTRLA                  _SFR_IO8(0x1D)  /* ADCSRA */

/* ADC0.MUXPOS  bit masks and bit positions */
#define ADC_MUXPOS_gm               (3<<0)      /* Multiplexer Select group mask. */
#define ADC_MUXPOS_gp               0           /* Multiplexer Select group position. */
#define ADC_MUXPOS_0_bm             (1<<0)      /* Multiplexer Select bit 0 mask. */
#define ADC_MUXPOS_0_bp             0           /* Multiplexer Select bit 0 position. */
#define ADC_MUXPOS_1_bm             (1<<1)      /* Multiplexer Select bit 1 mask. */
#define ADC_MUXPOS_1_bp             1           /* Multiplexer Select bit 1 position. */

/* ADC0.CTRLA  bit masks and bit positions */
#define ADC_PRESC_gm                (7<<0)      /* Clock Pre-scaler group mask. */
#define ADC_PRESC_gp                0           /* Clock Pre-scaler group position. */
#define ADC_PRESC_0_bm              (1<<0)      /* Clock Pre-scaler bit 0 mask. */
#define ADC_PRESC_0_bp              0           /* Clock Pre-scaler bit 0 position. */
#define ADC_PRESC_1_bm              (1<<1)      /* Clock Pre-scaler bit 1 mask. */
#define ADC_PRESC_1_bp              1           /* Clock Pre-scaler bit 1 position. */
#define ADC_PRESC_2_bm              (1<<2)      /* Clock Pre-scaler bit 2 mask. */
#define ADC_PRESC_2_bp              2           /* Clock Pre-scaler bit 2 position. */
#define ADC_IE_bm                   (1<<3)      /* Interrupt Enable bit mask. */
#define ADC_IE_bp                   3           /* Interrupt Enable bit position. */
#define ADC_IF_bm                   (1<<4)      /* Interrupt Flag bit mask. */
#define ADC_IF_bp                   4           /* Interrupt Flag bit position. */
#define ADC_ATE_bm                  (1<<5)      /* Automatic Trigger Enable bit mask. */
#define ADC_ATE_bp                  5           /* Automatic Trigger Enable bit position. */
#define ADC_STCONV_bm               (1<<6)      /* Start Conversion Operation bit mask. */
#define ADC_STCONV_bp               6           /* Start Conversion Operation bit position. */
#define ADC_EN_bm                   (1<<7)      /* ADC Enable bit mask. */
#define ADC_EN_bp                   7           /* ADC Enable bit position. */

/* ADC0.CTRLB  bit masks and bit positions */
#define ADC_ATMODE_gm               (7<<0)      /* Automatic Trigger group mask. */
#define ADC_ATMODE_gp               0           /* Automatic Trigger group position. */
#define ADC_ATMODE_0_bm             (1<<0)      /* Automatic Trigger bit 0 mask. */
#define ADC_ATMODE_0_bp             0           /* Automatic Trigger bit 0 position. */
#define ADC_ATMODE_1_bm             (1<<1)      /* Automatic Trigger bit 1 mask. */
#define ADC_ATMODE_1_bp             1           /* Automatic Trigger bit 1 position. */
#define ADC_ATMODE_2_bm             (1<<2)      /* Automatic Trigger bit 2 mask. */
#define ADC_ATMODE_2_bp             2           /* Automatic Trigger bit 2 position. */

#endif

/* BOD - Clock controller */
#define BOD_CTRLA                   _SFR_IO8(0x34)  /* VLMCSR */

/* BOD.CTRLA  bit masks and bit positions */
#define BOD_LEVEL_gm                (0x07<<0)   /* Trigger Level of Voltage Level Monitor group mask. */
#define BOD_LEVEL_gp                0           /* Trigger Level of Voltage Level Monitor group position. */
#define BOD_VLMIE_bm                (1<<6)      /* VLM Interrupt Enable bit mask. */
#define BOD_VLMIE_bp                6           /* VLM Interrupt Enable bit position. */
#define BOD_VLMF_bm                 (1<<7)      /* VLM Flag bit mask. */
#define BOD_VLMF_bp                 7           /* VLM Flag bit position. */


/* CLKCTRL - Clock controller */
#define CLKCTRL_MCLKCTRLB           _SFR_IO8(0x36)  /* CLKPSR */
#define CLKCTRL_MCLKCTRLA           _SFR_IO8(0x37)  /* CLKMSR */
#define CLKCTRL_OSCCALIB            _SFR_IO8(0x39)  /* OSCCAL */

/* CLKCTRL.MCLKCTRLB  bit masks and bit positions */
#define CLKCTRL_PDIV_gm             0x07        /* Prescaler division group mask. */
#define CLKCTRL_PDIV_gp             0           /* Prescaler division group position. */
#define CLKCTRL_PDIV_0_bm           (1<<0)      /* Prescaler division bit 0 mask. */
#define CLKCTRL_PDIV_0_bp           0           /* Prescaler division bit 0 position. */
#define CLKCTRL_PDIV_1_bm           (1<<1)      /* Prescaler division bit 1 mask. */
#define CLKCTRL_PDIV_1_bp           1           /* Prescaler division bit 1 position. */
#define CLKCTRL_PDIV_2_bm           (1<<2)      /* Prescaler division bit 2 mask. */
#define CLKCTRL_PDIV_2_bp           2           /* Prescaler division bit 2 position. */
#define CLKCTRL_PDIV_3_bm           (1<<3)      /* Prescaler division bit 3 mask. */
#define CLKCTRL_PDIV_3_bp           3           /* Prescaler division bit 3 position. */
#define CLKCTRL_PEN_bm              0           /* Prescaler division enable dummy mask. */

/* CLKCTRL.MCLKCTRLA  bit masks and bit positions */
#define CLKCTRL_CLKSEL_gm           0x03        /* Clock select group mask. */
#define CLKCTRL_CLKSEL_gp           0           /* Clock select group position. */
#define CLKCTRL_CLKSEL_0_bm         (1<<0)      /* Clock select bit 0 mask. */
#define CLKCTRL_CLKSEL_0_bp         0           /* Clock select bit 0 position. */
#define CLKCTRL_CLKSEL_1_bm         (1<<1)      /* Clock select bit 1 mask. */
#define CLKCTRL_CLKSEL_1_bp         1           /* Clock select bit 1 position. */

/* CLKCTRL.OSCCAL  bit masks and bit positions */
#define CLKCTRL_CALIB_gm            0xFF        /* Calibration group mask. */
#define CLKCTRL_CALIB_gp            0           /* Calibration group position. */


/* EXTINT - Interrupt Control */
#define EXTINT_INTFLAGS             _SFR_IO8(0x13)  /* $13 EIFR : External Interrupt Flag Register */
#define EXTINT_INTCTRL              _SFR_IO8(0x14)  /* $14 EIMSK : External Interrupt Mask Register */
#define EXTINT_CTRLA                _SFR_IO8(0x15)  /* $15 EICRA : External Interrupt Control Register A */

/* EXTINT.INTFLGS  bit masks and bit positions */
#define EXTINT_INT0_bm              (1<<0)          /* External Interrupt Flag 0 bit mask. */
#define EXTINT_INT0_pm              0               /* External Interrupt Flag 0 bit position. */

/* EXTINT.INTCTRL  bit masks and bit positions */
#define EXTINT_INT0_EN_bm           (1<<0)          /* External Interrupt Request 0 Enable bit mask. */
#define EXTINT_INT0_EN_pm           0               /* External Interrupt Request 0 Enable bit position. */

/* EXTINT.CTRLA  bit masks and bit positions */
#define EXTINT_ISC0_gm               (3<<0)         /* Interrupt Sense Control 0 group bit mask */
#define EXTINT_ISC0_gp               0              /* Interrupt Sense Control 0 group bit position */
#define EXTINT_ISC0_0_bm             (1<<0)         /* Interrupt Sense Control 0 bit 0 mask */
#define EXTINT_ISC0_0_bp             0              /* Interrupt Sense Control 0 bit 0 position */
#define EXTINT_ISC0_1_bm             (1<<1)         /* Interrupt Sense Control 0 bit 1 mask */
#define EXTINT_ISC0_1_bp             1              /* Interrupt Sense Control 0 bit 1 position */


/* NVMCTRL - Non-Volatile Memory Contorol */
#define NVMCTRL_STATUS              _SFR_IO8(0x32)  /* NVMCSR */
#define NVMCTRL_CTRLA               _SFR_IO8(0x33)  /* NVMCMD */

/* NVMCTRL.STATUS  bit masks and bit positions */
#define NVMCTRL_BUSY_bm             (1<<7)
#define NVMCTRL_BUSY_bp             7

/* NVMCTRL.CTRLA  bit masks and bit positions */
#define NVMCTRL_CMD_gm              0x3F        /* Command group mask. */
#define NVMCTRL_CMD_gp              0           /* Command group position. */
#define NVMCTRL_CMD_0_bm            (1<<0)      /* Command bit 0 mask. */
#define NVMCTRL_CMD_0_bp            0           /* Command bit 0 position. */
#define NVMCTRL_CMD_1_bm            (1<<1)      /* Command bit 1 mask. */
#define NVMCTRL_CMD_1_bp            1           /* Command bit 1 position. */
#define NVMCTRL_CMD_2_bm            (1<<2)      /* Command bit 2 mask. */
#define NVMCTRL_CMD_2_bp            2           /* Command bit 2 position. */
#define NVMCTRL_CMD_3_bm            (1<<3)      /* Command bit 3 mask. */
#define NVMCTRL_CMD_3_bp            3           /* Command bit 3 position. */
#define NVMCTRL_CMD_4_bm            (1<<4)      /* Command bit 4 mask. */
#define NVMCTRL_CMD_4_bp            4           /* Command bit 5 position. */


/* PCINT - Interrupt Control */
#define PCINT_INTCTRL               _SFR_IO8(0x10)  /* $10 PCMSK : Pin Change Mask Register */
#define PCINT_INTFLAGS              _SFR_IO8(0x11)  /* $11 PCIFR : Pin Change Interrupt Flag Register */
#define PCINT_CTRLA                 _SFR_IO8(0x12)  /* $12 PCICR : Pin Change Interrupt Control Register */

/* PCINT.INTFLGS  bit masks and bit positions */
#define PCINT_PCINT_bm              (1<<0)          /* Pin Change Interrupt Flag 0 bit mask. */
#define PCINT_PCINT_pm              0               /* Pin Change Interrupt Flag 0 bit position. */

/* PCINT.INTCTRL  bit masks and bit positions */
#define PCINT_PCINT0_EN_bm          (1<<0)          /* Pin Change Interrupt Request 0 Enable bit mask. */
#define PCINT_PCINT0_EN_pm          0               /* Pin Change Interrupt Request 0 Enable bit position. */
#define PCINT_PCINT1_EN_bm          (1<<1)          /* Pin Change Interrupt Request 1 Enable bit mask. */
#define PCINT_PCINT1_EN_pm          1               /* Pin Change Interrupt Request 1 Enable bit position. */
#define PCINT_PCINT2_EN_bm          (1<<2)          /* Pin Change Interrupt Request 2 Enable bit mask. */
#define PCINT_PCINT2_EN_pm          2               /* Pin Change Interrupt Request 2 Enable bit position. */
#define PCINT_PCINT3_EN_bm          (1<<3)          /* Pin Change Interrupt Request 3 Enable bit mask. */
#define PCINT_PCINT3_EN_pm          3               /* Pin Change Interrupt Request 3 Enable bit position. */


/* PORTB - I/O Ports */
#define PORTB_IN                    _SFR_IO8(0x00)  /* PINB */
#define PORTB_DIR                   _SFR_IO8(0x01)  /* DDRB */
#define PORTB_OUT                   _SFR_IO8(0x02)  /* PORTB */
#define PORTB_PUE                   _SFR_IO8(0x03)  /* PUEB */


/* PORTCTRL - I/O Ports Control */
#define PORTCTRL_CTRLA              _SFR_IO8(0x0C)  /* PORTCR */
#define PORTCTRL_DIDIS              _SFR_IO8(0x17)  /* DIDR0 */


/* PORTCTRL.CTRLA  bit masks and bit positions */
#define PORTCTRL_BBMME_bm           (1<<1)      /* Break-Before-Make Mode Enable bit mask. */
#define PORTCTRL_BBMME_bp           1           /* Break-Before-Make Mode Enable bit position. */


/* RSTCTRL - Reset controller */
#define RSTCTRL_RSTFLR              _SFR_IO8(0x3B)  /* RSTFLR */

/* RSTCTRL.RSTFLR  bit masks and bit positions */
#define RSTCTRL_PORF_bm             0x01        /* Power on Reset flag bit mask. */
#define RSTCTRL_PORF_bp             0           /* Power on Reset flag bit position. */
#define RSTCTRL_EXTRF_bm            0x02        /* External Reset flag bit mask. */
#define RSTCTRL_EXTRF_bp            1           /* External Reset flag bit position. */
#define RSTCTRL_WDRF_bm             0x08        /* Watch dog Reset flag bit mask. */
#define RSTCTRL_WDRF_bp             3           /* Watch dog Reset flag bit position. */


/* SLPCTRL - Sleep controller */
#define SLPCTRL_CTRLB               _SFR_IO8(0x35)  /* PRR */
#define SLPCTRL_CTRLA               _SFR_IO8(0x3A)  /* SMCR */

/* SLPCTRL.CTRLA  bit masks and bit positions */
#define SLPCTRL_SEN_bm              (1<<0)      /* Sleep enable bit mask. */
#define SLPCTRL_SEN_bp              0           /* Sleep enable bit position. */
#define SLPCTRL_SMODE_gm            (3<<1)      /* Sleep mode group mask. */
#define SLPCTRL_SMODE_gp            1           /* Sleep mode group position. */
#define SLPCTRL_SMODE_0_bm          (1<<1)      /* Sleep mode bit 0 mask. */
#define SLPCTRL_SMODE_0_bp          1           /* Sleep mode bit 0 position. */
#define SLPCTRL_SMODE_1_bm          (1<<2)      /* Sleep mode bit 1 mask. */
#define SLPCTRL_SMoDE_1_bp          2           /* Sleep mode bit 1 position. */

/* SLPCTRL.CTRLB  bit masks and bit positions */
#define SLPCTRL_PRTIM0_bm           (1<<0)      /* Power reduction TIM0 bit mask. */
#define SLPCTRL_PRTIM0_bp           0           /* Power reduction TIM0 bit position. */
#define SLPCTRL_PRADC0_bm           (1<<1)      /* Power reduction ADC0 bit mask. */
#define SLPCTRL_PRADC0_bp           1           /* Power reduction ADC0 bit position. */

/* [ defined ioXXX.h ] */
// #define SLEEP_MODE_IDLE             (0x00<<1)
// #define SLEEP_MODE_ADC              (0x01<<1)
// #define SLEEP_MODE_PWR_DOWN         (0x02<<1)
// #define SLEEP_MODE_STANDBY          (0x04<<1)


/* TIM0 - Timer/Counter 0 Control */
#define TIM0_CAPT                   _SFR_IO16(0x22) /* ICR0 */
#define TIM0_CAPTL                  _SFR_IO8(0x22)  /* ICR0L */
#define TIM0_CAPTH                  _SFR_IO8(0x23)  /* ICR0H */
#define TIM0_CMPB                   _SFR_IO16(0x24) /* OCR0B */
#define TIM0_CMPBL                  _SFR_IO8(0x24)  /* OCR0BL */
#define TIM0_CMPBH                  _SFR_IO8(0x25)  /* OCR0BH */
#define TIM0_CMPA                   _SFR_IO16(0x26) /* OCR0A */
#define TIM0_CMPAL                  _SFR_IO8(0x26)  /* OCR0AL */
#define TIM0_CMPAH                  _SFR_IO8(0x27)  /* OCR0BH */
#define TIM0_CNT                    _SFR_IO16(0x28) /* TCNT0 */
#define TIM0_CNTL                   _SFR_IO8(0x28)  /* TCNT0L */
#define TIM0_CNTH                   _SFR_IO8(0x29)  /* TCNT0H */
#define TIM0_INTFLAGS               _SFR_IO8(0x2A)  /* TIFR0 */
#define TIM0_INTCTRL                _SFR_IO8(0x2B)  /* TIMSK0 */
#define TIM0_CTRLC                  _SFR_IO8(0x2C)  /* TCCR0C */
#define TIM0_CTRLB                  _SFR_IO8(0x2D)  /* TCCR0B */
#define TIM0_CTRLA                  _SFR_IO8(0x2E)  /* TCCR0A */
#define TIM0_GTCR                   _SFR_IO8(0x2F)  /* GTCCR */

/* TIM0.CTRLA  bit masks and bit positions */
#define TIM_WGMODE_LOW_gm           (0x03<<0)   /* Wave Generation Mode group mask. */
#define TIM_WGMODE_LOW_gp           0           /* Wave Generation Mode group positon. */
#define TIM_WGMODE_0_bm             (1<<0)      /* Wave Generation Mode bit 0 mask. */
#define TIM_WGMODE_0_bp             0           /* Wave Generation Mode bit 0 positon. */
#define TIM_WGMODE_1_bm             (1<<1)      /* Wave Generation Mode bit 1 mask. */
#define TIM_WGMODE_1_bp             1           /* Wave Generation Mode bit 1 positon. */
#define TIM_CPMODE_B_gm             (3<<4)      /* Compare Mode Channel B group mask. */
#define TIM_CPMODE_B_gp             4           /* Compare Mode Channel B group positon. */
#define TIM_CPMODE_B_0_bm           (1<<4)      /* Compare Mode Channel B bit 0 mask. */
#define TIM_CPMODE_B_0_bp           4           /* Compare Mode Channel B bit 0 positon. */
#define TIM_CPMODE_B_1_bm           (1<<5)      /* Compare Mode Channel B bit 1 mask. */
#define TIM_CPMODE_B_1_bp           5           /* Compare Mode Channel B bit 1 positon. */
#define TIM_CPMODE_A_gm             (3<<6)      /* Compare Mode Channel A group mask. */
#define TIM_CPMODE_A_gp             6           /* Compare Mode Channel A group positon. */
#define TIM_CPMODE_A_0_bm           (1<<6)      /* Compare Mode Channel A bit 0 mask. */
#define TIM_CPMODE_A_0_bp           6           /* Compare Mode Channel A bit 0 positon. */
#define TIM_CPMODE_A_1_bm           (1<<7)      /* Compare Mode Channel A bit 1 mask. */
#define TIM_CPMODE_A_1_bp           7           /* Compare Mode Channel A bit 1 positon. */

/* TIM0.CTRLB  bit masks and bit positions */
#define TIM_CLCKSEL_gm              (0x07<<0)   /* Clock Selectoer group mask. */
#define TIM_CLCKSEL_gp              0           /* Clock Selectoer group position. */
#define TIM_CLCKSEL_0_bm            (1<<0)      /* Clock Selectoer bit 0 mask. */
#define TIM_CLCKSEL_0_bp            0           /* Clock Selectoer bit 0 position. */
#define TIM_CLCKSEL_1_bm            (1<<1)      /* Clock Selectoer bit 1 mask. */
#define TIM_CLCKSEL_1_bp            1           /* Clock Selectoer bit 1 position. */
#define TIM_CLCKSEL_2_bm            (1<<2)      /* Clock Selectoer bit 2 mask. */
#define TIM_CLCKSEL_2_bp            2           /* Clock Selectoer bit 2 position. */
#define TIM_WGMODE_HIGH_gm          (0x03<<3)   /* Wave Generation Mode group mask. */
#define TIM_WGMODE_HIGH_gp          3           /* Wave Generation Mode group positon. */
#define TIM_WGMODE_2_bm             (1<<3)      /* Wave Generation Mode bit 2 mask. */
#define TIM_WGMODE_2_bp             3           /* Wave Generation Mode bit 2 positon. */
#define TIM_WGMODE_3_bm             (1<<4)      /* Wave Generation Mode bit 3 mask. */
#define TIM_WGMODE_3_bp             4           /* Wave Generation Mode bit 3 positon. */
#define TIM_CAP_EDGE_bm             (1<<6)      /* Input Capture Edge Select bit mask */
#define TIM_CAP_EDGE_bp             6           /* Input Capture Edge Select bit position */
#define TIM_CAP_NC_bm               (1<<7)      /* Input Capture Noise Canceler bit mask */
#define TIM_CAP_NC_bp               7           /* Input Capture Noise Canceler bit position */

/* TIM0.CTRLB  bit masks and bit positions */
#define TIM_CAPB_STROBE_bm          (1<<6)      /* Force Output Compare for Channel B bit mask. */
#define TIM_CAPB_STROBE_bp          6           /* Force Output Compare for Channel B bit position. */
#define TIM_CAPA_STROBE_bm          (1<<6)      /* Force Output Compare for Channel A bit mask. */
#define TIM_CAPA_STROBE_bp          6           /* Force Output Compare for Channel A bit position. */

/* TIM0.INTCTRL  bit masks and bit positions */
#define TIM_OVF_EN_bm               (1<<0)      /* Overflow Interrupt Enable bit mask. */
#define TIM_OVF_EN_bp               0           /* Overflow Interrupt Enable bit position. */
#define TIM_CMPA_EN_bm              (1<<1)      /* Compare A Match Interrupt Enable bit mask. */
#define TIM_CMPA_EN_bp              1           /* Compare A Match Interrupt Enable bit position. */
#define TIM_CMPB_EN_bm              (1<<2)      /* Compare B Match Interrupt Enable bit mask. */
#define TIM_CMPB_EN_bp              2           /* Compare B Match Interrupt Enable bit position. */
#define TIM_CAP_EN_bm               (1<<5)      /* Input Capture Interrupt Enable bit mask. */
#define TIM_CAP_EN_bp               5           /* Input Capture Interrupt Enable bit position. */

/* TIM0.INTFLAGS  bit masks and bit positions */
/* TIM_OVF_EN  is already defined. */
/* TIM_CMP0A_EN  is already defined. */
/* TIM_CMP0B_EN  is already defined. */
/* TIM_CAP_EN  is already defined. */

/* TIM0.GTCC  bit masks and bit positions */
#define TIM_PS_RST_bm               (1<<0)      /* Prescaler Reset bit mask. */
#define TIM_PS_RST_bp               0           /* Prescaler Reset bit position. */
#define TIM_SYNC_EN_bm              (1<<7)      /* Synchronization Mode bit mask. */
#define TIM_SYNC_EN_bp              7           /* Synchronization Mode bit position. */


/* WDT - Watchdog Timer Contorol */
#define WDT_CTRLA                   _SFR_IO8(0x31)  /* WDTCSR */

/* WDT.CTRLA  bit masks and bit positions */
#define WDT_PDIV_gm                 0x27        /* Prescaler division group mask. */
#define WDT_PDIV_gp                 0           /* Prescaler division group position. */
#define WDT_PDIV_0_bm               (1<<0)      /* Prescaler division bit 0 mask. */
#define WDT_PDIV_0_bp               0           /* Prescaler division bit 0 position. */
#define WDT_PDIV_1_bm               (1<<1)      /* Prescaler division bit 1 mask. */
#define WDT_PDIV_1_bp               1           /* Prescaler division bit 1 position. */
#define WDT_PDIV_2_bm               (1<<2)      /* Prescaler division bit 2 mask. */
#define WDT_PDIV_2_bp               2           /* Prescaler division bit 2 position. */
#define WDT_SRE_bm                  (1<<3)      /* System Reset Enable bit mask. */
#define WDT_SRE_bp                  3           /* System Reset Enable bit position. */
#define WDT_PDIV_3_bm               (1<<5)      /* Prescaler division bit 3 mask. */
#define WDT_PDIV_3_bp               5           /* Prescaler division bit 3 position. */
#define WDT_IE_bm                   (1<<6)      /* Interrupt Enable bit mask. */
#define WDT_IE_bp                   6           /* Interrupt Enable bit position. */
#define WDT_IF_bm                   (1<<7)      /* Interrupt Flag bit mask. */
#define WDT_IF_bp                   7           /* Interrupt Flag bit position. */


/* ========== Generic Port Pins ========== */
#define PIN0_bm 0x01
#define PIN0_bp 0
#define PIN1_bm 0x02
#define PIN1_bp 1
#define PIN2_bm 0x04
#define PIN2_bp 2
#define PIN3_bm 0x08
#define PIN3_bp 3
#define PIN4_bm 0x10
#define PIN4_bp 4
#define PIN5_bm 0x20
#define PIN5_bp 5
#define PIN6_bm 0x40
#define PIN6_bp 6
#define PIN7_bm 0x80
#define PIN7_bp 7

/* ========== Interrupt Vector Definitions ========== */
/* [ defined ioXXX.h ] */
/* Interrupt vectors */
/* Vector 0 is the reset vector */
// #define INT0_vect_num         1
// #define INT0_vect             _VECTOR(1)    /* External Interrupt Request 0 */
// #define PCINT0_vect_num       2
// #define PCINT0_vect           _VECTOR(2)    /* Pin Change Interrupt Request 0 */
// #define TIM0_CAPT_vect_num    3
// #define TIM0_CAPT_vect        _VECTOR(3)    /* Timer/Counter0 Input Capture */
// #define TIM0_OVF_vect_num     4
// #define TIM0_OVF_vect         _VECTOR(4)    /* Timer/Counter0 Overflow */
// #define TIM0_COMPA_vect_num   5
// #define TIM0_COMPA_vect       _VECTOR(5)    /* Timer/Counter Compare Match A */
// #define TIM0_COMPB_vect_num   6
// #define TIM0_COMPB_vect       _VECTOR(6)    /* Timer/Counter Compare Match B */
// #define ANA_COMP_vect_num     7
// #define ANA_COMP_vect         _VECTOR(7)    /* Analog Comparator */
// #define WDT_vect_num          8
// #define WDT_vect              _VECTOR(8)    /* Watchdog Time-out */
// #define VLM_vect_num          9
// #define VLM_vect              _VECTOR(9)    /* Vcc Voltage Level Monitor */
// #define ADC_vect_num          10
// #define ADC_vect              _VECTOR(10)   /* ADC Conversion Complete */

// #define _VECTOR_SIZE          2             /* Size of individual vector. */
// #define _VECTORS_SIZE         (11 * _VECTOR_SIZE)

/* ========== Constants ========== */

/* ========== Fuses ========== */

/* ========== Lock Bits ========== */

/* ========== Signature ========== */

/* end of header */
