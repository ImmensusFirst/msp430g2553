/**
 * @file msp430g2553.h
 * @author Dmitrii Rubtsov (immensus.genuine@gmail.com)
 * @brief Header file compatible with VS Code
 * @version 0.6
 * @date 2025-06-27
 *
 * @copyright Copyright (c) 2025
 *
 */

/* Not tested yet, use at your own risk */

#ifndef __MSP430G2553_VS
#define __MSP430G2553_VS

#include <stdint.h>

#ifdef __cplusplus
#define __READ /* not supported */
#else
#define __READ const
#endif

/*****************************************************************************
* @brief Status register bits
*****************************************************************************/

#define C      (0x0001)
#define Z      (0x0002)
#define N      (0x0004)
#define V      (0x0100)
#define GIE    (0x0008)
#define CPUOFF (0x0010)
#define OSCOFF (0x0020)
#define SCG0   (0x0040)
#define SCG1   (0x0080)

/* Low Power Modes coded with Bits 4-7 in SR */

#define LPM0_bits (CPUOFF)
#define LPM1_bits (SCG0 + CPUOFF)
#define LPM2_bits (SCG1 + CPUOFF)
#define LPM3_bits (SCG1 + SCG0 + CPUOFF)
#define LPM4_bits (SCG1 + SCG0 + OSCOFF + CPUOFF)

/* clang-format off */
#define LPM0      __bis_SR_register(LPM0_bits)     /* Enter Low Power Mode 0 */
#define LPM0_EXIT __bic_SR_register_on_exit(LPM0_bits) /* Exit Low Power Mode 0 */
#define LPM1      __bis_SR_register(LPM1_bits)     /* Enter Low Power Mode 1 */
#define LPM1_EXIT __bic_SR_register_on_exit(LPM1_bits) /* Exit Low Power Mode 1 */
#define LPM2      __bis_SR_register(LPM2_bits)     /* Enter Low Power Mode 2 */
#define LPM2_EXIT __bic_SR_register_on_exit(LPM2_bits) /* Exit Low Power Mode 2 */
#define LPM3      __bis_SR_register(LPM3_bits)     /* Enter Low Power Mode 3 */
#define LPM3_EXIT __bic_SR_register_on_exit(LPM3_bits) /* Exit Low Power Mode 3 */
#define LPM4      __bis_SR_register(LPM4_bits)     /* Enter Low Power Mode 4 */
#define LPM4_EXIT __bic_SR_register_on_exit(LPM4_bits) /* Exit Low Power Mode 4 */

/*****************************************************************************
* @brief Calibration Data
*****************************************************************************/
/* clang-format on */

#define TLV_BCS_CLK_16M    (0U) /* Basic Clock Module+ cal. values: 16MHz */
#define TLV_BCS_CLK_12M    (1U) /* Basic Clock Module+ cal. values: 12MHz */
#define TLV_BCS_CLK_8M     (2U) /* Basic Clock Module+ cal. values: 8MHz */
#define TLV_BCS_CLK_1M     (3U) /* Basic Clock Module+ cal. values: 1MHz */
#define TLV_BCS_CLK_NUMBER (4U) /* Calibration values number */

typedef struct
{
    __READ uint16_t VREF_FACTOR; /* Ref. Factor */
    __READ uint16_t T30;         /* 30Deg Cal. Value */
    __READ uint16_t T85;         /* 85Deg Cal. Value */
} TLV_ADC_Type;

typedef struct
{
    __READ uint8_t DCOCTL;  /* DCO value */
    __READ uint8_t BCSCTL1; /* BCS CTL1 value */
} TLV_BCS_Type;

#pragma pack(push, 1)
typedef struct
{
    __READ uint16_t     CHECKSUM;            /* 2s complement of bit-wise XOR */
    __READ uint8_t      TAG_1;               /* Tag empty block */
    __READ uint8_t      LENGTH_1;            /* Length empty block */
    __READ uint16_t     RESERVED_0[11];      /* Empty block */
    __READ uint8_t      TAG_2;               /* Tag ADC12 block */
    __READ uint8_t      LENGTH_2;            /* Length ADC12 block */
    __READ uint16_t     CAL_ADC_GAIN_FACTOR; /* ADC Gain Factor */
    __READ uint16_t     CAL_ADC_OFFSET;      /* ADC Offset */
    __READ TLV_ADC_Type CAL_ADC_15;          /* ADC Cal. for 1.5V */
    __READ TLV_ADC_Type CAL_ADC_25;          /* ADC Cal. for 2.5V */
    __READ uint8_t      TAG_3;               /* Tag empty block */
    __READ uint8_t      LENGTH_3;            /* Length empty block */
    __READ uint16_t     RESERVED_1[4];       /* Empty block */
    __READ uint8_t      TAG_4;               /* Tag DCO block */
    __READ uint8_t      LENGTH_4;            /* Length DCO block */
    __READ TLV_BCS_Type CAL_BCS[TLV_BCS_CLK_NUMBER]; /* BCS Cal. values */
} TLV_Type;
#pragma pack(pop)

#define TLV_BASE       (0x10c0U)
#define TLV            ((TLV_Type *)TLV_BASE)
#define TLV_BASE_ADDRS {TLV_BASE}
#define TLV_BASE_PTRS  {TLV}

/*****************************************************************************
* @brief Special Function
*****************************************************************************/

typedef struct
{
    volatile uint8_t IE1;  /* SFR interrupt enable 1 */
    volatile uint8_t IE2;  /* SFR interrupt enable 2 */
    volatile uint8_t IFG1; /* SFR interrupt flag 1 */
    volatile uint8_t IFG2; /* SFR interrupt flag 2 */
} SFR_Type;

#define SFR_BASE       (0x0000U)
#define SFR            ((SFR_Type *)SFR_BASE)
#define SFR_BASE_ADDRS {SFR_BASE}
#define SFR_BASE_PTRS  {SFR}

/*****************************************************************************
* @brief ADC10
*****************************************************************************/

typedef struct
{
    volatile uint8_t         DTC0; /* ADC10 data transfer control 0 */
    volatile uint8_t         DTC1; /* ADC10 data transfer control 1 */
    volatile uint8_t         AE0;  /* ADC10 input enable 0 */
    volatile uint8_t         RESERVED_0[357];
    volatile uint16_t        CTL0; /* ADC10 control 0 */
    volatile uint16_t        CTL1; /* ADC10 control 1 */
    volatile __READ uint16_t MEM;  /* ADC10 memory */
    volatile uint16_t        RESERVED_1[3];
    volatile uint16_t        SA; /* ADC10 data transfer start address */
} ADC10_Type;

#define ADC10_BASE       (0x0048U)
#define ADC10            ((ADC10_Type *)ADC10_BASE)
#define ADC10_BASE_ADDRS {ADC10_BASE}
#define ADC10_BASE_PTRS  {ADC10}

/*****************************************************************************
* @brief System Clock
*****************************************************************************/

typedef struct
{
    volatile uint8_t CTL3; /* Basic clock system control 3 */
    uint8_t          RESERVED_0[2];
    volatile uint8_t DCOCTL; /* DCO control */
    volatile uint8_t CTL1;   /* Basic clock system control 1 */
    volatile uint8_t CTL2;   /* Basic clock system control 2 */
} BCS_Type;

#define BCS_BASE       (0x0053U)
#define BCS            ((BCS_Type *)BCS_BASE)
#define BCS_BASE_ADDRS {BCS_BASE}
#define BCS_BASE_PTRS  {BCS}

/*****************************************************************************
* @brief Comparator A
*****************************************************************************/

typedef struct
{
    volatile uint8_t CTL1; /* Comparator_A+ control 1 */
    volatile uint8_t CTL2; /* Comparator_A+ control 2 */
    volatile uint8_t PD;   /* Comparator_A+ port disable */
} CA_Type;

#define CA_BASE       (0x0059U)
#define CA            ((CA_Type *)CA_BASE)
#define CA_BASE_ADDRS {CA_BASE}
#define CA_BASE_PTRS  {CA}

/*****************************************************************************
* @brief Flash
*****************************************************************************/

typedef struct
{
    volatile uint16_t CTL1; /* Flash memory control 1 */
    volatile uint16_t CTL2; /* Flash memory control 2 */
    volatile uint16_t CTL3; /* Flash memory control 3 */
} FLASH_Type;

#define FLASH_BASE       (0x0128U)
#define FLASH            ((FLASH_Type *)FLASH_BASE)
#define FLASH_BASE_ADDRS {FLASH_BASE}
#define FLASH_BASE_PTRS  {FLASH}

/*****************************************************************************
* @brief Port 1, 2, 3
*****************************************************************************/

typedef struct
{
    volatile __READ uint8_t IN;  /* Input */
    volatile uint8_t        OUT; /* Output */
    volatile uint8_t        DIR; /* Direction */
    volatile uint8_t        IFG; /* Interrupt Flag */
    volatile uint8_t        IES; /* Interrupt Edge Select */
    volatile uint8_t        IE;  /* Interrupt Enable */
    volatile uint8_t        SEL; /* Port Select */
} PIO_Type;

#define PIO1_BASE (0x0020U)
#define PIO1      ((PIO_Type *)PIO1_BASE)
#define PIO2_BASE (0x0028U)
#define PIO2      ((PIO_Type *)PIO2_BASE)

typedef struct
{
    volatile __READ uint8_t IN;  /* Input */
    volatile uint8_t        OUT; /* Output */
    volatile uint8_t        DIR; /* Direction */
    volatile uint8_t        SEL; /* Port Select */
} PIOx_Type;

#define PIO3_BASE (0x0018U)
#define PIO3      ((PIOx_Type *)PIO3_BASE)

#define PIO_BASE_ADDRS {PIO1_BASE, PIO2_BASE, PIO3_BASE}
#define PIO_BASE_PTRS  {PIO1, PIO2, PIO3}

typedef struct
{
    volatile uint8_t P3REN; /* Port 3 Resistor Enable */
    uint8_t          RESERVED_0[22];
    volatile uint8_t P1REN; /* Port 1 Resistor Enable */
    uint8_t          RESERVED_1[7];
    volatile uint8_t P2REN; /* Port 2 Resistor Enable */
} REN_Type;

#define PIO_REN_BASE       (0x0010U)
#define PIO_REN            ((REN_Type *)PIO_REN_BASE)
#define PIO_REN_BASE_ADDRS {PIO_REN_BASE}
#define PIO_REN_BASE_PTRS  {PIO_REN}

typedef struct
{
    volatile uint8_t P1SEL2; /* Port 1 Select 2 */
    volatile uint8_t P2SEL2; /* Port 2 Select 2 */
    volatile uint8_t P3SEL2; /* Port 3 Select 2 */
} SEL2_Type;

#define PIO_SEL2_BASE       (0x0041U)
#define PIO_SEL2            ((SEL2_Type *)PIO_SEL2_BASE)
#define PIO_SEL2_BASE_ADDRS {PIO_SEL2_BASE}
#define PIO_SEL2_BASE_PTRS  {PIO_SEL2}

/*****************************************************************************
* @brief Timer0_A3
*****************************************************************************/

typedef struct
{
    volatile __READ uint16_t TA1IV; /* Timer_A1 interrupt vector */
    uint16_t                 RESERVED_0[7];
    volatile __READ uint16_t TA0IV; /* Timer_A0 interrupt vector */
} TAIV_Type;

#define TAIV_BASE       (0x011eU)
#define TAIV            ((TAIV_Type *)TAIV_BASE)
#define TAIV_BASE_ADDRS {TAIV_BASE}
#define TAIV_BASE_PTRS  {TAIV}

typedef struct
{
    volatile uint16_t CTL;     /* Timer_A control */
    volatile uint16_t CCTL[3]; /* Timer_A capture/compare control */
    uint16_t          RESERVED_1[4];
    volatile uint16_t R;      /* Timer_A counter */
    volatile uint16_t CCR[3]; /* Timer_A capture/compare */
} TA_Type;

#define TA0_BASE (0x0160U)
#define TA0      ((TA_Type *)TA0_BASE)
#define TA1_BASE (0x0180U)
#define TA1      ((TA_Type *)TA1_BASE)

#define TA_BASE_ADDRS {TA0_BASE, TA1_BASE}
#define TA_BASE_PTRS  {TA0, TA1}

/*****************************************************************************
* @brief USCI UART Mode
*****************************************************************************/

typedef struct
{
    volatile uint8_t        ABCTL;  /* USCI UART auto baud control */
    volatile uint8_t        IRTCTL; /* USCI UART IrDA transmit control */
    volatile uint8_t        IRRCTL; /* USCI UART IrDA receive control */
    volatile uint8_t        CTL0;   /* USCI UART control 0 */
    volatile uint8_t        CTL1;   /* USCI UART control 1 */
    volatile uint8_t        BR0;    /* USCI UART baud-rate control 0 */
    volatile uint8_t        BR1;    /* USCI UART baud-rate control 1 */
    volatile uint8_t        MCTL;   /* USCI UART modulation control */
    volatile uint8_t        STAT;   /* USCI UART status */
    volatile __READ uint8_t RXBUF;  /* USCI UART receive buffer */
    volatile uint8_t        TXBUF;  /* USCI UART transmit buffer */
} USCI_UART_Type;

#define UCA0_UART_BASE       (0x005dU)
#define UCA0_UART            ((USCI_UART_Type *)UCA0_UART_BASE)
#define USCI_UART_BASE_ADDRS {UCA0_UART_BASE}
#define USCI_UART_BASE_PTRS  {UCA0_UART}

/*****************************************************************************
* @brief USCI SPI Mode
*****************************************************************************/

typedef struct
{
    volatile uint8_t        CTL0; /* USCI SPI control 0 */
    volatile uint8_t        CTL1; /* USCI SPI control 1 */
    volatile uint8_t        BR0;  /* USCI SPI baud-rate control 0 */
    volatile uint8_t        BR1;  /* USCI SPI baud-rate control 1 */
    uint8_t                 RESERVED_0[1];
    volatile uint8_t        STAT;  /* USCI SPI status */
    volatile __READ uint8_t RXBUF; /* USCI SPI receive buffer */
    volatile uint8_t        TXBUF; /* USCI SPI transmit buffer */
} USCI_SPI_Type;

#define UCA0_SPI_BASE (0x0060U)
#define UCA0_SPI      ((USCI_SPI_Type *)UCA0_SPI_BASE)
#define UCB0_SPI_BASE (0x0068U)
#define UCB0_SPI      ((USCI_SPI_Type *)UCB0_SPI_BASE)

#define UCSI_SPI_BASE_ADDRS {UCA0_SPI_BASE, UCB0_SPI_BASE}
#define USCI_SPI_BASE_PTRS  {UCA0_SPI, UCB0_SPI}

/*****************************************************************************
* @brief UCSI I2C Mode
*****************************************************************************/

typedef struct
{
    volatile uint16_t I2COA; /* USCI I2C own address */
    volatile uint16_t I2CSA; /* USCI I2C slave address */
} USCI_I2C_ADDR_Type;

#define UCB0_I2C_ADDR_BASE (0x0118U)
#define UCB0_I2C_ADDR      ((USCI_I2C_ADDR_Type *)UCB0_I2C_ADDR_BASE)

typedef struct
{
    volatile uint8_t        CTL0;  /* USCI I2C control 0 */
    volatile uint8_t        CTL1;  /* USCI I2C control 1 */
    volatile uint8_t        BR0;   /* USCI I2C baud-rate control 0 */
    volatile uint8_t        BR1;   /* USCI I2C baud-rate control 1 */
    volatile uint8_t        IE;    /* USCI I2C interrupt enable */
    volatile uint8_t        STAT;  /* USCI I2C status */
    volatile __READ uint8_t RXBUF; /* USCI I2C receive buffer */
    volatile uint8_t        TXBUF; /* USCI I2C transmit buffer */
} USCI_I2C_Type;

#define UCB0_I2C_BASE       (0x0068U)
#define UCB0_I2C            ((USCI_I2C_Type *)UCB0_I2C_BASE)
#define UCSI_I2C_BASE_ADDRS {UCB0_I2C_BASE}
#define USCI_I2C_BASE_PTRS  {UCB0_I2C}

/*****************************************************************************
* @brief Watchdog Timer
*****************************************************************************/

typedef struct
{
    volatile uint16_t CTL; /* Watchdog timer+ control */
} WDT_Type;

#define WDT_BASE (0x0120U)
#define WDT      ((WDT_Type *)WDT_BASE)

/* clang-format off */

/*****************************************************************************
* @brief IE1
*****************************************************************************/

/* IE1_ACCVIE */
#define IE1_ACCVIE_MASK  (0x20U)
#define IE1_ACCVIE_SHIFT (0x5U)
/* Flash memory access violation interrupt enable. This bit enables the
  ACCVIFG interrupt.
  Because other bits in IE1 may be used for other modules, Ti
  recommends setting or clearing this bit using BIS.B or BIC.B
  instructions, respectively, rather than MOV.B or CLR.B instructions.
  0b = Interrupt not enabled
  1b = Interrupt enabled */
#define IE1_ACCVIE(x)    (((uint8_t)(((uint8_t)(x)) << IE1_ACCVIE_SHIFT)) & IE1_ACCVIE_MASK)

/* IE1_NMIIE */
#define IE1_NMIIE_MASK  (0x10U)
#define IE1_NMIIE_SHIFT (0x4U)
/* NMI interrupt enable. This bit enables the NMI interrupt.
  Because other bits in IE1 may be used for other modules, it
  is recommended to set or clear this bit using BIS.B or BIC.B
  instructions, rather than MOV.B or CLR.B instructions.
  0b = Interrupt not enabled
  1b = Interrupt enabled */
#define IE1_NMIIE(x)    (((uint8_t)(((uint8_t)(x)) << IE1_NMIIE_SHIFT)) & IE1_NMIIE_MASK)

/* IE1_OFIE */
#define IE1_OFIE_MASK  (0x2U)
#define IE1_OFIE_SHIFT (0x1U)
/* Oscillator fault interrupt enable. This bit enables the OFIFG interrupt.
  Because other bits in IE1 may be used for other modules, it
  is recommended to set or clear this bit using BIS.B or BIC.B
  instructions, rather than MOV.B or CLR.B instructions.
  MSP430G22x0: This bit should not be set.
  0b = Interrupt not enabled
  1b = Interrupt enabled */
#define IE1_OFIE(x)    (((uint8_t)(((uint8_t)(x)) << IE1_OFIE_SHIFT)) & IE1_OFIE_MASK)

 /* IE1_WDTIE */
#define IE1_WDTIE_MASK  (0x1U)
#define IE1_WDTIE_SHIFT (0x0U)
/* Watchdog timer+ interrupt enable. This bit enables the WDTIFG
  interrupt for interval timer mode. It is not necessary to set this bit
  for watchdog mode.
  Because other bits in IE1 may be used for other modules, it
  is recommended to set or clear this bit using BIS.B or BIC.B
  instructions, rather than MOV.B or CLR.B instructions.
  0b = Interrupt not enabled
  1b = Interrupt enabled */
#define IE1_WDTIE(x)    (((uint8_t)(((uint8_t)(x)) << IE1_WDTIE_SHIFT)) & IE1_WDTIE_MASK)

/*****************************************************************************
* @brief IE2
*****************************************************************************/

/* IE2_UCB0TXIE */
#define IE2_UCB0TXIE_MASK  (0x8U)
#define IE2_UCB0TXIE_SHIFT (0x3U)
/* USCI_B0 transmit interrupt enable
  0b = Interrupt disabled
  1b = Interrupt enabled */
#define IE2_UCB0TXIE(x)    (((uint8_t)(((uint8_t)(x)) << IE2_UCB0TXIE_SHIFT)) & IE2_UCB0TXIE_MASK)

/* IE2_UCB0RXIE */
#define IE2_UCB0RXIE_MASK  (0x4U)
#define IE2_UCB0RXIE_SHIFT (0x2U)
/* USCI_B0 receive interrupt enable
  0b = Interrupt disabled
  1b = Interrupt enabled */
#define IE2_UCB0RXIE(x)    (((uint8_t)(((uint8_t)(x)) << IE2_UCB0RXIE_SHIFT)) & IE2_UCB0RXIE_MASK)

/* IE2_UCA0TXIE */
#define IE2_UCA0TXIE_MASK  (0x2U)
#define IE2_UCA0TXIE_SHIFT (0x1U)
/* USCI_A0 transmit interrupt enable
  0b = Interrupt disabled
  1b = Interrupt enabled */
#define IE2_UCA0TXIE(x)    (((uint8_t)(((uint8_t)(x)) << IE2_UCA0TXIE_SHIFT)) & IE2_UCA0TXIE_MASK)

/* IE2_UCA0RXIE */
#define IE2_UCA0RXIE_MASK  (0x1U)
#define IE2_UCA0RXIE_SHIFT (0x0U)
/* USCI_A0 receive interrupt enable
  0b = Interrupt disabled
  1b = Interrupt enabled */
#define IE2_UCA0RXIE(x)    (((uint8_t)(((uint8_t)(x)) << IE2_UCA0RXIE_SHIFT)) & IE2_UCA0RXIE_MASK)

/*****************************************************************************
* @brief IFG1
*****************************************************************************/

/* IFG1_NMIIFG */
#define IFG1_NMIIFG_MASK  (0x10U)
#define IFG1_NMIIFG_SHIFT (0x4U)
/* NMI interrupt flag. NMIIFG must be reset by software. Because other
  bits in IFG1 may be used for other modules, it is recommended
  to clear NMIIFG by using BIS.B or BIC.B instructions, rather than
  MOV.B or CLR.B instructions.
  0b = No interrupt pending
  1b = Interrupt pending */
#define IFG1_NMIIFG(x)    (((uint8_t)(((uint8_t)(x)) << IFG1_NMIIFG_SHIFT)) & IFG1_NMIIFG_MASK)

/* IFG1_RSTIFG */
#define IFG1_RSTIFG_MASK  (0x8U)
#define IFG1_RSTIFG_SHIFT (0x3U)
#define IFG1_RSTIFG(x)    (((uint8_t)(((uint8_t)(x)) << IFG1_RSTIFG_SHIFT)) & IFG1_RSTIFG_MASK)

/* IFG1_PORIFG */
#define IFG1_PORIFG_MASK  (0x4U)
#define IFG1_PORIFG_SHIFT (0x2U)
#define IFG1_PORIFG(x)    (((uint8_t)(((uint8_t)(x)) << IFG1_PORIFG_SHIFT)) & IFG1_PORIFG_MASK)

/* IFG1_OFIFG */
#define IFG1_OFIFG_MASK  (0x2U)
#define IFG1_OFIFG_SHIFT (0x1U)
/* Oscillator fault interrupt flag. Because other bits in IFG1 may be
  used for other modules, it is recommended to set or clear this bit
  using BIS.B or BIC.B instructions, rather than MOV.B or CLR.B
  instructions.
  0b = Interrupt not pending
  1b = Interrupt pending */
#define IFG1_OFIFG(x)    (((uint8_t)(((uint8_t)(x)) << IFG1_OFIFG_SHIFT)) & IFG1_OFIFG_MASK)

/* IFG1_WDTIFG */
#define IFG1_WDTIFG_MASK  (0x1U)
#define IFG1_WDTIFG_SHIFT (0x0U)
/* Watchdog timer+ interrupt flag. In watchdog mode, WDTIFG remains
  set until reset by software. In interval mode, WDTIFG is reset
  automatically by servicing the interrupt, or can be reset by software.
  Because other bits in IFG1 may be used for other modules,
  it is recommended to clear WDTIFG by using BIS.B or BIC.B
  instructions, rather than MOV.B or CLR.B instructions.
  0b = No interrupt pending
  1b = Interrupt pending */
#define IFG1_WDTIFG(x)    (((uint8_t)(((uint8_t)(x)) << IFG1_WDTIFG_SHIFT)) & IFG1_WDTIFG_MASK)

/*****************************************************************************
* @brief IFG2
*****************************************************************************/

/* IFG2_UCB0TXIFG */
#define IFG2_UCB0TXIFG_MASK  (0x8U)
#define IFG2_UCB0TXIFG_SHIFT (0x3U)
/* USCI_B0 transmit interrupt flag. UCB0TXIFG is set when
  UCB0TXBUF is empty.
  0b = No interrupt pending
  1b = Interrupt pending */
#define IFG2_UCB0TXIFG(x)    (((uint8_t)(((uint8_t)(x)) << IFG2_UCB0TXIFG_SHIFT)) & IFG2_UCB0TXIFG_MASK)

/* IFG2_UCB0RXIFG */
#define IFG2_UCB0RXIFG_MASK  (0x4U)
#define IFG2_UCB0RXIFG_SHIFT (0x2U)
/* USCI_B0 receive interrupt flag. UCB0RXIFG is set when
  UCB0RXBUF has received a complete character.
  0b = No interrupt pending
  1b = Interrupt pending */
#define IFG2_UCB0RXIFG(x)    (((uint8_t)(((uint8_t)(x)) << IFG2_UCB0RXIFG_SHIFT)) & IFG2_UCB0RXIFG_MASK)

/* IFG2_UCA0TXIFG */
#define IFG2_UCA0TXIFG_MASK  (0x2U)
#define IFG2_UCA0TXIFG_SHIFT (0x1U)
/* USCI_A0 transmit interrupt flag. UCA0TXIFG is set when
  UCA0TXBUF is empty.
  0b = No interrupt pending
  1b = Interrupt pending */
#define IFG2_UCA0TXIFG(x)    (((uint8_t)(((uint8_t)(x)) << IFG2_UCA0TXIFG_SHIFT)) & IFG2_UCA0TXIFG_MASK)

/* IFG2_UCA0RXIFG */
#define IFG2_UCA0RXIFG_MASK  (0x1U)
#define IFG2_UCA0RXIFG_SHIFT (0x0U)
/* USCI_A0 receive interrupt flag. UCA0RXIFG is set when
  UCA0RXBUF has received a complete character.
  0b = No interrupt pending
  1b = Interrupt pending */
#define IFG2_UCA0RXIFG(x)    (((uint8_t)(((uint8_t)(x)) << IFG2_UCA0RXIFG_SHIFT)) & IFG2_UCA0RXIFG_MASK)

/*****************************************************************************
 * @brief ADC10_CTL0
 *****************************************************************************/

 /* ADC10_CTL0_SREF */
#define ADC10_CTL0_SREF_MASK  (0xe000U)
#define ADC10_CTL0_SREF_SHIFT (0xdU)
/* Select reference.
  Can be modified only when ENC = 0. */
#define ADC10_CTL0_SREF(x)    (((uint16_t)(((uint16_t)(x)) << ADC10_CTL0_SREF_SHIFT)) & ADC10_CTL0_SREF_MASK)

/* ADC10_CTL0_ADC10SHT */
#define ADC10_CTL0_ADC10SHT_MASK  (0x1800U)
#define ADC10_CTL0_ADC10SHT_SHIFT (0xbU)
/* ADC10 sample-and-hold time.
  Can be modified only when ENC = 0.
  00b = 4 ADC10CLK cycles
  01b = 8 ADC10CLK cycles
  10b = 16 ADC10CLK cycles
  11b = 64 ADC10CLK cycles */
#define ADC10_CTL0_ADC10SHT(x)    (((uint16_t)(((uint16_t)(x)) << ADC10_CTL0_ADC10SHT_SHIFT)) & ADC10_CTL0_ADC10SHT_MASK)

/* ADC10_CTL0_ADC10SR */
#define ADC10_CTL0_ADC10SR_MASK  (0x400U)
#define ADC10_CTL0_ADC10SR_SHIFT (0xaU)
/* ADC10 sampling rate.
  This bit selects the reference buffer drive capability for the maximum
  sampling rate. Setting ADC10SR reduces the current consumption of
  the reference buffer.
  Can be modified only when ENC = 0.
  0b = Reference buffer supports up to approximately 200 ksps
  1b = Reference buffer supports up to approximately 50 ksps */
#define ADC10_CTL0_ADC10SR(x)    (((uint16_t)(((uint16_t)(x)) << ADC10_CTL0_ADC10SR_SHIFT)) & ADC10_CTL0_ADC10SR_MASK)

/* ADC10_CTL0_REFOUT */
#define ADC10_CTL0_REFOUT_MASK  (0x200U)
#define ADC10_CTL0_REFOUT_SHIFT (0x9U)
/* Reference output.
  Can be modified only when ENC = 0.
  0b = Reference output off
  1b = Reference output on. Devices with VeREF+ / VREF+ pin only. */
#define ADC10_CTL0_REFOUT(x)    (((uint16_t)(((uint16_t)(x)) << ADC10_CTL0_REFOUT_SHIFT)) & ADC10_CTL0_REFOUT_MASK)

/* ADC10_CTL0_REFBURST */
#define ADC10_CTL0_REFBURST_MASK  (0x100U)
#define ADC10_CTL0_REFBURST_SHIFT (0x8U)
/* Reference burst.
  Can be modified only when ENC = 0.
  0b = Reference buffer on continuously
  1b = Reference buffer on only during sample-and-conversion */
#define ADC10_CTL0_REFBURST(x)    (((uint16_t)(((uint16_t)(x)) << ADC10_CTL0_REFBURST_SHIFT)) & ADC10_CTL0_REFBURST_MASK)

/* ADC10_CTL0_MSC */
#define ADC10_CTL0_MSC_MASK  (0x80U)
#define ADC10_CTL0_MSC_SHIFT (0x7U)
/* Multiple sample and conversion. Valid only for sequence or repeated modes.
  Can be modified only when ENC = 0.
  0b = The sampling requires a rising edge of the SHI signal to trigger
  each sample-and-conversion.
  1b = The first rising edge of the SHI signal triggers the
  sampling timer, but further sample-and-conversions are performed
  automatically as soon as the prior conversion is completed */
#define ADC10_CTL0_MSC(x)    (((uint16_t)(((uint16_t)(x)) << ADC10_CTL0_MSC_SHIFT)) & ADC10_CTL0_MSC_MASK)

/* ADC10_CTL0_REF2_5V */
#define ADC10_CTL0_REF2_5V_MASK  (0x40U)
#define ADC10_CTL0_REF2_5V_SHIFT (0x6U)
/* Reference-generator voltage. REFON must also be set.
  Can be modified only when ENC = 0.
  0b = 1.5 V
  1b = 2.5 V */
#define ADC10_CTL0_REF2_5V(x)    (((uint16_t)(((uint16_t)(x)) << ADC10_CTL0_REF2_5V_SHIFT)) & ADC10_CTL0_REF2_5V_MASK)

/* ADC10_CTL0_REFON */
#define ADC10_CTL0_REFON_MASK  (0x20U)
#define ADC10_CTL0_REFON_SHIFT (0x5U)
/* Reference generator on.
  Can be modified only when ENC = 0.
  0b = Reference off
  1b = Reference on */
#define ADC10_CTL0_REFON(x)    (((uint16_t)(((uint16_t)(x)) << ADC10_CTL0_REFON_SHIFT)) & ADC10_CTL0_REFON_MASK)

/* ADC10_CTL0_ADC10ON */
#define ADC10_CTL0_ADC10ON_MASK  (0x10U)
#define ADC10_CTL0_ADC10ON_SHIFT (0x4U)
/* ADC10 on.
  Can be modified only when ENC = 0.
  0b = ADC10 off
  1b = ADC10 on */
#define ADC10_CTL0_ADC10ON(x)    (((uint16_t)(((uint16_t)(x)) << ADC10_CTL0_ADC10ON_SHIFT)) & ADC10_CTL0_ADC10ON_MASK)

/* ADC10_CTL0_ADC10IE */
#define ADC10_CTL0_ADC10IE_MASK  (0x8U)
#define ADC10_CTL0_ADC10IE_SHIFT (0x3U)
/* ADC10 interrupt enable
  0b = Interrupt disabled
  1b = Interrupt enabled */
#define ADC10_CTL0_ADC10IE(x)    (((uint16_t)(((uint16_t)(x)) << ADC10_CTL0_ADC10IE_SHIFT)) & ADC10_CTL0_ADC10IE_MASK)

/* ADC10_CTL0_ADC10IFG */
#define ADC10_CTL0_ADC10IFG_MASK  (0x4U)
#define ADC10_CTL0_ADC10IFG_SHIFT (0x2U)
/* ADC10 interrupt flag.
  This bit is set if ADC10_MEM is loaded with a conversion result. It is
  automatically reset when the interrupt request is accepted, or it may
  be reset by software. When using the DTC, this flag is set when a
  block of transfers is completed.
  0b = No interrupt pending
  1b = Interrupt pending */
#define ADC10_CTL0_ADC10IFG(x)    (((uint16_t)(((uint16_t)(x)) << ADC10_CTL0_ADC10IFG_SHIFT)) & ADC10_CTL0_ADC10IFG_MASK)

/* ADC10_CTL0_ENC */
#define ADC10_CTL0_ENC_MASK  (0x2U)
#define ADC10_CTL0_ENC_SHIFT (0x1U)
/* Enable conversion
  0b = ADC10 disabled
  1b = ADC10 enabled */
#define ADC10_CTL0_ENC(x)    (((uint16_t)(((uint16_t)(x)) << ADC10_CTL0_ENC_SHIFT)) & ADC10_CTL0_ENC_MASK)

/* ADC10_CTL0_ADC10SC */
#define ADC10_CTL0_ADC10SC_MASK  (0x1U)
#define ADC10_CTL0_ADC10SC_SHIFT (0x0U)
/* Start conversion.
  Software-controlled sample-and-conversion start. ADC10SC and
  ENC may be set together with one instruction. ADC10SC is reset
  automatically.
  0b = No sample-and-conversion start
  1b = Start sample-and-conversion */
#define ADC10_CTL0_ADC10SC(x)    (((uint16_t)(((uint16_t)(x)) << ADC10_CTL0_ADC10SC_SHIFT)) & ADC10_CTL0_ADC10SC_MASK)

/* ADC10_CTL0_SHT */
#define ADC10_CTL0_SHT_4_CLOCKS  (0U) /* ADC10 sample-and-hold time: 4 ADC10CLK cycles */
#define ADC10_CTL0_SHT_8_CLOCKS  (1U) /* ADC10 sample-and-hold time: 8 ADC10CLK cycles */
#define ADC10_CTL0_SHT_16_CLOCKS (2U) /* ADC10 sample-and-hold time: 16 ADC10CLK cycles */
#define ADC10_CTL0_SHT_64_CLOCKS (3U) /* ADC10 sample-and-hold time: 64 ADC10CLK cycles */

/* ADC10_CTL0_SREF */
#define ADC10_CTL0_SREF_AVCC_AVSS      (0U) /* Select reference: VR+ = VCC and VR- = VSS */
#define ADC10_CTL0_SREF_VREF_AVSS      (1U) /* Select reference: VR+ = VREF+ and VR- = VSS */
#define ADC10_CTL0_SREF_VEREF_AVSS     (2U) /* Select reference: VR+ = VeREF+ and VR- = VSS. Devices with VeREF+ only */
#define ADC10_CTL0_SREF_BUF_VEREF_AVSS (3U) /* Select reference: VR+ = Buffered VeREF+ and VR- = VSS. Devices with VeREF+ pin only */
#define ADC10_CTL0_SREF_AVCC_VREF      (4U) /* Select reference: VR+ = VCC and VR- = VREF-/ VeREF-. Devices with VeREF- pin only */
#define ADC10_CTL0_SREF_VREF_VREF      (5U) /* Select reference: VR+ = VREF+ and VR- = VREF-/ VeREF-. Devices with VeREF+ and VeREF- pins only */
#define ADC10_CTL0_SREF_VEREF_VREF     (6U) /* Select reference: VR+ = VeREF+ and VR- = VREF-/ VeREF-. Devices with VeREF+ and VeREF- pins only */
#define ADC10_CTL0_SREF_BUF_VEREF_VREF (7U) /* Select reference: VR+ = Buffered VeREF+ and VR- = VREF-/ VeREF-. Devices with VeREF+ and VeREF- pins only */

/*****************************************************************************
 * @brief ADC10_CTL1
 *****************************************************************************/

/* ADC10_CTL1_INCH */
#define ADC10_CTL1_INCH_MASK  (0xf000U)
#define ADC10_CTL1_INCH_SHIFT (0xcU)
/* Input channel select.
  These bits select the channel for a single-conversion or the highest
  channel for a sequence of conversions.
  Only available ADC channels should be selected. See the devicespecific
  data sheet.
  Can be modified only when ENC = 0. */
#define ADC10_CTL1_INCH(x)    (((uint16_t)(((uint16_t)(x)) << ADC10_CTL1_INCH_SHIFT)) & ADC10_CTL1_INCH_MASK)

/* ADC10_CTL1_SHS */
#define ADC10_CTL1_SHS_MASK  (0xc00U)
#define ADC10_CTL1_SHS_SHIFT (0xaU)
/* Sample-and-hold source select.
  Can be modified only when ENC = 0.
  00b = ADC10SC bit
  01b = Timer_A.OUT1
  10b = Timer_A.OUT0
  11b = Timer_A.OUT2 (Timer_A.OUT1 on MSP430F20x0, MSP430G2x31, and MSP430G2x30 devices) */
#define ADC10_CTL1_SHS(x)    (((uint16_t)(((uint16_t)(x)) << ADC10_CTL1_SHS_SHIFT)) & ADC10_CTL1_SHS_MASK)

/* ADC10_CTL1_ADC10DF */
#define ADC10_CTL1_ADC10DF_MASK  (0x200U)
#define ADC10_CTL1_ADC10DF_SHIFT (0x9U)
/* ADC10 data format.
  Can be modified only when ENC = 0.
  0b = Straight binary
  1b = 2s complement */
#define ADC10_CTL1_ADC10DF(x)    (((uint16_t)(((uint16_t)(x)) << ADC10_CTL1_ADC10DF_SHIFT)) & ADC10_CTL1_ADC10DF_MASK)

/* ADC10_CTL1_ISSH */
#define ADC10_CTL1_ISSH_MASK  (0x100U)
#define ADC10_CTL1_ISSH_SHIFT (0x8U)
/* Invert signal sample-and-hold.
  Can be modified only when ENC = 0.
  0b = The sample-input signal is not inverted.
  1b = The sample-input signal is inverted. */
#define ADC10_CTL1_ISSH(x)    (((uint16_t)(((uint16_t)(x)) << ADC10_CTL1_ISSH_SHIFT)) & ADC10_CTL1_ISSH_MASK)

/* ADC10_CTL1_ADC10DIV */
#define ADC10_CTL1_ADC10DIV_MASK  (0xe0U)
#define ADC10_CTL1_ADC10DIV_SHIFT (0x5U)
/* ADC10 clock divider.
  Can be modified only when ENC = 0.
  000b = /1
  001b = /2
  010b = /3
  011b = /4
  100b = /5
  101b = /6
  110b = /7
  111b = /8 */
#define ADC10_CTL1_ADC10DIV(x)    (((uint16_t)(((uint16_t)(x)) << ADC10_CTL1_ADC10DIV_SHIFT)) & ADC10_CTL1_ADC10DIV_MASK)

/* ADC10_CTL1_ADC10SSEL */
#define ADC10_CTL1_ADC10SSEL_MASK  (0x18U)
#define ADC10_CTL1_ADC10SSEL_SHIFT (0x3U)
/* ADC10 clock source select.
  Can be modified only when ENC = 0.
  00b = ADC10OSC
  01b = ACLK
  10b = MCLK
  11b = SMCLK */
#define ADC10_CTL1_ADC10SSEL(x)    (((uint16_t)(((uint16_t)(x)) << ADC10_CTL1_ADC10SSEL_SHIFT)) & ADC10_CTL1_ADC10SSEL_MASK)

/* ADC10_CTL1_CONSEQ */
#define ADC10_CTL1_CONSEQ_MASK  (0x6U)
#define ADC10_CTL1_CONSEQ_SHIFT (0x1U)
/* Conversion sequence mode select
  00b = Single-channel single-conversion mode
  01b = Sequence-of-channels mode
  10b = Repeat-single-channel mode
  11b = Repeat-sequence-of-channels mode */
#define ADC10_CTL1_CONSEQ(x)    (((uint16_t)(((uint16_t)(x)) << ADC10_CTL1_CONSEQ_SHIFT)) & ADC10_CTL1_CONSEQ_MASK)

/* ADC10_CTL1_ADC10BUSY */
#define ADC10_CTL1_ADC10BUSY_MASK  (0x1U)
#define ADC10_CTL1_ADC10BUSY_SHIFT (0x0U)
/* ADC10 busy.
  This bit indicates an active sample or conversion operation
  0b = No operation is active.
  1b = A sequence, sample, or conversion is active. */
#define ADC10_CTL1_ADC10BUSY(x)    (((uint16_t)(((uint16_t)(x)) << ADC10_CTL1_ADC10BUSY_SHIFT)) & ADC10_CTL1_ADC10BUSY_MASK)

/* ADC10_CTL1_INCH */
#define ADC10_CTL1_INCH_A0            (00U) /* Input channel select: A0 */
#define ADC10_CTL1_INCH_A1            (01U) /* Input channel select: A1 */
#define ADC10_CTL1_INCH_A2            (02U) /* Input channel select: A2 */
#define ADC10_CTL1_INCH_A3            (03U) /* Input channel select: A3 */
#define ADC10_CTL1_INCH_A4            (04U) /* Input channel select: A4 */
#define ADC10_CTL1_INCH_A5            (05U) /* Input channel select: A5 */
#define ADC10_CTL1_INCH_A6            (06U) /* Input channel select: A6 */
#define ADC10_CTL1_INCH_A7            (07U) /* Input channel select: A7 */
#define ADC10_CTL1_INCH_VEREF         (08U) /* Input channel select: VeREF+ */
#define ADC10_CTL1_INCH_VREF_MINUS    (09U) /* Input channel select: VREF-/VeREF- */
#define ADC10_CTL1_INCH_TEMPERATURE   (10U) /* Input channel select: Temperature sensor */
#define ADC10_CTL1_INCH_VCC_VSS_HALF  (11U) /* Input channel select: (VCC - VSS) / 2 */
#define ADC10_CTL1_INCH_VCC_VSS_HALF2 (12U) /* Input channel select: (VCC - VSS) / 2, A12 on MSP430F22xx, MSP430G2x44, and MSP430G2x55 devices */
#define ADC10_CTL1_INCH_VCC_VSS_HALF3 (13U) /* Input channel select: (VCC - VSS) / 2, A13 on MSP430F22xx, MSP430G2x44, and MSP430G2x55 devices */
#define ADC10_CTL1_INCH_VCC_VSS_HALF4 (14U) /* Input channel select: (VCC - VSS) / 2, A14 on MSP430F22xx, MSP430G2x44, and MSP430G2x55 devices */
#define ADC10_CTL1_INCH_VCC_VSS_HALF5 (15U) /* Input channel select: (VCC - VSS) / 2, A15 on MSP430F22xx, MSP430G2x44, and MSP430G2x55 devices */

/* ADC10_CTL1_DIV */
#define ADC10_CTL1_DIV_1 (00U) /* ADC10 clock divider: 1 */
#define ADC10_CTL1_DIV_2 (01U) /* ADC10 clock divider: 2 */
#define ADC10_CTL1_DIV_3 (02U) /* ADC10 clock divider: 3 */
#define ADC10_CTL1_DIV_4 (03U) /* ADC10 clock divider: 4 */
#define ADC10_CTL1_DIV_5 (04U) /* ADC10 clock divider: 5 */
#define ADC10_CTL1_DIV_6 (05U) /* ADC10 clock divider: 6 */
#define ADC10_CTL1_DIV_7 (06U) /* ADC10 clock divider: 7 */
#define ADC10_CTL1_DIV_8 (07U) /* ADC10 clock divider: 8 */

/* ADC10_CTL1_SHS */
#define ADC10_CTL1_SHS_SC      (0U) /* Sample-and-hold source select: ADC10SC bit */
#define ADC10_CTL1_SHS_TA_OUT1 (1U) /* Sample-and-hold source select: Timer_A.OUT1 */
#define ADC10_CTL1_SHS_TA_OUT0 (2U) /* Sample-and-hold source select: Timer_A.OUT0 */
#define ADC10_CTL1_SHS_TA_OUT2 (3U) /* Sample-and-hold source select: Timer_A.OUT2 (Timer_A.OUT1 on MSP430F20x0, MSP430G2x31, and MSP430G2x30 devices) */

/* ADC10_CTL1_SSEL */
#define ADC10_CTL1_SSEL_ADC10OSC (0U) /* ADC10 clock source select: ADC10OSC */
#define ADC10_CTL1_SSEL_ACLK     (1U) /* ADC10 clock source select: ACLK */
#define ADC10_CTL1_SSEL_MCLK     (2U) /* ADC10 clock source select: MCLK */
#define ADC10_CTL1_SSEL_SMCLK    (3U) /* ADC10 clock source select: SMCLK */

/* ADC10_CTL1_CONSEQ */
#define ADC10_CTL1_CONSEQ_SINGLE          (0U) /* Conversion sequence mode select: Single-channel single-conversion mode */
#define ADC10_CTL1_CONSEQ_SEQUENCE        (1U) /* Conversion sequence mode select: Sequence-of-channels mode */
#define ADC10_CTL1_CONSEQ_REPEAT_SINGLE   (2U) /* Conversion sequence mode select: Repeat-single-channel mode */
#define ADC10_CTL1_CONSEQ_REPEAT_SEQUENCE (3U) /* Conversion sequence mode select: Repeat-sequence-of-channels mode */

/*****************************************************************************
 * @brief ADC10_MEM
 *****************************************************************************/

 /* ADC10_MEM */
#define ADC10_MEM_MASK  (0x03ffU)
#define ADC10_MEM_SHIFT (0x0U)
/* If ADC10DF = 0, the 10-bit conversion results are right-justified
  straight-binary format. Bit 9 is the MSB. 15-10 are always 0.
  If ADC10DF = 1, the 10-bit conversion results are left-justified 2scomplement
  format. Bit 15 is the MSB. Bits 5-0 are always 0. */
#define ADC10_MEM(x)    (((uint16_t)(((uint16_t)(x)) << ADC10_MEM_SHIFT)) & ADC10_MEM_MASK)

/*****************************************************************************
 * @brief ADC10_DTC0
 *****************************************************************************/

 /* ADC10_DTC0_ADC10TB */
#define ADC10_DTC0_ADC10TB_MASK  (0x8U)
#define ADC10_DTC0_ADC10TB_SHIFT (0x3U)
/* ADC10 two-block mode
  0b = One-block transfer mode
  1b = Two-block transfer mode */
#define ADC10_DTC0_ADC10TB(x)    (((uint8_t)(((uint8_t)(x)) << ADC10_DTC0_ADC10TB_SHIFT)) & ADC10_DTC0_ADC10TB_MASK)

/* ADC10_DTC0_ADC10CT */
#define ADC10_DTC0_ADC10CT_MASK  (0x4U)
#define ADC10_DTC0_ADC10CT_SHIFT (0x2U)
/* ADC10 continuous transfer
  0b = Data transfer stops when one block (one-block mode) or two
  blocks (two-block mode) have completed.
  1b = Data is transferred continuously. DTC operation is stopped only
  if ADC10CT cleared, or ADC10SA is written to. */
#define ADC10_DTC0_ADC10CT(x)    (((uint8_t)(((uint8_t)(x)) << ADC10_DTC0_ADC10CT_SHIFT)) & ADC10_DTC0_ADC10CT_MASK)

/* ADC10_DTC0_ADC10B1 */
#define ADC10_DTC0_ADC10B1_MASK  (0x2U)
#define ADC10_DTC0_ADC10B1_SHIFT (0x1U)
/* ADC10 block one.
  This bit indicates for two-block mode which block is filled with ADC10
  conversion results. ADC10B1 is valid only after ADC10IFG has been
  set the first time during DTC operation. ADC10TB must also be set.
  0b = Block 2 is filled
  1b = Block 1 is filled */
#define ADC10_DTC0_ADC10B1(x)    (((uint8_t)(((uint8_t)(x)) << ADC10_DTC0_ADC10B1_SHIFT)) & ADC10_DTC0_ADC10B1_MASK)

/* ADC10_DTC0_ADC10FETCH */
#define ADC10_DTC0_ADC10FETCH_MASK  (0x1U)
#define ADC10_DTC0_ADC10FETCH_SHIFT (0x0U)
/* This bit should normally be reset. */
#define ADC10_DTC0_ADC10FETCH(x)    (((uint8_t)(((uint8_t)(x)) << ADC10_DTC0_ADC10FETCH_SHIFT)) & ADC10_DTC0_ADC10FETCH_MASK)

/*****************************************************************************
* @brief BCS_DCOCTL
*****************************************************************************/

/* BCS_DCOCTL_DCO */
#define BCS_DCOCTL_DCO_MASK  (0xe0U)
#define BCS_DCOCTL_DCO_SHIFT (0x05U)
/* DCO frequency select. These bits select which of the eight discrete
  DCO frequencies within the range defined by the RSELx setting is
  selected. */
#define BCS_DCOCTL_DCO(x)    (((uint8_t)(((uint8_t)(x)) << BCS_DCOCTL_DCO_SHIFT)) & BCS_DCOCTL_DCO_MASK)

/* BCS_DCOCTL_MOD */
#define BCS_DCOCTL_MOD_MASK  (0x1fU)
#define BCS_DCOCTL_MOD_SHIFT (0x00U)
/* Modulator selection. These bits define how often the fDCO+1
  frequency is used within a period of 32 DCOCLK cycles. During the
  remaining clock cycles (32  MOD) the fDCO frequency is used. Not
  useable when DCOx = 7. */
#define BCS_DCOCTL_MOD(x)    (((uint8_t)(((uint8_t)(x)) << BCS_DCOCTL_MOD_SHIFT)) & BCS_DCOCTL_MOD_MASK)

/*****************************************************************************
* @brief BCS_CTL1
*****************************************************************************/

/* BCS_CTL1_XT2OFF */
#define BCS_CTL1_XT2OFF_MASK  (0x80U)
#define BCS_CTL1_XT2OFF_SHIFT (0x07U)
/* XT2 off. This bit turns off the XT2 oscillator.
  0b = XT2 is on
  1b = XT2 is off if it is not used for MCLK or SMCLK. */
#define BCS_CTL1_XT2OFF(x)    (((uint8_t)(((uint8_t)(x)) << BCS_CTL1_XT2OFF_SHIFT)) & BCS_CTL1_XT2OFF_MASK)

/* BCS_CTL1_XTS */
#define BCS_CTL1_XTS_MASK  (0x40U)
#define BCS_CTL1_XTS_SHIFT (0x06U)
/* LFXT1 mode select
  0b = Low-frequency mode
  1b = High-frequency mode */
#define BCS_CTL1_XTS(x)    (((uint8_t)(((uint8_t)(x)) << BCS_CTL1_XTS_SHIFT)) & BCS_CTL1_XTS_MASK)

/* BCS_CTL1_DIVA */
#define BCS_CTL1_DIVA_MASK  (0x30U)
#define BCS_CTL1_DIVA_SHIFT (0x04U)
/* Divider for ACLK
  00b = /1
  01b = /2
  10b = /4
  11b = /8 */
#define BCS_CTL1_DIVA(x)    (((uint8_t)(((uint8_t)(x)) << BCS_CTL1_DIVA_SHIFT)) & BCS_CTL1_DIVA_MASK)

/* BCS_CTL1_RSEL */
#define BCS_CTL1_RSEL_MASK  (0x0fU)
#define BCS_CTL1_RSEL_SHIFT (0x00U)
/* Range select. Sixteen different frequency ranges are available. The
  lowest frequency range is selected by setting RSELx = 0. RSEL3 is
  ignored when DCOR = 1. */
#define BCS_CTL1_RSEL(x)    (((uint8_t)(((uint8_t)(x)) << BCS_CTL1_RSEL_SHIFT)) & BCS_CTL1_RSEL_MASK)

/* BCS_CTL1_XT2OFF */
#define BCS_CTL1_XT2OFF_ON  (0U) /* XT2 is on */
#define BCS_CTL1_XT2OFF_OFF (1U) /* XT2 is off if it is not used for MCLK or SMCLK */

/* BCS_CTL1_XTS */
#define BCS_CTL1_XTS_LOW_FREQ (0U) /* Low-frequency mode */
#define BCS_CTL1_XTS_HI_FREQ  (1U) /* High-frequency mode */

/* BCS_CTL1_DIVA */
#define BCS_CTL1_DIVA_1 (0U) /* Divider for ACLK: 1 */
#define BCS_CTL1_DIVA_2 (1U) /* Divider for ACLK: 2 */
#define BCS_CTL1_DIVA_4 (2U) /* Divider for ACLK: 4 */
#define BCS_CTL1_DIVA_8 (3U) /* Divider for ACLK: 8 */

/*****************************************************************************
* @brief BCS_CTL2
*****************************************************************************/

/* BCS_CTL2_SELM */
#define BCS_CTL2_SELM_MASK  (0xc0U)
#define BCS_CTL2_SELM_SHIFT (0x06U)
/* Select MCLK. These bits select the MCLK source.
  00b = DCOCLK
  01b = DCOCLK
  10b = XT2CLK when XT2 oscillator present on-chip. LFXT1CLK or
  VLOCLK when XT2 oscillator not present on-chip.
  11b = LFXT1CLK or VLOCLK */
#define BCS_CTL2_SELM(x)    (((uint8_t)(((uint8_t)(x)) << BCS_CTL2_SELM_SHIFT)) & BCS_CTL2_SELM_MASK)

/* BCS_CTL2_DIVM */
#define BCS_CTL2_DIVM_MASK  (0x30U)
#define BCS_CTL2_DIVM_SHIFT (0x04U)
/* Divider for MCLK
  00b = /1
  01b = /2
  10b = /4
  11b = /8 */
#define BCS_CTL2_DIVM(x)    (((uint8_t)(((uint8_t)(x)) << BCS_CTL2_DIVM_SHIFT)) & BCS_CTL2_DIVM_MASK)

/* BCS_CTL2_SELS */
#define BCS_CTL2_SELS_MASK  (0x08U)
#define BCS_CTL2_SELS_SHIFT (0x03U)
/* Select SMCLK. This bit selects the SMCLK source.
  0b = DCOCLK
  1b = XT2CLK when XT2 oscillator present. LFXT1CLK or VLOCLK when XT2 oscillator not present */
#define BCS_CTL2_SELS(x)    (((uint8_t)(((uint8_t)(x)) << BCS_CTL2_SELS_SHIFT)) & BCS_CTL2_SELS_MASK)

/* BCS_CTL2_DIVS */
#define BCS_CTL2_DIVS_MASK  (0x06U)
#define BCS_CTL2_DIVS_SHIFT (0x01U)
/* Divider for SMCLK
  00b = /1
  01b = /2
  10b = /4
  11b = /8 */
#define BCS_CTL2_DIVS(x)    (((uint8_t)(((uint8_t)(x)) << BCS_CTL2_DIVS_SHIFT)) & BCS_CTL2_DIVS_MASK)

/* BCS_CTL2_DCOR */
#define BCS_CTL2_DCOR_MASK  (0x01U)
#define BCS_CTL2_DCOR_SHIFT (0x00U)
/* DCO resistor select. Not available in all devices. See the devicespecific data sheet.
  0b = Internal resistor
  1b = External resistor */
#define BCS_CTL2_DCOR(x)    (((uint8_t)(((uint8_t)(x)) << BCS_CTL2_DCOR_SHIFT)) & BCS_CTL2_DCOR_MASK)

/* BCS_CTL2_SELM */
#define BCS_CTL2_SELM_DCOCLK          (0U) /* Select MCLK source: DCOCLK */
#define BCS_CTL2_SELM_DCOCLK2         (1U) /* Select MCLK source: DCOCLK */
#define BCS_CTL2_SELM_XT2CLK_LFXT1CLK (2U) /* Select MCLK source: XT2CLK when XT2 oscillator present on-chip. LFXT1CLK or VLOCLK when XT2 oscillator not present on-chip. */
#define BCS_CTL2_SELM_LFXT1CLK_VLOCLK (3U) /* Select MCLK source: LFXT1CLK or VLOCLK */

/* BCS_CTL2_DIVM */
#define BCS_CTL2_DIVM_1 (0U) /* Divider for MCLK: 1 */
#define BCS_CTL2_DIVM_2 (1U) /* Divider for MCLK: 2 */
#define BCS_CTL2_DIVM_4 (2U) /* Divider for MCLK: 4 */
#define BCS_CTL2_DIVM_8 (3U) /* Divider for MCLK: 8 */

/* BCS_CTL2_DIVS */
#define BCS_CTL2_DIVS_1 (0U) /* Divider for SMCLK: 1 */
#define BCS_CTL2_DIVS_2 (1U) /* Divider for SMCLK: 2 */
#define BCS_CTL2_DIVS_4 (2U) /* Divider for SMCLK: 4 */
#define BCS_CTL2_DIVS_8 (3U) /* Divider for SMCLK: 8 */

/*****************************************************************************
* @brief BCS_CTL3
*****************************************************************************/

/* BCS_CTL3_XT2S */
#define BCS_CTL3_XT2S_MASK  (0xc0U)
#define BCS_CTL3_XT2S_SHIFT (0x06U)
/* XT2 range select. These bits select the frequency range for XT2.
  00b = 0.4- to 1-MHz crystal or resonator
  01b = 1- to 3-MHz crystal or resonator
  10b = 3- to 16-MHz crystal or resonator
  11b = Digital external 0.4- to 16-MHz clock source */
#define BCS_CTL3_XT2S(x)    (((uint8_t)(((uint8_t)(x)) << BCS_CTL3_XT2S_SHIFT)) & BCS_CTL3_XT2S_MASK)

/* BCS_CTL3_LFXT1S */
#define BCS_CTL3_LFXT1S_MASK  (0x30U)
#define BCS_CTL3_LFXT1S_SHIFT (0x04U)
/* Low-frequency clock select and LFXT1 range select. These bits
  select between LFXT1 and VLO when XTS = 0, and select the
  frequency range for LFXT1 when XTS = 1.
  MSP430G22x0: The LFXT1Sx bits should be programmed to 10b
  during the initialization and start-up code to select VLOCLK (for more
  details refer to Digital I/O chapter). The other bits are reserved and
  should not be altered.

  When XTS = 0:
  00b = 32768-Hz crystal on LFXT1
  01b = Reserved
  10b = VLOCLK (Reserved in MSP430F21x1 devices)
  11b = Digital external clock source

  When XTS = 1 (Not applicable for MSP430F20xx, MSP430G2xx1, MSP430G2xx2, MSP430G2xx3):
  00b = 0.4- to 1-MHz crystal or resonator
  01b = 1- to 3-MHz crystal or resonator
  10b = 3- to 16-MHz crystal or resonator
  11b = Digital external 0.4- to 16-MHz clock source

  LFXT1Sx definition for MSP430AFE2xx devices:
  00b = Reserved
  01b = Reserved
  10b = VLOCLK
  11b = Reserved */
#define BCS_CTL3_LFXT1S(x)    (((uint8_t)(((uint8_t)(x)) << BCS_CTL3_LFXT1S_SHIFT)) & BCS_CTL3_LFXT1S_MASK)

/* BCS_CTL3_XCAP */
#define BCS_CTL3_XCAP_MASK  (0x0cU)
#define BCS_CTL3_XCAP_SHIFT (0x02U)
/* Oscillator capacitor selection. These bits select the effective
  capacitance seen by the LFXT1 crystal when XTS = 0. If XTS = 1
  or if LFXT1Sx = 11 XCAPx should be 00.
  This bit is reserved in the MSP430AFE2xx devices.
  00b = Approximately 1 pF
  01b = Approximately 6 pF
  10b = Approximately 10 pF
  11b = Approximately 12.5 pF */
#define BCS_CTL3_XCAP(x)    (((uint8_t)(((uint8_t)(x)) << BCS_CTL3_XCAP_SHIFT)) & BCS_CTL3_XCAP_MASK)

/* BCS_CTL3_XT2OF */
#define BCS_CTL3_XT2OF_MASK  (0x02U)
#define BCS_CTL3_XT2OF_SHIFT (0x01U)
/* XT2 oscillator fault.
  Does not apply to MSP430x2xx, MSP430x21xx, or MSP430x22xx devices.
  0b = No fault condition present
  1b = Fault condition present */
#define BCS_CTL3_XT2OF(x)    (((uint8_t)(((uint8_t)(x)) << BCS_CTL3_XT2OF_SHIFT)) & BCS_CTL3_XT2OF_MASK)

/* BCS_CTL3_LFXT1OF */
#define BCS_CTL3_LFXT1OF_MASK  (0x01U)
#define BCS_CTL3_LFXT1OF_SHIFT (0x00U)
/* LFXT1 oscillator fault.
  This bit is reserved in the MSP430AFE2xx devices.
  0b = No fault condition present
  1b = Fault condition present */
#define BCS_CTL3_LFXT1OF(x)    (((uint8_t)(((uint8_t)(x)) << BCS_CTL3_LFXT1OF_SHIFT)) & BCS_CTL3_LFXT1OF_MASK)

/* BCS_CTL3_XT2S */
#define BCS_CTL3_XT2S_04_1MHZ (0U) /* XT2 range select: 0.4- to 1-MHz crystal or resonator */
#define BCS_CTL3_XT2S_1_3MHZ  (1U) /* XT2 range select: 1- to 3-MHz crystal or resonator */
#define BCS_CTL3_XT2S_3_16MHZ (2U) /* XT2 range select: 3- to 16-MHz crystal or resonator */
#define BCS_CTL3_XT2S_EXT     (3U) /* XT2 range select: Digital external 0.4- to 16-MHz clock source */

/* BCS_CTL3_XCAP */
#define BCS_CTL3_XCAP_1PF  (0U) /* Oscillator capacitor selection: 1 pF */
#define BCS_CTL3_XCAP_6PF  (1U) /* Oscillator capacitor selection: 6 pF */
#define BCS_CTL3_XCAP_10PF (2U) /* Oscillator capacitor selection: 10 pF */
#define BCS_CTL3_XCAP_12PF (3U) /* Oscillator capacitor selection: 12.5 pF */

/*****************************************************************************
* @brief CA_CTL1
*****************************************************************************/

/* CA_CTL1_CAIFG */
#define CA_CTL1_CAIFG_MASK  (0x1U)
#define CA_CTL1_CAIFG_SHIFT (0x0U)
/* The Comparator_A+ interrupt flag
  0b = No interrupt pending
  1b = Interrupt pending */
#define CA_CTL1_CAIFG(x)    (((uint8_t)(((uint8_t)(x)) << CA_CTL1_CAIFG_SHIFT)) & CA_CTL1_CAIFG_MASK)

/* CA_CTL1_CAIE */
#define CA_CTL1_CAIE_MASK  (0x2U)
#define CA_CTL1_CAIE_SHIFT (0x1U)
/* Comparator_A+ interrupt enable
  0b = Disabled
  1b = Enabled */
#define CA_CTL1_CAIE(x)    (((uint8_t)(((uint8_t)(x)) << CA_CTL1_CAIE_SHIFT)) & CA_CTL1_CAIE_MASK)

/* CA_CTL1_CAIES */
#define CA_CTL1_CAIES_MASK  (0x4U)
#define CA_CTL1_CAIES_SHIFT (0x2U)
/* Comparator_A+ interrupt edge select
  0b = Rising edge
  1b = Falling edge */
#define CA_CTL1_CAIES(x)    (((uint8_t)(((uint8_t)(x)) << CA_CTL1_CAIES_SHIFT)) & CA_CTL1_CAIES_MASK)

/* CA_CTL1_CAON */
#define CA_CTL1_CAON_MASK  (0x8U)
#define CA_CTL1_CAON_SHIFT (0x3U)
/* Comparator_A+ on. This bit turns on the comparator. When the
  comparator is off it consumes no current. The reference circuitry is
  enabled or disabled independently.
  0b = Off
  1b = On */
#define CA_CTL1_CAON(x)    (((uint8_t)(((uint8_t)(x)) << CA_CTL1_CAON_SHIFT)) & CA_CTL1_CAON_MASK)

/* CA_CTL1_CAREF */
#define CA_CTL1_CAREF0_MASK  (0x30U)
#define CA_CTL1_CAREF0_SHIFT (0x4U)
/* Comparator_A+ reference.
  These bits select the reference voltage VCAREF. */
#define CA_CTL1_CAREF0(x)    (((uint8_t)(((uint8_t)(x)) << CA_CTL1_CAREF0_SHIFT)) & CA_CTL1_CAREF0_MASK)

/* CA_CTL1_CARSEL */
#define CA_CTL1_CARSEL_MASK  (0x40U)
#define CA_CTL1_CARSEL_SHIFT (0x6U)
/* Comparator_A+ reference select. This bit selects which terminal the sVCAREF is applied to.
  When CAEX = 0:
  0b = VCAREF is applied to the positive terminal
  01b = VCAREF is applied to the negative terminal
  When CAEX = 1:
  0b = VCAREF is applied to the negative terminal
  1b = VCAREF is applied to the positive terminal */
#define CA_CTL1_CARSEL(x)    (((uint8_t)(((uint8_t)(x)) << CA_CTL1_CARSEL_SHIFT)) & CA_CTL1_CARSEL_MASK)

/* CA_CTL1_CAEX */
#define CA_CTL1_CAEX_MASK  (0x80U)
#define CA_CTL1_CAEX_SHIFT (0x7U)
/* Comparator_A+ exchange. This bit exchanges the comparator inputs and inverts the comparator output. */
#define CA_CTL1_CAEX(x)    (((uint8_t)(((uint8_t)(x)) << CA_CTL1_CAEX_SHIFT)) & CA_CTL1_CAEX_MASK)

/* CA_CTL1_CAREF */
#define CA_CTL1_CAREF_INTERNAL (0U) /* Comparator_A+ reference: Internal reference off. An external reference can be applied. */
#define CA_CTL1_CAREF_0_25_VCC (1U) /* Comparator_A+ reference: 0.25*VCC */
#define CA_CTL1_CAREF_0_5_VCC  (2U) /* Comparator_A+ reference: 0.50*VCC */
#define CA_CTL1_CAREF_DIOIDE   (3U) /* Comparator_A+ reference: Diode reference is selected */

/*****************************************************************************
* @brief CA_CTL2
*****************************************************************************/

/* CA_CTL2_CAOUT */
#define CA_CTL2_CAOUT_MASK  (0x1U)
#define CA_CTL2_CAOUT_SHIFT (0x0U)
/* Comparator_A+ output. This bit reflects the value of the comparator output.
  Writing this bit has no effect.*/
#define CA_CTL2_CAOUT(x)    (((uint8_t)(((uint8_t)(x)) << CA_CTL2_CAOUT_SHIFT)) & CA_CTL2_CAOUT_MASK)

/* CA_CTL2_CAF */
#define CA_CTL2_CAF_MASK  (0x2U)
#define CA_CTL2_CAF_SHIFT (0x1U)
/* Comparator_A+ output filter
  0b = Comparator_A+ output is not filtered
  1b = Comparator_A+ output is filtered */
#define CA_CTL2_CAF(x)    (((uint8_t)(((uint8_t)(x)) << CA_CTL2_CAF_SHIFT)) & CA_CTL2_CAF_MASK)

/* CA_CTL2_P2CA0 */
#define CA_CTL2_P2CA0_MASK  (0x44U)
#define CA_CTL2_P2CA0_SHIFT (0x2U)
/* Input select. This bit, together with P2CA4, selects the positive
 terminal input when CAEX = 0 and the negative terminal input when CAEX = 1. */
#define CA_CTL2_P2CA0(x)    (((uint8_t)(((uint8_t)(x)) << CA_CTL2_P2CA0_SHIFT)) & CA_CTL2_P2CA0_MASK)

/* CA_CTL2_P2CA1 */
#define CA_CTL2_P2CA1_MASK  (0x38U)
#define CA_CTL2_P2CA1_SHIFT (0x3U)
/* Input select. These bits select the negative terminal input when
  CAEX = 0 and the positive terminal input when CAEX = 1.
  MSP430G2210: Only channels 2, 5, 6, and 7 are available. Other
  channels should not be selected. */
#define CA_CTL2_P2CA1(x)    (((uint8_t)(((uint8_t)(x)) << CA_CTL2_P2CA1_SHIFT)) & CA_CTL2_P2CA1_MASK)

/* CA_CTL2_CASHORT */
#define CA_CTL2_CASHORT_MASK  (0x80U)
#define CA_CTL2_CASHORT_SHIFT (0x7U)
/* Input short. This bit shorts the positive and negative input terminals.
  0b = Inputs not shorted
  1b = Inputs shorted */
#define CA_CTL2_CASHORT(x)    (((uint8_t)(((uint8_t)(x)) << CA_CTL2_CASHORT_SHIFT)) & CA_CTL2_CASHORT_MASK)

/* CA_CTL2_P2CA0 */
#define CA_CTL2_P2CA0_NO_CONNECTION (00U) /* Input select: No connection */
#define CA_CTL2_P2CA0_CA0           (01U) /* Input select: CA0 */
#define CA_CTL2_P2CA0_CA1           (16U) /* Input select: CA1 */
#define CA_CTL2_P2CA0_CA2           (17U) /* Input select: CA2 */

/* CA_CTL2_P2CA1 */
#define CA_CTL2_P2CA1_NO_CONNECTION (0U) /* Input select: No connection */
#define CA_CTL2_P2CA1_CA1           (1U) /* Input select: CA1 */
#define CA_CTL2_P2CA1_CA2           (2U) /* Input select: CA2 */
#define CA_CTL2_P2CA1_CA3           (3U) /* Input select: CA3 */
#define CA_CTL2_P2CA1_CA4           (4U) /* Input select: CA4 */
#define CA_CTL2_P2CA1_CA5           (5U) /* Input select: CA5 */
#define CA_CTL2_P2CA1_CA6           (6U) /* Input select: CA6 */
#define CA_CTL2_P2CA1_CA7           (7U) /* Input select: CA7 */

/*****************************************************************************
* @brief CA_PD
*****************************************************************************/

/* CA_PD_CA_PD0 */
#define CA_PD_CA_PD0_MASK  (0x1U)
#define CA_PD_CA_PD0_SHIFT (0x0U)
/* Comparator_A+ port disable. These bits individually disable the input
  buffer for the pins of the port associated with Comparator_A+. For
  example, if CA0 is on pin P2.3, the CA_PDx bits can be used to
  individually enable or disable each P2.x pin buffer. CA_PD0 disables
  P2.0, CA_PD1 disables P2.1, and so forth.
  0b = The input buffer is enabled.
  1b = The input buffer is disabled. */
#define CA_PD_CA_PD0(x)    (((uint8_t)(((uint8_t)(x)) << CA_PD_CA_PD0_SHIFT)) & CA_PD_CA_PD0_MASK)

/* CA_PD_CA_PD1 */
#define CA_PD_CA_PD1_MASK  (0x2U)
#define CA_PD_CA_PD1_SHIFT (0x1U)
/* Comparator_A+ port disable. These bits individually disable the input
  buffer for the pins of the port associated with Comparator_A+. For
  example, if CA0 is on pin P2.3, the CA_PDx bits can be used to
  individually enable or disable each P2.x pin buffer. CA_PD0 disables
  P2.0, CA_PD1 disables P2.1, and so forth.
  0b = The input buffer is enabled.
  1b = The input buffer is disabled. */
#define CA_PD_CA_PD1(x)    (((uint8_t)(((uint8_t)(x)) << CA_PD_CA_PD1_SHIFT)) & CA_PD_CA_PD1_MASK)

/* CA_PD_CA_PD2 */
#define CA_PD_CA_PD2_MASK  (0x4U)
#define CA_PD_CA_PD2_SHIFT (0x2U)
/* Comparator_A+ port disable. These bits individually disable the input
  buffer for the pins of the port associated with Comparator_A+. For
  example, if CA0 is on pin P2.3, the CA_PDx bits can be used to
  individually enable or disable each P2.x pin buffer. CA_PD0 disables
  P2.0, CA_PD1 disables P2.1, and so forth.
  0b = The input buffer is enabled.
  1b = The input buffer is disabled. */
#define CA_PD_CA_PD2(x)    (((uint8_t)(((uint8_t)(x)) << CA_PD_CA_PD2_SHIFT)) & CA_PD_CA_PD2_MASK)

/* CA_PD_CA_PD3 */
#define CA_PD_CA_PD3_MASK  (0x8U)
#define CA_PD_CA_PD3_SHIFT (0x3U)
/* Comparator_A+ port disable. These bits individually disable the input
  buffer for the pins of the port associated with Comparator_A+. For
  example, if CA0 is on pin P2.3, the CA_PDx bits can be used to
  individually enable or disable each P2.x pin buffer. CA_PD0 disables
  P2.0, CA_PD1 disables P2.1, and so forth.
  0b = The input buffer is enabled.
  1b = The input buffer is disabled. */
#define CA_PD_CA_PD3(x)    (((uint8_t)(((uint8_t)(x)) << CA_PD_CA_PD3_SHIFT)) & CA_PD_CA_PD3_MASK)

/* CA_PD_CA_PD4 */
#define CA_PD_CA_PD4_MASK  (0x10U)
#define CA_PD_CA_PD4_SHIFT (0x4U)
/* Comparator_A+ port disable. These bits individually disable the input
  buffer for the pins of the port associated with Comparator_A+. For
  example, if CA0 is on pin P2.3, the CA_PDx bits can be used to
  individually enable or disable each P2.x pin buffer. CA_PD0 disables
  P2.0, CA_PD1 disables P2.1, and so forth.
  0b = The input buffer is enabled.
  1b = The input buffer is disabled. */
#define CA_PD_CA_PD4(x)    (((uint8_t)(((uint8_t)(x)) << CA_PD_CA_PD4_SHIFT)) & CA_PD_CA_PD4_MASK)

/* CA_PD_CA_PD5 */
#define CA_PD_CA_PD5_MASK  (0x20U)
#define CA_PD_CA_PD5_SHIFT (0x5U)
/* Comparator_A+ port disable. These bits individually disable the input
  buffer for the pins of the port associated with Comparator_A+. For
  example, if CA0 is on pin P2.3, the CA_PDx bits can be used to
  individually enable or disable each P2.x pin buffer. CA_PD0 disables
  P2.0, CA_PD1 disables P2.1, and so forth.
  0b = The input buffer is enabled.
  1b = The input buffer is disabled. */
#define CA_PD_CA_PD5(x)    (((uint8_t)(((uint8_t)(x)) << CA_PD_CA_PD5_SHIFT)) & CA_PD_CA_PD5_MASK)

/* CA_PD_CA_PD6 */
#define CA_PD_CA_PD6_MASK  (0x40U)
#define CA_PD_CA_PD6_SHIFT (0x6U)
/* Comparator_A+ port disable. These bits individually disable the input
  buffer for the pins of the port associated with Comparator_A+. For
  example, if CA0 is on pin P2.3, the CA_PDx bits can be used to
  individually enable or disable each P2.x pin buffer. CA_PD0 disables
  P2.0, CA_PD1 disables P2.1, and so forth.
  0b = The input buffer is enabled.
  1b = The input buffer is disabled. */
#define CA_PD_CA_PD6(x)    (((uint8_t)(((uint8_t)(x)) << CA_PD_CA_PD6_SHIFT)) & CA_PD_CA_PD6_MASK)

/* CA_PD_CA_PD7 */
#define CA_PD_CA_PD7_MASK  (0x80U)
#define CA_PD_CA_PD7_SHIFT (0x7U)
/* Comparator_A+ port disable. These bits individually disable the input
  buffer for the pins of the port associated with Comparator_A+. For
  example, if CA0 is on pin P2.3, the CA_PDx bits can be used to
  individually enable or disable each P2.x pin buffer. CA_PD0 disables
  P2.0, CA_PD1 disables P2.1, and so forth.
  0b = The input buffer is enabled.
  1b = The input buffer is disabled. */
#define CA_PD_CA_PD7(x)    (((uint8_t)(((uint8_t)(x)) << CA_PD_CA_PD7_SHIFT)) & CA_PD_CA_PD7_MASK)

/*****************************************************************************
* @brief FLASH_CTL1
*****************************************************************************/

/* FLASH_CTL1_FWKEY */
#define FLASH_CTL1_FWKEY_MASK  (0xff00U)
#define FLASH_CTL1_FWKEY_SHIFT (0x8U)
/* FLASH_CTLx password. Always reads as 096h. Must be written as 0A5h.
  Writing any other value generates a PUC. */
#define FLASH_CTL1_FWKEY(x)    (((uint16_t)(((uint16_t)(x)) << FLASH_CTL1_FWKEY_SHIFT)) & FLASH_CTL1_FWKEY_MASK)

/* FLASH_CTL1_BLKWRT */
#define FLASH_CTL1_BLKWRT_MASK  (0x80U)
#define FLASH_CTL1_BLKWRT_SHIFT (0x7U)
/* Block write mode. WRT must also be set for block write mode.
  BLKWRT is automatically reset when EMEX is set.
  0b = Block-write mode is off
  1b = Block-write mode is on */
#define FLASH_CTL1_BLKWRT(x)    (((uint16_t)(((uint16_t)(x)) << FLASH_CTL1_BLKWRT_SHIFT)) & FLASH_CTL1_BLKWRT_MASK)

/* FLASH_CTL1_WRT */
#define FLASH_CTL1_WRT_MASK  (0x40U)
#define FLASH_CTL1_WRT_SHIFT (0x6U)
/* Write. This bit is used to select any write mode. WRT is automatically
  reset when EMEX is set.
  0b = Write mode is off
  1b = Write mode is on */
#define FLASH_CTL1_WRT(x)    (((uint16_t)(((uint16_t)(x)) << FLASH_CTL1_WRT_SHIFT)) & FLASH_CTL1_WRT_MASK)

/* FLASH_CTL1_MERAS */
#define FLASH_CTL1_MERAS_MASK  (0x4U)
#define FLASH_CTL1_MERAS_SHIFT (0x2U)
/* Mass erase and erase. These bits are used together to select the
  erase mode. MERAS and ERASE are automatically reset when
  1 ERASE R/W 0h EMEX is set. */
#define FLASH_CTL1_MERAS(x)    (((uint16_t)(((uint16_t)(x)) << FLASH_CTL1_MERAS_SHIFT)) & FLASH_CTL1_MERAS_MASK)

/* FLASH_CTL1_ERASE */
#define FLASH_CTL1_ERASE_MASK  (0x2U)
#define FLASH_CTL1_ERASE_SHIFT (0x1U)
/* Mass erase and erase. These bits are used together to select the
  erase mode. MERAS and ERASE are automatically reset when
  1 ERASE R/W 0h EMEX is set. */
#define FLASH_CTL1_ERASE(x)    (((uint16_t)(((uint16_t)(x)) << FLASH_CTL1_ERASE_SHIFT)) & FLASH_CTL1_ERASE_MASK)

/*****************************************************************************
* @brief FLASH_CTL2
*****************************************************************************/

/* FLASH_CTL2_FWKEY */
#define FLASH_CTL2_FWKEY_MASK  (0xff00U)
#define FLASH_CTL2_FWKEY_SHIFT (0x8U)
/* FLASH_CTLx password. Always reads as 096h. Must be written as 0A5h.
  Writing any other value generates a PUC. */
#define FLASH_CTL2_FWKEY(x)    (((uint16_t)(((uint16_t)(x)) << FLASH_CTL2_FWKEY_SHIFT)) & FLASH_CTL2_FWKEY_MASK)

/* FLASH_CTL2_FSSEL */
#define FLASH_CTL2_FSSEL_MASK  (0xc0U)
#define FLASH_CTL2_FSSEL_SHIFT (0x6U)
/* Flash controller clock source select
  00b = ACLK
  01b = MCLK
  10b = SMCLK
  11b = SMCLK */
#define FLASH_CTL2_FSSEL(x)    (((uint16_t)(((uint16_t)(x)) << FLASH_CTL2_FSSEL_SHIFT)) & FLASH_CTL2_FSSEL_MASK)

/* FLASH_CTL2_FN */
#define FLASH_CTL2_FN_MASK  (0x3fU)
#define FLASH_CTL2_FN_SHIFT (0x0U)
/* Flash controller clock divider. These six bits select the divider for the
  flash controller clock. The divisor value is FNx + 1. For example,
  when FNx = 00h, the divisor is 1. When FNx = 03Fh, the divisor is 64. */
#define FLASH_CTL2_FN(x)    (((uint16_t)(((uint16_t)(x)) << FLASH_CTL2_FN_SHIFT)) & FLASH_CTL2_FN_MASK)

/* FLASH_CTL2_FSSEL */
#define FLASH_CTL2_FSSEL_ACLK   (0U) /* Flash controller clock source select: ACLK */
#define FLASH_CTL2_FSSEL_MCLK   (1U) /* Flash controller clock source select: MCLK */
#define FLASH_CTL2_FSSEL_SMCLK  (2U) /* Flash controller clock source select: SMCLK */
#define FLASH_CTL2_FSSEL_SMCLK2 (3U) /* Flash controller clock source select: SMCLK */

/*****************************************************************************
* @brief FLASH_CTL3
*****************************************************************************/

/* FLASH_CTL3_FWKEY */
#define FLASH_CTL3_FWKEY_MASK  (0xff00U)
#define FLASH_CTL3_FWKEY_SHIFT (0x8U)
/* FLASH_CTLx password. Always reads as 096h. Must be written as 0A5h.
  Writing any other value generates a PUC. */
#define FLASH_CTL3_FWKEY(x)    (((uint16_t)(((uint16_t)(x)) << FLASH_CTL3_FWKEY_SHIFT)) & FLASH_CTL3_FWKEY_MASK)

/* FLASH_CTL3_FAIL */
#define FLASH_CTL3_FAIL_MASK  (0x80U)
#define FLASH_CTL3_FAIL_SHIFT (0x7U)
/* Operation failure. This bit is set if the fFTG clock source fails, or a
  flash operation is aborted from an interrupt when EEIEX = 1. FAIL
  must be reset with software.
  0b = No failure
  1b = Failure */
#define FLASH_CTL3_FAIL(x)    (((uint16_t)(((uint16_t)(x)) << FLASH_CTL3_FAIL_SHIFT)) & FLASH_CTL3_FAIL_MASK)

/* FLASH_CTL3_LOCKA */
#define FLASH_CTL3_LOCKA_MASK  (0x40U)
#define FLASH_CTL3_LOCKA_SHIFT (0x6U)
/* Segment A and Info lock. Write a 1 to this bit to change its state.
  Writing 0 has no effect.
  0b = Segment A unlocked and all information memory is erased
  during a mass erase.
  1b = Segment A locked and all information memory is protected from
  erasure during a mass erase. */
#define FLASH_CTL3_LOCKA(x)    (((uint16_t)(((uint16_t)(x)) << FLASH_CTL3_LOCKA_SHIFT)) & FLASH_CTL3_LOCKA_MASK)

/* FLASH_CTL3_EMEX */
#define FLASH_CTL3_EMEX_MASK  (0x20U)
#define FLASH_CTL3_EMEX_SHIFT (0x5U)
/* Emergency exit
  0b = No emergency exit
  1b = Emergency exit */
#define FLASH_CTL3_EMEX(x)    (((uint16_t)(((uint16_t)(x)) << FLASH_CTL3_EMEX_SHIFT)) & FLASH_CTL3_EMEX_MASK)

/* FLASH_CTL3_LOCK */
#define FLASH_CTL3_LOCK_MASK  (0x10U)
#define FLASH_CTL3_LOCK_SHIFT (0x4U)
/* Lock. This bit unlocks the flash memory for writing or erasing. The
  LOCK bit can be set any time during a byte or word write or erase
  operation, and the operation completes normally. In the block write
  mode if the LOCK bit is set while BLKWRT = WAIT = 1, then
  BLKWRT and WAIT are reset and the mode ends normally.
  0b = Unlocked
  1b = Locked */
#define FLASH_CTL3_LOCK(x)    (((uint16_t)(((uint16_t)(x)) << FLASH_CTL3_LOCK_SHIFT)) & FLASH_CTL3_LOCK_MASK)

/* FLASH_CTL3_WAIT */
#define FLASH_CTL3_WAIT_MASK  (0x8U)
#define FLASH_CTL3_WAIT_SHIFT (0x3U)
/* Wait. Indicates the flash memory is being written to.
  0b = The flash memory is not ready for the next byte or word write
  1b = The flash memory is ready for the next byte or word write */
#define FLASH_CTL3_WAIT(x)    (((uint16_t)(((uint16_t)(x)) << FLASH_CTL3_WAIT_SHIFT)) & FLASH_CTL3_WAIT_MASK)

/* FLASH_CTL3_ACCVIFG */
#define FLASH_CTL3_ACCVIFG_MASK  (0x4U)
#define FLASH_CTL3_ACCVIFG_SHIFT (0x2U)
/* Access violation interrupt flag
  0b = No interrupt pending
  1b = Interrupt pending */
#define FLASH_CTL3_ACCVIFG(x)    (((uint16_t)(((uint16_t)(x)) << FLASH_CTL3_ACCVIFG_SHIFT)) & FLASH_CTL3_ACCVIFG_MASK)

/* FLASH_CTL3_KEYV */
#define FLASH_CTL3_KEYV_MASK  (0x2U)
#define FLASH_CTL3_KEYV_SHIFT (0x1U)
/* Flash security key violation. This bit indicates an incorrect FLASH_CTLx
  password was written to any flash control register and generates a
  PUC when set. KEYV must be reset with software. KEYV is reset
  with POR.
  0b = FLASH_CTLx password was written correctly
  1b = FLASH_CTLx password was written incorrectly */
#define FLASH_CTL3_KEYV(x)    (((uint16_t)(((uint16_t)(x)) << FLASH_CTL3_KEYV_SHIFT)) & FLASH_CTL3_KEYV_MASK)

/* FLASH_CTL3_BUSY */
#define FLASH_CTL3_BUSY_MASK  (0x1U)
#define FLASH_CTL3_BUSY_SHIFT (0x0U)
/* Busy. This bit indicates the status of the flash timing generator.
  0b = Not busy
  1b = Busy */
#define FLASH_CTL3_BUSY(x)    (((uint16_t)(((uint16_t)(x)) << FLASH_CTL3_BUSY_SHIFT)) & FLASH_CTL3_BUSY_MASK)

/*****************************************************************************
* @brief TA_CTL
*****************************************************************************/

/* TA_CTL_TASSEL */
#define TA_CTL_TASSEL_MASK  (0x300U)
#define TA_CTL_TASSEL_SHIFT (0x8U)
/* Timer_A clock source select
  00b = TACLK
  01b = ACLK
  10b = SMCLK
  11b = INCLK (INCLK is device-specific and is often assigned to the
  inverted TBCLK) (see the device-specific data sheet) */
#define TA_CTL_TASSEL(x)    (((uint16_t)(((uint16_t)(x)) << TA_CTL_TASSEL_SHIFT)) & TA_CTL_TASSEL_MASK)

/* TA_CTL_ID */
#define TA_CTL_ID_MASK  (0x30U)
#define TA_CTL_ID_SHIFT (0x6U)
/* Input divider. These bits select the divider for the input clock.
  00b = /1
  01b = /2
  10b = /4
  11b = /8 */
#define TA_CTL_ID(x)    (((uint16_t)(((uint16_t)(x)) << TA_CTL_ID_SHIFT)) & TA_CTL_ID_MASK)

/* TA_CTL_MC */
#define TA_CTL_MC_MASK  (0x30U)
#define TA_CTL_MC_SHIFT (0x4U)
/* Mode control. Set MCx = 00b when Timer_A is not in use to conserve power.
  00b = Stop mode: the timer is halted.
  01b = Up mode: the timer counts up to TACCR0.
  10b = Continuous mode: the timer counts up to 0FFFFh.
  11b = Up/down mode: the timer counts up to TACCR0 then down to 0000h. */
#define TA_CTL_MC(x)    (((uint16_t)(((uint16_t)(x)) << TA_CTL_MC_SHIFT)) & TA_CTL_MC_MASK)

/* TA_CTL_TACLR */
#define TA_CTL_TACLR_MASK  (0x4U)
#define TA_CTL_TACLR_SHIFT (0x2U)
/* Timer_A clear. Setting this bit resets TAR, the clock divider, and the
  count direction. The TACLR bit is automatically reset and always
  reads as zero. */
#define TA_CTL_TACLR(x)    (((uint16_t)(((uint16_t)(x)) << TA_CTL_TACLR_SHIFT)) & TA_CTL_TACLR_MASK)

/* TA_CTL_TAIE */
#define TA_CTL_TAIE_MASK  (0x2U)
#define TA_CTL_TAIE_SHIFT (0x1U)
/* Timer_A interrupt enable. This bit enables the TAIFG interrupt request.
  0b = Interrupt disabled
  1b = Interrupt enabled */
#define TA_CTL_TAIE(x)    (((uint16_t)(((uint16_t)(x)) << TA_CTL_TAIE_SHIFT)) & TA_CTL_TAIE_MASK)

/* TA_CTL_TAIFG */
#define TA_CTL_TAIFG_MASK  (0x1U)
#define TA_CTL_TAIFG_SHIFT (0x0U)
/* Timer_A interrupt flag
  0b = No interrupt pending
  1b = Interrupt pending */
#define TA_CTL_TAIFG(x)    (((uint16_t)(((uint16_t)(x)) << TA_CTL_TAIFG_SHIFT)) & TA_CTL_TAIFG_MASK)

#define TA_CTL_MC_STOP     (0U) /* Timer A mode control: Stop */
#define TA_CTL_MC_UPTOCCR0 (1U) /* Timer A mode control: Up to CCR0 */
#define TA_CTL_MC_CONT     (2U) /* Timer A mode control: Continous up */
#define TA_CTL_MC_UPDOWN   (3U) /* Timer A mode control: Up/Down */

#define TA_CTL_ID_1 (0U) /* Timer A input divider: 1 */
#define TA_CTL_ID_2 (1U) /* Timer A input divider: 2 */
#define TA_CTL_ID_4 (2U) /* Timer A input divider: 4 */
#define TA_CTL_ID_8 (3U) /* Timer A input divider: 8 */

#define TA_CTL_TASSEL_TACLK (0U) /* Timer A clock source select: TACLK */
#define TA_CTL_TASSEL_ACLK  (1U) /* Timer A clock source select: ACLK  */
#define TA_CTL_TASSEL_SMCLK (2U) /* Timer A clock source select: SMCLK */
#define TA_CTL_TASSEL_INCLK (3U) /* Timer A clock source select: INCLK */

/*****************************************************************************
* @brief TA_CCTL
*****************************************************************************/

/* TA_CCTL_CM */
#define TA_CCTL_CM_MASK  (0xc000U)
#define TA_CCTL_CM_SHIFT (0xeU)
/* Capture mode
  00b = No capture
  01b = Capture on rising edge
  10b = Capture on falling edge
  11b = Capture on both rising and falling edges */
#define TA_CCTL_CM(x)    (((uint16_t)(((uint16_t)(x)) << TA_CCTL_CM_SHIFT)) & TA_CCTL_CM_MASK)

/* TA_CCTL_CCIS */
#define TA_CCTL_CCIS_MASK  (0x3000U)
#define TA_CCTL_CCIS_SHIFT (0xcU)
/* Capture/compare input select. These bits select the TACCRx
  input signal. See the device-specific data sheet for specific signal connections.
  00b = CCIxA
  01b = CCIxB
  10b = GND
  11b = Vcc */
#define TA_CCTL_CCIS(x)    (((uint16_t)(((uint16_t)(x)) << TA_CCTL_CCIS_SHIFT)) & TA_CCTL_CCIS_MASK)

/* TA_CCTL_SCS */
#define TA_CCTL_SCS_MASK  (0x800U)
#define TA_CCTL_SCS_SHIFT (0xbU)
/* Synchronize capture source. This bit is used to synchronize the
  capture input signal with the timer clock.
  0b = Asynchronous capture
  1b = Synchronous capture */
#define TA_CCTL_SCS(x)    (((uint16_t)(((uint16_t)(x)) << TA_CCTL_SCS_SHIFT)) & TA_CCTL_SCS_MASK)

/* TA_CCTL_SCCI */
#define TA_CCTL_SCCI_MASK  (0x400U)
#define TA_CCTL_SCCI_SHIFT (0xaU)
/* Synchronized capture/compare input. The selected CCI input signal
is latched with the EQUx signal and can be read via this bit */
#define TA_CCTL_SCCI(x)    (((uint16_t)(((uint16_t)(x)) << TA_CCTL_SCCI_SHIFT)) & TA_CCTL_SCCI_MASK)

/* TA_CCTL_CAP */
#define TA_CCTL_CAP_MASK  (0x100U)
#define TA_CCTL_CAP_SHIFT (0x8U)
/* Capture mode
  0b = Compare mode
  1b = Capture mode */
#define TA_CCTL_CAP(x)    (((uint16_t)(((uint16_t)(x)) << TA_CCTL_CAP_SHIFT)) & TA_CCTL_CAP_MASK)

/* TA_CCTL_OUTMOD */
#define TA_CCTL_OUTMOD_MASK  (0xe0U)
#define TA_CCTL_OUTMOD_SHIFT (0x5U)
/* Output mode. Modes 2, 3, 6, and 7 are not useful for TACCR0, because EQUx = EQU0.
  000b = OUT bit value
  001b = Set
  010b = Toggle/reset
  011b = Set/reset
  100b = Toggle
  101b = Reset
  110b = Toggle/set
  111b = Reset/set */
#define TA_CCTL_OUTMOD(x)    (((uint16_t)(((uint16_t)(x)) << TA_CCTL_OUTMOD_SHIFT)) & TA_CCTL_OUTMOD_MASK)

/* TA_CCTL_CCIE */
#define TA_CCTL_CCIE_MASK  (0x10U)
#define TA_CCTL_CCIE_SHIFT (0x4U)
/* Capture/compare interrupt enable. This bit enables the interrupt
  request of the corresponding CCIFG flag.
  0b = Interrupt disabled
  1b = Interrupt enabled */
#define TA_CCTL_CCIE(x)    (((uint16_t)(((uint16_t)(x)) << TA_CCTL_CCIE_SHIFT)) & TA_CCTL_CCIE_MASK)

/* TA_CCTL_CCI */
#define TA_CCTL_CCI_MASK  (0x8U)
#define TA_CCTL_CCI_SHIFT (0x3U)
/* Capture/compare input. The selected input signal can be read by this bit. */
#define TA_CCTL_CCI(x)    (((uint16_t)(((uint16_t)(x)) << TA_CCTL_CCI_SHIFT)) & TA_CCTL_CCI_MASK)

/* TA_CCTL_OUT */
#define TA_CCTL_OUT_MASK  (0x4U)
#define TA_CCTL_OUT_SHIFT (0x2U)
/* Output. For output mode 0, this bit directly controls the state of the output.
  0b = Output low
  1b = Output high */
#define TA_CCTL_OUT(x)    (((uint16_t)(((uint16_t)(x)) << TA_CCTL_OUT_SHIFT)) & TA_CCTL_OUT_MASK)

/* TA_CCTL_COV */
#define TA_CCTL_COV_MASK  (0x2U)
#define TA_CCTL_COV_SHIFT (0x1U)
/* Capture overflow. This bit indicates a capture overflow occurred.
  COV must be reset with software.
  0b = No capture overflow occurred
  1b = Capture overflow occurred */
#define TA_CCTL_COV(x)    (((uint16_t)(((uint16_t)(x)) << TA_CCTL_COV_SHIFT)) & TA_CCTL_COV_MASK)

/* TA_CCTL_CCIFG */
#define TA_CCTL_CCIFG_MASK  (0x1U)
#define TA_CCTL_CCIFG_SHIFT (0x0U)
/* Capture/compare interrupt flag
  0b = No interrupt pending
  1b = Interrupt pending */
#define TA_CCTL_CCIFG(x)    (((uint16_t)(((uint16_t)(x)) << TA_CCTL_CCIFG_SHIFT)) & TA_CCTL_CCIFG_MASK)

#define TA_CCTL_OUTMOD_OUT              (0U) /* PWM output mode: 0 - output only */
#define TA_CCTL_OUTMOD_SET              (1U) /* PWM output mode: 1 - set */
#define TA_CCTL_OUTMOD_PWM_TOGGLE_RESET (2U) /* PWM output mode: 2 - PWM toggle/reset */
#define TA_CCTL_OUTMOD_PWM_SET_RESET    (3U) /* PWM output mode: 3 - PWM set/reset */
#define TA_CCTL_OUTMOD_TOGGLE           (4U) /* PWM output mode: 4 - toggle */
#define TA_CCTL_OUTMOD_RESET            (5U) /* PWM output mode: 5 - Reset */
#define TA_CCTL_OUTMOD_PWM_TOGGLE_SET   (6U) /* PWM output mode: 6 - PWM toggle/set */
#define TA_CCTL_OUTMOD_PWM_RESET_SET    (7U) /* PWM output mode: 7 - PWM reset/set */

#define TA_CCTL_CCIS_CCIXA (0U) /* Capture input select: 0 - CCIxA */
#define TA_CCTL_CCIS_CCIXB (1U) /* Capture input select: 1 - CCIxB */
#define TA_CCTL_CCIS_GND   (2U) /* Capture input select: 2 - GND */
#define TA_CCTL_CCIS_VCC   (3U) /* Capture input select: 3 - Vcc */

#define TA_CCTL_CM_DISABLED (0U) /* Capture mode: 0 - disabled */
#define TA_CCTL_CM_RISING   (1U) /* Capture mode: 1 - pos. edge */
#define TA_CCTL_CM_FALLING  (2U) /* Capture mode: 1 - neg. edge */
#define TA_CCTL_CM_BOTH     (3U) /* Capture mode: 1 - both edges */

#define TAIV_NONE   (00U) /* No Interrupt pending */
#define TAIV_TACCR1 (02U) /* TA0CCR1_CCIFG */
#define TAIV_TACCR2 (04U) /* TA0CCR2_CCIFG */
#define TAIV_6      (06U) /* Reserved */
#define TAIV_8      (08U) /* Reserved */
#define TAIV_TAIFG  (10U) /* TA0IFG */

/*****************************************************************************
* @brief USCI_UART_CTL0
*****************************************************************************/

/* USCI_UART_CTL0_UCPEN */
#define USCI_UART_CTL0_UCPEN_MASK  (0x80U)
#define USCI_UART_CTL0_UCPEN_SHIFT (0x7U)
/* Parity enable
  0b = Parity disabled
  1b = Parity enabled. Parity bit is generated (UCAxTXD) and
  expected (UCAxRXD). In address-bit multiprocessor mode, the
  address bit is included in the parity calculation. */
#define USCI_UART_CTL0_UCPEN(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_CTL0_UCPEN_SHIFT)) & USCI_UART_CTL0_UCPEN_MASK)

/* USCI_UART_CTL0_UCPAR */
#define USCI_UART_CTL0_UCPAR_MASK  (0x40U)
#define USCI_UART_CTL0_UCPAR_SHIFT (0x6U)
/* Parity select. UCPAR is not used when parity is disabled.
  0b = Odd parity
  1b = Even parity */
#define USCI_UART_CTL0_UCPAR(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_CTL0_UCPAR_SHIFT)) & USCI_UART_CTL0_UCPAR_MASK)

/* USCI_UART_CTL0_UCMSB */
#define USCI_UART_CTL0_UCMSB_MASK  (0x20U)
#define USCI_UART_CTL0_UCMSB_SHIFT (0x5U)
/* MSB first select. Controls the direction of the receive and transmit shift register.
  0b = LSB first
  1b = MSB first */
#define USCI_UART_CTL0_UCMSB(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_CTL0_UCMSB_SHIFT)) & USCI_UART_CTL0_UCMSB_MASK)

/* USCI_UART_CTL0_UC7BIT */
#define USCI_UART_CTL0_UC7BIT_MASK  (0x10U)
#define USCI_UART_CTL0_UC7BIT_SHIFT (0x4U)
/* Character length. Selects 7-bit or 8-bit character length.
  0b = 8-bit data
  1b = 7-bit data */
#define USCI_UART_CTL0_UC7BIT(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_CTL0_UC7BIT_SHIFT)) & USCI_UART_CTL0_UC7BIT_MASK)

/* USCI_UART_CTL0_UCSPB */
#define USCI_UART_CTL0_UCSPB_MASK  (0x8U)
#define USCI_UART_CTL0_UCSPB_SHIFT (0x3U)
/* Stop bit select. Number of stop bits.
  0b = One stop bit
  1b = Two stop bits */
#define USCI_UART_CTL0_UCSPB(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_CTL0_UCSPB_SHIFT)) & USCI_UART_CTL0_UCSPB_MASK)

/* USCI_UART_CTL0_UCMODE */
#define USCI_UART_CTL0_UCMODE_MASK  (0x6U)
#define USCI_UART_CTL0_UCMODE_SHIFT (0x1U)
/* USCI mode. The UCMODEx bits select the asynchronous mode when UCSYNC = 0.
  00b = UART mode
  01b = Idle-line multiprocessor mode
  10b = Address-bit multiprocessor mode
  11b = UART mode with automatic baud rate detection */
#define USCI_UART_CTL0_UCMODE(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_CTL0_UCMODE_SHIFT)) & USCI_UART_CTL0_UCMODE_MASK)

/* USCI_UART_CTL0_UCSYNC */
#define USCI_UART_CTL0_UCSYNC_MASK  (0x1U)
#define USCI_UART_CTL0_UCSYNC_SHIFT (0x0U)
/* Synchronous mode enable
  0b = Asynchronous mode
  1b = Synchronous mode */
#define USCI_UART_CTL0_UCSYNC(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_CTL0_UCSYNC_SHIFT)) & USCI_UART_CTL0_UCSYNC_MASK)

#define USCI_UART_CTL0_UCMODE_UART        (0U) /* USCI mode: UART mode */
#define USCI_UART_CTL0_UCMODE_IDLE_LINE   (1U) /* USCI mode: Idle-line multiprocessor mode */
#define USCI_UART_CTL0_UCMODE_ADDRESS_BIT (2U) /* USCI mode: Address-bit multiprocessor mode */
#define USCI_UART_CTL0_UCMODE_UART_AUTO   (3U) /* USCI mode: UART mode with automatic baud rate detection */

/*****************************************************************************
* @brief USCI_UART_CTL1
*****************************************************************************/

/* USCI_UART_CTL1_UCSSEL */
#define USCI_UART_CTL1_UCSSEL_MASK  (0xc0U)
#define USCI_UART_CTL1_UCSSEL_SHIFT (0x6U)
/* USCI clock source select. These bits select the BRCLK source clock.
  00b = UCLK
  01b = ACLK
  10b = SMCLK
  11b = SMCLK */
#define USCI_UART_CTL1_UCSSEL(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_CTL1_UCSSEL_SHIFT)) & USCI_UART_CTL1_UCSSEL_MASK)

/* USCI_UART_CTL1_UCRXEIE */
#define USCI_UART_CTL1_UCRXEIE_MASK  (0x20U)
#define USCI_UART_CTL1_UCRXEIE_SHIFT (0x5U)
/* Receive erroneous-character interrupt-enable
  0b = Erroneous characters rejected and UCAxRXIFG is not set
  1b = Erroneous characters received will set UCAxRXIFG */
#define USCI_UART_CTL1_UCRXEIE(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_CTL1_UCRXEIE_SHIFT)) & USCI_UART_CTL1_UCRXEIE_MASK)

/* USCI_UART_CTL1_UCBRKIE */
#define USCI_UART_CTL1_UCBRKIE_MASK  (0x10U)
#define USCI_UART_CTL1_UCBRKIE_SHIFT (0x4U)
/* Receive break character interrupt-enable
  0b = Received break characters do not set UCAxRXIFG.
  1b = Received break characters set UCAxRXIFG. */
#define USCI_UART_CTL1_UCBRKIE(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_CTL1_UCBRKIE_SHIFT)) & USCI_UART_CTL1_UCBRKIE_MASK)

/* USCI_UART_CTL1_UCDORM */
#define USCI_UART_CTL1_UCDORM_MASK  (0x8U)
#define USCI_UART_CTL1_UCDORM_SHIFT (0x3U)
/* Dormant. Puts USCI into sleep mode.
  0b = Not dormant. All received characters will set UCAxRXIFG.
  1b = Dormant. Only characters that are preceded by an idle-line
  or with address bit set will set UCAxRXIFG. In UART mode with
  automatic baud rate detection only the combination of a break and
  synch field will set UCAxRXIFG. */
#define USCI_UART_CTL1_UCDORM(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_CTL1_UCDORM_SHIFT)) & USCI_UART_CTL1_UCDORM_MASK)

/* USCI_UART_CTL1_UCTXADDR */
#define USCI_UART_CTL1_UCTXADDR_MASK  (0x4U)
#define USCI_UART_CTL1_UCTXADDR_SHIFT (0x2U)
/* Transmit address. Next frame to be transmitted will be marked as
  address depending on the selected multiprocessor mode.
  0b = Next frame transmitted is data
  1b = Next frame transmitted is an address */
#define USCI_UART_CTL1_UCTXADDR(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_CTL1_UCTXADDR_SHIFT)) & USCI_UART_CTL1_UCTXADDR_MASK)

/* USCI_UART_CTL1_UCTXBRK */
#define USCI_UART_CTL1_UCTXBRK_MASK  (0x2U)
#define USCI_UART_CTL1_UCTXBRK_SHIFT (0x1U)
/* Transmit break. Transmits a break with the next write to the transmit
  buffer. In UART mode with automatic baud rate detection 055h must
  be written into UCAxTXBUF to generate the required break/synch
  fields. Otherwise 0h must be written into the transmit buffer.
  0b = Next frame transmitted is not a break
  1b = Next frame transmitted is a break or a break/synch */
#define USCI_UART_CTL1_UCTXBRK(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_CTL1_UCTXBRK_SHIFT)) & USCI_UART_CTL1_UCTXBRK_MASK)

/* USCI_UART_CTL1_UCSWRST */
#define USCI_UART_CTL1_UCSWRST_MASK  (0x1U)
#define USCI_UART_CTL1_UCSWRST_SHIFT (0x0U)
/* Software reset enable
  0b = Disabled. USCI reset released for operation.
  1b = Enabled. USCI logic held in reset state. */
#define USCI_UART_CTL1_UCSWRST(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_CTL1_UCSWRST_SHIFT)) & USCI_UART_CTL1_UCSWRST_MASK)

#define USCI_UART_CTL1_UCSSEL_UCLK   (0U) /* USCI clock source select: UCLK */
#define USCI_UART_CTL1_UCSSEL_ACLK   (1U) /* USCI clock source select: ACLK */
#define USCI_UART_CTL1_UCSSEL_SMCLK  (2U) /* USCI clock source select: SMCLK */
#define USCI_UART_CTL1_UCSSEL_SMCLK2 (3U) /* USCI clock source select: SMCLK */

/*****************************************************************************
* @brief USCI_UART_MCTL
*****************************************************************************/

/* USCI_UART_MCTL_UCBRF0 */
#define USCI_UART_MCTL_UCBRF0_MASK  (0xf0U)
#define USCI_UART_MCTL_UCBRF0_SHIFT (0x4U)
/* First modulation stage select. These bits determine the modulation
  pattern for BITCLK16 when UCOS16 = 1. Ignored with UCOS16 = 0.
  Table 15-3 shows the modulation pattern. */
#define USCI_UART_MCTL_UCBRF0(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_MCTL_UCBRF0_SHIFT)) & USCI_UART_MCTL_UCBRF0_MASK)

/* USCI_UART_MCTL_UCBRS0 */
#define USCI_UART_MCTL_UCBRS0_MASK  (0xeU)
#define USCI_UART_MCTL_UCBRS0_SHIFT (0x1U)
/* Second modulation stage select. These bits determine the
  modulation pattern for BITCLK. Table 15-2 shows the modulation
  pattern. */
#define USCI_UART_MCTL_UCBRS0(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_MCTL_UCBRS0_SHIFT)) & USCI_UART_MCTL_UCBRS0_MASK)

/* USCI_UART_MCTL_UCOS16 */
#define USCI_UART_MCTL_UCOS16_MASK  (0x1U)
#define USCI_UART_MCTL_UCOS16_SHIFT (0x0U)
/* Oversampling mode enabled
  0b = Disabled
  1b = Enabled */
#define USCI_UART_MCTL_UCOS16(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_MCTL_UCOS16_SHIFT)) & USCI_UART_MCTL_UCOS16_MASK)

/*****************************************************************************
* @brief USCI_UART_STAT
*****************************************************************************/

/* USCI_UART_STAT_UCLISTEN */
#define USCI_UART_STAT_UCLISTEN_MASK  (0x80U)
#define USCI_UART_STAT_UCLISTEN_SHIFT (0x7U)
/* Listen enable. The UCLISTEN bit selects loopback mode.
  0b = Disabled
  1b = Enabled. UCAxTXD is internally fed back to the receiver. */
#define USCI_UART_STAT_UCLISTEN(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_STAT_UCLISTEN_SHIFT)) & USCI_UART_STAT_UCLISTEN_MASK)

/* USCI_UART_STAT_UCFE */
#define USCI_UART_STAT_UCFE_MASK  (0x40U)
#define USCI_UART_STAT_UCFE_SHIFT (0x6U)
/* Framing error flag
  0b = No error
  1b = Character received with low stop bit */
#define USCI_UART_STAT_UCFE(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_STAT_UCFE_SHIFT)) & USCI_UART_STAT_UCFE_MASK)

/* USCI_UART_STAT_UCOE */
#define USCI_UART_STAT_UCOE_MASK  (0x20U)
#define USCI_UART_STAT_UCOE_SHIFT (0x5U)
/* Overrun error flag. This bit is set when a character is transferred
  into UCAxRXBUF before the previous character was read. UCOE
  is cleared automatically when UCxRXBUF is read, and must not be
  cleared by software. Otherwise, it will not function correctly.
  0b = No error
  1b = Overrun error occurred */
#define USCI_UART_STAT_UCOE(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_STAT_UCOE_SHIFT)) & USCI_UART_STAT_UCOE_MASK)

/* USCI_UART_STAT_UCPE */
#define USCI_UART_STAT_UCPE_MASK  (0x10U)
#define USCI_UART_STAT_UCPE_SHIFT (0x4U)
/* Parity error flag. When UCPEN = 0, UCPE is read as 0.
  0b = No error
  1b = Character received with parity error */
#define USCI_UART_STAT_UCPE(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_STAT_UCPE_SHIFT)) & USCI_UART_STAT_UCPE_MASK)

/* USCI_UART_STAT_UCBRK */
#define USCI_UART_STAT_UCBRK_MASK  (0x8U)
#define USCI_UART_STAT_UCBRK_SHIFT (0x3U)
/* Break detect flag
  0b = No break condition
  1b = Break condition occurred */
#define USCI_UART_STAT_UCBRK(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_STAT_UCBRK_SHIFT)) & USCI_UART_STAT_UCBRK_MASK)

/* USCI_UART_STAT_UCRXERR */
#define USCI_UART_STAT_UCRXERR_MASK  (0x4U)
#define USCI_UART_STAT_UCRXERR_SHIFT (0x2U)
/* Receive error flag. This bit indicates a character was received with
  errors. When UCRXERR = 1, one or more error flags (UCFE, UCPE,
  UCOE) is also set. UCRXERR is cleared when UCAxRXBUF is read.
  0b = No receive errors detected
  1b = Receive error detected */
#define USCI_UART_STAT_UCRXERR(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_STAT_UCRXERR_SHIFT)) & USCI_UART_STAT_UCRXERR_MASK)

/* USCI_UART_STAT_UCADDR */
#define USCI_UART_STAT_UCADDR_MASK  (0x2U)
#define USCI_UART_STAT_UCADDR_SHIFT (0x1U)
/*
  UCADDR: Address received in address-bit multiprocessor mode.
  0b = Received character is data
  1b = Received character is an address

  UCIDLE: Idle line detected in idle-line multiprocessor mode.
  0b = No idle line detected
  1b = Idle line detected */
#define USCI_UART_STAT_UCADDR(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_STAT_UCADDR_SHIFT)) & USCI_UART_STAT_UCADDR_MASK)

/* USCI_UART_STAT_UCBUSY */
#define USCI_UART_STAT_UCBUSY_MASK  (0x1U)
#define USCI_UART_STAT_UCBUSY_SHIFT (0x0U)
/* USCI busy. This bit indicates if a transmit or receive operation is in progress.
  0b = USCI inactive
  1b = USCI transmitting or receiving */
#define USCI_UART_STAT_UCBUSY(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_STAT_UCBUSY_SHIFT)) & USCI_UART_STAT_UCBUSY_MASK)

/*****************************************************************************
* @brief USCI_UART_IRTCTL
*****************************************************************************/

/* USCI_UART_IRTCTL_UCIRTXPL */
#define USCI_UART_IRTCTL_UCIRTXPL_MASK  (0xfcU)
#define USCI_UART_IRTCTL_UCIRTXPL_SHIFT (0x2U)
/* Transmit pulse length. Pulse length tPULSE = (UCIRTXPLx + 1) / (2 ? fIRTXCLK) */
#define USCI_UART_IRTCTL_UCIRTXPL(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_IRTCTL_UCIRTXPL_SHIFT)) & USCI_UART_IRTCTL_UCIRTXPL_MASK)

/* USCI_UART_IRTCTL_UCIRTXCLK */
#define USCI_UART_IRTCTL_UCIRTXCLK_MASK  (0x2U)
#define USCI_UART_IRTCTL_UCIRTXCLK_SHIFT (0x1U)
/* IrDA transmit pulse clock select
  0b = BRCLK
  1b = BITCLK16 when UCOS16 = 1. Otherwise, BRCLK. */
#define USCI_UART_IRTCTL_UCIRTXCLK(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_IRTCTL_UCIRTXCLK_SHIFT)) & USCI_UART_IRTCTL_UCIRTXCLK_MASK)

/* USCI_UART_IRTCTL_UCIREN */
#define USCI_UART_IRTCTL_UCIREN_MASK  (0x1U)
#define USCI_UART_IRTCTL_UCIREN_SHIFT (0x0U)
/* IrDA encoder/decoder enable
  0b = IrDA encoder/decoder disabled
  1b = IrDA encoder/decoder enabled */
#define USCI_UART_IRTCTL_UCIREN(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_IRTCTL_UCIREN_SHIFT)) & USCI_UART_IRTCTL_UCIREN_MASK)

/*****************************************************************************
* @brief USCI_UART_IRRCTL
*****************************************************************************/

/* USCI_UART_IRRCTL_UCIRRXFL */
#define USCI_UART_IRRCTL_UCIRRXFL_MASK  (0x4U)
#define USCI_UART_IRRCTL_UCIRRXFL_SHIFT (0x2U)
/* Receive filter length. The minimum pulse length for receive is given
by: tMIN = (UCIRRXFLx + 4) / (2 ? fBRCLK) */
#define USCI_UART_IRRCTL_UCIRRXFL(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_IRRCTL_UCIRRXFL_SHIFT)) & USCI_UART_IRRCTL_UCIRRXFL_MASK)

/* USCI_UART_IRRCTL_UCIRRXPL */
#define USCI_UART_IRRCTL_UCIRRXPL_MASK  (0x2U)
#define USCI_UART_IRRCTL_UCIRRXPL_SHIFT (0x1U)
/* IrDA receive input UCAxRXD polarity
  0b = IrDA transceiver delivers a high pulse when a light pulse is seen
  1b = IrDA transceiver delivers a low pulse when a light pulse is seen */
#define USCI_UART_IRRCTL_UCIRRXPL(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_IRRCTL_UCIRRXPL_SHIFT)) & USCI_UART_IRRCTL_UCIRRXPL_MASK)

/* USCI_UART_IRRCTL_UCIRRXFE */
#define USCI_UART_IRRCTL_UCIRRXFE_MASK  (0x1U)
#define USCI_UART_IRRCTL_UCIRRXFE_SHIFT (0x0U)
/* IrDA receive filter enabled
  0b = Receive filter disabled
  1b = Receive filter enabled */
#define USCI_UART_IRRCTL_UCIRRXFE(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_IRRCTL_UCIRRXFE_SHIFT)) & USCI_UART_IRRCTL_UCIRRXFE_MASK)

/*****************************************************************************
* @brief USCI_UART_ABCTL
*****************************************************************************/

/* USCI_UART_ABCTL_UCDELIM */
#define USCI_UART_ABCTL_UCDELIM_MASK  (0x30U)
#define USCI_UART_ABCTL_UCDELIM_SHIFT (0x4U)
/* Break and synch delimiter length
  00b = 1 bit time
  01b = 2 bit times
  10b = 3 bit times
  11b = 4 bit times */
#define USCI_UART_ABCTL_UCDELIM(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_ABCTL_UCDELIM_SHIFT)) & USCI_UART_ABCTL_UCDELIM_MASK)

/* USCI_UART_ABCTL_UCSTOE */
#define USCI_UART_ABCTL_UCSTOE_MASK  (0x8U)
#define USCI_UART_ABCTL_UCSTOE_SHIFT (0x3U)
/* Synch field time-out error
  0b = No error
  1b = Length of synch field exceeded measurable time. */
#define USCI_UART_ABCTL_UCSTOE(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_ABCTL_UCSTOE_SHIFT)) & USCI_UART_ABCTL_UCSTOE_MASK)

/* USCI_UART_ABCTL_UCBTOE */
#define USCI_UART_ABCTL_UCBTOE_MASK  (0x4U)
#define USCI_UART_ABCTL_UCBTOE_SHIFT (0x2U)
/* Break time-out error
  0b = No error
  1b = Length of break field exceeded 22 bit times. */
#define USCI_UART_ABCTL_UCBTOE(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_ABCTL_UCBTOE_SHIFT)) & USCI_UART_ABCTL_UCBTOE_MASK)

/* USCI_UART_ABCTL_UCABDEN */
#define USCI_UART_ABCTL_UCABDEN_MASK  (0x1U)
#define USCI_UART_ABCTL_UCABDEN_SHIFT (0x0U)
/* Automatic baud rate detect enable
  0b = Baud rate detection disabled. Length of break and synch field is not measured.
  1b = Baud rate detection enabled. Length of break and synch field is
  measured and baud rate settings are changed accordingly. */
#define USCI_UART_ABCTL_UCABDEN(x)    (((uint8_t)(((uint8_t)(x)) << USCI_UART_ABCTL_UCABDEN_SHIFT)) & USCI_UART_ABCTL_UCABDEN_MASK)

/*****************************************************************************
* @brief UCSI_SPI_CTL0
*****************************************************************************/

/* USCI_SPI_CTL0_UCCKPH */
#define USCI_SPI_CTL0_UCCKPH_MASK  (0x80U)
#define USCI_SPI_CTL0_UCCKPH_SHIFT (0x7U)
/* Clock phase select
  0b = Data is changed on the first UCLK edge and captured on the following edge.
  1b = Data is captured on the first UCLK edge and changed on the following edge. */
#define USCI_SPI_CTL0_UCCKPH(x)    (((uint8_t)(((uint8_t)(x)) << USCI_SPI_CTL0_UCCKPH_SHIFT)) & USCI_SPI_CTL0_UCCKPH_MASK)

/* USCI_SPI_CTL0_UCCKPL */
#define USCI_SPI_CTL0_UCCKPL_MASK  (0x40U)
#define USCI_SPI_CTL0_UCCKPL_SHIFT (0x6U)
/* Clock polarity select
  0b = The inactive state is low.
  1b = The inactive state is high. */
#define USCI_SPI_CTL0_UCCKPL(x)    (((uint8_t)(((uint8_t)(x)) << USCI_SPI_CTL0_UCCKPL_SHIFT)) & USCI_SPI_CTL0_UCCKPL_MASK)

/* USCI_SPI_CTL0_UCMSB */
#define USCI_SPI_CTL0_UCMSB_MASK  (0x20U)
#define USCI_SPI_CTL0_UCMSB_SHIFT (0x5U)
/* MSB first select. Controls the direction of the receive and transmit shift register.
  0b = LSB first
  1b = MSB first */
#define USCI_SPI_CTL0_UCMSB(x)    (((uint8_t)(((uint8_t)(x)) << USCI_SPI_CTL0_UCMSB_SHIFT)) & USCI_SPI_CTL0_UCMSB_MASK)

/* USCI_SPI_CTL0_UC7BIT */
#define USCI_SPI_CTL0_UC7BIT_MASK  (0x10U)
#define USCI_SPI_CTL0_UC7BIT_SHIFT (0x4U)
/* Character length. Selects 7-bit or 8-bit character length.
  0b = 8-bit data
  1b = 7-bit data */
#define USCI_SPI_CTL0_UC7BIT(x)    (((uint8_t)(((uint8_t)(x)) << USCI_SPI_CTL0_UC7BIT_SHIFT)) & USCI_SPI_CTL0_UC7BIT_MASK)

/* USCI_SPI_CTL0_UCMST */
#define USCI_SPI_CTL0_UCMST_MASK  (0x8U)
#define USCI_SPI_CTL0_UCMST_SHIFT (0x3U)
/* Master mode select
  0b = Slave mode
  1b = Master mode */
#define USCI_SPI_CTL0_UCMST(x)    (((uint8_t)(((uint8_t)(x)) << USCI_SPI_CTL0_UCMST_SHIFT)) & USCI_SPI_CTL0_UCMST_MASK)

/* USCI_SPI_CTL0_UCMODE */
#define USCI_SPI_CTL0_UCMODE_MASK  (0x6U)
#define USCI_SPI_CTL0_UCMODE_SHIFT (0x1U)
/* USCI mode. The UCMODEx bits select the synchronous mode when
  UCSYNC = 1.
  00b = 3-pin SPI
  01b = 4-pin SPI with UCxSTE active high: slave enabled when UCxSTE = 1
  10b = 4-pin SPI with UCxSTE active low: slave enabled when UCxSTE = 0
  11b = I2C mode */
#define USCI_SPI_CTL0_UCMODE(x)    (((uint8_t)(((uint8_t)(x)) << USCI_SPI_CTL0_UCMODE_SHIFT)) & USCI_SPI_CTL0_UCMODE_MASK)

/* USCI_SPI_CTL0_UCSYNC */
#define USCI_SPI_CTL0_UCSYNC_MASK  (0x1U)
#define USCI_SPI_CTL0_UCSYNC_SHIFT (0x0U)
/* Synchronous mode enable. Must be 1 for SPI mode.
  0b = Asynchronous mode
  1b = Synchronous mode */
#define USCI_SPI_CTL0_UCSYNC(x)    (((uint8_t)(((uint8_t)(x)) << USCI_SPI_CTL0_UCSYNC_SHIFT)) & USCI_SPI_CTL0_UCSYNC_MASK)

#define USCI_SPI_CTL0_UCMODE_3PIN_SPI    (0U) /* USCI mode: 3-pin SPI */
#define USCI_SPI_CTL0_UCMODE_4PIN_SPI_AH (1U) /* USCI mode: 4-pin SPI with UCxSTE active high: slave enabled when UCxSTE = 1 */
#define USCI_SPI_CTL0_UCMODE_4PIN_SPI_AL (2U) /* USCI mode: 4-pin SPI with UCxSTE active low: slave enabled when UCxSTE = 0 */
#define USCI_SPI_CTL0_UCMODE_I2C         (3U) /* USCI mode: I2C mode */

/*****************************************************************************
* @brief UCSI_SPI_CTL1
*****************************************************************************/

/* UCSI_SPI_CTL1_UCSSEL */
#define UCSI_SPI_CTL1_UCSSEL_MASK  (0xc0U)
#define UCSI_SPI_CTL1_UCSSEL_SHIFT (0x6U)
/* USCI clock source select. These bits select the BRCLK source clock
  in master mode. UCxCLK is always used in slave mode.
  00b = Reserved
  01b = ACLK
  10b = SMCLK
  11b = SMCLK */
#define UCSI_SPI_CTL1_UCSSEL(x)    (((uint8_t)(((uint8_t)(x)) << UCSI_SPI_CTL1_UCSSEL_SHIFT)) & UCSI_SPI_CTL1_UCSSEL_MASK)

/* UCSI_SPI_CTL1_UCSWRST */
#define UCSI_SPI_CTL1_UCSWRST_MASK  (0x1U)
#define UCSI_SPI_CTL1_UCSWRST_SHIFT (0x0U)
/* Software reset enable
  0b = Disabled. USCI reset released for operation.
  1b = Enabled. USCI logic held in reset state. */
#define UCSI_SPI_CTL1_UCSWRST(x)    (((uint8_t)(((uint8_t)(x)) << UCSI_SPI_CTL1_UCSWRST_SHIFT)) & UCSI_SPI_CTL1_UCSWRST_MASK)

#define USCI_SPI_CTL1_UCSSEL_RESERVED (0U) /* USCI clock source select: Reserved */
#define USCI_SPI_CTL1_UCSSEL_ACLK     (1U) /* USCI clock source select: ACLK */
#define USCI_SPI_CTL1_UCSSEL_SMCLK    (2U) /* USCI clock source select: SMCLK */
#define USCI_SPI_CTL1_UCSSEL_SMCLK2   (3U) /* USCI clock source select: SMCLKs */

/*****************************************************************************
* @brief UCSI_SPI_STAT
*****************************************************************************/

/* UCSI_SPI_STAT_UCLISTEN */
#define UCSI_SPI_STAT_UCLISTEN_MASK  (0x80U)
#define UCSI_SPI_STAT_UCLISTEN_SHIFT (0x7U)
/* Listen enable. The UCLISTEN bit selects loopback mode.
  0b = Disabled
  1b = Enabled. The transmitter output is internally fed back to the receiver. */
#define UCSI_SPI_STAT_UCLISTEN(x)    (((uint8_t)(((uint8_t)(x)) << UCSI_SPI_STAT_UCLISTEN_SHIFT)) & UCSI_SPI_STAT_UCLISTEN_MASK)

/* UCSI_SPI_STAT_UCFE */
#define UCSI_SPI_STAT_UCFE_MASK  (0x40U)
#define UCSI_SPI_STAT_UCFE_SHIFT (0x6U)
/* Framing error flag. This bit indicates a bus conflict in 4-wire master
  mode. UCFE is not used in 3-wire master or any slave mode.
  0b = No error
  1b = Bus error occured */
#define UCSI_SPI_STAT_UCFE(x)    (((uint8_t)(((uint8_t)(x)) << UCSI_SPI_STAT_UCFE_SHIFT)) & UCSI_SPI_STAT_UCFE_MASK)

/* UCSI_SPI_STAT_UCOE */
#define UCSI_SPI_STAT_UCOE_MASK  (0x20U)
#define UCSI_SPI_STAT_UCOE_SHIFT (0x5U)
/* Overrun error flag. This bit is set when a character is transferred
  into UCxRXBUF before the previous character was read. UCOE is
  cleared automatically when UCxRXBUF is read, and must not be
  cleared by software. Otherwise, it will not function correctly.
  0b = No error
  1b = Overrun error occured */
#define UCSI_SPI_STAT_UCOE(x)    (((uint8_t)(((uint8_t)(x)) << UCSI_SPI_STAT_UCOE_SHIFT)) & UCSI_SPI_STAT_UCOE_MASK)

/* UCSI_SPI_STAT_UCBUSY */
#define UCSI_SPI_STAT_UCBUSY_MASK  (0x1U)
#define UCSI_SPI_STAT_UCBUSY_SHIFT (0x0U)
/* USCI busy. This bit indicates if a transmit or receive operation is in progress.
  0b = USCI inactive
  1b = USCI transmitting or receiving */
#define UCSI_SPI_STAT_UCBUSY(x)    (((uint8_t)(((uint8_t)(x)) << UCSI_SPI_STAT_UCBUSY_SHIFT)) & UCSI_SPI_STAT_UCBUSY_MASK)

/*****************************************************************************
* @brief UCSI_I2C_CTL0
*****************************************************************************/

/* USCI_I2C_CTL0_UCA10 */
#define USCI_I2C_CTL0_UCA10_MASK  (0x80U)
#define USCI_I2C_CTL0_UCA10_SHIFT (0x7U)
/* Own addressing mode select
  0b = Own address is a 7-bit address
  1b = Own address is a 10-bit address */
#define USCI_I2C_CTL0_UCA10(x)    (((uint8_t)(((uint8_t)(x)) << USCI_I2C_CTL0_UCA10_SHIFT)) & USCI_I2C_CTL0_UCA10_MASK)

/* USCI_I2C_CTL0_UCSLA10 */
#define USCI_I2C_CTL0_UCSLA10_MASK  (0x40U)
#define USCI_I2C_CTL0_UCSLA10_SHIFT (0x6U)
/* Slave addressing mode select
  0b = Address slave with 7-bit address
  1b = Address slave with 10-bit address */
#define USCI_I2C_CTL0_UCSLA10(x)    (((uint8_t)(((uint8_t)(x)) << USCI_I2C_CTL0_UCSLA10_SHIFT)) & USCI_I2C_CTL0_UCSLA10_MASK)

/* USCI_I2C_CTL0_UCMM */
#define USCI_I2C_CTL0_UCMM_MASK  (0x20U)
#define USCI_I2C_CTL0_UCMM_SHIFT (0x5U)
/* Multi-master environment select
  0b = Single master environment. There is no other master in the
  system. The address compare unit is disabled.
  1b = Multi-master environment */
#define USCI_I2C_CTL0_UCMM(x)    (((uint8_t)(((uint8_t)(x)) << USCI_I2C_CTL0_UCMM_SHIFT)) & USCI_I2C_CTL0_UCMM_MASK)

/* USCI_I2C_CTL0_UCMST */
#define USCI_I2C_CTL0_UCMST_MASK  (0x8U)
#define USCI_I2C_CTL0_UCMST_SHIFT (0x3U)
/* Master mode select. When a master loses arbitration in a multimaster
  environment (UCMM = 1) the UCMST bit is automatically
  cleared and the module acts as slave.
  0b = Slave mode
  1b = Master mode */
#define USCI_I2C_CTL0_UCMST(x)    (((uint8_t)(((uint8_t)(x)) << USCI_I2C_CTL0_UCMST_SHIFT)) & USCI_I2C_CTL0_UCMST_MASK)

/* USCI_I2C_CTL0_UCMODE */
#define USCI_I2C_CTL0_UCMODE_MASK  (0x6U)
#define USCI_I2C_CTL0_UCMODE_SHIFT (0x1U)
/* USCI Mode. The UCMODEx bits select the synchronous mode when UCSYNC = 1.
  00b = 3-pin SPI
  01b = 4-pin SPI (master/slave enabled if STE = 1)
  10b = 4-pin SPI (master/slave enabled if STE = 0)
  11b = I2C mode */
#define USCI_I2C_CTL0_UCMODE(x)    (((uint8_t)(((uint8_t)(x)) << USCI_I2C_CTL0_UCMODE_SHIFT)) & USCI_I2C_CTL0_UCMODE_MASK)

/* USCI_I2C_CTL0_UCSYNC */
#define USCI_I2C_CTL0_UCSYNC_MASK  (0x1U)
#define USCI_I2C_CTL0_UCSYNC_SHIFT (0x0U)
/* Synchronous mode enable.
  0b = Asynchronous mode
  1b = Synchronous mode */
#define USCI_I2C_CTL0_UCSYNC(x)    (((uint8_t)(((uint8_t)(x)) << USCI_I2C_CTL0_UCSYNC_SHIFT)) & USCI_I2C_CTL0_UCSYNC_MASK)

#define USCI_I2C_CTL0_UCMODE_3PIN_SPI    (0U) /* USCI mode: 3-pin SPI */
#define USCI_I2C_CTL0_UCMODE_4PIN_SPI_AH (1U) /* USCI mode: 4-pin SPI with UCxSTE active high: slave enabled when UCxSTE = 1 */
#define USCI_I2C_CTL0_UCMODE_4PIN_SPI_AL (2U) /* USCI mode: 4-pin SPI with UCxSTE active low: slave enabled when UCxSTE = 0 */
#define USCI_I2C_CTL0_UCMODE_I2C         (3U) /* USCI mode: I2C mode */

/*****************************************************************************
* @brief UCSI_I2C_CTL1
*****************************************************************************/

/* UCSI_I2C_CTL1_UCSSEL */
#define UCSI_I2C_CTL1_UCSSEL_MASK  (0xc0U)
#define UCSI_I2C_CTL1_UCSSEL_SHIFT (0x6U)
/* USCI clock source select. These bits select the BRCLK source clock.
  00b = UCLKI
  01b = ACLK
  10b = SMCLK
  11b = SMCLK */
#define UCSI_I2C_CTL1_UCSSEL(x)    (((uint8_t)(((uint8_t)(x)) << UCSI_I2C_CTL1_UCSSEL_SHIFT)) & UCSI_I2C_CTL1_UCSSEL_MASK)

/* UCSI_I2C_CTL1_UCTR */
#define UCSI_I2C_CTL1_UCTR_MASK  (0x10U)
#define UCSI_I2C_CTL1_UCTR_SHIFT (0x4U)
/* Transmitter or receiver
  0b = Receiver
  1b = Transmitter */
#define UCSI_I2C_CTL1_UCTR(x)    (((uint8_t)(((uint8_t)(x)) << UCSI_I2C_CTL1_UCTR_SHIFT)) & UCSI_I2C_CTL1_UCTR_MASK)

/* UCSI_I2C_CTL1_UCTXNACK */
#define UCSI_I2C_CTL1_UCTXNACK_MASK  (0x8U)
#define UCSI_I2C_CTL1_UCTXNACK_SHIFT (0x3U)
/* Transmit a NACK. UCTXNACK is automatically cleared after a NACK is transmitted.
  0b = Acknowledge normally
  1b = Generate NACK */
#define UCSI_I2C_CTL1_UCTXNACK(x)    (((uint8_t)(((uint8_t)(x)) << UCSI_I2C_CTL1_UCTXNACK_SHIFT)) & UCSI_I2C_CTL1_UCTXNACK_MASK)

/* UCSI_I2C_CTL1_UCTXSTP */
#define UCSI_I2C_CTL1_UCTXSTP_MASK  (0x4U)
#define UCSI_I2C_CTL1_UCTXSTP_SHIFT (0x2U)
/* Transmit STOP condition in master mode. Ignored in slave mode. In
  master receiver mode, the STOP condition is preceded by a NACK.
  UCTXSTP is automatically cleared after STOP is generated.
  0b = No STOP generated
  1b = Generate STOP */
#define UCSI_I2C_CTL1_UCTXSTP(x)    (((uint8_t)(((uint8_t)(x)) << UCSI_I2C_CTL1_UCTXSTP_SHIFT)) & UCSI_I2C_CTL1_UCTXSTP_MASK)

/* UCSI_I2C_CTL1_UCTXSTT */
#define UCSI_I2C_CTL1_UCTXSTT_MASK  (0x2U)
#define UCSI_I2C_CTL1_UCTXSTT_SHIFT (0x1U)
/* Transmit START condition in master mode. Ignored in slave mode. In
  master receiver mode a repeated START condition is preceded by a
  NACK. UCTXSTT is automatically cleared after START condition and
  address information is transmitted. Ignored in slave mode.
  0b = Do not generate START condition
  1b = Generate START condition */
#define UCSI_I2C_CTL1_UCTXSTT(x)    (((uint8_t)(((uint8_t)(x)) << UCSI_I2C_CTL1_UCTXSTT_SHIFT)) & UCSI_I2C_CTL1_UCTXSTT_MASK)

/* UCSI_I2C_CTL1_UCSWRST */
#define UCSI_I2C_CTL1_UCSWRST_MASK  (0x1U)
#define UCSI_I2C_CTL1_UCSWRST_SHIFT (0x0U)
/* Software reset enable
  0b = Disabled. USCI reset released for operation.
  1b = Enabled. USCI logic held in reset state. */
#define UCSI_I2C_CTL1_UCSWRST(x)    (((uint8_t)(((uint8_t)(x)) << UCSI_I2C_CTL1_UCSWRST_SHIFT)) & UCSI_I2C_CTL1_UCSWRST_MASK)

#define USCI_I2C_CTL1_UCSSEL_UCLKI    (0U) /* USCI clock source select: UCLKI */
#define USCI_I2C_CTL1_UCSSEL_ACLK     (1U) /* USCI clock source select: ACLK */
#define USCI_I2C_CTL1_UCSSEL_SMCLK    (2U) /* USCI clock source select: SMCLK */
#define USCI_I2C_CTL1_UCSSEL_SMCLK2   (3U) /* USCI clock source select: SMCLKs */

/*****************************************************************************
* @brief UCSI_I2C_STAT
*****************************************************************************/

/* UCSI_I2C_STAT_UCSCLLOW */
#define UCSI_I2C_STAT_UCSCLLOW_MASK  (0x40U)
#define UCSI_I2C_STAT_UCSCLLOW_SHIFT (0x6U)
/* SCL low
  0b = SCL is not held low
  1b = SCL is held low */
#define UCSI_I2C_STAT_UCSCLLOW(x)    (((uint8_t)(((uint8_t)(x)) << UCSI_I2C_STAT_UCSCLLOW_SHIFT)) & UCSI_I2C_STAT_UCSCLLOW_MASK)

/* UCSI_I2C_STAT_UCGC */
#define UCSI_I2C_STAT_UCGC_MASK  (0x20U)
#define UCSI_I2C_STAT_UCGC_SHIFT (0x5U)
/* General call address received. UCGC is automatically cleared when a START condition is received.
  0b = No general call address received
  1b = General call address received */
#define UCSI_I2C_STAT_UCGC(x)    (((uint8_t)(((uint8_t)(x)) << UCSI_I2C_STAT_UCGC_SHIFT)) & UCSI_I2C_STAT_UCGC_MASK)

/* UCSI_I2C_STAT_UCBBUSY */
#define UCSI_I2C_STAT_UCBBUSY_MASK  (0x10U)
#define UCSI_I2C_STAT_UCBBUSY_SHIFT (0x4U)
/* Bus busy
  0b = Bus inactive
  1b = Bus busy */
#define UCSI_I2C_STAT_UCBBUSY(x)    (((uint8_t)(((uint8_t)(x)) << UCSI_I2C_STAT_UCBBUSY_SHIFT)) & UCSI_I2C_STAT_UCBBUSY_MASK)

/* UCSI_I2C_STAT_UCNACKIFG */
#define UCSI_I2C_STAT_UCNACKIFG_MASK  (0x8U)
#define UCSI_I2C_STAT_UCNACKIFG_SHIFT (0x3U)
/* Not-acknowledge received interrupt flag. UCNACKIFG is automatically cleared when a START condition is received.
  0b = No interrupt pending
  1b = Interrupt pending */
#define UCSI_I2C_STAT_UCNACKIFG(x)    (((uint8_t)(((uint8_t)(x)) << UCSI_I2C_STAT_UCNACKIFG_SHIFT)) & UCSI_I2C_STAT_UCNACKIFG_MASK)

/* UCSI_I2C_STAT_UCSTPIFG */
#define UCSI_I2C_STAT_UCSTPIFG_MASK  (0x4U)
#define UCSI_I2C_STAT_UCSTPIFG_SHIFT (0x2U)
/* Stop condition interrupt flag. UCSTPIFG is automatically cleared when a START condition is received.
  0b = No interrupt pending
  1b = Interrupt pending */
#define UCSI_I2C_STAT_UCSTPIFG(x)    (((uint8_t)(((uint8_t)(x)) << UCSI_I2C_STAT_UCSTPIFG_SHIFT)) & UCSI_I2C_STAT_UCSTPIFG_MASK)

/* UCSI_I2C_STAT_UCSTTIFG */
#define UCSI_I2C_STAT_UCSTTIFG_MASK  (0x2U)
#define UCSI_I2C_STAT_UCSTTIFG_SHIFT (0x1U)
/* Start condition interrupt flag. UCSTTIFG is automatically cleared if a STOP condition is received.
  0b = No interrupt pending
  1b = Interrupt pending */
#define UCSI_I2C_STAT_UCSTTIFG(x)    (((uint8_t)(((uint8_t)(x)) << UCSI_I2C_STAT_UCSTTIFG_SHIFT)) & UCSI_I2C_STAT_UCSTTIFG_MASK)

/* UCSI_I2C_STAT_UCALIFG */
#define UCSI_I2C_STAT_UCALIFG_MASK  (0x1U)
#define UCSI_I2C_STAT_UCALIFG_SHIFT (0x0U)
/* Arbitration lost interrupt flag
  0b = No interrupt pending
  1b = Interrupt pending */
#define UCSI_I2C_STAT_UCALIFG(x)    (((uint8_t)(((uint8_t)(x)) << UCSI_I2C_STAT_UCALIFG_SHIFT)) & UCSI_I2C_STAT_UCALIFG_MASK)

/*****************************************************************************
* @brief UCSI_I2C_ADDR_I2COA
*****************************************************************************/

/* UCSI_I2C_ADDR_I2COA_UCGCEN */
#define UCSI_I2C_ADDR_I2COA_UCGCEN_MASK  (0x8000U)
#define UCSI_I2C_ADDR_I2COA_UCGCEN_SHIFT (0xfU)
/* General call response enable
  0b = Do not respond to a general call
  1b = Respond to a general call */
#define UCSI_I2C_ADDR_I2COA_UCGCEN(x)    (((uint16_t)(((uint16_t)(x)) << UCSI_I2C_ADDR_I2COA_UCGCEN_SHIFT)) & UCSI_I2C_ADDR_I2COA_UCGCEN_MASK)

/* UCSI_I2C_ADDR_I2COA_I2COA */
#define UCSI_I2C_ADDR_I2COA_I2COA_MASK  (0x3ffU)
#define UCSI_I2C_ADDR_I2COA_I2COA_SHIFT (0x0U)
/* I2C own address. The I2COAx bits contain the local address of
  the USCI_Bx I2C controller. The address is right-justified. In 7-bit
  addressing mode, bit 6 is the MSB, and bits 9-7 are ignored. In 10-bit
  addressing mode, bit 9 is the MSB. */
#define UCSI_I2C_ADDR_I2COA_I2COA(x)    (((uint16_t)(((uint16_t)(x)) << UCSI_I2C_ADDR_I2COA_I2COA_SHIFT)) & UCSI_I2C_ADDR_I2COA_I2COA_MASK)

/*****************************************************************************
* @brief UCSI_I2C_ADDR_I2CSA
*****************************************************************************/

/* UCSI_I2C_ADDR_I2CSA_I2CSA */
#define UCSI_I2C_ADDR_I2CSA_I2CSA_MASK  (0x3ffU)
#define UCSI_I2C_ADDR_I2CSA_I2CSA_SHIFT (0x0U)
/* I2C slave address. The I2CSAx bits contain the slave address of the
  external device to be addressed by the USCI_Bx module. It is only
  used in master mode. The address is right-justified. In 7-bit slave
  addressing mode, bit 6 is the MSB, and bits 9-7 are ignored. In 10-bit
  slave addressing mode, bit 9 is the MSB. */
#define UCSI_I2C_ADDR_I2CSA_I2CSA(x)    (((uint16_t)(((uint16_t)(x)) << UCSI_I2C_ADDR_I2CSA_I2CSA_SHIFT)) & UCSI_I2C_ADDR_I2CSA_I2CSA_MASK)

/*****************************************************************************
* @brief WDT_CTL
*****************************************************************************/

/* WDT_CTL_WDTPW */
#define WDT_CTL_WDTPW_MASK  (0xff00U)
#define WDT_CTL_WDTPW_SHIFT (0x8U)
/* Watchdog timer+ password. Always reads as 069h. Must be written
  as 05Ah. Writing any other value generates a PUC.s */
#define WDT_CTL_WDTPW(x)    (((uint16_t)(((uint16_t)(x)) << WDT_CTL_WDTPW_SHIFT)) & WDT_CTL_WDTPW_MASK)

/* WDT_CTL_WDTHOLD */
#define WDT_CTL_WDTHOLD_MASK  (0x80U)
#define WDT_CTL_WDTHOLD_SHIFT (0x7U)
/* Watchdog timer+ hold. This bit stops the watchdog timer+. Setting
  WDTHOLD = 1 when the WDT+ is not in use conserves power.
  0b = Watchdog timer+ is not stopped
  1b = Watchdog timer+ is stopped */
#define WDT_CTL_WDTHOLD(x)    (((uint16_t)(((uint16_t)(x)) << WDT_CTL_WDTHOLD_SHIFT)) & WDT_CTL_WDTHOLD_MASK)

/* WDT_CTL_WDTNMIES */
#define WDT_CTL_WDTNMIES_MASK  (0x40U)
#define WDT_CTL_WDTNMIES_SHIFT (0x6U)
/* Watchdog timer+ NMI edge select. This bit selects the interrupt edge
  for the NMI interrupt when WDTNMI = 1. Modifying this bit can
  trigger an NMI. Modify this bit when WDTIE = 0 to avoid triggering an
  accidental NMI.
  0b = NMI on rising edge
  1b = NMI on falling edge */
#define WDT_CTL_WDTNMIES(x)    (((uint16_t)(((uint16_t)(x)) << WDT_CTL_WDTNMIES_SHIFT)) & WDT_CTL_WDTNMIES_MASK)

/* WDT_CTL_WDTNMI */
#define WDT_CTL_WDTNMI_MASK  (0x20U)
#define WDT_CTL_WDTNMI_SHIFT (0x5U)
/* Watchdog timer+ NMI select. This bit selects the function for the RST/NMI pin.
  0b = Reset function
  1b = NMI function */
#define WDT_CTL_WDTNMI(x)    (((uint16_t)(((uint16_t)(x)) << WDT_CTL_WDTNMI_SHIFT)) & WDT_CTL_WDTNMI_MASK)

/* WDT_CTL_WDTTMSEL */
#define WDT_CTL_WDTTMSEL_MASK  (0x10U)
#define WDT_CTL_WDTTMSEL_SHIFT (0x4U)
/* Watchdog timer+ mode select
  0b = Watchdog mode
  1b = Interval timer mode */
#define WDT_CTL_WDTTMSEL(x)    (((uint16_t)(((uint16_t)(x)) << WDT_CTL_WDTTMSEL_SHIFT)) & WDT_CTL_WDTTMSEL_MASK)

/* WDT_CTL_WDTCNTCL */
#define WDT_CTL_WDTCNTCL_MASK  (0x8U)
#define WDT_CTL_WDTCNTCL_SHIFT (0x3U)
/* Watchdog timer+ counter clear. Setting WDTCNTCL = 1 clears the
  count value to 0000h. WDTCNTCL is automatically reset.
  0b = No action
  1b = WDTCNT = 0000h */
#define WDT_CTL_WDTCNTCL(x)    (((uint16_t)(((uint16_t)(x)) << WDT_CTL_WDTCNTCL_SHIFT)) & WDT_CTL_WDTCNTCL_MASK)

/* WDT_CTL_WDTSSEL */
#define WDT_CTL_WDTSSEL_MASK  (0x4U)
#define WDT_CTL_WDTSSEL_SHIFT (0x2U)
/* Watchdog timer+ clock source select
  0b = SMCLK
  1b = ACLK */
#define WDT_CTL_WDTSSEL(x)    (((uint16_t)(((uint16_t)(x)) << WDT_CTL_WDTSSEL_SHIFT)) & WDT_CTL_WDTSSEL_MASK)

/* WDT_CTL_WDTIS */
#define WDT_CTL_WDTIS_MASK  (0x3U)
#define WDT_CTL_WDTIS_SHIFT (0x0U)
/* Watchdog timer+ interval select. These bits select the watchdog timer+ interval to set the WDTIFG flag or generate a PUC.
  00b = Watchdog clock source /32768
  01b = Watchdog clock source /8192
  10b = Watchdog clock source /512
  11b = Watchdog clock source /64 */
#define WDT_CTL_WDTIS(x)    (((uint16_t)(((uint16_t)(x)) << WDT_CTL_WDTIS_SHIFT)) & WDT_CTL_WDTIS_MASK)

#define WDTIS0   (0x0001)
#define WDTIS1   (0x0002)
#define WDTSSEL  (0x0004)
#define WDTCNTCL (0x0008)
#define WDTTMSEL (0x0010)
#define WDTNMI   (0x0020)
#define WDTNMIES (0x0040)
#define WDTHOLD  (0x0080)

#define WDTPW               (0x5A00u)
/* WDT is clocked by fSMCLK (assumed 1MHz) */
#define WDT_MDLY_32         (WDTPW+WDTTMSEL+WDTCNTCL)                         /* 32ms interval (default) */
#define WDT_MDLY_8          (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS0)                  /* 8ms     " */
#define WDT_MDLY_0_5        (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS1)                  /* 0.5ms   " */
#define WDT_MDLY_0_064      (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS1+WDTIS0)           /* 0.064ms " */
/* WDT is clocked by fACLK (assumed 32KHz) */
#define WDT_ADLY_1000       (WDTPW+WDTTMSEL+WDTCNTCL+WDTSSEL)                 /* 1000ms  " */
#define WDT_ADLY_250        (WDTPW+WDTTMSEL+WDTCNTCL+WDTSSEL+WDTIS0)          /* 250ms   " */
#define WDT_ADLY_16         (WDTPW+WDTTMSEL+WDTCNTCL+WDTSSEL+WDTIS1)          /* 16ms    " */
#define WDT_ADLY_1_9        (WDTPW+WDTTMSEL+WDTCNTCL+WDTSSEL+WDTIS1+WDTIS0)   /* 1.9ms   " */
/* WDT is clocked by fSMCLK (assumed 1MHz) */
#define WDT_MRST_32         (WDTPW+WDTCNTCL)                                  /* 32ms interval (default) */
#define WDT_MRST_8          (WDTPW+WDTCNTCL+WDTIS0)                           /* 8ms     " */
#define WDT_MRST_0_5        (WDTPW+WDTCNTCL+WDTIS1)                           /* 0.5ms   " */
#define WDT_MRST_0_064      (WDTPW+WDTCNTCL+WDTIS1+WDTIS0)                    /* 0.064ms " */
/* WDT is clocked by fACLK (assumed 32KHz) */
#define WDT_ARST_1000       (WDTPW+WDTCNTCL+WDTSSEL)                          /* 1000ms  " */
#define WDT_ARST_250        (WDTPW+WDTCNTCL+WDTSSEL+WDTIS0)                   /* 250ms   " */
#define WDT_ARST_16         (WDTPW+WDTCNTCL+WDTSSEL+WDTIS1)                   /* 16ms    " */
#define WDT_ARST_1_9        (WDTPW+WDTCNTCL+WDTSSEL+WDTIS1+WDTIS0)            /* 1.9ms   " */

/*****************************************************************************
* @brief Calibration Data
*****************************************************************************/

#define TAG_DCO_30             (0x01)    /* Tag for DCO30  Calibration Data */
#define TAG_ADC10_1            (0x10)    /* Tag for ADC10_1 Calibration Data */
#define TAG_EMPTY              (0xFE)    /* Tag for Empty Data Field in Calibration Data */

/************************************************************
* Interrupt Vectors (offset from 0xFFE0)
************************************************************/

#define TRAPINT_VECTOR      (0u * 2u)  /* 0xFFE0 TRAPINT */
#define PORT1_VECTOR        (2u * 2u)  /* 0xFFE4 Port 1 */
#define PORT2_VECTOR        (3u * 2u)  /* 0xFFE6 Port 2 */
#define ADC10_VECTOR        (5u * 2u)  /* 0xFFEA ADC10 */
#define USCIAB0TX_VECTOR    (6u * 2u)  /* 0xFFEC USCI A0/B0 Transmit */
#define USCIAB0RX_VECTOR    (7u * 2u)  /* 0xFFEE USCI A0/B0 Receive */
#define TIMER0_A1_VECTOR    (8u * 2u)  /* 0xFFF0 Timer0_A CC1, TA0 */
#define TIMER0_A0_VECTOR    (9u * 2u)  /* 0xFFF2 Timer0_A CC0 */
#define WDT_VECTOR          (10u * 2u) /* 0xFFF4 Watchdog Timer */
#define COMPARATORA_VECTOR  (11u * 2u) /* 0xFFF6 Comparator A */
#define TIMER1_A1_VECTOR    (12u * 2u) /* 0xFFF8 Timer1_A CC1-4, TA1 */
#define TIMER1_A0_VECTOR    (13u * 2u) /* 0xFFFA Timer1_A CC0 */
#define NMI_VECTOR          (14u * 2u) /* 0xFFFC Non-maskable */
#define RESET_VECTOR        (15u * 2u) /* 0xFFFE Reset [Highest Priority] */

#endif /* __MSP430G2553_VS */
