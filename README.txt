This is the software portion of an attempt at an open vector network analyzer design.

The current development plan is to isolate the individual code components into separate files based on their purpose:


Current code structure
						 						 									  	
- main.c
	-Initializations	-> currently to be implemented in main.c, used to declare dependencies, ect.
	
	-Bootup -> stores any files related to the initial loading of the device
		-bootloader.c	-> may start with a simple timer, and move to something that actually monitors loading progress
	
	-Communications		-> used to control communication protocols
		-I2C_module.c  (clock)
		-SPI_module.c  (ADC)
		-UART_module.c (PC)
	
	-VNA.c	-> controls the actual signal analysis
		-VNA_submodules	-> used to separate core functions/components
			-Fourier_Series.c
			-ect.							 						 									  	
