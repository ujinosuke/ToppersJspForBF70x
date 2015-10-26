/*
 **
 ** pinmux_config.c source file generated on 10ŒŽ 27, 2015 at 06:36:00.	
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
 ** UART0 (TX, RX)
 **
 ** GPIO (unavailable)
 ** ------------------
 ** PB08, PB09
 */

#include <sys/platform.h>
#include <stdint.h>

#define UART0_TX_PORTB_MUX  ((uint32_t) ((uint32_t) 0<<16))
#define UART0_RX_PORTB_MUX  ((uint32_t) ((uint32_t) 0<<18))

#define UART0_TX_PORTB_FER  ((uint32_t) ((uint32_t) 1<<8))
#define UART0_RX_PORTB_FER  ((uint32_t) ((uint32_t) 1<<9))

int32_t adi_initpinmux(void);

/*
 * Initialize the Port Control MUX and FER Registers
 */
int32_t adi_initpinmux(void) {
    /* PORTx_MUX registers */
    *pREG_PORTB_MUX = UART0_TX_PORTB_MUX | UART0_RX_PORTB_MUX;

    /* PORTx_FER registers */
    *pREG_PORTB_FER = UART0_TX_PORTB_FER | UART0_RX_PORTB_FER;
    return 0;
}

