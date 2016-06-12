/*
 * SPI_module.h
 *
 *  Created on: Jun 3, 2016
 *      Author: aaron
 */

#ifndef COMMUNICATION_MODULES_SPI_MODULE_H_
#define COMMUNICATION_MODULES_SPI_MODULE_H_

//extern uint32_t resultsBuffer[3]; //using SPI_RXData instead as the global variable
extern uint32_t SPI_RXData;
//extern static volatile uint32_t RXData = 0;
//extern static volatile uint8_t RXHold = 0;
//extern const eUSCI_SPI_MasterConfig spiMasterConfig;

//void PORT1_SPI_ISR(void)
extern void PORT1_SPI_ISR(void)



#endif /* COMMUNICATION_MODULES_SPI_MODULE_H_ */
