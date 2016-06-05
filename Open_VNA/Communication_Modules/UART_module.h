/*
 * UART_module.h
 *
 *  Created on: Jun 3, 2016
 *      Author: aaron
 */

#ifndef COMMUNICATION_MODULES_UART_MODULE_H_
#define COMMUNICATION_MODULES_UART_MODULE_H_

extern const eUSCI_UART_Config uartConfig;
extern const char uartRXData[80];  // should this be uartRXData[80] (extern?)
extern bool uartEndOfLineFlag; // should this be static?

void EusciA0_ISR(void);

int initializeBackChannelUART(void);


#endif /* COMMUNICATION_MODULES_UART_MODULE_H_ */
