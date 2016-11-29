//
// Created by Steven Imle on 11/27/16.
//

#ifndef INC_4_TYPES_DATA_H
#define INC_4_TYPES_DATA_H

#include <cstdint>
#include <map>
#include "opcode_data.h"

typedef uint8_t reg_addr;
typedef uint32_t reg_value;

typedef uint32_t ins_value_t;
typedef int16_t immediate;

struct instruction {
	ins_value_t value;
	opcode opc;
	reg_addr rd;
	reg_addr rs;
	reg_addr rt;
	immediate imm;
};

typedef uint32_t mem_addr;
typedef uint8_t mem_byte;

typedef mem_addr prog_counter;

typedef std::map<mem_addr, mem_byte> mem_map;

enum SIM_MODE {
	MODE_RUN, MODE_DEBUG
};

enum MEM_UNIT {
	SIZE_BIT = 1, SIZE_NYBBLE = 4, SIZE_BYTE = 8, SIZE_WORD = 16, SIZE_DWORD = 32
};


#endif //INC_4_TYPES_DATA_H
