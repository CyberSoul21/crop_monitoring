connect -url tcp:127.0.0.1:3121
targets -set -filter {jtag_cable_name =~ "Digilent Nexys4 210274663620A" && level==0} -index 0
fpga -file /home/javier/Documents/monitoreo_cultivo/04_servicio_local/02_procesador/02_microblaze_axi_Artix7/lcd_v2_9600/_ide/bitstream/microblaze_bd_wrapper_lcd.bit
configparams mdm-detect-bscan-mask 2
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
rst -system
after 3000
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
dow /home/javier/Documents/monitoreo_cultivo/04_servicio_local/02_procesador/02_microblaze_axi_Artix7/lcd_v2_9600/Debug/lcd_v2_9600.elf
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
con
