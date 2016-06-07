//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

#define USE_SPI
/* DriverLib Includes */
#include "driverlib.h"
#include "msp432.h"
#include "hw_memmap.h"

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include <string.h>
#include "printf.h"
#include <math.h>

//#include "msp.h"

/* Code files to include */
// Communications modules, located in Communication_Modules folder
//#include "Communication_Modules/I2C_module.c"
//#include "Communication_Modules/SPI_module.c"
#include "Communication_Modules/UART_module.h"
#include "common.h"

// Startup modules, located in Startup folder
#include "Startup/bootloader.c"

// VNA (actual stuff related to signal processing), located in VNA_Functions folder
#include "VNA_Functions/VNA.c"


void main(void)	// This should call all the other needed modules (any initializations, bootloader, ect) before passing control over to the VNA code
{
	
    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer


    // will want to probably move this to startup
    while(!initializeBackChannelUART())
    {
    		volatile int i = 0;
		for(i=0;i<100;i++);  /*Wait to try again. */
	}
	
    while(1){
    		if(uartEndOfLineFlag){  /* Parse this command line. */
    			if(uartRXData[0]=='t'){
    				printf("%c", "Congraduations, the simple test passed");
    				volatile int i = 0;	// counting variable for delay
    				while(i < 3,000,000)		// delaying/sleeping for about 1 sec (using default clock speed of 1 MHz
    				i++;
    			}
    			else if(uartRXData[0]=='s'){
    				printf("%c", "Well, there's egg and bacon; egg sausage and bacon; egg and spam; egg bacon and spam; egg bacon sausage and spam; spam bacon sausage and spam; spam egg spam spam bacon and spam; spam sausage spam spam bacon spam tomato and spam");
    				volatile int i = 0;	// counting variable for delay
    				while(i < 3,000,000)		// delaying/sleeping for about 1 sec (using default clock speed of 1 MHz
    				i++;
    			}
    			else{
    				printf("%c", "Why are you ignoring me?");
    				volatile int i = 0;	// counting variable for delay
    				while(i < 3,000,000)		// delaying/sleeping for about 1 sec (using default clock speed of 1 MHz
    				i++;
    			}

    		}

    	}

}
