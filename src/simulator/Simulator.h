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

	Memory *mem;
	ScoreBoard *sb;
	RegisterFile *rf;
	MemoryLoader *ml;

	virtual ERROR_CODE loopPre();

	virtual ERROR_CODE loopBody();

	virtual ERROR_CODE loopPost();

public:
	Simulator(Memory *mem, MemoryLoader *ml);

	ERROR_CODE run(std::string file_path);

	void setMode(SIM_MODE mode);
};


#endif //INC_4_SIMULATOR_H
