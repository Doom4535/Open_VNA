This is the software portion of an attempt at an open vector network analyzer design.

The current developement plan is to isolate the individual code components into seperate files based on their purpose:

										main.c
										|
--------------------------------------------------------------------------------------------------------------------
			|					|						|							|
	Communications			Innitializations			   Bootup						VNA.c	
   |	      |	   	|			-currently handled		-Powers up components			The main control code for the
  I2C    SPI  	    UART		in main.c				 and enables device				actual VNA implementation.
-Clock   -ADC		-PC						 		 when ready						|		|		|		|
						 						 									------Sub. code/routines------