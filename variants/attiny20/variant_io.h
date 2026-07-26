/**
 * @file variant_io.h
 * @author askn (K.Sato) multix.jp
 * @brief ATtiny20 Macro/MicroAPI
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
 * The TIM0 module are also referred to as TCA0.
 * The TIM1 module are also referred to as TCB0.
 * 
 * The following declarations derived from io.h will be renamed.
 */
#undef PORTA    /* -> POTA */
#undef PORTB    /* -> POTB */

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
#define AC_MUXEN_bm             (1<<ACME)       /* to ADC Multiplexer Enable bit mask. */
#define AC_MUXEN_bp             ACME            /* to ADC Multiplexer Enable bit position. */
#define AC_HYSMODE_gm           (3<<HLEV)       /* Hysteresis Mode group mask. */
#define AC_HYSMODE_gp           HLEV            /* Hysteresis Mode group position. */
#define AC_HYSMODE_0_bm         (1<<HLEV)       /* Hysteresis Mode bit 0 mask. */
#define AC_HYSMODE_0_bp         HLEV            /* Hysteresis Mode bit 0 position. */
#define AC_HYSMODE_1_bm         (1<<HSEL)       /* Hysteresis Mode bit 1 mask. */
#define AC_HYSMODE_1_bp         HSEL            /* Hysteresis Mode bit 1 position. */


/* ADC0.MUXPOS [ADMUX] bit masks and bit positions */
#define ADC_MUXPOS_gm           (7<<MUX0)       /* Multiplexer Select group mask. */
#define ADC_MUXPOS_gp           MUX0            /* Multiplexer Select group position. */
#define ADC_MUXPOS_0_bm         (1<<MUX0)       /* Multiplexer Select bit 0 mask. */
#define ADC_MUXPOS_0_bp         MUX0            /* Multiplexer Select bit 0 position. */
#define ADC_MUXPOS_1_bm         (1<<MUX1)       /* Multiplexer Select bit 1 mask. */
#define ADC_MUXPOS_1_bp         MUX1            /* Multiplexer Select bit 1 position. */
#define ADC_MUXPOS_2_bm         (1<<MUX2)       /* Multiplexer Select bit 2 mask. */
#define ADC_MUXPOS_2_bp         MUX2            /* Multiplexer Select bit 2 position. */
#define ADC_MUXPOS_3_bm         (1<<MUX3)       /* Multiplexer Select bit 3 mask. */
#define ADC_MUXPOS_3_bp         MUX3            /* Multiplexer Select bit 3 position. */
#define ADC_MUXNEG_bm           (3<<REFS)       /* Negative Selection Bit bit mask. */
#define ADC_MUXNEG_bp           REFS            /* Negative Selection Bit bit position. */

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


/* EXTINT.INTCTRL [GIMSK] bit masks and bit positions */
#define EXTINT_INT0_bm          (1<<INT0)       /* External Interrupt 0 bit mask. */
#define EXTINT_INT0_bp          INT0            /* External Interrupt 0 bit position. */

/* EXTINT.INTFLAGS [GIFR] bit masks and bit positions */
/* EXTINT_INT0 [INTF0] is already defined. */

/* EXTINT.CTRLA [MCUCR] bit masks and bit positions */
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
#define PCINT_PORTB_1_bm        (1<<PCINT9)     /* PCINT PORTB 1 Enable bit mask. */
#define PCINT_PORTB_1_bp        PCINT9          /* PCINT PORTB 1 Enable bit position. */
#define PCINT_PORTB_2_bm        (1<<PCINT10)    /* PCINT PORTB 2 Enable bit mask. */
#define PCINT_PORTB_2_bp        PCINT10         /* PCINT PORTB 2 Enable bit position. */
#define PCINT_PORTB_3_bm        (1<<PCINT11)    /* PCINT PORTB 3 Enable bit mask. */
#define PCINT_PORTB_3_bp        PCINT11         /* PCINT PORTB 3 Enable bit position. */

/* PCINT.INTFLAGS [GIFR] bit masks and bit positions */
#define PCINT_PORTA_bm          (1<<PCIF0)      /* PCINT PORTA bit mask. */
#define PCINT_PORTA_bp          PCIF0           /* PCINT PORTA bit position. */
#define PCINT_PORTB_bm          (1<<PCIF1)      /* PCINT PORTB bit mask. */
#define PCINT_PORTB_bp          PCIF1           /* PCINT PORTB bit position. */

/* PCINT.CTRLA [GIMSK] bit masks and bit positions */
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
#define PORTCTRL_AIN2_bm        (1<<ADC2D)      /* ADC input pin 2 Enable bit mask. */
#define PORTCTRL_AIN2_bp        ADC2D           /* ADC input pin 2 Enable bit position. */
#define PORTCTRL_AIN3_bm        (1<<ADC3D)      /* ADC input pin 3 Enable bit mask. */
#define PORTCTRL_AIN3_bp        ADC3D           /* ADC input pin 3 Enable bit position. */
#define PORTCTRL_AIN4_bm        (1<<ADC4D)      /* ADC input pin 4 Enable bit mask. */
#define PORTCTRL_AIN4_bp        ADC4D           /* ADC input pin 4 Enable bit position. */
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
#define RSTCTRL_BORF_bm         (1<<BORF)       /* Brown-Out Reset flag bit mask. */
#define RSTCTRL_BORF_bp         BORF            /* Brown-Out Reset flag bit position. */
#define RSTCTRL_WDRF_bm         (1<<WDRF)       /* Watch dog Reset flag bit mask. */
#define RSTCTRL_WDRF_bp         WDRF            /* Watch dog Reset flag bit position. */


/* SLPCTRL.CTRLA [MCUCR] bit masks and bit positions */
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
#define SLPCTRL_BODSLP_bm       (1<<BODS)       /* BOD Sleep bit mask. */
#define SLPCTRL_BODSLP_bp       BODS            /* BOD Sleep bit position. */

/* SLPCTRL.CTRLB [PRR] bit masks and bit positions */
#define SLPCTRL_ADC0_bm         (1<<PRADC)      /* Power reduction ADC0 bit mask. */
#define SLPCTRL_ADC0_bp         PRADC           /* Power reduction ADC0 bit position. */
#define SLPCTRL_TCA0_bm         (1<<PRTIM0)     /* Power reduction TCA0 bit mask. */
#define SLPCTRL_TCA0_bp         PRTIM0          /* Power reduction TCA0 bit position. */
#define SLPCTRL_TCB0_bm         (1<<PRTIM1)     /* Power reduction TCB0 bit mask. */
#define SLPCTRL_TCB0_bp         PRTIM1          /* Power reduction TCB0 bit position. */
#define SLPCTRL_SPI0_bm         (1<<PRSPI)      /* Power reduction SPI0 bit mask. */
#define SLPCTRL_SPI0_bp         PRSPI           /* Power reduction SPI0 bit position. */
#define SLPCTRL_TWI0_bm         (1<<PRTWI)      /* Power reduction TWI0 bit mask. */
#define SLPCTRL_TWI0_bp         PRTWI           /* Power reduction TWI0 bit position. */

/* [ defined ioXXX.h ] */
/* #define SLEEP_MODE_IDLE         (0x00<<1) */
/* #define SLEEP_MODE_ADC          (0x01<<1) */
/* #define SLEEP_MODE_PWR_DOWN     (0x02<<1) */
/* #define SLEEP_MODE_STANDBY      (0x04<<1) */


/* SPI0.CTRL [SPCR] bit masks and bit positions */
#define SPI_PRESC_gm            (3<<SPR0)       /* Prescaler select group mask. */
#define SPI_PRESC_gp            SPR0            /* Prescaler select group position. */
#define SPI_PRESC_0_bm          (1<<SPR0)       /* Prescaler select bit 0 mask. */
#define SPI_PRESC_0_bp          SPR0            /* Prescaler select bit 0 position. */
#define SPI_PRESC_1_bm          (1<<SPR1)       /* Prescaler select bit 1 mask. */
#define SPI_PRESC_1_bp          SPR1            /* Prescaler select bit 1 position. */
#define SPI_CPHA_bm             (1<<CPHA)       /* Clock Phase bit mask. */
#define SPI_CPHA_bp             CPHA            /* Clock Phase bit position. */
#define SPI_CPOL_bm             (1<<CPOL)       /* Clock Polarity bit mask. */
#define SPI_CPOL_bp             CPOL            /* Clock Polarity bit position. */
#define SPI_MASTER_bm           (1<<MSTR)       /* Host Operation bit mask. */
#define SPI_MASTER_bp           MSTR            /* Host Operation bit position. */
#define SPI_DORD_bm             (1<<DORD)       /* Data Order Setting bit mask. */
#define SPI_DORD_bp             DORD            /* Data Order Setting bit position. */
#define SPI_ENABLE_bm           (1<<SPE)        /* Enable Module bit mask. */
#define SPI_ENABLE_bp           SPE             /* Enable Module bit position. */
#define SPI_IE_bm               (1<<SPIE)       /* Interrupt Enable bit mask. */
#define SPI_IE_bp               SPIE            /* Interrupt Enable bit position. */

/* SPI0.STATUS [SPSR] bit masks and bit positions */
#define SPI_CLK2X_bm            (1<<SPI2X)      /* Enable Double Speed bit mask. */
#define SPI_CLK2X_bp            SPI2X           /* Enable Double Speed bit position. */
#define SPI_BUFOVF_bm           (1<<WCOL)       /* Buffer Overflow bit mask. */
#define SPI_BUFOVF_bp           WCOL            /* Buffer Overflow bit position. */
#define SPI_IF_bm               (1<<SPIF)       /* Interrupt Flag bit mask. */
#define SPI_IF_bp               SPIF            /* Interrupt Flag bit position. */


/* TCA0.CTRLA [TCCR0A] bit masks and bit positions */
#define TCA_WGMODE_A_gm         (0x03<<WGM00)   /* Wave Generation Mode group mask. */
#define TCA_WGMODE_A_gp         WGM00           /* Wave Generation Mode group positon. */
#define TCA_WGMODE_0_bm         (1<<WGM00)      /* Wave Generation Mode bit 0 mask. */
#define TCA_WGMODE_0_bp         WGM00           /* Wave Generation Mode bit 0 positon. */
#define TCA_WGMODE_1_bm         (1<<WGM01)      /* Wave Generation Mode bit 1 mask. */
#define TCA_WGMODE_1_bp         WGM01           /* Wave Generation Mode bit 1 positon. */
#define TCA_WOB_gm              (3<<COM0B0)     /* Compare Mode Channel B group mask. */
#define TCA_WOB_gp              COM0B0          /* Compare Mode Channel B group positon. */
#define TCA_WOB_0_bm            (1<<COM0B0)     /* Compare Mode Channel B bit 0 mask. */
#define TCA_WOB_0_bp            COM0B0          /* Compare Mode Channel B bit 0 positon. */
#define TCA_WOB_1_bm            (1<<COM0B1)     /* Compare Mode Channel B bit 1 mask. */
#define TCA_WOB_1_bp            COM0B1          /* Compare Mode Channel B bit 1 positon. */
#define TCA_WOA_gm              (3<<COM0A0)     /* Compare Mode Channel A group mask. */
#define TCA_WOA_gp              COM0A0          /* Compare Mode Channel A group positon. */
#define TCA_WOA_0_bm            (1<<COM0A0)     /* Compare Mode Channel A bit 0 mask. */
#define TCA_WOA_0_bp            COM0A0          /* Compare Mode Channel A bit 0 positon. */
#define TCA_WOA_1_bm            (1<<COM0A1)     /* Compare Mode Channel A bit 1 mask. */
#define TCA_WOA_1_bp            COM0A1          /* Compare Mode Channel A bit 1 positon. */

/* TCA0.CTRLB [TCCR0B] bit masks and bit positions */
#define TCA_CLCKSEL_gm          (7<<CS00)       /* Clock Selectoer group mask. */
#define TCA_CLCKSEL_gp          CS00            /* Clock Selectoer group position. */
#define TCA_CLCKSEL_0_bm        (1<<CS00)       /* Clock Selectoer bit 0 mask. */
#define TCA_CLCKSEL_0_bp        CS00            /* Clock Selectoer bit 0 position. */
#define TCA_CLCKSEL_1_bm        (1<<CS01)       /* Clock Selectoer bit 1 mask. */
#define TCA_CLCKSEL_1_bp        CS01            /* Clock Selectoer bit 1 position. */
#define TCA_CLCKSEL_2_bm        (1<<CS02)       /* Clock Selectoer bit 2 mask. */
#define TCA_CLCKSEL_2_bp        CS02            /* Clock Selectoer bit 2 position. */
#define TCA_WGMODE_B_gm         (1<<WGM02)      /* Wave Generation Mode group mask. */
#define TCA_WGMODE_B_gp         WGM02           /* Wave Generation Mode group positon. */
#define TCA_WGMODE_2_bm         (1<<WGM02)      /* Wave Generation Mode bit 2 mask. */
#define TCA_WGMODE_2_bp         WGM02           /* Wave Generation Mode bit 2 positon. */
#define TCA_STROBEB_bm          (1<<FOC0B)      /* Force Output Compare for Channel B bit mask. */
#define TCA_STROBEB_bp          FOC0B           /* Force Output Compare for Channel B bit position. */
#define TCA_STROBEA_bm          (1<<FOC0A)      /* Force Output Compare for Channel A bit mask. */
#define TCA_STROBEA_bp          FOC0A           /* Force Output Compare for Channel A bit position. */

/* TCA0.INTCTRL [TIMSK] bit masks and bit positions */
#define TCA_OVF_bm              (1<<TOIE0)      /* Overflow Interrupt bit mask. */
#define TCA_OVF_bp              TOIE0           /* Overflow Interrupt bit position. */
#define TCA_CMPA_bm             (1<<OCIE0A)     /* Compare A Match Interrupt bit mask. */
#define TCA_CMPA_bp             OCIE0A          /* Compare A Match Interrupt bit position. */
#define TCA_CMPB_bm             (1<<OCIE0B)     /* Compare B Match Interrupt bit mask. */
#define TCA_CMPB_bp             OCIE0B          /* Compare B Match Interrupt bit position. */

/* TCA0.INTFLAGS [TIFR] bit masks and bit positions */
/* TCA_OVF [TOV0] is already defined. */
/* TCA_CMPA [OCF0A] is already defined. */
/* TCA_CMPB [OCF0B] is already defined. */

/* TCA0.CTRLD [GTCCR] bit masks and bit positions */
#define TCA_PSRESET_bm          (1<<PSR)        /* Prescaler Reset bit mask. */
#define TCA_PSRESET_bp          PSR             /* Prescaler Reset bit position. */
#define TCA_SYNC_EN_bm          (1<<TSM)        /* Synchronization Mode bit mask. */
#define TCA_SYNC_EN_bp          TSM             /* Synchronization Mode bit position. */


/* TCB0.CTRLA [TCCR1A] bit masks and bit positions */
#define TCB_WGMODE_A_gm         (0x03<<WGM10)   /* Wave Generation Mode group mask. */
#define TCB_WGMODE_A_gp         WGM10           /* Wave Generation Mode group positon. */
#define TCB_WGMODE_0_bm         (1<<WGM10)      /* Wave Generation Mode bit 0 mask. */
#define TCB_WGMODE_0_bp         WGM10           /* Wave Generation Mode bit 0 positon. */
#define TCB_WGMODE_1_bm         (1<<WGM11)      /* Wave Generation Mode bit 1 mask. */
#define TCB_WGMODE_1_bp         WGM11           /* Wave Generation Mode bit 1 positon. */
#define TCB_WOB_gm              (3<<COM1B0)     /* Compare Mode Channel B group mask. */
#define TCB_WOB_gp              COM1B0          /* Compare Mode Channel B group positon. */
#define TCB_WOB_0_bm            (1<<COM1B0)     /* Compare Mode Channel B bit 0 mask. */
#define TCB_WOB_0_bp            COM1B0          /* Compare Mode Channel B bit 0 positon. */
#define TCB_WOB_1_bm            (1<<COM1B1)     /* Compare Mode Channel B bit 1 mask. */
#define TCB_WOB_1_bp            COM1B1          /* Compare Mode Channel B bit 1 positon. */
#define TCB_WOA_gm              (3<<COM1A0)     /* Compare Mode Channel A group mask. */
#define TCB_WOA_gp              COM1A0          /* Compare Mode Channel A group positon. */
#define TCB_WOA_0_bm            (1<<COM1A0)     /* Compare Mode Channel A bit 0 mask. */
#define TCB_WOA_0_bp            COM1A0          /* Compare Mode Channel A bit 0 positon. */
#define TCB_WOA_1_bm            (1<<COM1A1)     /* Compare Mode Channel A bit 1 mask. */
#define TCB_WOA_1_bp            COM1A1          /* Compare Mode Channel A bit 1 positon. */

/* TCB0.CTRLB [TCCR1B] bit masks and bit positions */
#define TCB_CLCKSEL_gm          (0x07<<CS10)    /* Clock Selectoer group mask. */
#define TCB_CLCKSEL_gp          CS10            /* Clock Selectoer group position. */
#define TCB_CLCKSEL_0_bm        (1<<CS10)       /* Clock Selectoer bit 0 mask. */
#define TCB_CLCKSEL_0_bp        CS10            /* Clock Selectoer bit 0 position. */
#define TCB_CLCKSEL_1_bm        (1<<CS11)       /* Clock Selectoer bit 1 mask. */
#define TCB_CLCKSEL_1_bp        CS11            /* Clock Selectoer bit 1 position. */
#define TCB_CLCKSEL_2_bm        (1<<CS12)       /* Clock Selectoer bit 2 mask. */
#define TCB_CLCKSEL_2_bp        CS12            /* Clock Selectoer bit 2 position. */
#define TCB_WGMODE_B_gm         (0x03<<WGM12)   /* Wave Generation Mode group mask. */
#define TCB_WGMODE_B_gp         WGM12           /* Wave Generation Mode group positon. */
#define TCB_WGMODE_2_bm         (1<<WGM12)      /* Wave Generation Mode bit 2 mask. */
#define TCB_WGMODE_2_bp         WGM12           /* Wave Generation Mode bit 2 positon. */
#define TCB_WGMODE_3_bm         (1<<WGM13)      /* Wave Generation Mode bit 3 mask. */
#define TCB_WGMODE_3_bp         WGM13           /* Wave Generation Mode bit 3 positon. */
#define TCB_CAP_EDGE_bm         (1<<ICES1)      /* Input Capture Edge Select bit mask */
#define TCB_CAP_EDGE_bp         ICES1           /* Input Capture Edge Select bit position */
#define TCB_CAP_NC_bm           (1<<ICNC1)      /* Input Capture Noise Canceler bit mask */
#define TCB_CAP_NC_bp           ICNC1           /* Input Capture Noise Canceler bit position */

/* TCB0.CTRLC [TCCR1C] bit masks and bit positions */
#define TCB_STROBEB_bm          (1<<FOC1B)      /* Force Output Compare Channel B bit mask. */
#define TCB_STROBEB_bp          FOC1B           /* Force Output Compare Channel B bit position. */
#define TCB_STROBEA_bm          (1<<FOC1A)      /* Force Output Compare Channel A bit mask. */
#define TCB_STROBEA_bp          FOC1A           /* Force Output Compare Channel A bit position. */

/* TCB0.INTCTRL [TIMSK] bit masks and bit positions */
#define TCB_OVF_bm              (1<<TOIE1)      /* Overflow Interrupt Enable bit mask. */
#define TCB_OVF_bp              TOIE1           /* Overflow Interrupt Enable bit position. */
#define TCB_CMPA_bm             (1<<OCIE1A)     /* Compare A Match Interrupt Enable bit mask. */
#define TCB_CMPA_bp             OCIE1A          /* Compare A Match Interrupt Enable bit position. */
#define TCB_CMPB_bm             (1<<OCIE1B)     /* Compare B Match Interrupt Enable bit mask. */
#define TCB_CMPB_bp             OCIE1B          /* Compare B Match Interrupt Enable bit position. */
#define TCB_CAP_bm              (1<<ICIE1)      /* Input Capture Interrupt Enable bit mask. */
#define TCB_CAP_bp              ICIE1           /* Input Capture Interrupt Enable bit position. */

/* TCB0.INTFLAGS [TIFR] bit masks and bit positions */
/* TCB_OVF [TOV1] is already defined. */
/* TCB_CMPA [OCF1A] is already defined. */
/* TCB_CMPB [OCF1B] is already defined. */


/* TCB0.CTRLD [GTCCR] bit masks and bit positions */
#define TCB_PSRESET_bm          (1<<PSR)        /* Prescaler Reset bit mask. */
#define TCB_PSRESET_bp          PSR             /* Prescaler Reset bit position. */
#define TCB_SYNC_EN_bm          (1<<TSM)        /* Synchronization Mode bit mask. */
#define TCB_SYNC_EN_bp          TSM             /* Synchronization Mode bit position. */


/* TWI0.SCTRLA [TWSCRA] bit masks and bit positions */
#define TWI_SMEN_bm             (0<<TWSME)      /* Smart Mode Enable bit mask. */ 
#define TWI_SMEN_bp             TWSME           /* Smart Mode Enable bit positon. */ 
#define TWI_PMEN_bm             (0<<TWPME)      /* Promiscuous Mode Enable bit mask. */ 
#define TWI_PMEN_bp             TWPME           /* Promiscuous Mode Enable bit positon. */ 
#define TWI_STPIEN_bm           (0<<TWSIE)      /* Stop Interrupt Enable bit mask. */ 
#define TWI_STPIEN_bp           TWSIE           /* Stop Interrupt Enable bit positon. */ 
#define TWI_ENABLE_bm           (0<<TWEN)       /* Enable Module bit mask. */ 
#define TWI_ENABLE_bp           TWEN            /* Enable Module bit positon. */ 
#define TWI_ASIEN_bm            (0<<TWASIE)     /* Address Stop Interrupt Enable bit mask. */ 
#define TWI_ASIEN_bp            TWASIE          /* Address Stop Interrupt Enable bit positon. */ 
#define TWI_DIEN_bm             (0<<TWDIE)      /* Data Interrupt Enable bit mask. */ 
#define TWI_DIEN_bp             TWDIE           /* Data Interrupt Enable bit positon. */ 
#define TWI_HOLDEN_bm           (0<<TWSHE)      /* Clock Hold Enable bit mask. */ 
#define TWI_HOLDEN_bp           TWSHE           /* Clock Hold Enable bit positon. */ 

/* TWI0.SCTRLB [TWSCRB] bit masks and bit positions */
#define TWI_SCMD_gm             (3<<TWCMD0)     /* Command group mask. */ 
#define TWI_SCMD_gp             TWCMD0          /* Command group positon. */ 
#define TWI_SCMD_0_bm           (1<<TWCMD0)     /* Command bit mask. */ 
#define TWI_SCMD_0_bp           TWCMD0          /* Command bit positon. */ 
#define TWI_SCMD_1_bm           (1<<TWCMD1)     /* Command bit mask. */ 
#define TWI_SCMD_1_bp           TWCMD1          /* Command bit positon. */ 
#define TWI_ACKACT_bm           (1<<TWAA)       /* Acknowledge Action bit mask. */ 
#define TWI_ACKACT_bp           TWAA            /* Acknowledge Action bit positon. */ 

/* TWI0.SSTATUS [TWSSRA] bit masks and bit positions */
#define TWI_AS_bm               (1<<TWAS)       /* Address or Stop bit mask. */ 
#define TWI_AS_bp               TWAS            /* Address or Stop bit positon. */ 
#define TWI_DIR_bm              (1<<TWDIR)      /* Read/Write Direction bit mask. */ 
#define TWI_DIR_bp              TWDIR           /* Read/Write Direction bit positon. */ 
#define TWI_BUSERR_bm           (1<<TWBE)       /* Bus Error bit mask. */ 
#define TWI_BUSERR_bp           TWBE            /* Bus Error bit positon. */ 
#define TWI_COLL_bm             (1<<TWC)        /* Collision bit mask. */ 
#define TWI_COLL_bp             TWC             /* Collision bit positon. */ 
#define TWI_RXACK_bm            (1<<TWRA)       /* Received Acknowledge bit mask. */
#define TWI_RXACK_bp            TWRA            /* Received Acknowledge bit position. */
#define TWI_CLKHOLD_bm          (1<<TWCH)       /* Clock Hold bit mask. */
#define TWI_CLKHOLD_bp          TWCH            /* Clock Hold bit position. */
#define TWI_ASIF_bm             (1<<TWASIF)     /* Address/Stop Interrupt Flag bit mask. */
#define TWI_ASIF_bp             TWASIF          /* Address/Stop Interrupt Flag bit position. */
#define TWI_DIF_bm              (1<<TWDIF)      /* Data Interrupt Flag bit mask. */
#define TWI_DIF_bp              TWDIF           /* Data Interrupt Flag bit position. */

/* TWI0.SADDRMASK [TWSAM] bit masks and bit positions */
#define TWI_ADDREN_bm           (1<<TWAE)       /* Address Enable bit mask. */
#define TWI_ADDREN_bp           TWAE            /* Address Enable bit position. */
#define TWI_ADDRMASK_gm         (0x7F<<TWSAM1)  /* Address Mask group mask. */
#define TWI_ADDRMASK_gp         TWSAM1          /* Address Mask group position. */
#define TWI_ADDRMASK_0_bm       (1<<TWSAM1)     /* Address Mask bit 0 mask. */
#define TWI_ADDRMASK_0_bp       TWSAM1          /* Address Mask bit 0 position. */
#define TWI_ADDRMASK_1_bm       (1<<TWSAM2)     /* Address Mask bit 1 mask. */
#define TWI_ADDRMASK_1_bp       TWSAM2          /* Address Mask bit 1 position. */
#define TWI_ADDRMASK_2_bm       (1<<TWSAM3)     /* Address Mask bit 2 mask. */
#define TWI_ADDRMASK_2_bp       TWSAM3          /* Address Mask bit 2 position. */
#define TWI_ADDRMASK_3_bm       (1<<TWSAM4)     /* Address Mask bit 3 mask. */
#define TWI_ADDRMASK_3_bp       TWSAM4          /* Address Mask bit 3 position. */
#define TWI_ADDRMASK_4_bm       (1<<TWSAM5)     /* Address Mask bit 4 mask. */
#define TWI_ADDRMASK_4_bp       TWSAM5          /* Address Mask bit 4 position. */
#define TWI_ADDRMASK_5_bm       (1<<TWSAM6)     /* Address Mask bit 5 mask. */
#define TWI_ADDRMASK_5_bp       TWSAM6          /* Address Mask bit 5 position. */
#define TWI_ADDRMASK_6_bm       (1<<TWSAM7)     /* Address Mask bit 6 mask. */
#define TWI_ADDRMASK_6_bp       TWSAM7          /* Address Mask bit 6 position. */


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
    register8_t CTRLB;          /* $13 ACSRB : Analog Comparator Control B */
    register8_t CTRLA;          /* $14 ACSRA : Analog Comparator Control A */
} AC_t;

/* Interrupt Mode select */
typedef enum AC_INTMODE_enum
{
    AC_INTMODE_BOTHEDGES_gc     = (0<<ACIS0),   /* Edge Sense Both Edges */
    AC_INTMODE_FALLING_gc       = (2<<ACIS0),   /* Edge Sense Falling Edge */
    AC_INTMODE_RISING_gc        = (3<<ACIS0)    /* Edge Sense Rising Edge */
} AC_INTMODE_t;

/* Hysteresis Mode select */
typedef enum AC_HYSMODE_enum
{
    AC_HYSMODE_DISABLE_gc       = (0<<HLEV),    /* disable */
    AC_HYSMODE_LEVEL_20MV_gc    = (2<<HLEV),    /* select level 20mV */
    AC_HYSMODE_LEVEL_50MV_gc    = (3<<HLEV)     /* select level 50mV */
} AC_HYSMODE_t;


/*
--------------------------------------------------------------------------
ADC - Analog to Digital Converter
--------------------------------------------------------------------------
*/

/* Analog to Digital Converter */
typedef struct ADC_struct
{
    _WORDREGISTER(RES);         /* $0E ADCL      : data Result register */
    register8_t MUXPOS;         /* $10 ADMUX     : Multiplexer Positive Selector */
    register8_t CTRLB;          /* $11 ADCSRB    : Control B */
    register8_t CTRLA;          /* $12 ADCSRA    : Control A */
} ADC_t;

/* Analog Channel Selection Bits */
typedef enum ADC_MUXPOS_enum
{
    ADC_MUXPOS_AIN0_gc          = (0<<MUX0),    /* Multiplexer Select PA0 */
    ADC_MUXPOS_AIN1_gc          = (1<<MUX0),    /* Multiplexer Select PA1 */
    ADC_MUXPOS_AIN2_gc          = (2<<MUX0),    /* Multiplexer Select PA2 */
    ADC_MUXPOS_AIN3_gc          = (3<<MUX0),    /* Multiplexer Select PA3 */
    ADC_MUXPOS_AIN4_gc          = (4<<MUX0),    /* Multiplexer Select PA4 */
    ADC_MUXPOS_AIN5_gc          = (5<<MUX0),    /* Multiplexer Select PA5 */
    ADC_MUXPOS_AIN6_gc          = (6<<MUX0),    /* Multiplexer Select PA6 */
    ADC_MUXPOS_AIN7_gc          = (7<<MUX0),    /* Multiplexer Select PA7 */
    ADC_MUXPOS_GND_gc           = (8<<MUX0),    /* Multiplexer Select GND */
    ADC_MUXPOS_VBG_1V1_gc       = (9<<MUX0),    /* Multiplexer Select VBG 1.1V */
    ADC_MUXPOS_TEMP_gc          = (10<<MUX0)    /* Multiplexer Select Temperature */
} ADC_MUXPOS_t;

/* Analog Reference Selection Bits */
typedef enum ADC_MUXNEG_enum
{
    ADC_MUXNEG_VCC_gc           = (0<<REFS),    /* Negative Reference Select VCC */
    ADC_MUXNEG_VBG_1V1_gc       = (1<<REFS)     /* Negative Reference Select VBG 1.1V */
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
    ADC_ATMODE_TCA0_CMPA_gc     = (3<<ADTS0),   /* Timer/Counter 0 Compare Match A */
    ADC_ATMODE_TCA0_OVF_gc      = (4<<ADTS0),   /* Timer/Counter 0 Overflow */
    ADC_ATMODE_TCB0_CMPB_gc     = (5<<ADTS0),   /* Timer/Counter 1 Compare Match B */
    ADC_ATMODE_TCB0_OVF_gc      = (6<<ADTS0),   /* Timer/Counter 1 Overflow */
    ADC_ATMODE_TCB0_CAPT_gc     = (7<<ADTS0)    /* Timer/Counter 1 Capture Event */
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
    register8_t INTFLAGS;       /* $0B GIFR  : External Interrupt Flag Register */
    register8_t INTCTRL;        /* $0C GIMSK : External Interrupt Mask Register */
    register8_t reserved[45];
    register8_t CTRLA;          /* $3A MCUCR : External Interrupt Control Register A */
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
    register8_t INTCTRLA;      /* $09 PCMSK0 : Pin Change Mask Register 0 */
    register8_t INTCTRLB;      /* $0A PCMSK1 : Pin Change Mask Register 1 */
    register8_t INTFLAGS;      /* $0B GIFR   : Pin Change Interrupt Flag Register */
    register8_t CTRLA;         /* $0C GIMSK  : Pin Change Interrupt Control Register */
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
    register8_t CTRLA;          /* $08 PORTCR : Port Control Register */
    register8_t reserved[4];
    register8_t CTRLB;          /* $0D DIDR0  : Digital Input Disable Register 0 */
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
    register8_t CTRLB;          /* $35 PRR   : Power Reduction Register */
    register8_t reserved[4];
    register8_t CTRLA;          /* $3A MCUCR : MCU Control Register */
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
SPI - Serial Peripheral Interface
--------------------------------------------------------------------------
*/

/* Serial Peripheral Interface */
typedef struct SPI_struct
{
    register8_t DATA;           /* $2E SPDR : Data register */
    register8_t STATUS;         /* $2F SPSR : Status register */
    register8_t CTRL;           /* $30 SPCR : Control register */
} SPI_t;

/* Prescaler select bit group configurations*/
typedef enum SPI_PRESC_enum
{
    SPI_PRESC_DIV4_gc           = (0<<SPR0),    /* CLK_PER / 4 */
    SPI_PRESC_DIV16_gc          = (1<<SPR0),    /* CLK_PER / 16 */
    SPI_PRESC_DIV32_gc          = (2<<SPR0),    /* CLK_PER / 32 */
    SPI_PRESC_DIV128_gc         = (3<<SPR0)     /* CLK_PER / 128 */
} SPI_PRESC_enum;

/*
--------------------------------------------------------------------------
TCA - Timer/Counter controller
--------------------------------------------------------------------------
*/

/* 8-bit Timer */
typedef struct TCA_struct
{
    register8_t CMPB;           /* $15 OCR0B  : Output Compare Register B */
    register8_t CMPA;           /* $16 OCR0A  : Output Compare Register A */
    register8_t CNT;            /* $17 TCNT0  : Count */
    register8_t CTRLB;          /* $18 TCCR0B : Control Register B */
    register8_t CTRLA;          /* $19 TCCR0A : Control Register A */
    register8_t reserved[11];
    register8_t INTFLAGS;       /* $25 TIFR   : Interrupt Flag Register */
    register8_t INTCTRL;        /* $26 TIMSK  : Interrupt Mask Register */
    register8_t CTRLD;          /* $27 GTCCR  : General Timer/Counter Control Register */
} TCA_t;

/* Compare Output Mode Channel A */
typedef enum TCA_WOA_enum
{
    TCA_WOA_OFF_gc              = (0<<COM0A0),  /* Normal port operation: OC0A disconnected */
    TCA_WOA_TOGGLE_gc           = (1<<COM0A0),
    TCA_WOA_LOW_gc              = (2<<COM0A0),
    TCA_WOA_HIGH_gc             = (3<<COM0A0)
} TCA_WOA_t;

/* Compare Output Mode Channel B */
typedef enum TCA_WOB_enum
{
    TCA_WOB_OFF_gc              = (0<<COM0B0),  /* Normal port operation: OC0B disconnected */
    TCA_WOB_TOGGLE_gc           = (1<<COM0B0),
    TCA_WOB_LOW_gc              = (2<<COM0B0),
    TCA_WOB_HIGH_gc             = (3<<COM0B0)
} TCA_WOB_t;

/* Wave Generation */
typedef enum TCA_WGMODE_enum
{
    TCA_WGMODE_NORMAL_gc        = (0|0),        /* Normal Mode                  0x00FF-Imd----MAX */
    TCA_WGMODE_PWM8_BTM_gc      = (0|1),        /* PWM, Phase Correct, 8-bit    0x00FF-TOP----BOTTOM */
    TCA_WGMODE_CTC_CMPA_gc      = (0|2),        /* CTC (Clear Timer on Compare) OCR0A--Imd----MAX */
    TCA_WGMODE_FPWM8_MAX_gc     = (0|3),        /* Fast PWM, 8-bit              0x00FF-BOTTOM-MAX */
    TCA_WGMODE_PWPH_CMPA_gc     = (8|1),        /* PWM, Phase Correct           OCR0A--TOP----BOTOM */
    TCA_WGMODE_FPWM_CMPA_gc     = (8|3)         /* Fast PWM                     OCR0A--BOTOM--TOP */
} TCA_WGMODE_t;

/* Clock Selection configurations */
typedef enum TCA_CLKSEL_enum
{
    TCA_CLKSEL_CLKSTOP_gc       = (0<<CS00),    /* CLK_PER stop */
    TCA_CLKSEL_CLKDIV1_gc       = (1<<CS00),    /* CLK_PER / 1 */
    TCA_CLKSEL_CLKDIV8_gc       = (2<<CS00),    /* CLK_PER / 8 */
    TCA_CLKSEL_CLKDIV64_gc      = (3<<CS00),    /* CLK_PER / 64 */
    TCA_CLKSEL_CLKDIV256_gc     = (4<<CS00),    /* CLK_PER / 256 */
    TCA_CLKSEL_CLKDIV1024_gc    = (5<<CS00),    /* CLK_PER / 1024 */
    TCA_CLKSEL_T0_FALLING_gc    = (6<<CS00),    /* T0 Pin FALLING */
    TCA_CLKSEL_T0_RISING_gc     = (7<<CS00)     /* T0 Pin RISING */
} TCA_CLKSEL_t;

/*
--------------------------------------------------------------------------
TCB - Timer/Counter controller
--------------------------------------------------------------------------
*/

/* 16-bit Timer */
typedef struct TCB_struct
{
    _WORDREGISTER(CAPT);        /* $1A ICR1   : Input Capture Register */
    _WORDREGISTER(CMPB);        /* $1C OCR1B  : Output Compare Register B */
    _WORDREGISTER(CMPA);        /* $1E OCR1A  : Output Compare Register A */
    _WORDREGISTER(CNT);         /* $20 TCNT1  : Count */
    register8_t CTRLC;          /* $22 TCCR1C : Control Register C */
    register8_t CTRLB;          /* $23 TCCR1B : Control Register B */
    register8_t CTRLA;          /* $24 TCCR1A : Control Register A */
    register8_t INTFLAGS;       /* $25 TIFR   : Interrupt Flag Register */
    register8_t INTCTRL;        /* $26 TIMSK  : Interrupt Mask Register */
    register8_t CTRLD;          /* $27 GTCCR  : General Timer/Counter Control Register */
} TCB_t;

/* Compare Output Mode Channel A */
typedef enum TCB_WOA_enum
{
    TCB_WOA_OFF_gc              = (0<<COM1A0),  /* Normal port operation: OC0A disconnected */
    TCB_WOA_TOGGLE_gc           = (1<<COM1A0),
    TCB_WOA_LOW_gc              = (2<<COM1A0),
    TCB_WOA_HIGH_gc             = (3<<COM1A0)
} TCB_WOA_t;

/* Compare Output Mode Channel B */
typedef enum TCB_WOB_enum
{
    TCB_WOB_OFF_gc              = (0<<COM1B0),  /* Normal port operation: OC0B disconnected */
    TCB_WOB_TOGGLE_gc           = (1<<COM1B0),
    TCB_WOB_LOW_gc              = (2<<COM1B0),
    TCB_WOB_HIGH_gc             = (3<<COM1B0)
} TCB_WOB_t;

/* Wave Generation */
typedef enum TCB_WGMODE_enum
{
    TCB_WGMODE_NORMAL_gc        = (0|0),        /* Normal Mode                  0xFFFF-Imd----MAX */
    TCB_WGMODE_PWM8_BTM_gc      = (0|1),        /* PWM, Phase Correct, 8-bit    0x00FF-TOP----BOTTOM */
    TCB_WGMODE_PWM9_BTM_gc      = (0|2),        /* PWM, Phase Correct, 9-bit    0x01FF-TOP----BOTTOM */
    TCB_WGMODE_PWM10_BTM_gc     = (0|3),        /* PWM, Phase Correct, 10-bit   0x03FF-TOP----BOTTOM */
    TCB_WGMODE_CTC_CMPA_gc      = (8|0),        /* CTC (Clear Timer on Compare) OCR1A--Imd----MAX */
    TCB_WGMODE_PWM8_TOP_gc      = (8|1),        /* Fast PWM, 8-bit              0x00FF-TOP----TOP */
    TCB_WGMODE_PWM9_TOP_gc      = (8|2),        /* Fast PWM, 9-bit              0x01FF-TOP----TOP */
    TCB_WGMODE_PWM10_TOP_gc     = (8|3),        /* Fast PWM, 10-bit             0x03FF-TOP----TOP */
    TCB_WGMODE_PWFQ_CAPT_gc     = (16|0),       /* PWM, Phase & Freq. Correct   ICR1---BOTTOM-BOTTOM */
    TCB_WGMODE_PWFQ_CMPA_gc     = (16|1),       /* PWM, Phase & Freq. Correct   OCR1A--BOTTOM-BOTTOM */
    TCB_WGMODE_PWPH_CAPT_gc     = (16|2),       /* PWM, Phase Correct           ICR1---TOP----BOTTOM */
    TCB_WGMODE_PWPH_CMPA_gc     = (16|3),       /* PWM, Phase Correct           OCR1A--TOP----BOTOM */
    TCB_WGMODE_CTC_CAPT_gc      = (24|0),       /* CTC (Clear Timer on Compare) ICR1---Imd----MAX */
    TCB_WGMODE_PWM_CAPT_gc      = (24|2),       /* Fast PWM                     ICR1---TOP----TOP */
    TCB_WGMODE_PWM_CMPA_gc      = (24|3)        /* Fast PWM                     OCR0A--TOP----TOP */
} TCB_WGMODE_t;

/* Clock Select */
typedef enum TCB_CLKSEL_enum
{
    TCB_CLKSEL_CLKSTOP_gc       = (0<<CS10),    /* No clock */
    TCB_CLKSEL_CLKDIV1_gc       = (1<<CS10),    /* CLK_PER (No Prescaling)  */
    TCB_CLKSEL_CLKDIV8_gc       = (2<<CS10),    /* CLK_PER/8 (From Prescaler) */
    TCB_CLKSEL_CLKDIV64_gc      = (3<<CS10),    /* CLK_PER/64 (From Prescaler) */
    TCB_CLKSEL_CLKDIV256_gc     = (4<<CS10),    /* CLK_PER/256 (From Prescaler) */
    TCB_CLKSEL_CLKDIV1024_gc    = (5<<CS10),    /* CLK_PER/1024 (From Prescaler) */
    TCB_CLKSEL_T1_FALLING_gc    = (6<<CS10),    /* T1 pin edge falling (T1 == PB0) */
    TCB_CLKSEL_T1_RISING_gc     = (7<<CS10),    /* T1 pin edge rising (T1 == PB0) */
} TCB_CLKSEL_t;


/*
--------------------------------------------------------------------------
TWI - Two-Wire Interface
--------------------------------------------------------------------------
*/

/* Two-Wire Interface : Client Only */
typedef struct TWI_struct
{
    register8_t SDATA;          /* $28 TWSD   : Client Data */
    register8_t SADDRMASK;      /* $29 TWSAM  : Client Address Mask */
    register8_t SADDR;          /* $2A TWSA   : Client Address */
    register8_t SSTATUS;        /* $2B TWSSRA : Client Status */
    register8_t SCTRLB;         /* $2C TWSCRB : Client Control B */
    register8_t SCTRLA;         /* $2D TWSCRA : Client Control A */
} TWI_t;

/* TWI Command */
typedef enum TWI_SCMD_enum
{
    TWI_SCMD_NOACT_gc           = (0<<TWCMD0),  /* No Action */
    TWI_SCMD_COMPTRANS_gc       = (2<<TWCMD0),  /* Used To Complete a Transaction */
    TWI_SCMD_RESPONSE_gc        = (3>>TWCMD0)   /* Used in Response to Address/Data Interrupt */
} TWI_SCMD_t;


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

#define PORTA                          (*(PORT_t *) 0x00) /* Alias PINA */
#define PORTB                          (*(PORT_t *) 0x04) /* Alias PINB */
#define PORTCTRL                   (*(PORTCTRL_t *) 0x08) /* Alias PORTCR */
#define PCINT                         (*(PCINT_t *) 0x09) /* Alias PCMSK0 */
#define EXTINT                       (*(EXTINT_t *) 0x0B) /* Alias GIFR */
#define ADC0                            (*(ADC_t *) 0x0E) /* Alias ADCL */
#define AC0                              (*(AC_t *) 0x13) /* Alias ACSRB */
#define TCA0                           (*(TCA0_t *) 0x15) /* Alias OCR0B */
#define TCB0                           (*(TCB0_t *) 0x1A) /* Alias ICR1L */
#define TWI0                            (*(TWI_t *) 0x28) /* Alias TWSD */
#define SPI0                            (*(SPI_t *) 0x2E) /* Alias SPDR */
#define WDT                             (*(WDT_t *) 0x31) /* Alias WDTCSR */
#define NVMCTRL                     (*(NVMCTRL_t *) 0x32) /* Alias NVMCSR */
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
#define AC0_CTRLB                   _SFR_IO8(0x13)  /* ACSRB */
#define AC0_CTRLA                   _SFR_IO8(0x14)  /* ACSRA */

/* ADC0 - Analog Digital Converter */
#if !defined (__ASSEMBLER__)
#define ADC0_RES                    _SFR_IO16(0x0E) /* ADCL */
#endif
#define ADC0_RESL                   _SFR_IO8(0x0E)  /* ADCL */
#define ADC0_RESH                   _SFR_IO8(0x0F)  /* ADCH */
#define ADC0_MUXPOS                 _SFR_IO8(0x10)  /* ADMUX */
#define ADC0_CTRLB                  _SFR_IO8(0x11)  /* ADCSRB */
#define ADC0_CTRLA                  _SFR_IO8(0x12)  /* ADCSRA */

/* CLKCTRL - Clock controller */
#define CLKCTRL_MCLKCTRLB           _SFR_IO8(0x36)  /* CLKPSR */
#define CLKCTRL_MCLKCTRLA           _SFR_IO8(0x37)  /* CLKMSR */
#define CLKCTRL_OSCCALIB            _SFR_IO8(0x39)  /* OSCCAL */

/* EXTINT - Interrupt Control */
#define EXTINT_INTFLAGS             _SFR_IO8(0x0B)  /* GIFR  : External Interrupt Flag Register */
#define EXTINT_INTCTRL              _SFR_IO8(0x0C)  /* GIMSK : External Interrupt Mask Register */
#define EXTINT_CTRLA                _SFR_IO8(0x3A)  /* MCUCR : External Interrupt Control Register */

/* NVMCTRL - Non-Volatile Memory Contorol */
#define NVMCTRL_STATUS              _SFR_IO8(0x32)  /* NVMCSR */
#define NVMCTRL_CTRLA               _SFR_IO8(0x33)  /* NVMCMD */

/* PCINT - Port group Interrupt Control */
#define PCINT_INTCTRLA              _SFR_IO8(0x09)  /* PCMSK0 : Pin Change Mask PORTA Register */
#define PCINT_INTCTRLB              _SFR_IO8(0x0A)  /* PCMSK1 : Pin Change Mask PORTB Register */
#define PCINT_INTFLAGS              _SFR_IO8(0x0B)  /* PCIFR  : Pin Change Interrupt Flag Register */
#define PCINT_CTRLA                 _SFR_IO8(0x0C)  /* PCICR  : Pin Change Interrupt Control Register */

/* PORTA - I/O Ports */
#define PORTA_IN                    _SFR_IO8(0x00)  /* PINB */
#define PORTA_DIR                   _SFR_IO8(0x01)  /* DDRB */
#define PORTA_OUT                   _SFR_IO8(0x02)  /* PORTB */
#define POTA                        _SFR_IO8(0x02)  /* alias legacy PORTA */
#define PORTA_PUE                   _SFR_IO8(0x03)  /* PUEB */

/* PORTB - I/O Ports */
#define PORTB_IN                    _SFR_IO8(0x04)  /* PINB */
#define PORTB_DIR                   _SFR_IO8(0x05)  /* DDRB */
#define PORTB_OUT                   _SFR_IO8(0x06)  /* PORTB */
#define POTB                        _SFR_IO8(0x06)  /* alias legacy PORTB */
#define PORTB_PUE                   _SFR_IO8(0x07)  /* PUEB */

/* PORTCTRL - I/O Ports Control */
#define PORTCTRL_CTRLA              _SFR_IO8(0x08)  /* PORTCR */
#define PORTCTRL_CTRLB              _SFR_IO8(0x0D)  /* DIDR0 */

/* RSTCTRL - Reset controller */
#define RSTCTRL_RSTFR               _SFR_IO8(0x3B)  /* RSTFLR */

/* SLPCTRL - Sleep controller */
#define SLPCTRL_CTRLB               _SFR_IO8(0x35)  /* PRR */
#define SLPCTRL_CTRLA               _SFR_IO8(0x3A)  /* SMCR */

/* SPI0 - Serial Peripheral Interface Control */
#define SPI0_DATA                   _SFR_IO8(0x2E)  /* SPDR */
#define SPI0_STATUS                 _SFR_IO8(0x2F)  /* SPSR */
#define SPI0_CTRL                   _SFR_IO8(0x30)  /* SPCR */

/* TWI0 - I2C Client Control */
#define TWI0_SDATA                  _SFR_IO8(0x28)  /* TWSD */
#define TWI0_SADDRMASK              _SFR_IO8(0x29)  /* TWSAM */
#define TWI0_SADDR                  _SFR_IO8(0x2A)  /* TWSA */
#define TWI0_SSTATUS                _SFR_IO8(0x2B)  /* TWSSRA */
#define TWI0_SCTRLB                 _SFR_IO8(0x2C)  /* TWSCRB */
#define TWI0_SCTRLA                 _SFR_IO8(0x2D)  /* TWSCRA */

/* TCA0 - 8-bit Timer/Counter 0 Control */
#define TCA0_CMPB                   _SFR_IO8(0x15)  /* OCR0B */
#define TCA0_CMPA                   _SFR_IO8(0x16)  /* OCR0A */
#define TCA0_CNT                    _SFR_IO8(0x17)  /* TCNT0 */
#define TCA0_CTRLB                  _SFR_IO8(0x18)  /* TCCR0B */
#define TCA0_CTRLA                  _SFR_IO8(0x19)  /* TCCR0A */
#define TCA0_INTFLAGS               _SFR_IO8(0x25)  /* TIFR */
#define TCA0_INTCTRL                _SFR_IO8(0x26)  /* TIMSK */

/* TCB0 - 18-bit Timer/Counter 1 Control */
#if !defined (__ASSEMBLER__)
#define TCB0_CAPT                   _SFR_IO16(0x1A) /* ICR1L */
#define TCB0_CMPB                   _SFR_IO16(0x1C) /* OCR1BL */
#define TCB0_CMPA                   _SFR_IO16(0x1E) /* OCR1AL */
#endif
#define TCB0_CAPTL                  _SFR_IO8(0x1A)  /* ICR1L */
#define TCB0_CAPTH                  _SFR_IO8(0x1B)  /* ICR1H */
#define TCB0_CMPBL                  _SFR_IO8(0x1C)  /* OCR1BL */
#define TCB0_CMPBH                  _SFR_IO8(0x1D)  /* OCR1BH */
#define TCB0_CMPAL                  _SFR_IO8(0x1E)  /* OCR1AL */
#define TCB0_CMPAH                  _SFR_IO8(0x1F)  /* OCR1AH */
#if !defined (__ASSEMBLER__)
#define TCB0_CNT                    _SFR_IO16(0x20) /* TCNT1L */
#endif
#define TCB0_CNTL                   _SFR_IO8(0x20)  /* TCNT1L */
#define TCB0_CNTH                   _SFR_IO8(0x21)  /* TCNT1H */
#define TCB0_CTRLC                  _SFR_IO8(0x22)  /* TCCR1C */
#define TCB0_CTRLB                  _SFR_IO8(0x23)  /* TCCR1B */
#define TCB0_CTRLA                  _SFR_IO8(0x24)  /* TCCR1A */
#define TCB0_INTFLAGS               _SFR_IO8(0x25)  /* TIFR */
#define TCB0_INTCTRL                _SFR_IO8(0x26)  /* TIMSK */
#define TCB0_CTRLD                  _SFR_IO8(0x27)  /* GTCCR */

/* TWI0 - I2C Client Control */
#define TWI0_SDATA                  _SFR_IO8(0x28)  /* TWSD */
#define TWI0_SADDRMASK              _SFR_IO8(0x29)  /* TWSAM */
#define TWI0_SADDR                  _SFR_IO8(0x2A)  /* TWSA */
#define TWI0_SSTATUS                _SFR_IO8(0x2B)  /* TWSSRA */
#define TWI0_SCTRLB                 _SFR_IO8(0x2C)  /* TWSCRB */
#define TWI0_SCTRLA                 _SFR_IO8(0x2D)  /* TWSCRA */

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
#define TCB0_CAPT_vect          TIM1_CAPT_vect
#define TCB0_CAPT_vect_num      TIM1_CAPT_vect_num
#define TCB0_CMPA_vect          TIM1_COMPA_vect
#define TCB0_CMPA_vect_num      TIM1_COMPA_vect_num
#define TCB0_CMPB_vect          TIM1_COMPB_vect
#define TCB0_CMPB_vect_num      TIM1_COMPB_vect_num
#define TCB0_OVF_vect           TIM1_OVF_vect
#define TCB0_OVF_vect_num       TIM1_OVF_vect_num
#define TCA0_CMPA_vect          TIM0_COMPA_vect
#define TCA0_CMPA_vect_num      TIM0_COMPA_vect_num
#define TCA0_CMPB_vect          TIM0_COMPB_vect
#define TCA0_CMPB_vect_num      TIM0_COMPB_vect_num
#define TCA0_OVF_vect           TIM0_OVF_vect
#define TCA0_OVF_vect_num       TIM0_OVF_vect_num
#define AC0_CMP_vect            ANA_COMP_vect
#define AC0_CMP_vect_num        ANA_COMP_vect_num
#define ADC0_vect               ADC_ADC_vect
#define ADC0_vect_num           ADC_ADC_vect_num
#define TWI0_SLAVE_vect         TWI_SLAVE_vect
#define TWI0_SLAVE_vect_num     TWI_SLAVE_vect_num
#define SPI0_vect               SPI_vect
#define SPI0_vect_num           SPI_vect_num


/* ========== Constants ========== */

/* ========== Fuses ========== */
#define FUSE_RSTDISBL    (unsigned char)~_BV(0)
#define FUSE_WDTON       (unsigned char)~_BV(1)
#define FUSE_CKOUT       (unsigned char)~_BV(2)
#define FUSE_BODLEVEL0   (unsigned char)~_BV(4)
#define FUSE_BODLEVEL1   (unsigned char)~_BV(5)
#define FUSE_BODLEVEL2   (unsigned char)~_BV(6)

/* ========== Lock Bits ========== */
#define LFUSE_DEFAULT    (0xFF)

/* ========== Signature ========== */

/* end of header */
