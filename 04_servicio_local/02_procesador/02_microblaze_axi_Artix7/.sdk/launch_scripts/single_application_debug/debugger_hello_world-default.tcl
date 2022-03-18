connect -url tcp:127.0.0.1:3121
targets -set -filter {jtag_cable_name =~ "Digilent Nexys4 210274663448A" && level==0} -index 0
fpga -file /home/dorfell/Documents/Vitis_2019.2/socs_design/02_microblaze_axi/hello_world/_ide/bitstream/microblaze_bd_wrapper.bit
configparams mdm-detect-bscan-mask 2
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
rst -system
after 3000
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
dow /home/dorfell/Documents/Vitis_2019.2/socs_design/02_microblaze_axi/hello_world/Debug/hello_world.elf
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
con
