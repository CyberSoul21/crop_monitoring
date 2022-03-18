## This file defines the SoC pins for MicroBlaze with AXI
## FPGA: XC7A100T-CGS324

# Clock
set_property -dict { PACKAGE_PIN E3    IOSTANDARD LVCMOS33 } [get_ports { clk }];


# CPU Reset
set_property -dict { PACKAGE_PIN C12   IOSTANDARD LVCMOS33 } [get_ports { reset }];


##Switches
set_property -dict { PACKAGE_PIN U9    IOSTANDARD LVCMOS33 } [get_ports { pushs_tri_i[0] }]; #IO_L19N_T3_VREF_35 Sch=sw[0]
set_property -dict { PACKAGE_PIN U8    IOSTANDARD LVCMOS33 } [get_ports { pushs_tri_i[1] }]; #IO_L24P_T3_34 Sch=sw[1]
set_property -dict { PACKAGE_PIN R7    IOSTANDARD LVCMOS33 } [get_ports { pushs_tri_i[2] }]; #IO_L4N_T0_34 Sch=sw[2]
set_property -dict { PACKAGE_PIN R6    IOSTANDARD LVCMOS33 } [get_ports { pushs_tri_i[3] }]; #IO_L9P_T1_DQS_34 Sch=sw[3]


##LEDs
set_property -dict { PACKAGE_PIN T8    IOSTANDARD LVCMOS33 } [get_ports { leds_tri_o[0] }]; #IO_L23P_T3_35 Sch=led[0]
set_property -dict { PACKAGE_PIN V9    IOSTANDARD LVCMOS33 } [get_ports { leds_tri_o[1] }]; #IO_L23N_T3_35 Sch=led[1]
set_property -dict { PACKAGE_PIN R8    IOSTANDARD LVCMOS33 } [get_ports { leds_tri_o[2] }]; #IO_0_35 Sch=led[2]
set_property -dict { PACKAGE_PIN T6    IOSTANDARD LVCMOS33 } [get_ports { leds_tri_o[3] }]; #IO_L3N_T0_DQS_AD1N_35 Sch=led[3]


## USB RS232 UART0
set_property -dict { PACKAGE_PIN V11    IOSTANDARD LVCMOS33     } [get_ports { uart_txd }]; #IO_L15P_T2_DQS_13 Sch=jb_p[1]		 
set_property -dict { PACKAGE_PIN V15    IOSTANDARD LVCMOS33     } [get_ports { uart_rxd }]; #IO_L15N_T2_DQS_13 Sch=jb_n[1]  

## USB RS232 UART1
set_property -dict { PACKAGE_PIN D17    IOSTANDARD LVCMOS33     } [get_ports { uart_rtl_0_txd }]; #IO_L15P_T2_DQS_13 Sch=jb_p[1]		 
set_property -dict { PACKAGE_PIN E17    IOSTANDARD LVCMOS33     } [get_ports { uart_rtl_0_rxd }]; #IO_L15N_T2_DQS_13 Sch=jb_n[1]  

 