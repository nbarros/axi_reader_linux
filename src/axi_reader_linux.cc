/*
 * Copyright (c) 2012 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>

#include "memregisters.h"
#include "memutils.h"


int main()
{
    printf("Starting the system to read the AXI slave registers.\n");


    // Map the whole memory bunch
    printf("Mapping the memory needed...\n");

    mem_dev regs;
    regs.base_addr = XPAR_MEMORY_MAPPER_0_S00_AXI_BASEADDR;
    regs.high_addr = XPAR_MEMORY_MAPPER_0_S00_AXI_HIGHADDR;
    regs.dev_id = 0;
    regs.n_regs = 20;
    regs.reg_offset = 4;

    void *mappedCmd = MemoryMapping(regs.base_addr,regs.high_addr);

    printf("Mapping completed...\n");

    printf("Sending a reset to clear up any lingering trash...\n");

    mWriteReg((u32)mappedCmd,10*REGISTER_OFFSET,0);

    sleep(1);
    printf("Reset sent. Now proceeding with device setup...\n");
    sleep(1);

    mWriteReg((u32)mappedCmd,10*REGISTER_OFFSET,1);

    const unsigned int nRegisters = 5;
    unsigned int i;
    uint32_t data[nRegisters];


    // Go into the loop and start reading.
    int counter = 100000;
    while(counter > 1) {
        for (i = 0; i < nRegisters; ++i) {
            	data[i] = mReadReg((u32)mappedCmd, i*REGISTER_OFFSET);
        }

		// print the readout contents:
		printf("Status : 0x%08X TS : 0x%08X 0x%08X PRE : 0x%08X 0x%08X \n",data[0],data[1],data[2],data[3],data[4]);
		sleep(1);
		counter--;
    }

    printf("Unmapping the registers...\n");
      munmap((void*)mappedCmd, regs.high_addr-regs.base_addr);
    printf("All done!\n");

    return 0;
}
