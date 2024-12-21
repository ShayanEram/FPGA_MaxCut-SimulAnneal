# MaxCut_SimulatedAnnealing_FPGA

## Making the project

### Creating the IP on VIVADO HLS
1. Create a .cpp file, name it example.cpp
2. Create another .cpp file, name it example_test.cpp
3. Create a new project on VIVADO HLS
4. Add the previously created design source file by clicking on Add Files and pointing to the file example.cpp, then click Next
5. Add the previously created testbench file by clicking on Add Files and pointing to the file example_test.cpp, then click Next
6. Select the appropriate chip by choosing xc7z020clg400-1. Then click Finish.
7. Save your work and Click on Run C Synthesis
8. Click on Export RTL. Go to configuration and set Version to 0.0.0. Then click OK

### Integration of IP and Hardware Design
1. Launch VIVADO. Create a new project. Choose RTL Project, without specifying the source. Then choose the `PYNQ-Z2` board.
2. Create a new Block Design, add the Zynq IP, click Run Block Automation, and click OK.
3. Add the AXI Direct Memory Access IP to the design, and name it DMA. The DMA is the component for controlling the data flow for read and write operations between the memory (in this application, PS DRAM) and the AXI Stream interface through the read and write channels.
4. DMA Configuration: <br>
   a. Double-click on the component and uncheck the Enable Scatter Gather Engine box because PYNQ does not support this feature. <br>
   b. Set the DMA buffer length size to 14 bits to maximize the size of each packet to be transferred (Width of Buffer Length Register = 14 bits). <br>
   c. Set the address width to 32-bit (Address Width = 32-bit) since the DMA will be connected to the PS of the ZYNQ which itself operates at 32-bit. <br>
   d. Enable read and write on DMA by checking the Enable Read Channel and Enable Write Channel boxes. <br>
   e. Set the read channel memory map data width to 32 bits (Memory Map Data Width = 32-bit). <br>
   f. Leave the write channel memory map data width to Auto. <br>
   g. Set the stream data width (Stream Data Width) to 8 bits. <br>
   h. Ensure that the Allow unaligned transfers box is not checked, then click OK. <br>
   h.maxburst to 16 bits. <br>
5. Connect the DMA by clicking on Run Connection Automation.
6. Double-click on the ZYNQ IP. Go to PS-PL configuration > HP Slave AXI Interface, enable X AXI HP0 and X AXI HP2, and ensure the data width is set to 64-bit. Then click OK.
7. Additional ports will be added to the ZYNQ, click on Run Connection Automation to connect them. Select S_AXI_HP0 and for Master Interface choose /DMA/M_AXI_MM2S, while for S_AXI_HP2 choose /DMA/M_AXI_S2MM. Click OK.
8. Go to Flow Manager > PROJECT MANAGER > Settings > Project Settings > IP > Repository and click the “+” sign to point to the previously created IP directory under … \HLS_EXMP\HLS_EXMP\solution1\impl\ip.
9. Go to the diagram and add the IP we just created "Example".
10. Click on Run block automation for the AXI control interface ports (s_axi_control), the clock (ap_clk), and the reset (ap_rst_n) of the IP to be automatically connected to the rest of the design.
11. Manually connect the A and B ports of your IP respectively to the M_AXIS_MM2S and S_AXIS_S2MM ports of the axi_dma.
12. Validate your design. Generate the HDL wrapper, Output Products, then the Bitstream.

### Software Development
1. Install and connect the PYNQ board.
2. Access Jupyter Notebook through your browser at http://192.168.2.99.
3. Create a new folder and name it EXMP_HLS.
4. Locate the Bitstream file already created by VIVADO and add it to the folder you just created. Then rename this file to design_1.bit.
5. Locate the design_1.hwh file and add it to the folder.
6. Create a new notebook by clicking on New > Notebook: Python 3. Enter it and rename it to Example_HLS.
7. Identify the HLS IP and check the status of the registers. Upon startup, they will indicate that the IP is idle.
8. Write 0x81 in the control register as follows. This will start the DMA and enable auto restart.

## Running the project on FPGA
1. Connect the FPGA to the PC and open [http://192.168.2.99](http://192.168.2.99).
2. Write the input data in Jupyter Notebook.
3. Receive the data from FPGA.