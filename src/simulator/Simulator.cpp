//
// Created by Steven Imle on 11/28/16.
//

#include "Simulator.h"

void Simulator::setMode(SIM_MODE mode) {
	this->mode = mode;
}

Simulator::Simulator(Memory *mem, MemoryLoader *ml) {
	this->mem = mem;
	this->ml = ml;

	this->user_mode = false;
	this->mode = MODE_RUN;
	this->pc = 0;
}

ERROR_CODE Simulator::run(std::string file_path) {
	this->ml->loadFileIntoMemory(file_path, this->mem);

	return NO_ERROR;
}

ERROR_CODE Simulator::loopPre() {
	return NO_ERROR;
}

ERROR_CODE Simulator::loopBody() {
	return NO_ERROR;
}

ERROR_CODE Simulator::loopPost() {
	return NO_ERROR;
}
