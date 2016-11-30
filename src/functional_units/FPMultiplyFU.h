//
// Created by Steven Imle on 11/29/16.
//

#ifndef INC_4_FPMULTFU_H
#define INC_4_FPMULTFU_H


#include "FunctionalUnit.h"

class FPMultiplyFU : public FunctionalUnit {
public:
	FPMultiplyFU();

	int32_t performOperation(uint8_t alu_opc, int32_t operand_a, int32_t operand_b) override;

	uint8_t getFUOpc(opcode opc) override;

	bool getFlag(uint8_t flag) override;
};


#endif //INC_4_FPMULTFU_H
