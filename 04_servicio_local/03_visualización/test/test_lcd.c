#include <stdio.h>
#include "platform.h"
#include "xparameters.h"// Information about AXI peripherals
#include "xgpio.h"      // AXI GPIO driver
#include "xil_printf.h"
#include "xuartlite.h"  // Data over AXI UART


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

	//SendBuffer[BUFFER_SIZE] = "xFF\xFF\xFF";
	//SendBuffer = "ÿÿÿ";


	int StatusUart0,StatusUart1;
	u32 sws;
	//u8  buffer[8] = "Led \n";
	char buffer[]="Javier\r\n";
	char buffer2[]="Almario\r\n";
	u8   RBuf[8] = "";
	u8   comp[8] = "123456\n\r";
	u8   comp2[8] = "wils56\n\r";
	u8   reSend[8] = "";//"000000\n\r";
	//char RBuf[]="";

	unsigned int ReceivedCount=0;

	u8 BytesSent;

    XGpio_Initialize(&AXI_GPIO0, 0);   // Initialize AXI GPIO 0

    init_platform();

	// UartLite0 initialization
	StatusUart0 = XUartLite_Initialize(&AXI_UartLite0, XPAR_AXI_UARTLITE_0_DEVICE_ID);
	if (StatusUart0 != XST_SUCCESS){
		print("UartLite INIT FAILED\n\r");
        return XST_FAILURE; }

	// UartLite1 initialization
	StatusUart1 = XUartLite_Initialize(&AXI_UartLite1, XPAR_AXI_UARTLITE_1_DEVICE_ID);
	if (StatusUart1 != XST_SUCCESS){
		print("UartLite INIT FAILED\n\r");
        return XST_FAILURE; }


    // set AXI GPIO 0 channel (1, 2) tristates to Output (0) or inputs (1)
    XGpio_SetDataDirection(&AXI_GPIO0, 1, 0x00000000); // leds
    XGpio_SetDataDirection(&AXI_GPIO0, 2, 0x0000000F); // sws


    while(1){

    	//----- AXI GPIO ----
    	sws = XGpio_DiscreteRead(&AXI_GPIO0, 2);

    	//XGpio_DiscreteWrite(&AXI_GPIO0, 1, sws);

    	if(sws == 1)
    	{
    		//XUartLite_Send(&AXI_UartLite, buffer, 8);
    		//XUartLite_Send(&AXI_UartLite, buffer, sizeof(buffer));
//    		XUartLite_Send(&AXI_UartLite0, "t0.txt=\"wil\"\xFF\xFF\xFF", sizeof("t0.txt=\"wil\"\xFF\xFF\xFF")); //works

//    		BytesSent = XUartLite_Send(&AXI_UartLite0, "t0.txt=\"fpga9600\"\xFF\xFF\xFF", strlen("t0.txt=\"fpga9600\"\xFF\xFF\xFF")); //works
//    		while (XUartLite_IsSending(&AXI_UartLite0)) {/*Wait*/}

//    		XUartLite_Send(&AXI_UartLite0, "t0.txt=\"23.2\"", 13); //Funciona 12/06/2020
//    		XUartLite_Send(&AXI_UartLite0, "\xFF\xFF\xFF", 8);
    		//XUartLite_SendBuffer(&AXI_UartLite0);
    		usleep(1000000); // 200msec



//    		XUartLite_Send(&AXI_UartLite1, "t0.txt=\"wil\"\xFF\xFF\xFF", sizeof("t0.txt=\"wil\"\xFF\xFF\xFF")); //works

//    		BytesSent = XUartLite_Send(&AXI_UartLite1, "t0.txt=\"fpga9600\"\xFF\xFF\xFF", strlen("t0.txt=\"fpga9600\"\xFF\xFF\xFF")); //works
//    		while (XUartLite_IsSending(&AXI_UartLite1)) {/*Wait*/}

//    		XUartLite_Send(&AXI_UartLite1, "t0.txt=\"23.2\"", 13); // Funciona !! 12/06/20
//    		XUartLite_Send(&AXI_UartLite1, "\xFF\xFF\xFF", 8);
    		//XUartLite_SendBuffer(&AXI_UartLite1);
    		usleep(1000000); // 200msec

    		//XUartLite_SendByte(&AXI_UartLite,0xff);
  //  		XUartLite_SendByte(&AXI_UartLite1,SendBuffer[BUFFER_SIZE]);
  //  		XUartLite_SendByte(&AXI_UartLite1,SendBuffer[BUFFER_SIZE]);
  //  		XUartLite_SendByte(&AXI_UartLite1,SendBuffer[BUFFER_SIZE]);


    		//XUartLite_Send(&AXI_UartLite0, "ÿÿÿ", sizeof("ÿÿÿ"));
    		//XUartLite_Send(&AXI_UartLite0, "ÿÿÿ", sizeof("ÿÿÿ"));
    		//XUartLite_Send(&AXI_UartLite0, "ÿÿÿ", sizeof("ÿÿÿ"));
    		//XUartLite_Send(&AXI_UartLite0, 0xFF, 8);
    		//XUartLite_Send(&AXI_UartLite0, 0xFF, 8);

    	}

    	//----- AXI UART ----
//    	XUartLite_Send(&AXI_UartLite0, buffer, sizeof(buffer)); //JB
//    	usleep(200000); // 200msec

    	XUartLite_Recv(&AXI_UartLite0, RBuf, 8);
    	usleep(100000); // 100msec
    	XUartLite_Send(&AXI_UartLite1, RBuf, 8);
    	//if(RBuf == comp){XGpio_DiscreteWrite(&AXI_GPIO0, 1, 1);}else{XGpio_DiscreteWrite(&AXI_GPIO0, 1, 2);}
  //      for (int Index = 0; Index < 4; Index++)
  //      {  /*
  //          if (comp[Index] == RBuf[Index])
  //          {
  //          	XGpio_DiscreteWrite(&AXI_GPIO0, 1, 3);
  //          	usleep(500000); // 100msec
  //          }else{
  //          	XGpio_DiscreteWrite(&AXI_GPIO0, 1, 1);
 //           	usleep(500000); // 100msec
 //           }*/
 //           reSend[Index] = RBuf[Index];
 //       }
        //usleep(500000); // 100mse
        XUartLite_Send(&AXI_UartLite1, RBuf, 8);
        XUartLite_Send(&AXI_UartLite1, "\n", sizeof("\n"));
    	//delay(delay_time);
 //       if(reSend[0] == comp2[0]){
 //       	XGpio_DiscreteWrite(&AXI_GPIO0, 1, 2);
 //       }

//    	XUartLite_Send(&AXI_UartLite1, buffer2, sizeof(buffer2)); //JA
//    	usleep(200000); // 200msec
    	//delay(delay_time);











    }



    return 0;
}