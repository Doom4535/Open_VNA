/*
 * UART_module.c
 *
 *  Created on: Jun 2, 2016
 *      Author: aaron
 *      based on code by Dr. Frohne
 */

/* DriverLib Includes */
#include "driverlib.h"
#include "msp432.h"
#include "hw_memmap.h"

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

//#include <string.h>
#include "../printf.h"
#include <math.h>

#include "UART_Module.h"
#include "../common.h"

/* UART constants */
#define REFLECTION_MODE 0
#define TRANSMISSION_MODE 1

/* UART Configuration Parameter. These are the configuration parameters to
 * make the eUSCI A UART module to operate with a 115200 baud rate. These
 * values were calculated using the online calculator that TI provides
 * at:
 * http://processors.wiki.ti.com/index.php/
 *               USCI_UART_Baud_Rate_Gen_Mode_Selection
 *
 * On Linux use /dev/ttyACM0, 115200, 8N1.
 *               CuteCom works well.
 */

/*
 * This configuration below seems to run at some unknown rate at the present time
const eUSCI_UART_Config uartConfig =
{
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
        78,                                      // BRDIV = 26 for 115200 baud
        0,                                       // UCxBRF = 0 for 115200 baud
        0x10,                                       // UCxBRS = 0 for 115200 baud
        EUSCI_A_UART_NO_PARITY,                  // No Parity
        EUSCI_A_UART_LSB_FIRST,                  // MSB First
        EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
        EUSCI_A_UART_MODE,                       // UART mode
//		EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION // Oversampling Mode
        EUSCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION  // Low Frequency Mode
};
*/

// This configuration below for some reason seems to actually run at 460800 baud install of 115200...
const eUSCI_UART_Config uartConfig =
{
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
        26,                                      // BRDIV = 26 for 115200 baud
        0,                                       // UCxBRF = 0 for 115200 baud
        0,                                       // UCxBRS = 0 for 115200 baud
        EUSCI_A_UART_NO_PARITY,                  // No Parity
        EUSCI_A_UART_LSB_FIRST,                  // MSB First
        EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
        EUSCI_A_UART_MODE,                       // UART mode
//		EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION // Oversampling Mode
        EUSCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION  // Low Frequency Mode
};
/* Array used to store received data */
char uartRXData[80];
/* Used to determine if we are at the end of a transmission */
bool uartEndOfLineFlag = false;

/*
 * USCIA0 interrupt handler for backchannel UART.
 * For interrupts, don't forget to edit the startup...c file!
 */

/* Interrupt subroutine that is triggered whenever data is received over serial */
void EusciA0_ISR(void)
{
    static int i=0;
	uint32_t status = UART_getEnabledInterruptStatus(EUSCI_A0_BASE);
	uint_fast8_t errorStatus = UART_queryStatusFlags(EUSCI_A0_BASE,
			EUSCI_A_UART_FRAMING_ERROR|EUSCI_A_UART_RECEIVE_ERROR
			|EUSCI_A_UART_PARITY_ERROR|EUSCI_A_UART_OVERRUN_ERROR
			|EUSCI_A_UART_BUSY);

    UART_clearInterruptFlag(EUSCI_A0_BASE, status);
//    if((errorStatus & (EUSCI_A_UART_FRAMING_ERROR|EUSCI_A_UART_RECEIVE_ERROR
//			|EUSCI_A_UART_PARITY_ERROR|EUSCI_A_UART_OVERRUN_ERROR
//			|EUSCI_A_UART_BUSY)) != 0)
//	{
//		printf("errorStatus is: %x\n");
//	}
    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT)
    {
        uartRXData[i] = UART_receiveData(EUSCI_A0_BASE);
        if(uartRXData[i++]==0x0d)		// was 0x0d
        {
        	uartEndOfLineFlag = true;
        	uartRXData[i] = 0;  // To end the array.
        	i=0; // Get ready for the next command.
        }
    }
}

// will want to move this to start up later
/* Intializes the system clock */
void initializeClocks(void)
{
    /* Initialize main clock to 48MHz.  To make it 3 MHz change the 48 to 3
     * and the 16's to 1.*/
	PCM_setCoreVoltageLevel(PCM_VCORE1);
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48); // Full speed
    CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_16 );
    MAP_CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_16 );
    MAP_CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_16 );
}

/*  We may want to use P3.2 and P3.3 as a Bluetooth UART because the
 *  backchannel UART is a bit slow.  I only get every other character
 *  at 115200 baud.
 */
int initializeBackChannelUART(void){

	initializeClocks();
    /* Selecting P1.2 and P1.3 in UART mode. */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
        GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

    /* Configuring UART Module */
    if(UART_initModule(EUSCI_A0_BASE, &uartConfig)==STATUS_FAIL)
    	return (STATUS_FAIL);

    UART_selectDeglitchTime(EUSCI_A0_BASE,EUSCI_A_UART_DEGLITCH_TIME_200ns);

    /* Enable UART module */
    MAP_UART_enableModule(EUSCI_A0_BASE);

    /* Enable UART interrupts for backchannel UART
     * We may or may not need to do this.  The simple
     * printf() routine doesn't seem to use it.  */
    UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    		/*EUSCI_A_SPI_TRANSMIT_INTERRUPT);*/
    Interrupt_enableInterrupt(INT_EUSCIA0);
    //EusciA0_ISR();	// adding this? <-------------
    return 1;
}
