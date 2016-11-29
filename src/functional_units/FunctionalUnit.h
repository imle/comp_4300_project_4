//
// Created by Steven Imle on 11/28/16.
//

#ifndef INC_1_FUNCTIONALUNIT_H
#define INC_1_FUNCTIONALUNIT_H


#include <cstdint>
#include "../opcode_data.h"

class FunctionalUnit {
protected:
	OPC_FU_TYPE fu_type;

	uint8_t cycles_needed;

public:
	OPC_FU_TYPE getFUType();

	uint8_t getCyclesNeeded(void);

	virtual int32_t performOperation(uint8_t alu_opc, int32_t operand_a, int32_t operand_b) = 0;

	virtual bool getFlag(uint8_t flag) = 0;
};


#endif //INC_1_FUNCTIONALUNIT_H
