//
// Created by Steven Imle on 11/28/16.
//

#include <iostream>
#include <iomanip>
#include "Memory.h"

const uint8_t Memory::MEM_ADDR_BIT_SIZE_TOTAL = sizeof(mem_byte) * 8;

void printMemoryAddress(mem_addr addr) {
	std::cout << std::setfill('0') << std::setw(sizeof(mem_addr) * 2) << std::hex << addr;
}

void printMemoryValue(ins_value_t value) {
	std::cout << std::setfill('0')
	          << std::setw(2) << std::hex << (value >> 24) << " "
	          << std::setw(2) << std::hex << (value << 8 >> 24) << " "
	          << std::setw(2) << std::hex << (value << 16 >> 24) << " "
	          << std::setw(2) << std::hex << (value << 24 >> 24) << " "
	          << "(" << std::dec << value << ")";
}

ins_value_t Memory::read(mem_addr address, MEM_UNIT size) {
	ins_value_t temp = 0;

	if (size == SIZE_BIT)
		return this->memory[address] >> (Memory::MEM_ADDR_BIT_SIZE_TOTAL - SIZE_BIT);

	if (size == SIZE_NYBBLE)
		return this->memory[address] >> (Memory::MEM_ADDR_BIT_SIZE_TOTAL - SIZE_NYBBLE);

	for (uint8_t i = 0; i < size / SIZE_BYTE; i++) {
		temp <<= SIZE_BYTE;
		temp |= this->memory[address + i];
	}

	return temp;
}

void Memory::write(mem_addr address, uint32_t value) {
	this->write(address, (uint8_t)(value >> 24));
	this->write(address + 1, (uint8_t)(value << 8 >> 24));
	this->write(address + 2, (uint8_t)(value << 16 >> 24));
	this->write(address + 3, (uint8_t)(value << 24 >> 24));
}

void Memory::write(mem_addr address, mem_byte byte) {
	this->memory[address] = byte;

}

void Memory::print() {
	ins_value_t temp;

	for (mem_map::iterator iter = this->memory.begin(); iter != this->memory.end();) {
		mem_addr k = iter->first;

		std::cout << "0x";
		printMemoryAddress(k);

		temp = this->memory[k];

		mem_addr prev = k;
		temp <<= MEM_ADDR_BIT_SIZE_TOTAL;
		iter++;
		k = iter->first;

		if (prev + 1 == k) {
			temp |= this->memory[k];

			prev = k;
			temp <<= MEM_ADDR_BIT_SIZE_TOTAL;
			iter++;
			k = iter->first;

			if (prev + 1 == k) {
				temp |= this->memory[k];

				prev = k;
				temp <<= MEM_ADDR_BIT_SIZE_TOTAL;
				iter++;
				k = iter->first;

				if (prev + 1 == k) {
					temp |= this->memory[k];

					iter++;
				}
			}
		}

		std::cout << ": ";
		printMemoryValue(temp);
		std::cout << std::endl;
	}
}
