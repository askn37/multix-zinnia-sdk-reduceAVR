/**
 * @file variant_io.h
 * @author askn (K.Sato) multix.jp
 * @brief ATtiny102/104 Macro/MicroAPI
 * @version 0.4.2
 * @date 2026-07-20
 *
 * @copyright Copyright (c) 2026 askn37 at github.com
 *
 */
/* MIT License : https://askn37.github.io/LICENSE.html */

#pragma once
#include <avr/io.h>
#define AVR_MODERNAVR_LIKE_REDUCEAVR

/**
 * Points to consider when using `MicroAPI`
 * 
 * The TIM0 module are also referred to as TCB0.
 * 
 * The following declarations derived from io.h will be renamed.
 */
#undef PORTA    /* -> POTA */
#undef PORTB    /* -> POTB */

/* Registers and associated bit numbers. */
#if !defined(ADCL0)
#define ADCL0 0
#define ADCL1 1
#define ADCL2 2
#define ADCL3 3
#define ADCL4 4
#define ADCL5 5
#define ADCL6 6
#define ADCL7 7
#endif
#if !defined(NVMCMD0)
#define NVMCMD0 0
#define NVMCMD1 1
#define NVMCMD2 2
#define NVMCMD3 3
#define NVMCMD4 4
#define NVMCMD5 5
#endif
#if !defined(UCPHA0)
#define UCPHA0  1
#endif
#if !defined(UDORD0)
#define UDORD0  2
#endif

/* Properties */
#if !defined(CCP_IOREG_gc)
#define CCP_IOREG_gc    0xD8    /* IOREG signature for Change Protect */
#endif

#if !defined(CCP_SPM_gc)
#define CCP_SPM_gc      0xE7    /* SPM signature for Change Protect */
#endif


/* C Language Only */
#if !defined (__ASSEMBLER__)

#include <stdint.h>

typedef volatile unsigned char  register8_t;
typedef volatile unsigned short register16_t;

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

#endif


/*================== Bitfield Definitions ================== */

/* AC0.CTRLA [ACSRA] bit masks and bit positions */
#define AC_INTMODE_gm           (3<<ACIS0)      /* Interrupt Mode Select group mask. */
#define AC_INTMODE_gp           ACIS0           /* Interrupt Mode Select group position. */
#define AC_INTMODE_0_bm         (1<<ACIS0)      /* Interrupt Mode Select bit mask. */
#define AC_INTMODE_0_bp         ACIS0           /* Interrupt Mode Select bit position. */
#define AC_INTMODE_1_bm         (1<<ACIS1)      /* Interrupt Mode Select bit mask. */
#define AC_INTMODE_1_bp         ACIS1           /* Interrupt Mode Select bit position. */
#define AC_CAPEN_bm             (1<<ACIC)       /* Input Capture Enable bit mask. */
#define AC_CAPEN_bp             ACIC            /* Input Capture Enable bit position. */
#define AC_IE_bm                (1<<ACIE)       /* Interrupt Enable bit mask. */
#define AC_IE_bp                ACIE            /* Interrupt Enable bit position. */
#define AC_IF_bm                (1<<ACI)        /* Interrupt Flag bit mask. */
#define AC_IF_bp                ACI             /* Interrupt Flag bit position. */
#define AC_OUT_bm               (1<<ACO)        /* Output bit mask. */
#define AC_OUT_bp               ACO             /* Output bit position. */
#define AC_VBGEN_bm             (1<<ACBG)       /* V-BandGap Enable bit mask. */
#define AC_VBGEN_bp             ACBG            /* V-BandGap Enable bit position. */
#define AC_DISABLE_bm           (1<<ACD)        /* Module Disable bit mask. */
#define AC_DISABLE_bp           ACD             /* Module Disable bit position. */

/* AC0.CTRLB [ACSRB] bit masks and bit positions */
#define AC_PIM_bm               (1<<ACPMUX)     /* Positive Input Multiplexer bit mask. */
#define AC_PIM_bp               ACPMUX          /* Positive Input Multiplexer bit position. */
#define AC_OEN_bm               (1<<ACOE)       /* Output pin Enable bit mask. */
#define AC_OEN_bp               ACOE            /* Output pin Enable bit position. */


/* ADC0.MUXPOS [ADMUX] bit masks and bit positions */
#define ADC_MUXPOS_gm           (7<<MUX0)       /* Multiplexer Select group mask. */
#define ADC_MUXPOS_gp           MUX0            /* Multiplexer Select group position. */
#define ADC_MUXPOS_0_bm         (1<<MUX0)       /* Multiplexer Select bit 0 mask. */
#define ADC_MUXPOS_0_bp         MUX0            /* Multiplexer Select bit 0 position. */
#define ADC_MUXPOS_1_bm         (1<<MUX1)       /* Multiplexer Select bit 1 mask. */
#define ADC_MUXPOS_1_bp         MUX1            /* Multiplexer Select bit 1 position. */
#define ADC_MUXPOS_2_bm         (1<<MUX2)       /* Multiplexer Select bit 2 mask. */
#define ADC_MUXPOS_2_bp         MUX2            /* Multiplexer Select bit 2 position. */
#define ADC_MUXNEG_gm           (3<<REFS0)      /* Negative Select group mask. */
#define ADC_MUXNEG_gp           REFS0           /* Negative Select group position. */
#define ADC_MUXNEG_0_bm         (1<<REFS0)      /* Negative Select bit 0 mask. */
#define ADC_MUXNEG_0_bp         REFS0           /* Negative Select bit 0 position. */
#define ADC_MUXNEG_1_bm         (1<<REFS1)      /* Negative Select bit 1 mask. */
#define ADC_MUXNEG_1_bp         REFS1           /* Negative Select bit 1 position. */

/* ADC0.CTRLA [ADCSRA] bit masks and bit positions */
#define ADC_PRESC_gm            (7<<ADPS0)      /* Clock Pre-scaler group mask. */
#define ADC_PRESC_gp            ADPS0           /* Clock Pre-scaler group position. */
#define ADC_PRESC_0_bm          (1<<ADPS0)      /* Clock Pre-scaler bit 0 mask. */
#define ADC_PRESC_0_bp          ADPS0           /* Clock Pre-scaler bit 0 position. */
#define ADC_PRESC_1_bm          (1<<ADPS1)      /* Clock Pre-scaler bit 1 mask. */
#define ADC_PRESC_1_bp          ADPS1           /* Clock Pre-scaler bit 1 position. */
#define ADC_PRESC_2_bm          (1<<ADPS2)      /* Clock Pre-scaler bit 2 mask. */
#define ADC_PRESC_2_bp          ADPS2           /* Clock Pre-scaler bit 2 position. */
#define ADC_IE_bm               (1<<ADIE)       /* Interrupt Enable bit mask. */
#define ADC_IE_bp               ADIE            /* Interrupt Enable bit position. */
#define ADC_IF_bm               (1<<ADIF)       /* Interrupt Flag bit mask. */
#define ADC_IF_bp               ADIF            /* Interrupt Flag bit position. */
#define ADC_ATEN_bm             (1<<ADATE)      /* Automatic Trigger Enable bit mask. */
#define ADC_ATEN_bp             ADATE           /* Automatic Trigger Enable bit position. */
#define ADC_RUN_bm              (1<<ADSC)       /* Start Conversion bit mask. */
#define ADC_RUN_bp              ADSC            /* Start Conversion bit position. */
#define ADC_ENABLE_bm           (1<<ADEN)       /* Enable Module bit mask. */
#define ADC_ENABLE_bp           ADEN            /* Enable Module bit position. */

/* ADC0.CTRLB [ADCSRB] bit masks and bit positions */
#define ADC_ATMODE_gm           (7<<ADTS0)      /* Automatic Trigger group mask. */
#define ADC_ATMODE_gp           ADTS0           /* Automatic Trigger group position. */
#define ADC_ATMODE_0_bm         (1<<ADTS0)      /* Automatic Trigger bit 0 mask. */
#define ADC_ATMODE_0_bp         ADTS0           /* Automatic Trigger bit 0 position. */
#define ADC_ATMODE_1_bm         (1<<ADTS1)      /* Automatic Trigger bit 1 mask. */
#define ADC_ATMODE_1_bp         ADTS1           /* Automatic Trigger bit 1 position. */
#define ADC_ATMODE_2_bm         (1<<ADTS2)      /* Automatic Trigger bit 2 mask. */
#define ADC_ATMODE_2_bp         ADTS2           /* Automatic Trigger bit 2 position. */
#define ADC_LAR_bm              (1<<ADLAR)      /* Left Adjust Result bit mask. */
#define ADC_LAR_bp              ADLAR           /* Left Adjust Result bit position. */


/* CLKCTRL.MCLKCTRLB [CLKPSR] bit masks and bit positions */
#define CLKCTRL_PDIV_gm         0x0F            /* Prescaler division group mask. */
#define CLKCTRL_PDIV_gp         CLKPS0          /* Prescaler division group position. */
#define CLKCTRL_PDIV_0_bm       (1<<CLKPS0)     /* Prescaler division bit 0 mask. */
#define CLKCTRL_PDIV_0_bp       CLKPS0          /* Prescaler division bit 0 position. */
#define CLKCTRL_PDIV_1_bm       (1<<CLKPS1)     /* Prescaler division bit 1 mask. */
#define CLKCTRL_PDIV_1_bp       CLKPS1          /* Prescaler division bit 1 position. */
#define CLKCTRL_PDIV_2_bm       (1<<CLKPS2)     /* Prescaler division bit 2 mask. */
#define CLKCTRL_PDIV_2_bp       CLKPS2          /* Prescaler division bit 2 position. */
#define CLKCTRL_PDIV_3_bm       (1<<CLKPS3)     /* Prescaler division bit 3 mask. */
#define CLKCTRL_PDIV_3_bp       CLKPS3          /* Prescaler division bit 3 position. */
#define CLKCTRL_PEN_bm          0               /* Prescaler division enable dummy mask. */

/* CLKCTRL.MCLKCTRLA [CLKMSR] bit masks and bit positions */
#define CLKCTRL_CLKSEL_gm       0x03            /* Clock select group mask. */
#define CLKCTRL_CLKSEL_gp       CLKMS0          /* Clock select group position. */
#define CLKCTRL_CLKSEL_0_bm     (1<<CLKMS0)     /* Clock select bit 0 mask. */
#define CLKCTRL_CLKSEL_0_bp     CLKMS0          /* Clock select bit 0 position. */
#define CLKCTRL_CLKSEL_1_bm     (1<<CLKMS1)     /* Clock select bit 1 mask. */
#define CLKCTRL_CLKSEL_1_bp     CLKMS1          /* Clock select bit 1 position. */

/* CLKCTRL.OSCCALIB [OSCCAL] bit masks and bit positions */
#define CLKCTRL_OSCCALIB_gm     0xFF            /* Calibration group mask. */
#define CLKCTRL_OSCCALIB_gp     0               /* Calibration group position. */


/* EXTINT.INTCTRL [EIMSK] bit masks and bit positions */
#define EXTINT_INT0_bm          (1<<INT0)       /* External Interrupt 0 bit mask. */
#define EXTINT_INT0_bp          INT0            /* External Interrupt 0 bit position. */

/* EXTINT.INTFLAGS [EIFR] bit masks and bit positions */
/* EXTINT_INT0 [INTF0] is already defined. */

/* EXTINT.CTRLA [EICRA] bit masks and bit positions */
#define EXTINT_EDGE_gm          (3<<ISC00)      /* Interrupt Edge Sense group bit mask */
#define EXTINT_EDGE_gp          ISC00           /* Interrupt Edge Sense group bit position */
#define EXTINT_EDGE_0_bm        (1<<ISC00)      /* Interrupt Edge Sense bit 0 mask */
#define EXTINT_EDGE_0_bp        ISC00           /* Interrupt Edge Sense bit 0 position */
#define EXTINT_EDGE_1_bm        (1<<ISC01)      /* Interrupt Edge Sense bit 1 mask */
#define EXTINT_EDGE_1_bp        ISC01           /* Interrupt Edge Sense bit 1 position */


/* NVMCTRL.STATUS [NVMCSR] bit masks and bit positions */
#define NVMCTRL_BUSY_bm         (1<<NVMBSY)
#define NVMCTRL_BUSY_bp         NVMBSY

/* NVMCTRL.CTRLA [NVMCMD] bit masks and bit positions */
#define NVMCTRL_CMD_gm          0x3F            /* Command group mask. */
#define NVMCTRL_CMD_gp          NVMCMD0         /* Command group position. */
#define NVMCTRL_CMD_0_bm        (1<<NVMCMD0)    /* Command bit 0 mask. */
#define NVMCTRL_CMD_0_bp        NVMCMD0         /* Command bit 0 position. */
#define NVMCTRL_CMD_1_bm        (1<<NVMCMD1)    /* Command bit 1 mask. */
#define NVMCTRL_CMD_1_bp        NVMCMD1         /* Command bit 1 position. */
#define NVMCTRL_CMD_2_bm        (1<<NVMCMD2)    /* Command bit 2 mask. */
#define NVMCTRL_CMD_2_bp        NVMCMD2         /* Command bit 2 position. */
#define NVMCTRL_CMD_3_bm        (1<<NVMCMD3)    /* Command bit 3 mask. */
#define NVMCTRL_CMD_3_bp        NVMCMD3         /* Command bit 3 position. */
#define NVMCTRL_CMD_4_bm        (1<<NVMCMD4)    /* Command bit 4 mask. */
#define NVMCTRL_CMD_4_bp        NVMCMD4         /* Command bit 4 position. */
#define NVMCTRL_CMD_5_bm        (1<<NVMCMD5)    /* Command bit 5 mask. */
#define NVMCTRL_CMD_5_bp        NVMCMD5         /* Command bit 5 position. */


/* PCINT.INTCTRLA [PCMSK0] bit masks and bit positions */
#define PCINT_PORTA_0_bm        (1<<PCINT0)     /* PCINT PORTA 0 Enable bit mask. */
#define PCINT_PORTA_0_bp        PCINT0          /* PCINT PORTA 0 Enable bit position. */
#define PCINT_PORTA_1_bm        (1<<PCINT1)     /* PCINT PORTA 1 Enable bit mask. */
#define PCINT_PORTA_1_bp        PCINT1          /* PCINT PORTA 1 Enable bit position. */
#define PCINT_PORTA_2_bm        (1<<PCINT2)     /* PCINT PORTA 2 Enable bit mask. */
#define PCINT_PORTA_2_bp        PCINT2          /* PCINT PORTA 2 Enable bit position. */
#if !defined(__AVR_ATtiny102__)
#define PCINT_PORTA_3_bm        (1<<PCINT3)     /* PCINT PORTA 3 Enable bit mask. */
#define PCINT_PORTA_3_bp        PCINT3          /* PCINT PORTA 3 Enable bit position. */
#define PCINT_PORTA_4_bm        (1<<PCINT4)     /* PCINT PORTA 4 Enable bit mask. */
#define PCINT_PORTA_4_bp        PCINT4          /* PCINT PORTA 4 Enable bit position. */
#define PCINT_PORTA_5_bm        (1<<PCINT5)     /* PCINT PORTA 5 Enable bit mask. */
#define PCINT_PORTA_5_bp        PCINT5          /* PCINT PORTA 5 Enable bit position. */
#define PCINT_PORTA_6_bm        (1<<PCINT6)     /* PCINT PORTA 6 Enable bit mask. */
#define PCINT_PORTA_6_bp        PCINT6          /* PCINT PORTA 6 Enable bit position. */
#define PCINT_PORTA_7_bm        (1<<PCINT7)     /* PCINT PORTA 7 Enable bit mask. */
#define PCINT_PORTA_7_bp        PCINT7          /* PCINT PORTA 7 Enable bit position. */

/* PCINT.INTCTRLB [PCMSK1] bit masks and bit positions */
#define PCINT_PORTB_0_bm        (1<<PCINT8)     /* PCINT PORTB 0 Enable bit mask. */
#define PCINT_PORTB_0_bp        PCINT8          /* PCINT PORTB 0 Enable bit position. */
#define PCINT_PORTA_gm          (0xFF)          /* PCINT PORTA Enable group mask. */
#define PCINT_PORTB_gm          (0x0F)          /* PCINT PORTB Enable group mask. */
#else
#define PCINT_PORTA_gm          (0x07)          /* PCINT PORTA Enable group mask. */
#define PCINT_PORTB_gm          (0x0E)          /* PCINT PORTB Enable group mask. */
#endif
#define PCINT_PORTB_1_bm        (1<<PCINT9)     /* PCINT PORTB 1 Enable bit mask. */
#define PCINT_PORTB_1_bp        PCINT9          /* PCINT PORTB 1 Enable bit position. */
#define PCINT_PORTB_2_bm        (1<<PCINT10)    /* PCINT PORTB 2 Enable bit mask. */
#define PCINT_PORTB_2_bp        PCINT10         /* PCINT PORTB 2 Enable bit position. */
#define PCINT_PORTB_3_bm        (1<<PCINT11)    /* PCINT PORTB 3 Enable bit mask. */
#define PCINT_PORTB_3_bp        PCINT11         /* PCINT PORTB 3 Enable bit position. */

/* PCINT.INTFLAGS [PCIFR] bit masks and bit positions */
#define PCINT_PORTA_bm          (1<<PCIF0)      /* PCINT PORTA bit mask. */
#define PCINT_PORTA_bp          PCIF0           /* PCINT PORTA bit position. */
#define PCINT_PORTB_bm          (1<<PCIF1)      /* PCINT PORTB bit mask. */
#define PCINT_PORTB_bp          PCIF1           /* PCINT PORTB bit position. */

/* PCINT.CTRLA [PCICR] bit masks and bit positions */
/* PCINT_PORTA [PCIE0] is already defined. */
/* PCINT_PORTB [PCIE1] is already defined. */


/* PORTCTRL.CTRLA [PORTCR] bit masks and bit positions */
#define PORTCTRL_BBMAE_bm       (1<<BBMA)       /* Break-Before-Make PORTA Enable bit mask. */
#define PORTCTRL_BBMAE_bp       BBMA            /* Break-Before-Make PORTA Enable bit position. */
#define PORTCTRL_BBMBE_bm       (1<<BBMB)       /* Break-Before-Make PORTB Enable bit mask. */
#define PORTCTRL_BBMBE_bp       BBMB            /* Break-Before-Make PORTB Enable bit position. */

/* PORTCTRL.CTRLB [DIDR0] bit masks and bit positions */
#define PORTCTRL_DID0_gm        0xFF            /* Digital Input Disable 0 group mask. */
#define PORTCTRL_DID0_gp        ADC0D           /* Digital Input Disable 0 group position. */
#define PORTCTRL_AINN_bm        (1<<AIN0D)      /* AC Input pin 0 (NEG) Enable bit mask. */
#define PORTCTRL_AINN_bp        AIN0D           /* AC Input pin 0 (NEG) Enable bit position. */
#define PORTCTRL_AINP_bm        (1<<AIN1D)      /* AC Input pin 1 (POS) Enable bit mask. */
#define PORTCTRL_AINP_bp        AIN1D           /* AC Input pin 1 (POS) Enable bit position. */
#define PORTCTRL_AIN0_bm        (1<<ADC0D)      /* ADC input pin 0 Enable bit mask. */
#define PORTCTRL_AIN0_bp        ADC0D           /* ADC input pin 0 Enable bit position. */
#define PORTCTRL_AIN1_bm        (1<<ADC1D)      /* ADC input pin 1 Enable bit mask. */
#define PORTCTRL_AIN1_bp        ADC1D           /* ADC input pin 1 Enable bit position. */
#if !defined(__AVR_ATtiny102__)
#define PORTCTRL_AIN2_bm        (1<<ADC2D)      /* ADC input pin 2 Enable bit mask. */
#define PORTCTRL_AIN2_bp        ADC2D           /* ADC input pin 2 Enable bit position. */
#define PORTCTRL_AIN3_bm        (1<<ADC3D)      /* ADC input pin 3 Enable bit mask. */
#define PORTCTRL_AIN3_bp        ADC3D           /* ADC input pin 3 Enable bit position. */
#define PORTCTRL_AIN4_bm        (1<<ADC4D)      /* ADC input pin 4 Enable bit mask. */
#define PORTCTRL_AIN4_bp        ADC4D           /* ADC input pin 4 Enable bit position. */
#endif
#define PORTCTRL_AIN5_bm        (1<<ADC5D)      /* ADC input pin 5 Enable bit mask. */
#define PORTCTRL_AIN5_bp        ADC5D           /* ADC input pin 5 Enable bit position. */
#define PORTCTRL_AIN6_bm        (1<<ADC6D)      /* ADC input pin 6 Enable bit mask. */
#define PORTCTRL_AIN6_bp        ADC6D           /* ADC input pin 6 Enable bit position. */
#define PORTCTRL_AIN7_bm        (1<<ADC7D)      /* ADC input pin 7 Enable bit mask. */
#define PORTCTRL_AIN7_bp        ADC7D           /* ADC input pin 7 Enable bit position. */


/* RSTCTRL.RSTFR [RSTFLR] bit masks and bit positions */
#define RSTCTRL_PORF_bm         (1<<PORF)       /* Power on Reset flag bit mask. */
#define RSTCTRL_PORF_bp         PORF            /* Power on Reset flag bit position. */
#define RSTCTRL_EXTRF_bm        (1<<EXTRF)      /* External Reset flag bit mask. */
#define RSTCTRL_EXTRF_bp        EXTRF           /* External Reset flag bit position. */
#define RSTCTRL_WDRF_bm         (1<<WDRF)       /* Watch dog Reset flag bit mask. */
#define RSTCTRL_WDRF_bp         WDRF            /* Watch dog Reset flag bit position. */


/* SLPCTRL.CTRLA [SMCR] bit masks and bit positions */
#define SLPCTRL_ENABLE_bm       (1<<SE)         /* Enable Module bit mask. */
#define SLPCTRL_ENABLE_bp       SE              /* Enable Module bit position. */
#define SLPCTRL_SMODE_gm        (7<<SM0)        /* Sleep mode group mask. */
#define SLPCTRL_SMODE_gp        SM0             /* Sleep mode group position. */
#define SLPCTRL_SMODE_0_bm      (1<<SM0)        /* Sleep mode bit 0 mask. */
#define SLPCTRL_SMODE_0_bp      SM0             /* Sleep mode bit 0 position. */
#define SLPCTRL_SMODE_1_bm      (1<<SM1)        /* Sleep mode bit 1 mask. */
#define SLPCTRL_SMODE_1_bp      SM1             /* Sleep mode bit 1 position. */
#define SLPCTRL_SMODE_2_bm      (1<<SM2)        /* Sleep mode bit 2 mask. */
#define SLPCTRL_SMODE_2_bp      SM2             /* Sleep mode bit 2 position. */

/* SLPCTRL.CTRLB [PRR] bit masks and bit positions */
#define SLPCTRL_TCB0_bm         (1<<PRTIM0)     /* Power reduction TCB0 bit mask. */
#define SLPCTRL_TCB0_bp         PRTIM0          /* Power reduction TCB0 bit position. */
#define SLPCTRL_ADC0_bm         (1<<PRADC)      /* Power reduction ADC0 bit mask. */
#define SLPCTRL_ADC0_bp         PRADC           /* Power reduction ADC0 bit position. */
#define SLPCTRL_USART0_bm       (1<<PRUSART)    /* Power reduction USART0 bit mask. */
#define SLPCTRL_USART0_bp       PRUSART         /* Power reduction USART0 bit position. */

/* [ defined ioXXX.h ] */
/* #define SLEEP_MODE_IDLE         (0x00<<1) */
/* #define SLEEP_MODE_ADC          (0x01<<1) */
/* #define SLEEP_MODE_PWR_DOWN     (0x02<<1) */
/* #define SLEEP_MODE_STANDBY      (0x04<<1) */


/* TCB0.CTRLA [TCCR0A] bit masks and bit positions */
#define TCB_WGMODE_A_gm         (0x03<<WGM00)   /* Wave Generation Mode group mask. */
#define TCB_WGMODE_A_gp         WGM00           /* Wave Generation Mode group positon. */
#define TCB_WGMODE_0_bm         (1<<WGM00)      /* Wave Generation Mode bit 0 mask. */
#define TCB_WGMODE_0_bp         WGM00           /* Wave Generation Mode bit 0 positon. */
#define TCB_WGMODE_1_bm         (1<<WGM01)      /* Wave Generation Mode bit 1 mask. */
#define TCB_WGMODE_1_bp         WGM01           /* Wave Generation Mode bit 1 positon. */
#define TCB_WOB_gm              (3<<COM0B0)     /* Compare Mode Channel B group mask. */
#define TCB_WOB_gp              COM0B0          /* Compare Mode Channel B group positon. */
#define TCB_WOB_0_bm            (1<<COM0B0)     /* Compare Mode Channel B bit 0 mask. */
#define TCB_WOB_0_bp            COM0B0          /* Compare Mode Channel B bit 0 positon. */
#define TCB_WOB_1_bm            (1<<COM0B1)     /* Compare Mode Channel B bit 1 mask. */
#define TCB_WOB_1_bp            COM0B1          /* Compare Mode Channel B bit 1 positon. */
#define TCB_WOA_gm              (3<<COM0A0)     /* Compare Mode Channel A group mask. */
#define TCB_WOA_gp              COM0A0          /* Compare Mode Channel A group positon. */
#define TCB_WOA_0_bm            (1<<COM0A0)     /* Compare Mode Channel A bit 0 mask. */
#define TCB_WOA_0_bp            COM0A0          /* Compare Mode Channel A bit 0 positon. */
#define TCB_WOA_1_bm            (1<<COM0A1)     /* Compare Mode Channel A bit 1 mask. */
#define TCB_WOA_1_bp            COM0A1          /* Compare Mode Channel A bit 1 positon. */

/* TCB0.CTRLB [TCCR0B] bit masks and bit positions */
#define TCB_CLCKSEL_gm          (7<<CS00)       /* Clock Selectoer group mask. */
#define TCB_CLCKSEL_gp          CS00            /* Clock Selectoer group position. */
#define TCB_CLCKSEL_0_bm        (1<<CS00)       /* Clock Selectoer bit 0 mask. */
#define TCB_CLCKSEL_0_bp        CS00            /* Clock Selectoer bit 0 position. */
#define TCB_CLCKSEL_1_bm        (1<<CS01)       /* Clock Selectoer bit 1 mask. */
#define TCB_CLCKSEL_1_bp        CS01            /* Clock Selectoer bit 1 position. */
#define TCB_CLCKSEL_2_bm        (1<<CS02)       /* Clock Selectoer bit 2 mask. */
#define TCB_CLCKSEL_2_bp        CS02            /* Clock Selectoer bit 2 position. */
#define TCB_WGMODE_B_gm         (3<<WGM02)      /* Wave Generation Mode group mask. */
#define TCB_WGMODE_B_gp         WGM02           /* Wave Generation Mode group positon. */
#define TCB_WGMODE_2_bm         (1<<WGM02)      /* Wave Generation Mode bit 2 mask. */
#define TCB_WGMODE_2_bp         WGM02           /* Wave Generation Mode bit 2 positon. */
#define TCB_WGMODE_3_bm         (1<<WGM03)      /* Wave Generation Mode bit 3 mask. */
#define TCB_WGMODE_3_bp         WGM03           /* Wave Generation Mode bit 3 positon. */
#define TCB_CAP_EDGE_bm         (1<<ICES0)      /* Input Capture Edge Select bit mask */
#define TCB_CAP_EDGE_bp         ICES0           /* Input Capture Edge Select bit position */
#define TCB_CAP_NC_bm           (1<<ICNC0)      /* Input Capture Noise Canceler bit mask */
#define TCB_CAP_NC_bp           ICNC0           /* Input Capture Noise Canceler bit position */

/* TCB0.CTRLC [TCCR0C] bit masks and bit positions */
#define TCB_STROBEB_bm          (1<<FOC0B)      /* Force Output Compare Channel B bit mask. */
#define TCB_STROBEB_bp          FOC0B           /* Force Output Compare Channel B bit position. */
#define TCB_STROBEA_bm          (1<<FOC0A)      /* Force Output Compare Channel A bit mask. */
#define TCB_STROBEA_bp          FOC0A           /* Force Output Compare Channel A bit position. */

/* TCB0.INTCTRL [TIMSK0] bit masks and bit positions */
#define TCB_OVF_bm              (1<<TOIE0)      /* Overflow Interrupt Enable bit mask. */
#define TCB_OVF_bp              TOIE0           /* Overflow Interrupt Enable bit position. */
#define TCB_CMPA_bm             (1<<OCIE0A)     /* Compare A Match Interrupt Enable bit mask. */
#define TCB_CMPA_bp             OCIE0A          /* Compare A Match Interrupt Enable bit position. */
#define TCB_CMPB_bm             (1<<OCIE0B)     /* Compare B Match Interrupt Enable bit mask. */
#define TCB_CMPB_bp             OCIE0B          /* Compare B Match Interrupt Enable bit position. */
#define TCB_CAP_bm              (1<<ICIE0)      /* Input Capture Interrupt Enable bit mask. */
#define TCB_CAP_bp              ICIE0           /* Input Capture Interrupt Enable bit position. */

/* TCA0.INTFLAGS [TIFR0] bit masks and bit positions */
/* TCA_OVF [TOV0] is already defined. */
/* TCA_CMPA [OCF0A] is already defined. */
/* TCA_CMPB [OCF0B] is already defined. */
/* TCA_CAP [ICF0] is already defined. */


/* TCB0.CTRLD [GTCCR] bit masks and bit positions */
#define TCB_PSRESET_bm          (1<<PSR)        /* Prescaler Reset bit mask. */
#define TCB_PSRESET_bp          PSR             /* Prescaler Reset bit position. */
#define TCB_IO_ALT_bm           (1<<REMAP)      /* IO Remap pin alternate bit mask. */
#define TCB_IO_ALT_bp           REMAP           /* IO Remap pin alternate bit position. */
#define TCB_SYNC_EN_bm          (1<<TSM)        /* Synchronization Mode bit mask. */
#define TCB_SYNC_EN_bp          TSM             /* Synchronization Mode bit position. */


/* USART0.CTRLA [UCSRA] bit masks and bit positions */
#define USART_MPCM_bm           (1<<MPCM)       /* Multi-processor Communication Mode bit mask. */
#define USART_MPCM_bp           MPCM            /* Multi-processor Communication Mode bit position. */
#define USART_CLK2X_bm          (1<<U2X)        /* Double the USART Transmission Speed bit mask. */
#define USART_CLK2X_bp          U2X             /* Double the USART Transmission Speed bit position. */
#define USART_PERR_bm           (1<<UPE)        /* Parity Error bit mask. */
#define USART_PERR_bp           UPE             /* Parity Error bit position. */
#define USART_BUFOVF_bm         (1<<DOR)        /* Buffer Overflow bit mask. */
#define USART_BUFOVF_bp         DOR             /* Buffer Overflow bit position. */
#define USART_FERR_bm           (1<<FE)         /* Frame Error bit mask. */
#define USART_FERR_bp           FE              /* Frame Error bit position. */
#define USART_DREIF_bm          (1<<UDRE)       /* Data Register Empty Flag bit mask. */
#define USART_DREIF_bp          UDRE            /* Data Register Empty Flag bit position. */
#define USART_TXCIF_bm          (1<<TXC)        /* Transmit Complete Interrupt Flag bit mask. */
#define USART_TXCIF_bp          TXC             /* Transmit Complete Interrupt Flag bit position. */
#define USART_RXCIF_bm          (1<<RXC)        /* Receive Complete Interrupt Flag bit mask. */
#define USART_RXCIF_bp          RXC             /* Receive Complete Interrupt Flag bit position. */

/* USART0.CTRLB [UCSRB] bit masks and bit positions */
#define USART_TXD8_bm           (1<<TXB8)       /* Transmit Data Bit-8 bit mask. */
#define USART_TXD8_bp           TXB8            /* Transmit Data Bit-8 bit position. */
#define USART_RXD8_bm           (1<<RXB8)       /* Receive Data Bit-8 bit mask. */
#define USART_RXD8_bp           RXB8            /* Receive Data Bit-8 bit position. */
#define USART_CHSIZE_2_bm       (1<<UCSZ2)      /* Character Size bit 2 mask. */
#define USART_CHSIZE_2_bp       UCSZ2           /* Character Size bit 2 position. */
#define USART_TXEN_bm           (1<<TXEN)       /* Transmitter Enable bit mask. */
#define USART_TXEN_bp           TXEN            /* Transmitter Enable bit position. */
#define USART_RXEN_bm           (1<<RXEN)       /* Receiver Enable bit mask. */
#define USART_RXEN_bp           RXEN            /* Receiver Enable bit position. */
#define USART_DREIE_bm          (1<<UDRIE)      /* Data Register Empty Interrupt Enable bit mask. */
#define USART_DREIE_bp          UDRIE           /* Data Register Empty Interrupt Enable bit position. */
#define USART_TXCIE_bm          (1<<TXCIE)      /* Transmit Complete Interrupt Enable bit mask. */
#define USART_TXCIE_bp          TXCIE           /* Transmit Complete Interrupt Enable bit position. */
#define USART_RXCIE_bm          (1<<RXCIE)      /* Receive Complete Interrupt Enable bit mask. */
#define USART_RXCIE_bp          RXCIE           /* Receive Complete Interrupt Enable bit position. */

/* USART0.CTRLC [UCSRC] bit masks and bit positions */
#define USART_CPOL_bm           (1<<UCPOL)      /* SPI Host Mode, Clock Polarity bit mask. */
#define USART_CPOL_bp           UCPOL           /* SPI Host Mode, Clock Polarity bit position. */
#define USART_CPHA_bm           (1<<UCPHA0)     /* SPI Host Mode, Clock Phase bit mask. */
#define USART_CPHA_bp           UCPHA0          /* SPI Host Mode, Clock Phase bit position. */
#define USART_UDORD_bm          (1<<UCPHA0)     /* SPI Host Mode, Data Order bit mask. */
#define USART_UDORD_bp          UCPHA0          /* SPI Host Mode, Data Order bit position. */
#define USART_CHSIZEL_gm        (3<<UCSZ0)      /* Character Size group mask. */
#define USART_CHSIZEL_gp        UCSZ0           /* Character Size group position. */
#define USART_CHSIZE_0_bm       (1<<UCSZ0)      /* Character Size bit 0 mask. */
#define USART_CHSIZE_0_bp       UCSZ0           /* Character Size bit 0 position. */
#define USART_CHSIZE_1_bm       (1<<UCSZ1)      /* Character Size bit 1 mask. */
#define USART_CHSIZE_1_bp       UCSZ1           /* Character Size bit 1 position. */
#define USART_SBMODE_bm         (1<<USBS)       /* Stop Bit Mode bit mask. */
#define USART_SBMODE_bp         USBS            /* Stop Bit Mode bit position. */
#define USART_PMODE_gm          (3<<UPM0)       /* Parity Mode group mask. */
#define USART_PMODE_gp          UPM0            /* Parity Mode group position. */
#define USART_PMODE_0_bm        (1<<UPM0)       /* Parity Mode bit 0 mask. */
#define USART_PMODE_0_bp        UPM0            /* Parity Mode bit 0 position. */
#define USART_PMODE_1_bm        (1<<UPM1)       /* Parity Mode bit 1 mask. */
#define USART_PMODE_1_bp        UPM1            /* Parity Mode bit 1 position. */
#define USART_CMODE_gm          (3<<UMSEL0)     /* Communication Mode group mask. */
#define USART_CMODE_gp          UMSEL0          /* Communication Mode group position. */
#define USART_CMODE_0_bm        (1<<UMSEL0)     /* Communication Mode bit 0 mask. */
#define USART_CMODE_0_bp        UMSEL0          /* Communication Mode bit 0 position. */
#define USART_CMODE_1_bm        (1<<UMSEL1)     /* Communication Mode bit 1 mask. */
#define USART_CMODE_1_bp        UMSEL1          /* Communication Mode bit 1 position. */

/* USART0.CTRLD [UCSRD] bit masks and bit positions */
#define USART_SFDEN_bm          (1<<SFDE)       /* Start Frame Detection Enable bit mask. */
#define USART_SFDEN_bp          SFDE            /* Start Frame Detection Enable bit position. */
#define USART_RXSIF_bm          (1<<RXS)        /* RX Start Interrupt Flag bit mask. */
#define USART_RXSIF_bp          RXS             /* RX Start Interrupt Flag bit position. */
#define USART_RXSIE_bm          (1<<RXSIE)      /* RX Start Interrupt Enable bit mask. */
#define USART_RXSIE_bp          RXSIE           /* RX Start Interrupt Enable bit position. */


/* VLM.CTRLA [VLMCSR] bit masks and bit positions */
#define VLM_LEVEL_gm            (7<<VLM0)       /* Trigger Level group mask. */
#define VLM_LEVEL_gp            VLM0            /* Trigger Level group position. */
#define VLM_LEVEL_0_bm          (1<<VLM0)       /* Trigger Level bit 0 mask. */
#define VLM_LEVEL_0_bp          VLM0            /* Trigger Level bit 0 position. */
#define VLM_LEVEL_1_bm          (1<<VLM1)       /* Trigger Level bit 1 mask. */
#define VLM_LEVEL_1_bp          VLM1            /* Trigger Level bit 1 position. */
#define VLM_LEVEL_2_bm          (1<<VLM2)       /* Trigger Level bit 2 mask. */
#define VLM_LEVEL_2_bp          VLM2            /* Trigger Level bit 2 position. */
#define VLM_IE_bm               (1<<VLMIE)      /* Interrupt Enable bit mask. */
#define VLM_IE_bp               VLMIE           /* Interrupt Enable bit position. */
#define VLM_IF_bm               (1<<VLMF)       /* Interrupt Flag bit mask. */
#define VLM_IF_bp               VLMF            /* Interrupt Flag bit position. */


/* WDT.CTRLA [WDTCSR] bit masks and bit positions */
#define WDT_PDIV_gm             0x27            /* Prescaler division group mask. */
#define WDT_PDIV_gp             WDP0            /* Prescaler division group position. */
#define WDT_PDIV_0_bm           (1<<WDP0)       /* Prescaler division bit 0 mask. */
#define WDT_PDIV_0_bp           WDP0            /* Prescaler division bit 0 position. */
#define WDT_PDIV_1_bm           (1<<WDP1)       /* Prescaler division bit 1 mask. */
#define WDT_PDIV_1_bp           WDP1            /* Prescaler division bit 1 position. */
#define WDT_PDIV_2_bm           (1<<WDP2)       /* Prescaler division bit 2 mask. */
#define WDT_PDIV_2_bp           WDP2            /* Prescaler division bit 2 position. */
#define WDT_SREN_bm             (1<<WDE)        /* System Reset Enable bit mask. */
#define WDT_SREN_bp             WDE             /* System Reset Enable bit position. */
#define WDT_PDIV_3_bm           (1<<WDP3)       /* Prescaler division bit 3 mask. */
#define WDT_PDIV_3_bp           WDP3            /* Prescaler division bit 3 position. */
#define WDT_IE_bm               (1<<WDIE)       /* Interrupt Enable bit mask. */
#define WDT_IE_bp               WDIE            /* Interrupt Enable bit position. */
#define WDT_IF_bm               (1<<WDIF)       /* Interrupt Flag bit mask. */
#define WDT_IF_bp               WDIF            /* Interrupt Flag bit position. */


/* C Language Only */
#if !defined (__ASSEMBLER__)
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
    register8_t CTRLB;          /* $1E ACSRB : Analog Comparator Control B */
    register8_t CTRLA;          /* $1F ACSRA : Analog Comparator Control A */
} AC_t;

/* Interrupt Mode select */
typedef enum AC_INTMODE_enum
{
    AC_INTMODE_BOTHEDGES_gc     = (0<<ACIS0),   /* Edge Sense Both Edges */
    AC_INTMODE_FALLING_gc       = (2<<ACIS0),   /* Edge Sense Falling Edge */
    AC_INTMODE_RISING_gc        = (3<<ACIS0)    /* Edge Sense Rising Edge */
} AC_INTMODE_t;


/*
--------------------------------------------------------------------------
ADC - Analog to Digital Converter
--------------------------------------------------------------------------
*/

/* Analog to Digital Converter */
typedef struct ADC_struct
{
    _WORDREGISTER(RES);         /* $19 ADCL      : data Result register */
    register8_t MUXPOS;         /* $1B ADMUX     : Multiplexer Positive Selector */
    register8_t CTRLB;          /* $1C ADCSRB    : Control B */
    register8_t CTRLA;          /* $1D ADCSRA    : Control A */
} ADC_t;

/* Analog Channel Selection Bits */
typedef enum ADC_MUXPOS_enum
{
    ADC_MUXPOS_AIN0_gc          = (0<<MUX0),    /* Multiplexer Select PA0 */
    ADC_MUXPOS_AIN1_gc          = (1<<MUX0),    /* Multiplexer Select PA1 */
#if !defined(__AVR_ATtiny102__)
    ADC_MUXPOS_AIN2_gc          = (2<<MUX0),    /* Multiplexer Select PA5 */
    ADC_MUXPOS_AIN3_gc          = (3<<MUX0),    /* Multiplexer Select PA6 */
    ADC_MUXPOS_AIN4_gc          = (4<<MUX0),    /* Multiplexer Select PB0 */
#endif
    ADC_MUXPOS_AIN5_gc          = (5<<MUX0),    /* Multiplexer Select PB1 */
    ADC_MUXPOS_AIN6_gc          = (6<<MUX0),    /* Multiplexer Select PB2 */
    ADC_MUXPOS_AIN7_gc          = (7<<MUX0)     /* Multiplexer Select PB3 */
} ADC_MUXPOS_t;

/* Analog Reference Selection Bits */
typedef enum ADC_MUXNEG_enum
{
    ADC_MUXNEG_VCC_gc           = (0<<REFS0),   /* Negative Reference Select VCC */
    ADC_MUXNEG_VBG_1V1_gc       = (1<<REFS0),   /* Negative Reference Select VREF 1.1V */
    ADC_MUXNEG_VBG_2V2_gc       = (2<<REFS0),   /* Negative Reference Select VREF 2.2V */
    ADC_MUXNEG_VBG_4V2_gc       = (3<<REFS0)    /* Negative Reference Select VREF 4.2V */
} ADC_MUXNEG_t;

/* Clock Pre-scaler select */
typedef enum ADC_PRESC_enum
{
    ADC_PRESC_DEFAULT_gc        = (0<<ADPS0),   /* CLK_PER default (divided by 2) */
    ADC_PRESC_DIV2_gc           = (1<<ADPS0),   /* CLK_PER divided by 2 */
    ADC_PRESC_DIV4_gc           = (2<<ADPS0),   /* CLK_PER divided by 4 */
    ADC_PRESC_DIV8_gc           = (3<<ADPS0),   /* CLK_PER divided by 8 */
    ADC_PRESC_DIV16_gc          = (4<<ADPS0),   /* CLK_PER divided by 16 */
    ADC_PRESC_DIV32_gc          = (5<<ADPS0),   /* CLK_PER divided by 32 */
    ADC_PRESC_DIV64_gc          = (6<<ADPS0),   /* CLK_PER divided by 64 */
    ADC_PRESC_DIV128_gc         = (7<<ADPS0)    /* CLK_PER divided by 128 */
} ADC_PRESC_t;

/* Automatic Trigger Source select */
typedef enum ADC_ATS_enum
{
    ADC_ATMODE_FREERUN_gc       = (0<<ADTS0),   /* Free Running mode */
    ADC_ATMODE_AC0_OUT_gc       = (1<<ADTS0),   /* Analog Comparator OUT */
    ADC_ATMODE_EXTINT_gc        = (2<<ADTS0),   /* External Interrupt Request */
    ADC_ATMODE_TCB0_CMPA_gc     = (3<<ADTS0),   /* Timer/Counter 0 Compare Match A */
    ADC_ATMODE_TCB0_OVF_gc      = (4<<ADTS0),   /* Timer/Counter 0 Overflow */
    ADC_ATMODE_TCB0_CMPB_gc     = (5<<ADTS0),   /* Timer/Counter 0 Compare Match B */
    ADC_ATMODE_PCINT_gc         = (6<<ADTS0),   /* Pin Change Interrupt Request */
    ADC_ATMODE_TCB0_CAPT_gc     = (7<<ADTS0)    /* Timer/Counter 0 Capture Event */
} ADC_ATS_t;


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
    register8_t reserved[1];
    register8_t OSCCALIB;       /* $39 OSCCAL : Oscillator Calibration Register */
} CLKCTRL_t;

/* Clock select */
typedef enum CLKCTRL_CLKSEL_enum
{
    CLKCTRL_CLKSEL_OSC8M_gc     = (0<<CLKMS0),  /* 8MHz oscillator */
    CLKCTRL_CLKSEL_OSC128K_gc   = (1<<CLKMS0),  /* 128KHz oscillator */
    CLKCTRL_CLKSEL_EXTCLK_gc    = (2<<CLKMS0)   /* External clock */
} CLKCTRL_CLKSEL_t;

/* Prescaler division select */
typedef enum CLKCTRL_PDIV_enum
{
    CLKCTRL_PDIV_1X_gc          = (0<<CLKPS0),  /* 1X */
    CLKCTRL_PDIV_2X_gc          = (1<<CLKPS0),  /* 2X */
    CLKCTRL_PDIV_4X_gc          = (2<<CLKPS0),  /* 4X */
    CLKCTRL_PDIV_8X_gc          = (3<<CLKPS0),  /* 8X */
    CLKCTRL_PDIV_16X_gc         = (4<<CLKPS0),  /* 16X */
    CLKCTRL_PDIV_32X_gc         = (5<<CLKPS0),  /* 32X */
    CLKCTRL_PDIV_64X_gc         = (6<<CLKPS0),  /* 64X */
    CLKCTRL_PDIV_128X_gc        = (7<<CLKPS0),  /* 128X */
    CLKCTRL_PDIV_256X_gc        = (8<<CLKPS0)   /* 256X */
} CLKCTRL_PDIV_t;


/*
--------------------------------------------------------------------------
EXTINT - External Interrupt Controller
--------------------------------------------------------------------------
*/

/* External Interrupt Controller */
typedef struct EXTINT_struct
{
    register8_t INTCTRL;        /* $13 EIMSK : External Interrupt Mask Register */
    register8_t INTFLAGS;       /* $14 EIFR  : External Interrupt Flag Register */
    register8_t CTRLA;          /* $15 EICRA : External Interrupt Control Register A */
} EXTINT_t;

/* Input Edge Sense Configuration select */
typedef enum EXTINT_EDGE_enum
{
    EXTINT_EDGE_LEVEL_gc        = (0<<ISC00),   /* Edge Sense low Level */
    EXTINT_EDGE_BOTHEDGES_gc    = (1<<ISC00),   /* Edge Sense Both Edges */
    EXTINT_EDGE_FALLING_gc      = (2<<ISC00),   /* Edge Sense Falling Edge */
    EXTINT_EDGE_RISING_gc       = (3<<ISC00)    /* Edge Sense Rising Edge */
} EXTINT_EDGE_t;


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
    NVMCTRL_CMD_NONE_gc         = (0x00<<NVMCMD0),  /* No command */
    NVMCTRL_CMD_CHIPERASE_gc    = (0x10<<NVMCMD0),  /* Chip erase */
    NVMCTRL_CMD_PAGEERASE_gc    = (0x14<<NVMCMD0),  /* Section erase */
    NVMCTRL_CMD_WORDWRITE_gc    = (0x1D<<NVMCMD0)   /* Word write */
} NVMCTRL_CMD_t;


/*
--------------------------------------------------------------------------
PCINT - Pin Change Interrupt Controller
--------------------------------------------------------------------------
*/

typedef struct PCINT_struct
{
    register8_t INTCTRLA;       /* $0F PCMSK0 : Pin Change Mask Register 0 */
    register8_t INTCTRLB;       /* $10 PCMSK1 : Pin Change Mask Register 1 */
    register8_t INTFLAGS;       /* $11 PCIFR  : Pin Change Interrupt Flag Register */
    register8_t CTRLA;          /* $12 PCICR  : Pin Change Interrupt Control Register */
} PCINT_t;


/*
--------------------------------------------------------------------------
PORTx - Ports controller
--------------------------------------------------------------------------
*/

/* Ports */
typedef struct PORT_struct
{
    register8_t IN;             /* $00 INx   : Input Value */
    register8_t DIR;            /* $01 DDRx  : Data Direction */
    register8_t OUT;            /* $02 PORTx : Output Value */
    register8_t PUE;            /* $03 PUEx  : Pullup Enable Value */
} PORT_t;

/* Port Control */
typedef struct PORTCTRL_struct
{
    register8_t CTRLA;          /* $16 PORTCR : Port Control Register */
    register8_t CTRLB;          /* $17 DIDR0  : Digital Input Disable Register 0 */
} PORTCTRL_t;


/*
--------------------------------------------------------------------------
RSTCTRL - Reset controller
--------------------------------------------------------------------------
*/

/* Reset controller */
typedef struct RSTCTRL_struct
{
    register8_t RSTFR;          /* $3B RSTFLR : Reset control Register */
} RSTCTRL_t;


/*
--------------------------------------------------------------------------
SLPCTRL - Sleep controller
--------------------------------------------------------------------------
*/

/* Sleep controller */
typedef struct SLPCTRL_struct
{
    register8_t CTRLB;          /* $35 PRR  : Power Reduction Register */
    register8_t reserved[4];
    register8_t CTRLA;          /* $3A SMCR : Sleep Mode Control Register */
} SLPCTRL_t;

/* Sleep mode select */
typedef enum SLPCTRL_SMODE_enum
{
    SLPCTRL_SMODE_IDLE_gc       = (0<<SM0),     /* Idle mode */
    SLPCTRL_SMODE_ADC_gc        = (1<<SM0),     /* Power-down Mode */
    SLPCTRL_SMODE_PDOWN_gc      = (2<<SM0),     /* Power-down Mode */
    SLPCTRL_SMODE_STDBY_gc      = (4<<SM0)      /* Standby Mode */
} SLPCTRL_SMODE_t;


/*
--------------------------------------------------------------------------
TCB - Timer/Counter controller
--------------------------------------------------------------------------
*/

/* 16-bit Timer */
typedef struct TCB_struct
{
    _WORDREGISTER(CAPT);        /* $22 ICR0   : Input Capture Register */
    _WORDREGISTER(CMPB);        /* $24 OCR0B  : Output Compare Register B */
    _WORDREGISTER(CMPA);        /* $26 OCR0A  : Output Compare Register A */
    _WORDREGISTER(CNT);         /* $28 TCNT0  : Count */
    register8_t INTFLAGS;       /* $2A TIFR0  : Interrupt Flag Register */
    register8_t INTCTRL;        /* $2B TIMSK0 : Interrupt Mask Register */
    register8_t CTRLC;          /* $2C TCCR0C : Control Register C */
    register8_t CTRLB;          /* $2D TCCR0B : Control Register B */
    register8_t CTRLA;          /* $2E TCCR0A : Control Register A */
    register8_t CTRLD;          /* $2F GTCCR  : General Timer/Counter Control Register */
} TCB_t;

/* Compare Output Mode Channel A */
typedef enum TCB_WOA_enum
{
    TCB_WOA_OFF_gc              = (0<<COM0A0),  /* Normal port operation: OC0A disconnected */
    TCB_WOA_TOGGLE_gc           = (1<<COM0A0),
    TCB_WOA_LOW_gc              = (2<<COM0A0),
    TCB_WOA_HIGH_gc             = (3<<COM0A0)
} TCB_WOA_t;

/* Compare Output Mode Channel B */
typedef enum TCB_WOB_enum
{
    TCB_WOB_OFF_gc              = (0<<COM0B0),  /* Normal port operation: OC0B disconnected */
    TCB_WOB_TOGGLE_gc           = (1<<COM0B0),
    TCB_WOB_LOW_gc              = (2<<COM0B0),
    TCB_WOB_HIGH_gc             = (3<<COM0B0)
} TCB_WOB_t;

/* Wave Generation */
typedef enum TCB_WGMODE_enum
{
    TCB_WGMODE_NORMAL_gc        = (0|0),        /* Normal Mode                  0xFFFF-Imd----MAX */
    TCB_WGMODE_PWM8_BTM_gc      = (0|1),        /* PWM, Phase Correct, 8-bit    0x00FF-TOP----BOTTOM */
    TCB_WGMODE_PWM9_BTM_gc      = (0|2),        /* PWM, Phase Correct, 9-bit    0x01FF-TOP----BOTTOM */
    TCB_WGMODE_PWM10_BTM_gc     = (0|3),        /* PWM, Phase Correct, 10-bit   0x03FF-TOP----BOTTOM */
    TCB_WGMODE_CTC_CMPA_gc      = (8|0),        /* CTC (Clear Timer on Compare) OCR0A--Imd----MAX */
    TCB_WGMODE_PWM8_TOP_gc      = (8|1),        /* Fast PWM, 8-bit              0x00FF-TOP----TOP */
    TCB_WGMODE_PWM9_TOP_gc      = (8|2),        /* Fast PWM, 9-bit              0x01FF-TOP----TOP */
    TCB_WGMODE_PWM10_TOP_gc     = (8|3),        /* Fast PWM, 10-bit             0x03FF-TOP----TOP */
    TCB_WGMODE_PWFQ_CAPT_gc     = (16|0),       /* PWM, Phase & Freq. Correct   ICR0---BOTTOM-BOTTOM */
    TCB_WGMODE_PWFQ_CMPA_gc     = (16|1),       /* PWM, Phase & Freq. Correct   OCR0A--BOTTOM-BOTTOM */
    TCB_WGMODE_PWPH_CAPT_gc     = (16|2),       /* PWM, Phase Correct           ICR0---TOP----BOTTOM */
    TCB_WGMODE_PWPH_CMPA_gc     = (16|3),       /* PWM, Phase Correct           OCR0A--TOP----BOTOM */
    TCB_WGMODE_CTC_CAPT_gc      = (24|0),       /* CTC (Clear Timer on Compare) ICR0---Imd----MAX */
    TCB_WGMODE_PWM_CAPT_gc      = (24|2),       /* Fast PWM                     ICR0---TOP----TOP */
    TCB_WGMODE_PWM_CMPA_gc      = (24|3)        /* Fast PWM                     OCR0A--TOP----TOP */
} TCB_WGMODE_t;

/* Clock Select */
typedef enum TCB_CLKSEL_enum
{
    TCB_CLKSEL_CLKSTOP_gc       = (0<<CS00),    /* No clock */
    TCB_CLKSEL_CLKDIV1_gc       = (1<<CS00),    /* CLK_PER (No Prescaling)  */
    TCB_CLKSEL_CLKDIV8_gc       = (2<<CS00),    /* CLK_PER/8 (From Prescaler) */
    TCB_CLKSEL_CLKDIV64_gc      = (3<<CS00),    /* CLK_PER/64 (From Prescaler) */
    TCB_CLKSEL_CLKDIV256_gc     = (4<<CS00),    /* CLK_PER/256 (From Prescaler) */
    TCB_CLKSEL_CLKDIV1024_gc    = (5<<CS00),    /* CLK_PER/1024 (From Prescaler) */
    TCB_CLKSEL_T0_FALLING_gc    = (6<<CS00),    /* T0 pin edge falling (T0 == PB2) */
    TCB_CLKSEL_T0_RISING_gc     = (7<<CS00),    /* T0 pin edge rising (T0 == PB2) */
} TCB_CLKSEL_t;


/*
--------------------------------------------------------------------------
USART - Universal Synchronous and Asynchronous Receiver and Transmitter
--------------------------------------------------------------------------
*/

/* Universal Synchronous and Asynchronous Receiver and Transmitter */
/* Not all USART registers can be accessed using the SBI and CBI instructions. */
typedef struct USART_struct
{
    register8_t DATA;           /* $08 UDR0  : Data Register */
    _WORDREGISTER(BAUD);        /* $09 UBRR  : Baud Rate Register */
    register8_t CTRLD;          /* $0B UCSRD : Control and Status Register D */
    register8_t CTRLC;          /* $0C UCSRC : Control and Status Register C */
    register8_t CTRLB;          /* $0C UCSRB : Control and Status Register B */
    register8_t CTRLA;          /* $0C UCSRA : Control and Status Register A */
} USART_t;

/* Character Size select bit group configurations*/
typedef enum USART_CHSIZE_enum
{
    USART_CHSIZE_NONE_gc        = (0<<UCSZ0),   /* Character size: (none) */
    USART_CHSIZE_5BIT_gc        = (0<<UCSZ0),   /* Character size: 5 bit */
    USART_CHSIZE_6BIT_gc        = (1<<UCSZ0),   /* Character size: 6 bit */
    USART_CHSIZE_7BIT_gc        = (2<<UCSZ0),   /* Character size: 7 bit */
    USART_CHSIZE_8BIT_gc        = (3<<UCSZ0),   /* Character size: 8 bit */
    USART_CHSIZE_9BIT_gc        = (2<<UCSZ0)    /* Character size: 9 bit */
} USART_CHSIZE_t;

/* Communication Mode select bit group configurations*/
typedef enum USART_CMODE_enum
{
    USART_CMODE_ASYNCHRONOUS_gc = (0<<UMSEL0),  /* Asynchronous Mode */
    USART_CMODE_SYNCHRONOUS_gc  = (1<<UMSEL0),  /* Synchronous Mode */
    USART_CMODE_MSPI_gc         = (3<<UMSEL0)   /* SPI Host Mode */
} USART_CMODE_t;

/* Parity Mode select bit group configurations*/
typedef enum USART_PMODE_enum
{
    USART_PMODE_DISABLED_gc     = (0<<UPM0),    /* No Parity */
    USART_PMODE_EVEN_gc         = (2<<UPM0),    /* Even Parity */
    USART_PMODE_ODD_gc          = (3<<UPM0)     /* Odd Parity */
} USART_PMODE_t;

/* Stop Bit Mode select bit group configurations*/
typedef enum USART_SBMODE_enum
{
    USART_SBMODE_1BIT_gc        = (0<<USBS),    /* 1 stop bit */
    USART_SBMODE_2BIT_gc        = (1<<USBS)     /* 2 stop bits */
} USART_SBMODE_t;


/*
--------------------------------------------------------------------------
VLM - VCC Monitoring Control
--------------------------------------------------------------------------
*/

typedef struct VLM_struct
{
    register8_t CTRLA;          /* $34 VLMCSR : VCC Monitoring Control and Status Register */
} VLM_t;

/* Clock select */
typedef enum VLM_LEVEL_enum
{
    VLM_LEVEL0_gc               = (0<<VLM0),    /* Dsiable */
    VLM_LEBEL1L_gc              = (1<<VLM0),    /* 1.4 V to RESET */
    VLM_LEVEL1H_gc              = (2<<VLM0),    /* 1.6 V to RESET */
    VLM_LEVEL2_gc               = (3<<VLM0),    /* 2.5 V to Interrupt */
    VLM_LEVEL4_gc               = (4<<VLM0)     /* 3.7 V to Interrupt */
} VLM_LEVEL_t;


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
    WDT_PERIOD_2CLK_gc          = (0x00<<WDP0), /* 2 cycles (64Hz) */
    WDT_PERIOD_4CLK_gc          = (0x01<<WDP0), /* 4 cycles (32Hz) */
    WDT_PERIOD_8CLK_gc          = (0x02<<WDP0), /* 8 cycles (16Hz) */
    WDT_PERIOD_16CLK_gc         = (0x03<<WDP0), /* 16 cycles (8Hz) */
    WDT_PERIOD_32CLK_gc         = (0x04<<WDP0), /* 32 cycles (4Hz) */
    WDT_PERIOD_64CLK_gc         = (0x05<<WDP0), /* 64 cycles (2Hz) */
    WDT_PERIOD_128CLK_gc        = (0x06<<WDP0), /* 128 cycles (1.0s) */
    WDT_PERIOD_256CLK_gc        = (0x07<<WDP0), /* 256 cycles (2.0s) */
    WDT_PERIOD_512CLK_gc        = (0x20<<WDP0), /* 512 cycles (4.0s) */
    WDT_PERIOD_1KCLK_gc         = (0x21<<WDP0)  /* 1K cycles (8.0s) */
} WDT_PERIOD_t;


/*
==========================================================================
IO Module Instances. Mapped to memory.
==========================================================================
*/
#define PORTA                          (*(PORT_t *) 0x00) /* Alias PORTA */
#define PORTB                          (*(PORT_t *) 0x04) /* Alias PORTB */
#define USERT0                        (*(USART_t *) 0x08) /* Alias UDR */
#define PORTCTRL                   (*(PORTCTRL_t *) 0x0C) /* Alias PORTCR */
#define PCINT                         (*(PCINT_t *) 0x0F) /* Alias PCMSK0 */
#define EXTINT                       (*(EXTINT_t *) 0x13) /* Alias EIMSK */
#define ADC0                            (*(ADC_t *) 0x19) /* Alias ADCL */
#define AC0                              (*(AC_t *) 0x1E) /* Alias ACSRB */
#define TCB                             (*(TCB_t *) 0x22) /* Alias ICR0L */
#define WDT                             (*(WDT_t *) 0x31) /* Alias WDTCSR */
#define NVMCTRL                     (*(NVMCTRL_t *) 0x32) /* Alias NVMCSR */
#define VLM                             (*(VLM_t *) 0x34) /* Alias VLMCSR */
#define SLPCTRL                     (*(SLPCTRL_t *) 0x35) /* Alias PRR */
#define CLKCTRL                     (*(CLKCTRL_t *) 0x36) /* Alias CLKPSR */
#define RSTCTRL                     (*(RSTCTRL_t *) 0x3B) /* Alias RSTFLR */

#endif /* #if !defined (__ASSEMBLER__) */


/* ========== Flattened fully qualified IO register names ========== */

/* [ defined ioXXX.h ] */
/* #define CCP                         _SFR_IO8(0x3C) */
/* #define SPL                         _SFR_IO8(0x3D) */
/* #define SPH                         _SFR_IO8(0x3E) */
/* #define SREG                        _SFR_IO8(0x3F) */

/* AC0 - Analog Comparator */
#define AC0_CTRLB                   _SFR_IO8(0x1E)  /* ACSRB */
#define AC0_CTRLA                   _SFR_IO8(0x1F)  /* ACSRA */

/* ADC0 - Analog Digital Converter */
#if !defined (__ASSEMBLER__)
#define ADC0_RES                    _SFR_IO16(0x19) /* ADCL */
#endif
#define ADC0_RESL                   _SFR_IO8(0x19)  /* ADCL */
#define ADC0_RESH                   _SFR_IO8(0x1A)  /* ADCH */
#define ADC0_MUXPOS                 _SFR_IO8(0x1B)  /* ADMUX */
#define ADC0_CTRLB                  _SFR_IO8(0x1C)  /* ADCSRB */
#define ADC0_CTRLA                  _SFR_IO8(0x1D)  /* ADCSRA */

/* CLKCTRL - Clock controller */
#define CLKCTRL_MCLKCTRLB           _SFR_IO8(0x36)  /* CLKPSR */
#define CLKCTRL_MCLKCTRLA           _SFR_IO8(0x37)  /* CLKMSR */
#define CLKCTRL_CALIB               _SFR_IO8(0x39)  /* OSCCAL */

/* EXTINT - Interrupt Control */
#define EXTINT_INTCTRL              _SFR_IO8(0x13)  /* EIMSK : External Interrupt Mask Register */
#define EXTINT_INTFLAGS             _SFR_IO8(0x14)  /* EIFR  : External Interrupt Flag Register */
#define EXTINT_CTRLA                _SFR_IO8(0x15)  /* EICRA : External Interrupt Control Register A */

/* NVMCTRL - Non-Volatile Memory Contorol */
#define NVMCTRL_STATUS              _SFR_IO8(0x32)  /* NVMCSR */
#define NVMCTRL_CTRLA               _SFR_IO8(0x33)  /* NVMCMD */

/* PCINT - Port group Interrupt Control */
#define PCINT_INTCTRLA              _SFR_IO8(0x0F)  /* PCMSK0 : Pin Change Mask PORTA Register */
#define PCINT_INTCTRLB              _SFR_IO8(0x10)  /* PCMSK1 : Pin Change Mask PORTB Register */
#define PCINT_INTFLAGS              _SFR_IO8(0x11)  /* PCIFR  : Pin Change Interrupt Flag Register */
#define PCINT_CTRLA                 _SFR_IO8(0x12)  /* PCICR  : Pin Change Interrupt Control Register */

/* PORTA - I/O Ports */
#define PORTA_IN                    _SFR_IO8(0x00)  /* PINB */
#define PORTA_DIR                   _SFR_IO8(0x01)  /* DDRB */
#define PORTA_OUT                   _SFR_IO8(0x02)  /* PORTB */
#define POTA                        _SFR_IO8(0x02)  /* alias legacy PORTB */
#define PORTA_PUE                   _SFR_IO8(0x03)  /* PUEB */

/* PORTB - I/O Ports */
#define PORTB_IN                    _SFR_IO8(0x04)  /* PINB */
#define PORTB_DIR                   _SFR_IO8(0x05)  /* DDRB */
#define PORTB_OUT                   _SFR_IO8(0x06)  /* PORTB */
#define POTB                        _SFR_IO8(0x06)  /* alias legacy PORTB */
#define PORTB_PUE                   _SFR_IO8(0x07)  /* PUEB */

/* PORTCTRL - I/O Ports Control */
#define PORTCTRL_CTRLA              _SFR_IO8(0x16)  /* PORTCR */
#define PORTCTRL_CTRLB              _SFR_IO8(0x17)  /* DIDR0 */

/* RSTCTRL - Reset controller */
#define RSTCTRL_RSTFR               _SFR_IO8(0x3B)  /* RSTFLR */

/* SLPCTRL - Sleep controller */
#define SLPCTRL_CTRLB               _SFR_IO8(0x35)  /* PRR */
#define SLPCTRL_CTRLA               _SFR_IO8(0x3A)  /* SMCR */

/* TCB0 - 16-bit Timer/Counter 0 Control */
#if !defined (__ASSEMBLER__)
#define TCB0_CAPT                   _SFR_IO16(0x22) /* ICR0 */
#define TCB0_CMPB                   _SFR_IO16(0x24) /* OCR0B */
#define TCB0_CMPA                   _SFR_IO16(0x26) /* OCR0A */
#define TCB0_CNT                    _SFR_IO16(0x28) /* TCNT0 */
#endif
#define TCB0_CAPTL                  _SFR_IO8(0x22)  /* ICR0L */
#define TCB0_CAPTH                  _SFR_IO8(0x23)  /* ICR0H */
#define TCB0_CMPBL                  _SFR_IO8(0x24)  /* OCR0BL */
#define TCB0_CMPBH                  _SFR_IO8(0x25)  /* OCR0BH */
#define TCB0_CMPAL                  _SFR_IO8(0x26)  /* OCR0AL */
#define TCB0_CMPAH                  _SFR_IO8(0x27)  /* OCR0BH */
#define TCB0_CNTL                   _SFR_IO8(0x28)  /* TCNT0L */
#define TCB0_CNTH                   _SFR_IO8(0x29)  /* TCNT0H */
#define TCB0_INTFLAGS               _SFR_IO8(0x2A)  /* TIFR0 */
#define TCB0_INTCTRL                _SFR_IO8(0x2B)  /* TIMSK0 */
#define TCB0_CTRLC                  _SFR_IO8(0x2C)  /* TCCR0C */
#define TCB0_CTRLB                  _SFR_IO8(0x2D)  /* TCCR0B */
#define TCB0_CTRLA                  _SFR_IO8(0x2E)  /* TCCR0A */
#define TCB0_CTRLD                  _SFR_IO8(0x2F)  /* GTCCR */

/* USART0 - Universal Synchronous and Asynchronous Receiver and Transmitter */
#define USART0_DATA                 _SFR_IO8(0x08)  /* UDR */
#if !defined (__ASSEMBLER__)
#define USART0_BAUD                 _SFR_IO16(0x09) /* UBRR */
#endif
#define USART0_BAUDL                _SFR_IO8(0x09)  /* UBRRL */
#define USART0_BAUDH                _SFR_IO8(0x0A)  /* UBRRH */
#define USART0_CTRLD                _SFR_IO8(0x0B)  /* UCSRD */
#define USART0_CTRLC                _SFR_IO8(0x0C)  /* UCSRC */
#define USART0_CTRLB                _SFR_IO8(0x0D)  /* UCSRB */
#define USART0_CTRLA                _SFR_IO8(0x0E)  /* UCSRA */

/* VLM - VCC Monitoring Control */
#define VLM_CTRLA                   _SFR_IO8(0x34)  /* VLMCSR */

/* WDT - Watchdog Timer Contorol */
#define WDT_CTRLA                   _SFR_IO8(0x31)  /* WDTCSR */


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
#define PORTA_PORT_vect         PCINT0_vect
#define PORTA_PORT_vect_num     PCINT0_vect_num
#define PORTB_PORT_vect         PCINT1_vect
#define PORTB_PORT_vect_num     PCINT1_vect_num
#define TCB0_CAPT_vect          TIM0_CAPT_vect
#define TCB0_CAPT_vect_num      TIM0_CAPT_vect_num
#define TCB0_OVF_vect           TIM0_OVF_vect
#define TCB0_OVF_vect_num       TIM0_OVF_vect_num
#define TCB0_CMPA_vect          TIM0_COMPA_vect
#define TCB0_CMPA_vect_num      TIM0_COMPA_vect_num
#define TCB0_CMPB_vect          TIM0_COMPB_vect
#define TCB0_CMPB_vect_num      TIM0_COMPB_vect_num
#define AC0_CMP_vect            ANA_COMP_vect
#define AC0_CMP_vect_num        ANA_COMP_vect_num
#define ADC0_vect               ADC_vect
#define ADC0_vect_num           ADC_vect_num
#define USART0_RXS_vect         USART_RXS_vect
#define USART0_RXS_vect_num     USART_RXS_vect_num
#define USART0_RXC_vect         USART_RXC_vect
#define USART0_RXC_vect_num     USART_RXC_vect_num
#define USART0_DRE_vect         USART_DRE_vect
#define USART0_DRE_vect_num     USART_DRE_vect_num
#define USART0_TXC_vect         USART_TXC_vect
#define USART0_TXC_vect_num     USART_TXC_vect_num

#if !defined(_VECTOR_SIZE)
#define _VECTOR_SIZE 2 /* Size of individual vector. */
#endif

/* ========== Constants ========== */

/* ========== Fuses ========== */

/* ========== Lock Bits ========== */

/* ========== Signature ========== */
#define SIGROW_SERNUM0  0x06
#define SIGROW_SERNUM1  0x07
#define SIGROW_SERNUM2  0x08
#define SIGROW_SERNUM3  0x09
#define SIGROW_SERNUM4  0x0A
#define SIGROW_SERNUM5  0x0B
#define SIGROW_SERNUM6  0x0C
#define SIGROW_SERNUM7  0x0D
#define SIGROW_SERNUM8  0x0E
#define SIGROW_SERNUM9  0x0F

/* end of header */
