/**
 * @file variant_io.h
 * @author askn (K.Sato) multix.jp
 * @brief ATtiny4/5/9/10 Macro/MicroAPI
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
#undef PORTB    /* -> POTB */
#undef ADC0     /* -> ADCL0 */

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

/* AC0.CTRLA [ACSR] bit masks and bit positions */
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
#define AC_DISABLE_bm           (1<<ACD)        /* Module Disable bit mask. */
#define AC_DISABLE_bp           ACD             /* Module Disable bit position. */


#if !defined(__AVR_ATtiny4__) && !defined(__AVR_ATtiny9__)
/* ADC0.MUXPOS [ADMUX] bit masks and bit positions */
#define ADC_MUXPOS_gm           (3<<MUX0)       /* Multiplexer Select group mask. */
#define ADC_MUXPOS_gp           MUX0            /* Multiplexer Select group position. */
#define ADC_MUXPOS_0_bm         (1<<MUX0)       /* Multiplexer Select bit 0 mask. */
#define ADC_MUXPOS_0_bp         MUX0            /* Multiplexer Select bit 0 position. */
#define ADC_MUXPOS_1_bm         (1<<MUX1)       /* Multiplexer Select bit 1 mask. */
#define ADC_MUXPOS_1_bp         MUX1            /* Multiplexer Select bit 1 position. */

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
#endif


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


/* PCINT.INTCTRLB [PCMSK] bit masks and bit positions */
#define PCINT_PORTB_0_bm        (1<<PCINT0)     /* PCINT PORTB 0 bit mask. */
#define PCINT_PORTB_0_bp        PCINT0          /* PCINT PORTB 0 bit position. */
#define PCINT_PORTB_1_bm        (1<<PCINT1)     /* PCINT PORTB 1 bit mask. */
#define PCINT_PORTB_1_bp        PCINT1          /* PCINT PORTB 1 bit position. */
#define PCINT_PORTB_2_bm        (1<<PCINT2)     /* PCINT PORTB 2 bit mask. */
#define PCINT_PORTB_2_bp        PCINT2          /* PCINT PORTB 2 bit position. */
#define PCINT_PORTB_3_bm        (1<<PCINT3)     /* PCINT PORTB 3 bit mask. */
#define PCINT_PORTB_3_bp        PCINT3          /* PCINT PORTB 3 bit position. */

/* PCINT.INTFLAGS [PCIFR] bit masks and bit positions */
#define PCINT_PORTB_bm          (1<<PCIF0)      /* PCINT PORTB bit mask. */
#define PCINT_PORTB_bp          PCIF0           /* PCINT PORTB bit position. */

/* PCINT.CTRLA [PCICR] bit masks and bit positions */
/* PCINT_PORTB [PCIE0] is already defined. */


/* PORTCTRL.CTRLA [PORTCR] bit masks and bit positions */
#define PORTCTRL_BBMBE_bm       (1<<BBMB)       /* Break-Before-Make PORTB Enable bit mask. */
#define PORTCTRL_BBMBE_bp       BBMB            /* Break-Before-Make PORTB Enable bit position. */

/* PORTCTRL.CTRLB [DIDR0] bit masks and bit positions */
#define PORTCTRL_DID0_gm        0x0F            /* Digital Input Disable 0 group mask. */
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

/* TCB0.INTCTRL [TIMSK] bit masks and bit positions */
#define TCB_OVF_bm              (1<<TOIE0)      /* Overflow Interrupt Enable bit mask. */
#define TCB_OVF_bp              TOIE0           /* Overflow Interrupt Enable bit position. */
#define TCB_CMPA_bm             (1<<OCIE0A)     /* Compare A Match Interrupt Enable bit mask. */
#define TCB_CMPA_bp             OCIE0A          /* Compare A Match Interrupt Enable bit position. */
#define TCB_CMPB_bm             (1<<OCIE0B)     /* Compare B Match Interrupt Enable bit mask. */
#define TCB_CMPB_bp             OCIE0B          /* Compare B Match Interrupt Enable bit position. */
#define TCB_CAP_bm              (1<<ICIE0)      /* Input Capture Interrupt Enable bit mask. */
#define TCB_CAP_bp              ICIE0           /* Input Capture Interrupt Enable bit position. */

/* TCA0.INTFLAGS [TIFR] bit masks and bit positions */
/* TCA_OVF [TOV0] is already defined. */
/* TCA_CMPA [OCF0A] is already defined. */
/* TCA_CMPB [OCF0B] is already defined. */
/* TCA_CAP [ICF0] is already defined. */


/* TCB0.CTRLD [GTCCR] bit masks and bit positions */
#define TCB_PSRESET_bm          (1<<PSR)        /* Prescaler Reset bit mask. */
#define TCB_PSRESET_bp          PSR             /* Prescaler Reset bit position. */
#define TCB_SYNC_EN_bm          (1<<TSM)        /* Synchronization Mode bit mask. */
#define TCB_SYNC_EN_bp          TSM             /* Synchronization Mode bit position. */


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
    register8_t CTRLA;          /* $1F ACSR : Analog Comparator Control and Status Register */
} AC_t;

/* Interrupt Mode select */
typedef enum AC_INTMODE_enum
{
    AC_INTMODE_BOTHEDGES_gc     = (0<<ACIS0),   /* Edge Sense Both Edges */
    AC_INTMODE_FALLING_gc       = (2<<ACIS0),   /* Edge Sense Falling Edge */
    AC_INTMODE_RISING_gc        = (3<<ACIS0)    /* Edge Sense Rising Edge */
} AC_INTMODE_t;

#if !defined(__AVR_ATtiny4__) && !defined(__AVR_ATtiny9__)
/*
--------------------------------------------------------------------------
ADC - Analog to Digital Converter
--------------------------------------------------------------------------
*/

/* Analog to Digital Converter */
typedef struct ADC_struct
{
    register8_t RES;            /* $19 ADCL      : data Result register */
    register8_t reserved[1];
    register8_t MUXPOS;         /* $1B ADMUX     : Multiplexer Positive Selector */
    register8_t CTRLB;          /* $1C ADCSRB    : Control B */
    register8_t CTRLA;          /* $1D ADCSRA    : Control A */
} ADC_t;

/* Analog Channel Selection Bits */
typedef enum ADC_MUXPOS_enum
{
    ADC_MUXPOS_AIN0_gc          = (0<<MUX0),    /* Multiplexer Select PB0 */
    ADC_MUXPOS_AIN1_gc          = (1<<MUX0),    /* Multiplexer Select PB1 */
    ADC_MUXPOS_AIN2_gc          = (2<<MUX0),    /* Multiplexer Select PB2 */
    ADC_MUXPOS_AIN3_gc          = (3<<MUX0)     /* Multiplexer Select PB3 */
} ADC_MUXPOS_t;

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
#endif /* #if !defined(__AVR_ATtiny4__) && !defined(__AVR_ATtiny9__) */


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
    register8_t INTCTRLB;       /* $10 PCMSK  : Pin Change Mask Register */
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
    register8_t CTRLA;          /* $0C PORTCR : Port Control Register */
    register8_t reserved[10];
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
#define PORTB                          (*(PORT_t *) 0x00) /* Alias PORTB */
#define PORTCTRL                   (*(PORTCTRL_t *) 0x0C) /* Alias PORTCR */
#define PCINT                         (*(PCINT_t *) 0x10) /* Alias PCMSK0 */
#define EXTINT                       (*(EXTINT_t *) 0x13) /* Alias EIMSK */
#if !defined(__AVR_ATtiny4__) && !defined(__AVR_ATtiny9__)
#define ADC0                            (*(ADC_t *) 0x19) /* Alias ADCL */
#endif
#define AC0                              (*(AC_t *) 0x1F) /* Alias ACSRA */
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
#define AC0_CTRLA                   _SFR_IO8(0x1F)  /* ACSR */

#if !defined(__AVR_ATtiny4__) && !defined(__AVR_ATtiny9__)
/* ADC0 - Analog Digital Converter */
#define ADC0_RES                    _SFR_IO8(0x19)  /* ADCL */
#define ADC0_RESL                   _SFR_IO8(0x19)  /* ADCL */
#define ADC0_MUXPOS                 _SFR_IO8(0x1B)  /* ADMUX */
#define ADC0_CTRLB                  _SFR_IO8(0x1C)  /* ADCSRB */
#define ADC0_CTRLA                  _SFR_IO8(0x1D)  /* ADCSRA */
#endif

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
#define PCINT_INTCTRLB              _SFR_IO8(0x10)  /* PCMSK  : Pin Change Mask PORTB Register */
#define PCINT_INTFLAGS              _SFR_IO8(0x11)  /* PCIFR  : Pin Change Interrupt Flag Register */
#define PCINT_CTRLA                 _SFR_IO8(0x12)  /* PCICR  : Pin Change Interrupt Control Register */

/* PORTB - I/O Ports */
#define PORTB_IN                    _SFR_IO8(0x00)  /* PINB */
#define PORTB_DIR                   _SFR_IO8(0x01)  /* DDRB */
#define PORTB_OUT                   _SFR_IO8(0x02)  /* PORTB */
#define POTB                        _SFR_IO8(0x02)  /* alias legacy PORTB */
#define PORTB_PUE                   _SFR_IO8(0x03)  /* PUEB */

/* PORTCTRL - I/O Ports Control */
#define PORTCTRL_CTRLA              _SFR_IO8(0x0C)  /* PORTCR */
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

/* ========== Constants ========== */

/* ========== Fuses ========== */
#define FUSE_RSTDISBL    (unsigned char)~_BV(0)
#define FUSE_WDTON       (unsigned char)~_BV(1)
#define FUSE_CKOUT       (unsigned char)~_BV(2)

/* ========== Lock Bits ========== */
#define LFUSE_DEFAULT    (0xFF)

/* ========== Signature ========== */

/* end of header */
