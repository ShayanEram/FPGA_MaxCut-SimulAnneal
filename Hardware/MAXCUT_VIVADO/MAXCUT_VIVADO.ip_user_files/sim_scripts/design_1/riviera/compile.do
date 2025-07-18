vlib work
vlib riviera

vlib riviera/xilinx_vip
vlib riviera/xpm
vlib riviera/lib_pkg_v1_0_2
vlib riviera/fifo_generator_v13_2_7
vlib riviera/lib_fifo_v1_0_16
vlib riviera/lib_srl_fifo_v1_0_2
vlib riviera/lib_cdc_v1_0_2
vlib riviera/axi_datamover_v5_1_28
vlib riviera/axi_sg_v4_1_15
vlib riviera/axi_dma_v7_1_27
vlib riviera/xil_defaultlib
vlib riviera/generic_baseblocks_v2_1_0
vlib riviera/axi_infrastructure_v1_1_0
vlib riviera/axi_register_slice_v2_1_26
vlib riviera/axi_data_fifo_v2_1_25
vlib riviera/axi_crossbar_v2_1_27
vlib riviera/axi_vip_v1_1_12
vlib riviera/processing_system7_vip_v1_0_14
vlib riviera/proc_sys_reset_v5_0_13
vlib riviera/axi_protocol_converter_v2_1_26
vlib riviera/axi_clock_converter_v2_1_25
vlib riviera/blk_mem_gen_v8_4_5
vlib riviera/axi_dwidth_converter_v2_1_26

vmap xilinx_vip riviera/xilinx_vip
vmap xpm riviera/xpm
vmap lib_pkg_v1_0_2 riviera/lib_pkg_v1_0_2
vmap fifo_generator_v13_2_7 riviera/fifo_generator_v13_2_7
vmap lib_fifo_v1_0_16 riviera/lib_fifo_v1_0_16
vmap lib_srl_fifo_v1_0_2 riviera/lib_srl_fifo_v1_0_2
vmap lib_cdc_v1_0_2 riviera/lib_cdc_v1_0_2
vmap axi_datamover_v5_1_28 riviera/axi_datamover_v5_1_28
vmap axi_sg_v4_1_15 riviera/axi_sg_v4_1_15
vmap axi_dma_v7_1_27 riviera/axi_dma_v7_1_27
vmap xil_defaultlib riviera/xil_defaultlib
vmap generic_baseblocks_v2_1_0 riviera/generic_baseblocks_v2_1_0
vmap axi_infrastructure_v1_1_0 riviera/axi_infrastructure_v1_1_0
vmap axi_register_slice_v2_1_26 riviera/axi_register_slice_v2_1_26
vmap axi_data_fifo_v2_1_25 riviera/axi_data_fifo_v2_1_25
vmap axi_crossbar_v2_1_27 riviera/axi_crossbar_v2_1_27
vmap axi_vip_v1_1_12 riviera/axi_vip_v1_1_12
vmap processing_system7_vip_v1_0_14 riviera/processing_system7_vip_v1_0_14
vmap proc_sys_reset_v5_0_13 riviera/proc_sys_reset_v5_0_13
vmap axi_protocol_converter_v2_1_26 riviera/axi_protocol_converter_v2_1_26
vmap axi_clock_converter_v2_1_25 riviera/axi_clock_converter_v2_1_25
vmap blk_mem_gen_v8_4_5 riviera/blk_mem_gen_v8_4_5
vmap axi_dwidth_converter_v2_1_26 riviera/axi_dwidth_converter_v2_1_26

vlog -work xilinx_vip  -sv2k12 "+incdir+C:/Logiciels/Xilinx/Vivado/2022.1/data/xilinx_vip/include" \
"C:/Logiciels/Xilinx/Vivado/2022.1/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
"C:/Logiciels/Xilinx/Vivado/2022.1/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
"C:/Logiciels/Xilinx/Vivado/2022.1/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
"C:/Logiciels/Xilinx/Vivado/2022.1/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
"C:/Logiciels/Xilinx/Vivado/2022.1/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
"C:/Logiciels/Xilinx/Vivado/2022.1/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
"C:/Logiciels/Xilinx/Vivado/2022.1/data/xilinx_vip/hdl/axi_vip_if.sv" \
"C:/Logiciels/Xilinx/Vivado/2022.1/data/xilinx_vip/hdl/clk_vip_if.sv" \
"C:/Logiciels/Xilinx/Vivado/2022.1/data/xilinx_vip/hdl/rst_vip_if.sv" \

vlog -work xpm  -sv2k12 "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/5765/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ip/design_1_maxCut_0_0/drivers/maxCut_v0_0/src" "+incdir+C:/Logiciels/Xilinx/Vivado/2022.1/data/xilinx_vip/include" \
"C:/Logiciels/Xilinx/Vivado/2022.1/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
"C:/Logiciels/Xilinx/Vivado/2022.1/data/ip/xpm/xpm_fifo/hdl/xpm_fifo.sv" \
"C:/Logiciels/Xilinx/Vivado/2022.1/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \

vcom -work xpm -93 \
"C:/Logiciels/Xilinx/Vivado/2022.1/data/ip/xpm/xpm_VCOMP.vhd" \

vcom -work lib_pkg_v1_0_2 -93 \
"../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/0513/hdl/lib_pkg_v1_0_rfs.vhd" \

vlog -work fifo_generator_v13_2_7  -v2k5 "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/5765/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ip/design_1_maxCut_0_0/drivers/maxCut_v0_0/src" "+incdir+C:/Logiciels/Xilinx/Vivado/2022.1/data/xilinx_vip/include" \
"../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/83df/simulation/fifo_generator_vlog_beh.v" \

vcom -work fifo_generator_v13_2_7 -93 \
"../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/83df/hdl/fifo_generator_v13_2_rfs.vhd" \

vlog -work fifo_generator_v13_2_7  -v2k5 "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/5765/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ip/design_1_maxCut_0_0/drivers/maxCut_v0_0/src" "+incdir+C:/Logiciels/Xilinx/Vivado/2022.1/data/xilinx_vip/include" \
"../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/83df/hdl/fifo_generator_v13_2_rfs.v" \

vcom -work lib_fifo_v1_0_16 -93 \
"../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/6c82/hdl/lib_fifo_v1_0_rfs.vhd" \

vcom -work lib_srl_fifo_v1_0_2 -93 \
"../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/51ce/hdl/lib_srl_fifo_v1_0_rfs.vhd" \

vcom -work lib_cdc_v1_0_2 -93 \
"../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/ef1e/hdl/lib_cdc_v1_0_rfs.vhd" \

vcom -work axi_datamover_v5_1_28 -93 \
"../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/1bb8/hdl/axi_datamover_v5_1_vh_rfs.vhd" \

vcom -work axi_sg_v4_1_15 -93 \
"../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/751a/hdl/axi_sg_v4_1_rfs.vhd" \

vcom -work axi_dma_v7_1_27 -93 \
"../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/7b0b/hdl/axi_dma_v7_1_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/design_1/ip/design_1_axi_dma_0_0/sim/design_1_axi_dma_0_0.vhd" \

vlog -work generic_baseblocks_v2_1_0  -v2k5 "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/5765/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ip/design_1_maxCut_0_0/drivers/maxCut_v0_0/src" "+incdir+C:/Logiciels/Xilinx/Vivado/2022.1/data/xilinx_vip/include" \
"../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/b752/hdl/generic_baseblocks_v2_1_vl_rfs.v" \

vlog -work axi_infrastructure_v1_1_0  -v2k5 "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/5765/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ip/design_1_maxCut_0_0/drivers/maxCut_v0_0/src" "+incdir+C:/Logiciels/Xilinx/Vivado/2022.1/data/xilinx_vip/include" \
"../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/ec67/hdl/axi_infrastructure_v1_1_vl_rfs.v" \

vlog -work axi_register_slice_v2_1_26  -v2k5 "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/5765/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ip/design_1_maxCut_0_0/drivers/maxCut_v0_0/src" "+incdir+C:/Logiciels/Xilinx/Vivado/2022.1/data/xilinx_vip/include" \
"../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/0a3f/hdl/axi_register_slice_v2_1_vl_rfs.v" \

vlog -work axi_data_fifo_v2_1_25  -v2k5 "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/5765/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ip/design_1_maxCut_0_0/drivers/maxCut_v0_0/src" "+incdir+C:/Logiciels/Xilinx/Vivado/2022.1/data/xilinx_vip/include" \
"../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/5390/hdl/axi_data_fifo_v2_1_vl_rfs.v" \

vlog -work axi_crossbar_v2_1_27  -v2k5 "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/5765/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ip/design_1_maxCut_0_0/drivers/maxCut_v0_0/src" "+incdir+C:/Logiciels/Xilinx/Vivado/2022.1/data/xilinx_vip/include" \
"../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/3fa0/hdl/axi_crossbar_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/5765/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ip/design_1_maxCut_0_0/drivers/maxCut_v0_0/src" "+incdir+C:/Logiciels/Xilinx/Vivado/2022.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_xbar_0/sim/design_1_xbar_0.v" \
"../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/408d/hdl/verilog/maxCut_AXILiteS_s_axi.v" \
"../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/408d/hdl/verilog/maxCut_currentSolbkb.v" \
"../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/408d/hdl/verilog/maxCut_matrix.v" \
"../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/408d/hdl/verilog/maxCut_mul_mul_8sfYi.v" \
"../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/408d/hdl/verilog/maxCut_sdiv_32ns_eOg.v" \
"../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/408d/hdl/verilog/maxCut_urem_29ns_cud.v" \
"../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/408d/hdl/verilog/maxCut_urem_32ns_dEe.v" \
"../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/408d/hdl/verilog/maxCut.v" \
"../../../bd/design_1/ip/design_1_maxCut_0_0/sim/design_1_maxCut_0_0.v" \

vlog -work axi_vip_v1_1_12  -sv2k12 "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/5765/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ip/design_1_maxCut_0_0/drivers/maxCut_v0_0/src" "+incdir+C:/Logiciels/Xilinx/Vivado/2022.1/data/xilinx_vip/include" \
"../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/1033/hdl/axi_vip_v1_1_vl_rfs.sv" \

vlog -work processing_system7_vip_v1_0_14  -sv2k12 "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/5765/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ip/design_1_maxCut_0_0/drivers/maxCut_v0_0/src" "+incdir+C:/Logiciels/Xilinx/Vivado/2022.1/data/xilinx_vip/include" \
"../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/5765/hdl/processing_system7_vip_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/5765/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ip/design_1_maxCut_0_0/drivers/maxCut_v0_0/src" "+incdir+C:/Logiciels/Xilinx/Vivado/2022.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_processing_system7_0_0/sim/design_1_processing_system7_0_0.v" \

vcom -work proc_sys_reset_v5_0_13 -93 \
"../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/8842/hdl/proc_sys_reset_v5_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/design_1/ip/design_1_rst_ps7_0_100M_0/sim/design_1_rst_ps7_0_100M_0.vhd" \

vlog -work axi_protocol_converter_v2_1_26  -v2k5 "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/5765/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ip/design_1_maxCut_0_0/drivers/maxCut_v0_0/src" "+incdir+C:/Logiciels/Xilinx/Vivado/2022.1/data/xilinx_vip/include" \
"../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/90c8/hdl/axi_protocol_converter_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/5765/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ip/design_1_maxCut_0_0/drivers/maxCut_v0_0/src" "+incdir+C:/Logiciels/Xilinx/Vivado/2022.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_auto_pc_0/sim/design_1_auto_pc_0.v" \
"../../../bd/design_1/ip/design_1_auto_pc_1/sim/design_1_auto_pc_1.v" \

vlog -work axi_clock_converter_v2_1_25  -v2k5 "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/5765/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ip/design_1_maxCut_0_0/drivers/maxCut_v0_0/src" "+incdir+C:/Logiciels/Xilinx/Vivado/2022.1/data/xilinx_vip/include" \
"../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/e893/hdl/axi_clock_converter_v2_1_vl_rfs.v" \

vlog -work blk_mem_gen_v8_4_5  -v2k5 "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/5765/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ip/design_1_maxCut_0_0/drivers/maxCut_v0_0/src" "+incdir+C:/Logiciels/Xilinx/Vivado/2022.1/data/xilinx_vip/include" \
"../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/25a8/simulation/blk_mem_gen_v8_4.v" \

vlog -work axi_dwidth_converter_v2_1_26  -v2k5 "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/5765/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ip/design_1_maxCut_0_0/drivers/maxCut_v0_0/src" "+incdir+C:/Logiciels/Xilinx/Vivado/2022.1/data/xilinx_vip/include" \
"../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/b3c7/hdl/axi_dwidth_converter_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ipshared/5765/hdl" "+incdir+../../../../MAXCUT_VIVADO.gen/sources_1/bd/design_1/ip/design_1_maxCut_0_0/drivers/maxCut_v0_0/src" "+incdir+C:/Logiciels/Xilinx/Vivado/2022.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_auto_us_0/sim/design_1_auto_us_0.v" \
"../../../bd/design_1/ip/design_1_auto_pc_2/sim/design_1_auto_pc_2.v" \
"../../../bd/design_1/ip/design_1_auto_us_1/sim/design_1_auto_us_1.v" \
"../../../bd/design_1/sim/design_1.v" \

vlog -work xil_defaultlib \
"glbl.v"

