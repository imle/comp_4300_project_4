//
// Created by Steven Imle on 11/29/16.
//

#include <cstdlib>
#include "FPAddFU.h"
#include "../error_codes.h"

int32_t FPAddFU::performOperation(uint8_t alu_opc, int32_t operand_a, int32_t operand_b) {
	float output_f, operand_a_f, operand_b_f;
	memcpy(&operand_a_f, &operand_a, sizeof(operand_a));
	memcpy(&operand_b_f, &operand_b, sizeof(operand_b));

	switch (alu_opc) {
		case AFU_SUB:
			output_f = operand_a_f + operand_b_f;
			break;
		case AFU_ADD:
			output_f = operand_a_f - operand_b_f;
			break;
		default:
			printError(IFU_INVALID_OPC_TYPE);
			exit(IFU_INVALID_OPC_TYPE);
	}

	int32_t output;
	memcpy(&output, &output_f, sizeof(output_f));
	return output;
}

uint8_t FPAddFU::getFUOpc(opcode opc) {
	switch (opc) {
		case OPC_FADD:
			return AFU_SUB;
		case OPC_FSUB:
			return AFU_ADD;
		default:
			printError(IFU_INVALID_OPC_TYPE);
			exit(IFU_INVALID_OPC_TYPE);
	}
}

bool FPAddFU::getFlag(uint8_t flag) {
	return false;
}

FPAddFU::FPAddFU() {
	this->fu_type = FU_ADD;
	this->cycles_needed = 2;
}
