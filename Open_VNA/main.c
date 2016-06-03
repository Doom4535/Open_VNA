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

#include "msp.h"

/* Code files to include */
// Communications modules, located in Communication_Modules folder
#include "I2C_module.c"
#include "SPI_module.c"
#include "UART_module.c"

// Startup modules, located in Startup folder
#include "bootloader.c"

// VNA (actual stuff related to signal processing), located in VNA_Functions folder
#include "VNA.c"


void main(void)	// This should call all the other needed modules (any initializations, bootloader, ect) before passing control over to the VNA code
{
	
    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer
	

}
