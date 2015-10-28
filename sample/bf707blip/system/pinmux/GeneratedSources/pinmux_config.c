/*
 **
 ** pinmux_config.c source file generated on 10ŒŽ 29, 2015 at 07:13:54.	
 **
 ** Copyright (C) 2000-2015 Analog Devices Inc., All Rights Reserved.
 **
 ** This file is generated automatically based upon the options selected in 
 ** the Pin Multiplexing configuration editor. Changes to the Pin Multiplexing
 ** configuration should be made by changing the appropriate options rather
 ** than editing this file.
 **
 ** Selected Peripherals
 ** --------------------
 ** UART1 (TX, RX)
 **
 ** GPIO (unavailable)
 ** ------------------
 ** PC00, PC01
 */

#include <sys/platform.h>
#include <stdint.h>

#define UART1_TX_PORTC_MUX  ((uint16_t) ((uint16_t) 0<<0))
#define UART1_RX_PORTC_MUX  ((uint16_t) ((uint16_t) 0<<2))

#define UART1_TX_PORTC_FER  ((uint16_t) ((uint16_t) 1<<0))
#define UART1_RX_PORTC_FER  ((uint16_t) ((uint16_t) 1<<1))

int32_t adi_initpinmux(void);

/*
 * Initialize the Port Control MUX and FER Registers
 */
int32_t adi_initpinmux(void) {
    /* PORTx_MUX registers */
    *pREG_PORTC_MUX = UART1_TX_PORTC_MUX | UART1_RX_PORTC_MUX;

    /* PORTx_FER registers */
    *pREG_PORTC_FER = UART1_TX_PORTC_FER | UART1_RX_PORTC_FER;
    return 0;
}

