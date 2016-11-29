//
// Created by Steven Imle on 11/27/16.
//

#include <cstdlib>
#include "RegisterFile.h"
#include "../error_codes.h"

const std::map<std::string, reg_addr> RegisterFile::REGISTER_NAME_MAP = {
		{ "zero", 0 }, { "at", 1 }, { "v0", 2 }, { "v1", 3 }, { "a0", 4 }, { "a1", 5 }, { "a2", 6 },
		{ "a3", 7 }, { "t0", 8 }, { "t1", 9 }, { "t2", 10 }, { "t3", 11 }, { "t4", 12 }, { "t5", 13 },
		{ "t6", 14 }, { "t7", 15 }, { "s0", 16 }, { "s1", 17 }, { "s2", 18 }, { "s3", 19 }, { "s4", 20 },
		{ "s5", 21 }, { "s6", 22 }, { "s7", 23 }, { "t8", 24 }, { "t9", 25 }, { "k0", 26 }, { "k1", 27 },
		{ "gp", 28 }, { "sp", 29 }, { "s8", 30 }, { "ra", 31 }, { "fp", 30 }
};

const char *RegisterFile::REGISTER_NAME_BASE = "$";

reg_value RegisterFile::read(reg_addr addr) {
	if (addr >= MAX_ADDRESS_FP) {
		printError(RS_INVALID_REGISTER_ADDRESS);
		exit(RS_INVALID_REGISTER_ADDRESS);
	}

	return this->values[addr];
}

void RegisterFile::write(reg_addr addr, reg_value value) {
	if (addr >= MAX_ADDRESS_FP) {
		printError(RS_INVALID_REGISTER_ADDRESS);
		exit(RS_INVALID_REGISTER_ADDRESS);
	}

	this->values[addr] = value;
}

reg_addr RegisterFile::registerNameToAddress(std::string reg_name) {
	if (std::strncmp(REGISTER_NAME_BASE, reg_name.c_str(), strlen(REGISTER_NAME_BASE)) != 0) {
		printError(RS_INVALID_REGISTER_ADDRESS);
		exit(RS_INVALID_REGISTER_ADDRESS);
	}

	reg_addr addr;

	if (std::isdigit(reg_name[1]))
		addr = (reg_addr)std::stoi(reg_name.substr(1));
	else if (reg_name[1] == 'f' && reg_name[2] != 'p')
		addr = (reg_addr)std::stoi(reg_name.substr(2)) + MIN_ADDRESS_FP;
	else
		addr = REGISTER_NAME_MAP.at(reg_name.substr(1));

	return addr;
}
