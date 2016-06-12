/*
 * SPI_module.c
 *
 *  Created on: Jun 2, 2016
 *      Author: aaron
 *      based on code by victor
 */

/*
 * SPI to ADS131A04
 * author: victor
*/
#include <stdint.h>
#include <driverlib.h>
#include <stdbool.h>

uint32_t resultsBuffer[3]={0,0,0};

/* CS on Pin 4.7
 * SCLK on Pin 1.5
 * Din on Pin 1.6
 * Dout on Pin 1.7
 */
static volatile uint32_t RXData = 0;
static volatile uint8_t RXHold = 0;
int count=0;
int i=-1;

const eUSCI_SPI_MasterConfig spiMasterConfig =
{
        EUSCI_B_SPI_CLOCKSOURCE_SMCLK,             // SMCLK Clock Source
        3000000,                                   // SMCLK = DCO = 3MHZ
        500000,                                    // SPICLK = 500khz
        EUSCI_B_SPI_MSB_FIRST,                     // MSB First
        EUSCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT,    // Phase
        EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_LOW, // LOW polarity
        EUSCI_B_SPI_3PIN                           // 3Wire SPI Mode
};

// remember to modify the startup file for the SPI interrupt
int initialize_SPI_com(void)
{
	MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P6, GPIO_PIN0);
	  MAP_GPIO_clearInterruptFlag(GPIO_PORT_P6, GPIO_PIN0);
	    MAP_GPIO_enableInterrupt(GPIO_PORT_P6, GPIO_PIN0);
	    MAP_Interrupt_enableInterrupt(INT_PORT6);
	void GPIO_interruptEdgeSelect(GPIO_PORT_P6,GPIO_PIN0,GPIO_HIGH_TO_LOW_TRANSITION);
	/* Enabling SRAM Bank Retention */
	    MAP_SysCtl_enableSRAMBankRetention(SYSCTL_SRAM_BANK1);

	    /* Enabling MASTER interrupts */
	    MAP_Interrupt_enableMaster();
	    /* Halting WDT  */
	        WDT_A_holdTimer();

	        /* Selecting P1.5 P1.6 and P1.7 in SPI mode */
	        GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
	                GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);

	        /* Configuring SPI in 3wire master mode */
	        SPI_initMaster(EUSCI_B0_BASE, &spiMasterConfig);
	        /* Enable SPI module */
	            SPI_enableModule(EUSCI_B0_BASE);
}

//void PORT1_IRQHandler(void)
void PORT1_SPI_ISR(void)
{
    uint32_t status;

    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P6);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P6, status);

    /* Toggling the output on the LED */
    while(status & (GPIO_PIN0==0))
    {
    		RXHold=RXData*256
    		RXData = SPI_receiveData(EUSCI_B0_BASE);
    		RXHold=RXHold+RXData;
    		count++;
    		if (count==3)
    		{
    		i++;
    		resultsBuffer[i]=RXHold;
    		}
    }

}




