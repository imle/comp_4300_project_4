//
// Created by Steven Imle on 11/28/16.
//

#ifndef INC_4_SIMULATOR_H
#define INC_4_SIMULATOR_H


#include "../types_data.h"
#include "../memory/Memory.h"
#include "../score_board/ScoreBoard.h"
#include "../error_codes.h"
#include "../memory/MemoryLoader.h"

class Simulator {
protected:
	bool user_mode;
	SIM_MODE mode;
	prog_counter pc;

	uint32_t nop_count;
	uint32_t instruction_count;
	uint32_t cycle_count;

	Memory *mem;
	MemoryLoader *ml;
	ScoreBoard *sb;
	RegisterFile *rf;

	instruction decodeInstruction(ins_value_t inst);

	void issueInstruction();

public:
	Simulator(Memory *mem, MemoryLoader *ml, ScoreBoard *sb, RegisterFile *rf);

	ERROR_CODE run(std::string file_path);

	void setMode(SIM_MODE mode);

	ins_value_t getNBitsFrom(ins_value_t ins, uint8_t start, uint8_t length);

	ERROR_CODE systemCall(ins_value_t code);
};


#endif //INC_4_SIMULATOR_H
