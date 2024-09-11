//Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2020.1 (win64) Build 2902540 Wed May 27 19:54:49 MDT 2020
//Date        : Mon Aug 12 15:58:29 2024
//Host        : TX running 64-bit major release  (build 9200)
//Command     : generate_target system_wrapper.bd
//Design      : system_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module system_wrapper
   (gpio_tri_io);
  inout [1:0]gpio_tri_io;

  wire [0:0]gpio_tri_i_0;
  wire [1:1]gpio_tri_i_1;
  wire [0:0]gpio_tri_io_0;
  wire [1:1]gpio_tri_io_1;
  wire [0:0]gpio_tri_o_0;
  wire [1:1]gpio_tri_o_1;
  wire [0:0]gpio_tri_t_0;
  wire [1:1]gpio_tri_t_1;

  IOBUF gpio_tri_iobuf_0
       (.I(gpio_tri_o_0),
        .IO(gpio_tri_io[0]),
        .O(gpio_tri_i_0),
        .T(gpio_tri_t_0));
  IOBUF gpio_tri_iobuf_1
       (.I(gpio_tri_o_1),
        .IO(gpio_tri_io[1]),
        .O(gpio_tri_i_1),
        .T(gpio_tri_t_1));
  system system_i
       (.gpio_tri_i({gpio_tri_i_1,gpio_tri_i_0}),
        .gpio_tri_o({gpio_tri_o_1,gpio_tri_o_0}),
        .gpio_tri_t({gpio_tri_t_1,gpio_tri_t_0}));
endmodule
