/*
 * UART_module.h
 *
 *  Created on: Jun 3, 2016
 *      Author: aaron
 */

#ifndef COMMUNICATION_MODULES_UART_MODULE_H_
#define COMMUNICATION_MODULES_UART_MODULE_H_

extern const eUSCI_UART_Config uartConfig;
extern char uartRXData[80];
extern bool uartEndOfLineFlag;

extern void EusciA0_ISR(void);

//int initializeBackChannelUART(void);
extern int initializeBackChannelUART(void);


#endif /* COMMUNICATION_MODULES_UART_MODULE_H_ */
