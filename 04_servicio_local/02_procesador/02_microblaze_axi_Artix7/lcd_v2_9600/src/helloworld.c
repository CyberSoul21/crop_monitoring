
/**************************************************************************//**
 * @file serial_fpga.c
 *
 *
 * @authors:
 * Wilson Javier Almario Rodriguez.
 * Diana Natali Maldonado Ramirez
 * Camilo Andres Garzon Lopez
 * Wendy Alejandra Garcia Rojas
 * Sebastian Betancour Peñaranda
 *
 * @date 07/01/2020
 *
 *
 *
 *****************************************************************************/
/******************************************************************************
 * Copyright (C) 2020 by Monitoreo de cultivo
 *****************************************************************************/


#include <stdio.h>
#include "platform.h"
#include "xparameters.h"// Information about AXI peripherals
#include "xgpio.h"      // AXI GPIO driver
#include "xil_printf.h"
#include "xuartlite.h"  // Data over AXI UART

#define SIZE 14

#define delay_time 10000000

XGpio AXI_GPIO0;        // Structure to handle the AXI GPIO 0
XUartLite AXI_UartLite0; // Structure to handle the AXI UART 0
XUartLite AXI_UartLite1; // Structure to handle the AXI UART 1

// Delay function
//-----------------------------
void delay(int time){
  int i;

  for (i = 0; i < time; i++); };


int main()
{
	u32 sws;
	int StatusUart0,StatusUart1;
	int flag = 0;
	u8   input_serial[8] = "";
	u8   plants[8] = "123aif";
	u8   init[6] = ".txt=\"";
	u8   end[2] = "\"";
	u8   output_serial[SIZE]= "";
	int aux = 0;

//*******************************************************************************************************
//*******************************************************************************************************
    XGpio_Initialize(&AXI_GPIO0, 0);   // Initialize AXI GPIO 0
    init_platform();
	// UartLite0 initialization
	StatusUart0 = XUartLite_Initialize(&AXI_UartLite0, XPAR_AXI_UARTLITE_0_DEVICE_ID); // JB
	if (StatusUart0 != XST_SUCCESS){
		print("UartLite INIT FAILED\n\r");
        return XST_FAILURE; }

	// UartLite1 initialization
	StatusUart1 = XUartLite_Initialize(&AXI_UartLite1, XPAR_AXI_UARTLITE_1_DEVICE_ID); // JA
	if (StatusUart1 != XST_SUCCESS){
		print("UartLite INIT FAILED\n\r");
        return XST_FAILURE; }
    // set AXI GPIO 0 channel (1, 2) tristates to Output (0) or inputs (1)
    XGpio_SetDataDirection(&AXI_GPIO0, 1, 0x00000000); // leds
    XGpio_SetDataDirection(&AXI_GPIO0, 2, 0x0000000F); // sws
//*******************************************************************************************************
//*******************************************************************************************************

    while(1){
    	sws = XGpio_DiscreteRead(&AXI_GPIO0, 2);

    	XGpio_DiscreteWrite(&AXI_GPIO0, 1, sws);

//    	XUartLite_Recv(&AXI_UartLite0, input_serial, 8); //JB

/*
    	int i = 0;
    	int j = 0;
    	int k = 0;
    	for (i = 0; i < SIZE; i++) {
    		if (input_serial[i] == plants[4]) { //Inicio
    			for(j = 0; j < 6; j++){
    				output_serial[i+j] = init[j];

    			}
    		}else{
    			output_serial[i+j] = input_serial[i];

    		}

    	}
    	int o = 8;
    	for(int l = 3; l<7; l++){
    		output_serial[o] = input_serial[l];
    		o++;
    	}
    	int p = 12;
    	for(int q = 0; q<2; q++){
    		output_serial[p] = end[q];
    		p++;
    	}
    	*/


/*
    	if(input_serial[0] == plants[3] && input_serial[4] == plants[0]){
    		XGpio_DiscreteWrite(&AXI_GPIO0, 1, 1);

    	}else{
    		//XGpio_DiscreteWrite(&AXI_GPIO0, 1, 0);
    	}
*/



 /*
    	usleep(2000000); // 100mse
    //	XUartLite_Send(&AXI_UartLite1, input_serial, 13); // Funciona !! 12/06/20 JA
		XUartLite_Send(&AXI_UartLite1, output_serial, 13); // Funciona !! 12/06/20 JA
		XUartLite_Send(&AXI_UartLite1, "\xFF\xFF\xFF", 8);
		usleep(2000000); // 100mse
*/








    	//----- AXI GPIO ----
    	sws = XGpio_DiscreteRead(&AXI_GPIO0, 2);
    	if(sws == 1 && flag !=1)
    	{
    		XUartLite_Send(&AXI_UartLite1, "t2.txt=\"23.9\"", 13); // Funciona !! 12/06/20
    		XUartLite_Send(&AXI_UartLite1, "\xFF\xFF\xFF", 8);
			usleep(2000000); // 100mse
			flag = 1;
    	}
    	if(sws == 2 && flag !=2)
    	{
    		XUartLite_Send(&AXI_UartLite1, "h2.txt=\"0074\"", 13); // Funciona !! 12/06/20
    		XUartLite_Send(&AXI_UartLite1, "\xFF\xFF\xFF", 8);
			usleep(2000000); // 100mse
			flag = 2;
    	}
    	if(sws == 3 && flag !=3)
    	{
    		XUartLite_Send(&AXI_UartLite1, "c2.txt=\"16.0\"", 13); // Funciona !! 12/06/20
    		XUartLite_Send(&AXI_UartLite1, "\xFF\xFF\xFF", 8);
			usleep(2000000); // 100mse
			flag = 3;
    	}
    	if(sws == 4 && flag !=4)
    	{
    		XUartLite_Send(&AXI_UartLite1, "l2.txt=\"1111\"", 13); // Funciona !! 12/06/20
    		XUartLite_Send(&AXI_UartLite1, "\xFF\xFF\xFF", 8);
			usleep(2000000); // 100mse
			flag = 4;
    	}
    	if(sws == 5 && flag !=5)
    	{
    		XUartLite_Send(&AXI_UartLite1, "l2.txt=\"0000\"", 13); // Funciona !! 12/06/20
    		XUartLite_Send(&AXI_UartLite1, "\xFF\xFF\xFF", 8);
			usleep(2000000); // 100mse
			flag = 5;
    	}

    }

    return 0;
}
