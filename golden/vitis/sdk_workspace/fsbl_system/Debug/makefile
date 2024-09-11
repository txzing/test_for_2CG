#
# This file was created by Xilinx Vitis tool.
#


#
# tools
#

RM = rm -f
RMDIR = rm -rf



#
# variables
#

SDCARD_GEN = sdcard_gen
GENERATE_BIF = ::scw::generate_bif

XPFM_PATH = C:/Users/txzing/Desktop/test_for_2cg/golden/vitis/sdk_workspace/system_wrapper/export/system_wrapper/system_wrapper.xpfm
SYS_CONFIG = system_wrapper
DOMAINS = fsbl_domain
BIF_PATH = C:/Users/txzing/Desktop/test_for_2cg/golden/vitis/sdk_workspace/fsbl_system/Debug/system.bif

BITSTREAM_PATH = C:/Users/txzing/Desktop/test_for_2cg/golden/vitis/sdk_workspace/fsbl/_ide/bitstream/system_wrapper.bit
SD_FILES = --elf C:/Users/txzing/Desktop/test_for_2cg/golden/vitis/sdk_workspace/fsbl/Debug/fsbl.elf,psu_cortexa53_0

#
# primary build targets
#

all: package

package:
	-@echo Generating bif file for the system project
	generate_system_bif.bat 61643 ${XPFM_PATH} ${DOMAINS} ${BIF_PATH}
	${SDCARD_GEN} --xpfm ${XPFM_PATH} --sys_config ${SYS_CONFIG} --bif ${BIF_PATH} --bitstream ${BITSTREAM_PATH} ${SD_FILES}

clean:
	$(RMDIR) ./_sds
	${RMDIR} package
	${RM} system.bif

.PHONY: all package clean


