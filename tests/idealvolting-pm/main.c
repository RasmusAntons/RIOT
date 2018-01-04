/*
 * Copyright (C) 2017 Rasmus Antons <r.antons@tu-bs.de>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     tests
 * @{
 *
 * @file
 * @brief       Test application for the IdealVolting implementation in
 *              boards_inga_common.
 *
 * @author      Rasmus Antons <r.antons@tu-bs.de>
 *
 * @}
 */

//#include "xtimer.h"
#include <stdio.h>
#include "pm_layered.h"
#include "periph/uart.h"
#include "uart_stdio.h"

int main(void)
{
	char buffer[100];
	volatile double d = 0;
	(void) d;
	puts("Welcome to the RIOT Operating System");
	while (1) {
		puts("hello?\n");
		// Delay
		uart_poweroff(UART_STDIO_DEV);
		//for (unsigned long i = 0; i < 65535 >> 2; ++i)
		//	d = (double) i / ((double) i + 0.00004);
		sprintf(buffer, "%d %d %d %d %d", blocks(0), blocks(1), blocks(2), blocks(3), blocks(4));
		uart_poweron(UART_STDIO_DEV);
		//uart_stdio_init();
		for (unsigned long i = 0; i < 65535 >> 2; ++i)
					d = (double) i / ((double) i + 0.00004);
		puts(buffer);
	}
	return 0;
}
