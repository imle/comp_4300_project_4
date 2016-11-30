//
// Created by Steven Imle on 11/27/16.
//

#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <iostream>
#include "RegisterFile.h"
#include "../error_codes.h"
#include "../util/Color.h"

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

	if (addr == 0) {
		printError(RS_INVALID_REGISTER_ADDRESS);
		exit(RS_INVALID_REGISTER_ADDRESS);
	}

	this->values[addr] = value;
	this->register_changes[addr] = true;
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

std::string formatRegisterValue(ins_value_t value) {
	std::ostringstream stream;

	stream << std::setfill('0')
	       << std::setw(2) << std::hex << (value >> 24) << " "
	       << std::setw(2) << std::hex << (value << 8 >> 24) << " "
	       << std::setw(2) << std::hex << (value << 16 >> 24) << " "
	       << std::setw(2) << std::hex << (value << 24 >> 24);

	return stream.str();
}

std::string formatRegisterName(reg_addr reg) {
	std::ostringstream stream;

	stream << "$" << (uint16_t)reg << ":";

	return stream.str();
}

void RegisterFile::print() {
	uint8_t reg_per_line = 8;
	uint8_t reg_width = 5;
	uint8_t value_width = 12;
	uint8_t dash_count = reg_per_line * (reg_width + value_width);
	dash_count += (reg_per_line - 1) * 3;
	std::string dash_line = std::string(dash_count, '-');

	std::cout << std::endl << dash_line << std::endl;
	for (reg_addr i = 0; i < REGISTER_COUNT / reg_per_line; i++) {
		for (reg_addr j = 0; j < reg_per_line; j++) {
			std::cout << std::left << std::setw(reg_width) << std::setfill(' ')
			          << formatRegisterName(i + j * (REGISTER_COUNT / reg_per_line));
			if (this->register_changes[i + j * (REGISTER_COUNT / reg_per_line)]) {
				std::cout << Color::FG_RED;
			}
			std::cout << std::right << std::setw(value_width) << std::setfill(' ')
			          << formatRegisterValue(this->values[i + j * (REGISTER_COUNT / reg_per_line)])
			          << Color::FG_DEFAULT;

			if (j + 1 == reg_per_line) {
				std::cout << std::endl;
			}
			else {
				std::cout << " | ";
			}

			this->register_changes[i + j * (REGISTER_COUNT / reg_per_line)] = false;
		}
	}

	std::cout << dash_line << std::endl;
}
