set_property SRC_FILE_INFO {cfile:/home/dorfell/Documents/Vitis_2019.2/socs_design/02_microblaze_axi/02_microblaze_axi.srcs/sources_1/bd/microblaze_bd/ip/microblaze_bd_clk_wiz_1_0/microblaze_bd_clk_wiz_1_0.xdc rfile:../../../02_microblaze_axi.srcs/sources_1/bd/microblaze_bd/ip/microblaze_bd_clk_wiz_1_0/microblaze_bd_clk_wiz_1_0.xdc id:1 order:EARLY scoped_inst:inst} [current_design]
current_instance inst
set_property src_info {type:SCOPED_XDC file:1 line:57 export:INPUT save:INPUT read:READ} [current_design]
set_input_jitter [get_clocks -of_objects [get_ports clk_in1]] 0.1
