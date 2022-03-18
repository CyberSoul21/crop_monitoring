#!/bin/sh

# 
# Vivado(TM)
# runme.sh: a Vivado-generated Runs Script for UNIX
# Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
# 

if [ -z "$PATH" ]; then
  PATH=/usr/local/Xilinx_Vitis/Vitis/2019.2/bin:/usr/local/Xilinx_Vitis/Vivado/2019.2/ids_lite/ISE/bin/lin64:/usr/local/Xilinx_Vitis/Vivado/2019.2/bin
else
  PATH=/usr/local/Xilinx_Vitis/Vitis/2019.2/bin:/usr/local/Xilinx_Vitis/Vivado/2019.2/ids_lite/ISE/bin/lin64:/usr/local/Xilinx_Vitis/Vivado/2019.2/bin:$PATH
fi
export PATH

if [ -z "$LD_LIBRARY_PATH" ]; then
  LD_LIBRARY_PATH=
else
  LD_LIBRARY_PATH=:$LD_LIBRARY_PATH
fi
export LD_LIBRARY_PATH

HD_PWD='/home/dorfell/Documents/Vitis_2019.2/socs_design/02_microblaze_axi/02_microblaze_axi.runs/microblaze_bd_microblaze_0_0_synth_1'
cd "$HD_PWD"

HD_LOG=runme.log
/bin/touch $HD_LOG

ISEStep="./ISEWrap.sh"
EAStep()
{
     $ISEStep $HD_LOG "$@" >> $HD_LOG 2>&1
     if [ $? -ne 0 ]
     then
         exit
     fi
}

EAStep vivado -log microblaze_bd_microblaze_0_0.vds -m64 -product Vivado -mode batch -messageDb vivado.pb -notrace -source microblaze_bd_microblaze_0_0.tcl
