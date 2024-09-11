set_property BITSTREAM.GENERAL.COMPRESS TRUE [current_design]

#set_property PACKAGE_PIN AG13 [get_ports uart_0_rxd]
#set_property IOSTANDARD LVCMOS33 [get_ports uart_0_rxd]
#set_property PACKAGE_PIN W11 [get_ports uart_0_txd]
#set_property IOSTANDARD LVCMOS33 [get_ports uart_0_txd]
#set_property PACKAGE_PIN AH13 [get_ports {uart_0_txen[0]}]
#set_property IOSTANDARD LVCMOS33 [get_ports {uart_0_txen[0]}]

# eeprom
## eeprom sda
set_property PACKAGE_PIN W14 [get_ports i2c_0_sda_io]
set_property IOSTANDARD LVCMOS33 [get_ports i2c_0_sda_io]
## eeprom scl
set_property PACKAGE_PIN AB15 [get_ports i2c_0_scl_io]
set_property IOSTANDARD LVCMOS33 [get_ports i2c_0_scl_io]
## eeprom wp: (lo: wr; hi: ro)
set_property PACKAGE_PIN AB14 [get_ports {gpo_0[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpo_0[0]}]


# relay_ctrl
set_property PACKAGE_PIN AG11 [get_ports {gpio_tri_io[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio_tri_io[0]}]

# PL_LOCK_LED
set_property PACKAGE_PIN AF11 [get_ports {gpio_tri_io[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio_tri_io[1]}]


