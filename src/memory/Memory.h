//
// Created by Steven Imle on 11/28/16.
//

#ifndef INC_4_MEMORY_H
#define INC_4_MEMORY_H


#include <cmath>
#include "../types_data.h"
#include "../util/number_functions.h"

const uint8_t MEM_ADDR_BIT_SIZE_TOTAL = sizeof(uint8_t) * 8;
const mem_addr MEM_SIZE_TOTAL = (mem_addr)(pow(2, MEM_ADDR_BIT_SIZE_TOTAL) - 1);

const uint8_t MEM_ADDR_SIZE_OPC = 6;  // Opcode
const uint8_t MEM_ADDR_SIZE_REG = 5;  // Register
const uint8_t MEM_ADDR_SIZE_IMM = 16; // Immediate
const uint8_t MEM_ADDR_SIZE_LAB = 16; // Label
const uint8_t MEM_ADDR_SIZE_ADD = 26; // Address

const uint8_t MEM_ADDR_BIT_START_INSTRUCTION = SIZE_DWORD - MEM_ADDR_SIZE_OPC;

const uint16_t MAX_VALUE_IMM = (uint16_t)std::pow(2, MEM_ADDR_SIZE_IMM);
const uint16_t MAX_VALUE_LAB = (uint16_t)std::pow(2, MEM_ADDR_SIZE_LAB);

const uint8_t MEM_REGIONS = 4;
const mem_addr MEM_SIZE_SECT = (mem_addr)(MEM_SIZE_TOTAL / MEM_REGIONS);

const mem_addr MEM_ADDR_MIN_USER_DATA = MEM_SIZE_SECT * 0;
const mem_addr MEM_ADDR_MIN_USER_TEXT = (mem_addr)roundToMultipleOf(MEM_SIZE_SECT * 1, 4);
const mem_addr MEM_ADDR_MIN_KERNEL_DATA = (mem_addr)roundToMultipleOf(MEM_SIZE_SECT * 2, 4);
const mem_addr MEM_ADDR_MIN_KERNEL_TEXT = (mem_addr)roundToMultipleOf(MEM_SIZE_SECT * 3, 4);

const mem_addr MEM_ADDR_MAX_USER_DATA = MEM_ADDR_MIN_USER_DATA + MEM_SIZE_SECT - 1;
const mem_addr MEM_ADDR_MAX_USER_TEXT = MEM_ADDR_MIN_USER_TEXT + MEM_SIZE_SECT - 1;
const mem_addr MEM_ADDR_MAX_KERNEL_DATA = MEM_ADDR_MIN_KERNEL_DATA + MEM_SIZE_SECT - 1;
const mem_addr MEM_ADDR_MAX_KERNEL_TEXT = MEM_SIZE_TOTAL;


class Memory {
private:
	mem_map memory;
public:
	static const uint8_t MEM_ADDR_BIT_SIZE_TOTAL;

	enum MEM_UNIT {
		SIZE_BIT = 1, SIZE_NYBBLE = 4, SIZE_BYTE = 8, SIZE_WORD = 16, SIZE_DWORD = 32
	};

	ins_value_t read(mem_addr address, MEM_UNIT size);

	void write(mem_addr address, uint32_t value);

	void write(mem_addr address, mem_byte byte);
};


#endif //INC_4_MEMORY_H
