//
// Created by Steven Imle on 11/28/16.
//

#include <cstdlib>
#include "IntegerFU.h"
#include "../error_codes.h"

const uint32_t IntegerFU::MSB_HIGH = 0x80000000;

int32_t IntegerFU::performOperation(uint8_t alu_opc, int32_t operand_a, int32_t operand_b) {
	int32_t value;

	this->flag_overflow = 0;
	this->flag_carry = 0;

	switch (alu_opc) {
		case IFU_OPC_AND:
			value = operand_a & operand_b;
			break;
		case IFU_OPC_OR:
			value = operand_a | operand_b;
			break;
		case IFU_OPC_ADD:
			value = operand_a + operand_b;

			if ((operand_b > 0) && (operand_a > UINT32_MAX - operand_b))
				this->flag_carry = 1;
			if ((operand_b < 0) && (operand_a < 0 - operand_b))
				this->flag_carry = 1;

			break;
		case IFU_OPC_SUB:
			value = operand_a - operand_b;

			if ((operand_b < 0) && (operand_a > UINT32_MAX + operand_b))
				this->flag_carry = 1;
			if ((operand_b > 0) && (operand_a < 0 + operand_b))
				this->flag_carry = 1;

			break;
		case IFU_OPC_SHL:
			value = operand_a << 16;
			break;
		case IFU_OPC_SLT:
			value = (uint8_t)(operand_a < operand_b);
			break;
		case IFU_OPC_SE:
			value = (uint8_t)(operand_a == operand_b);
			break;
		case IFU_OPC_SGT:
			value = (uint8_t)(operand_a > operand_b);
			break;
		case IFU_OPC_NOR:
			value = ~(operand_a | operand_b);
			break;
		case IFU_OPC_NA:
			value = 0;
			break;
		default:
			printError(IFU_INVALID_OPC_TYPE);
			exit(IFU_INVALID_OPC_TYPE);
	}

	if (alu_opc == IFU_OPC_ADD || alu_opc == IFU_OPC_SUB) {
		if ((value & MSB_HIGH) != MSB_HIGH) {
			this->flag_overflow = (operand_a & MSB_HIGH) == MSB_HIGH && (operand_b & MSB_HIGH) == MSB_HIGH;
		}
		else if ((value & MSB_HIGH) == MSB_HIGH) {
			this->flag_overflow = (operand_a & MSB_HIGH) == 0 && (operand_b & MSB_HIGH) == 0;
		}
	}

	this->flag_zero = value == 0;

	return value;
}

bool IntegerFU::getFlag(uint8_t flag) {
	switch (flag) {
		case IFU_FLAG_ZERO:
			return this->flag_zero;
		case IFU_FLAG_OVERFLOW:
			return this->flag_overflow;
		case IFU_FLAG_CARRY:
			return this->flag_carry;
		default:
			printError(IFU_INVALID_FLAG_TYPE);
			exit(IFU_INVALID_FLAG_TYPE);
	}
}

IntegerFU::IntegerFU() {
	this->fu_type = FU_INT;
	this->cycles_needed = 2;
}

uint8_t IntegerFU::getFUOpc(opcode opc) {
	switch (opc) {
		case OPC_SYSCALL:
		case OPC_NOP:
		case OPC_B:
		case OPC_BNE:
		case OPC_BEQ:
			return IFU_OPC_NA;
		case OPC_LB:
		case OPC_ADDI:
		case OPC_ADD:
			return IFU_OPC_ADD;
		case OPC_SUBI:
			return IFU_OPC_SUB;
		case OPC_SLT:
			return IFU_OPC_SLT;
		case OPC_LUI:
			return IFU_OPC_SHL;
		case OPC_ORI:
			return IFU_OPC_OR;
		default:
			printError(IFU_INVALID_OPC_TYPE);
			exit(IFU_INVALID_OPC_TYPE);
	}
}
