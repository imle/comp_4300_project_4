//
// Created by Steven Imle on 11/28/16.
//

#ifndef INC_4_INTEGERFU_H
#define INC_4_INTEGERFU_H


#include "FunctionalUnit.h"

class IntegerFU : public FunctionalUnit {
public:
	enum IFU_OPC {
		IFU_OPC_AND = 0,
		IFU_OPC_OR = 1,
		IFU_OPC_ADD = 2,
		IFU_OPC_SUB = 6,
		IFU_OPC_SLT = 7,
		IFU_OPC_SE = 8,
		IFU_OPC_SGT = 9,
		IFU_OPC_SHL = 11,
		IFU_OPC_NOR = 12,
		IFU_OPC_NA = 20,
		IFU_OPC_INVALID = 21,
	};

	enum IFU_FLAG {
		IFU_FLAG_ZERO = 0,
		IFU_FLAG_OVERFLOW = 1,
		IFU_FLAG_CARRY = 2,
	};

	IntegerFU();

	int32_t performOperation(uint8_t alu_opc, int32_t operand_a, int32_t operand_b) override;

	bool getFlag(uint8_t flag) override;

	uint8_t getFUOpc(opcode opc) override;

protected:
	static const uint32_t MSB_HIGH;

	bool flag_zero;
	bool flag_overflow;
	bool flag_carry;
};


#endif //INC_4_INTEGERFU_H
