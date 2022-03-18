/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xparameters.h"// Information about AXI peripherals
#include "xgpio.h"      // AXI GPIO driver
#include "xil_printf.h"
#include "xuartlite.h"  // Data over AXI UART


#define delay_time 1000000


XGpio AXI_GPIO0;        // Structure to handle the AXI GPIO 0
XUartLite AXI_UartLite; // Structure to handle the AXI UART 0


// Delay function
//-----------------------------
void delay(int time){
  int i;
  for (i = 0; i < time; i++); };



//-----------------------------
// Main function
//-----------------------------
int main()
{

	int StatusUart;
	u32 sws;
	u8  buffer[8] = "Salut!";

    XGpio_Initialize(&AXI_GPIO0, 0);   // Initialize AXI GPIO 0

    init_platform();

	// UartLite initialization
	StatusUart = XUartLite_Initialize(&AXI_UartLite, XPAR_AXI_UARTLITE_0_DEVICE_ID);
	if (StatusUart != XST_SUCCESS){
		print("UartLite INIT FAILED\n\r");
        return XST_FAILURE; }

    // set AXI GPIO 0 channel (1, 2) tristates to Output (0) or inputs (1)
    XGpio_SetDataDirection(&AXI_GPIO0, 1, 0x00000000); // leds
    XGpio_SetDataDirection(&AXI_GPIO0, 2, 0x0000000F); // sws


    while(1){

    	//----- AXI GPIO ----
    	sws = XGpio_DiscreteRead(&AXI_GPIO0, 2);     // Lire les interrupteurs

    	// Allumer leds avec les interrupteurs
    	XGpio_DiscreteWrite(&AXI_GPIO0, 1, sws);

    	//----- AXI UART ----
    	XUartLite_Send(&AXI_UartLite, buffer, 8);

    	delay(delay_time);
    }

    return 0;
}
