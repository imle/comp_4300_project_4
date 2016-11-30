//
// Created by Steven Imle on 11/28/16.
//

#include <iostream>
#include "Simulator.h"
#include "../functional_units/IntegerFU.h"
#include "../functional_units/FPAddFU.h"
#include "../functional_units/FPMemoryFU.h"
#include "../functional_units/FPMultiplyFU.h"

void Simulator::setMode(SIM_MODE mode) {
	this->mode = mode;
}

Simulator::Simulator(Memory *mem, MemoryLoader *ml, ScoreBoard *sb, RegisterFile *rf)
		: mem(mem), ml(ml), sb(sb), rf(rf) {
	this->user_mode = false;
	this->mode = MODE_RUN;
	this->pc = MEM_ADDR_MIN_USER_TEXT;

	this->sb->registerFunctionalUnit(new IntegerFU());
	this->sb->registerFunctionalUnit(new IntegerFU());
	this->sb->registerFunctionalUnit(new FPAddFU());
	this->sb->registerFunctionalUnit(new FPMultiplyFU());
	this->sb->registerFunctionalUnit(new FPMemoryFU(this->mem));
}

ERROR_CODE Simulator::run(std::string file_path) {
	this->nop_count = 0;
	this->instruction_count = 0;
	this->cycle_count = 0;

	ERROR_CODE result = this->ml->loadFileIntoMemory(file_path, this->mem);

	if (result != NO_ERROR)
		return result;

	if (this->mode == MODE_DEBUG) {
		this->mem->print();
	}

	this->user_mode = true;

	while (this->user_mode || (!this->user_mode && !this->sb->allIdle())) {
		std::map<FunctionalUnit *, instruction> finished = this->sb->write();

		std::map<FunctionalUnit *, instruction>::iterator iter;
		for (iter = finished.begin(); iter != finished.end(); iter++) {
			instruction &ins = iter->second;

			reg_value rd1 = this->rf->read(ins.rs);
			reg_value rd2 = this->rf->read(ins.rt);

			if (this->mode == MODE_DEBUG) {
				std::cout << OPC_STRINGS[ins.opc] << std::endl;
			}

			bool reg_equal = rd1 == rd2;

			if ((ins.opc == OPC_BNE && !reg_equal) || (ins.opc == OPC_BEQ && reg_equal)) {
				this->pc = ins.pc + ((uint32_t)ins.imm << 2);
				continue;
			}

			if (ins.opc == OPC_SYSCALL) {
				this->systemCall(rd1, this->user_mode);

				this->user_mode = !this->user_mode;
			}

			if (OPC_FU[ins.opc] == FU_MEM) {
				rd1 += ins.imm;
			}

			uint32_t alu_value = std::get<5>(OPC_CONTROL_SIGNALS[ins.opc]) ? (uint32_t)ins.imm : rd2;
			uint8_t operation = (iter->first)->getFUOpc(ins.opc);

			uint32_t value = (iter->first)->performOperation(operation, rd1, alu_value);

			if (OPC_FU[ins.opc] == FU_INT) {
				if (std::get<0>(OPC_CONTROL_SIGNALS[ins.opc])) {
					this->rf->write(ins.rd, value);
				}

				if (std::get<3>(OPC_CONTROL_SIGNALS[ins.opc])) {
					this->mem->write(value, rd2);
				}

				if (std::get<4>(OPC_CONTROL_SIGNALS[ins.opc]) && std::get<1>(OPC_CONTROL_SIGNALS[ins.opc])) {
					this->rf->write(ins.rd, this->mem->read(value, SIZE_BYTE));
				}
			}

			if (OPC_FU[ins.opc] == FU_ADD || OPC_FU[ins.opc] == FU_MULT || OPC_FU[ins.opc] == FU_MEM) {
				this->rf->write(ins.rd, value);
			}
		}

		this->sb->read();

		this->sb->advance();

		this->issueInstruction();
	}

	if (this->mode == MODE_DEBUG) {
		this->mem->print();
	}

	return NO_ERROR;
}

void Simulator::issueInstruction() {
	ins_value_t value = this->mem->read(this->pc, SIZE_DWORD);
	instruction ins = this->decodeInstruction(value);

	this->cycle_count++;

	if (ins.opc == OPC_NOP) {
		this->nop_count++;
		this->instruction_count++;
		this->pc += sizeof(SIZE_DWORD);

		return;
	}

	if (ins.opc == OPC_B) {
		this->instruction_count++;
		this->pc = ins.addr | (this->pc >> 26 << 26);

		return;
	}

	FunctionalUnit *fu = this->sb->issue(ins);

	if (fu != nullptr) {
		this->pc += sizeof(SIZE_DWORD);

		this->instruction_count++;
	}
}

ins_value_t Simulator::getNBitsFrom(ins_value_t ins, uint8_t start, uint8_t length) {
	return ins << start >> (SIZE_DWORD - length);
}

instruction Simulator::decodeInstruction(ins_value_t inst) {
	instruction ins = instruction();

	ins.value = inst;
	ins.opc = static_cast<opcode>((reg_addr)this->getNBitsFrom(ins.value, 0, 6));
	ins.rs = (reg_addr)this->getNBitsFrom(ins.value, 6, 5);
	ins.rt = (reg_addr)this->getNBitsFrom(ins.value, 11, 5);
	ins.rd = (reg_addr)this->getNBitsFrom(ins.value, 16, 5);
	ins.imm = (immediate)this->getNBitsFrom(ins.value, 16, 16);
	ins.addr = (mem_addr)this->getNBitsFrom(ins.value, 6, 26) << 2;
	ins.pc = this->pc;

	if (!std::get<6>(OPC_CONTROL_SIGNALS[ins.opc])) {
		ins.rd = ins.rt;
	}

	if (ins.opc == OPC_SYSCALL) {
		ins.rs = this->rf->registerNameToAddress("$v0");
	}

	return ins;
}

ERROR_CODE Simulator::systemCall(ins_value_t code, bool &should_exit) {
	if (code == 1) {
		/// $a0 = integer to be printed
		std::cout << this->rf->read(this->rf->registerNameToAddress("$a0")) << std::endl;
	}

	else if (code == 2) {
		/// $f12 = float to be printed
		uint32_t value = this->rf->read(this->rf->registerNameToAddress("$f12"));

		float output_float;
		memcpy(&output_float, &value, sizeof(value));

		std::cout << output_float << std::endl;
	}

	else if (code == 3) {
		/// $f12 = double to be printed
		uint64_t value1 = this->rf->read(this->rf->registerNameToAddress("$f12"));
		uint64_t value2 = this->rf->read(this->rf->registerNameToAddress("$f13"));

		uint64_t value = (value1 << 32) | value2;

		double output_double;
		memcpy(&output_double, &value, sizeof(value));

		std::cout << output_double << std::endl;
	}

	else if (code == 4) {
		// TODO: Implement
		/// $a0 = address of string in memory
		mem_addr addr = this->rf->read(this->rf->registerNameToAddress("$a0"));

		while (true) {
			uint8_t byte = (uint8_t)this->mem->read(addr++, SIZE_BYTE);

			if (byte == 0)
				break;

			std::cout << byte;
		}
	}

	else if (code == 5) {
		// TODO: Implement
		/// integer returned in $v0
	}

	else if (code == 6) {
		// TODO: Implement
		/// float returned in $v0
	}

	else if (code == 7) {
		// TODO: Implement
		/// double returned in $v0
	}

	else if (code == 8) {
		/// $a0 = memory address of string input buffer
		/// $a1 = length of string buffer (n)
		mem_addr addr = this->rf->read(this->rf->registerNameToAddress("$a0"));
		immediate length = (immediate)this->rf->read(this->rf->registerNameToAddress("$a1"));

		std::string temp;
		std::cout << "> ";
		std::cin >> temp;

		if (temp.length() > length - 1) {
			return INVALID_READ_VALUE;
		}

		std::vector<uint8_t> bytes(temp.begin(), temp.end());
		bytes.push_back('\n');
		bytes.push_back(0);

		for (immediate i = 0; i < bytes.size(); i++) {
			this->mem->write(addr + i, bytes[i]);
		}
	}

		//// sbrk	9
		///     $a0 = amount	address in $v0

	else if (code == 10) {
		should_exit = true;
	}

	return NO_ERROR;
}
