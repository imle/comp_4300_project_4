//
// Created by Steven Imle on 11/29/16.
//

#ifndef INC_4_MEMORYFU_H
#define INC_4_MEMORYFU_H


#include "FunctionalUnit.h"
#include "../memory/Memory.h"
#include "../register_file/RegisterFile.h"

class FPMemoryFU : public FunctionalUnit {
public:
	FPMemoryFU(Memory *mem);

	enum MEM_FU_OPC {
		MFU_LOAD,
		MFU_STORE,
	};

	int32_t performOperation(uint8_t alu_opc, int32_t operand_a, int32_t operand_b) override;

	uint8_t getFUOpc(opcode opc) override;

	bool getFlag(uint8_t flag) override;

protected:
	Memory *mem;
};


#endif //INC_4_MEMORYFU_H
