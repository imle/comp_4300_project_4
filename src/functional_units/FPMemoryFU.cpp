//
// Created by Steven Imle on 11/29/16.
//

#include <cstdlib>
#include "FPMemoryFU.h"
#include "../error_codes.h"

int32_t FPMemoryFU::performOperation(uint8_t alu_opc, int32_t operand_a, int32_t operand_b) {
	if (alu_opc == OPC_SD) {
		this->mem->write((uint32_t)operand_a, (uint32_t)operand_b);
	}
	else if (alu_opc == MFU_LOAD) {
		return this->mem->read((uint32_t)operand_a, SIZE_DWORD);
	}
	else {
		printError(IFU_INVALID_OPC_TYPE);
		exit(IFU_INVALID_OPC_TYPE);
	}

	return 1;
}

uint8_t FPMemoryFU::getFUOpc(opcode opc) {
	switch (opc) {
		case OPC_SD:
			return MFU_STORE;
		case OPC_LD:
			return MFU_LOAD;
		default:
			printError(IFU_INVALID_OPC_TYPE);
			exit(IFU_INVALID_OPC_TYPE);
	}
}

bool FPMemoryFU::getFlag(uint8_t flag) {
	return false;
}

FPMemoryFU::FPMemoryFU(Memory *mem) : mem(mem) {
	this->fu_type = FU_MEM;
	this->cycles_needed = 2;
}
