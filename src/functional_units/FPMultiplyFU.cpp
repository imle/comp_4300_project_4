//
// Created by Steven Imle on 11/29/16.
//

#include <cstdlib>
#include "FPMultiplyFU.h"
#include "../error_codes.h"

int32_t FPMultiplyFU::performOperation(uint8_t alu_opc, int32_t operand_a, int32_t operand_b) {
	float output_f, operand_a_f, operand_b_f;
	memcpy(&operand_a_f, &operand_a, sizeof(operand_a));
	memcpy(&operand_b_f, &operand_b, sizeof(operand_b));

	if (alu_opc != 0) {
		printError(IFU_INVALID_OPC_TYPE);
		exit(IFU_INVALID_OPC_TYPE);
	}

	output_f = operand_a_f * operand_b_f;

	int32_t output;
	memcpy(&output, &output_f, sizeof(output_f));
	return output;
}

uint8_t FPMultiplyFU::getFUOpc(opcode opc) {
	return 0; // Only does multiplication
}

bool FPMultiplyFU::getFlag(uint8_t flag) {
	return false;
}

FPMultiplyFU::FPMultiplyFU() {
	this->fu_type = FU_MULT;
	this->cycles_needed = 6;
}
