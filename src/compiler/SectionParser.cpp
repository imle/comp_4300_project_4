//
// Created by Steven Imle on 11/28/16.
//

#include <fstream>
#include <sstream>
#include "SectionParser.h"
#include "../util/string_functions.h"
#include "../register_file/RegisterFile.h"

DataSectionParser::DataSectionParser(Memory *mem, mem_addr min_address, mem_addr max_address)
		: AbstractDataSectionParser(mem, min_address, max_address) {}

TextSectionParser::TextSectionParser(Memory *mem, mem_addr min_address, mem_addr max_address,
                                     AbstractDataSectionParser *dsp)
		: AbstractTextSectionParser(mem, min_address, max_address, dsp) {}

ERROR_CODE TextSectionParser::parse(std::string file_path) {
	variable_map dsp_labels = this->dsp->getVariableMap();
	this->labels.insert(dsp_labels.begin(), dsp_labels.end());

	mem_addr load_at = this->min_address;

	std::ifstream src_file;
	src_file.open(file_path);

	std::string line;
	while (std::getline(src_file, line)) {
		if (load_at > this->max_address)
			return SRC_FILE_HAS_TOO_MUCH_DATA;

		if (line[line.length() - 1] == ':') {
			this->labels[line.substr(0, std::strlen(line.c_str()) - 1)] = std::make_pair(load_at, false);

			continue;
		}

		load_at += sizeof(SIZE_DWORD);
	}

	src_file.clear();
	src_file.seekg(0, std::ios::beg);
	load_at = this->min_address;

	for (mem_addr line_number = 0; std::getline(src_file, line);) {
		if (load_at > this->max_address)
			return SRC_FILE_HAS_TOO_MUCH_DATA;

		if (line[line.length() - 1] == ':')
			continue;

		mem_addr pre_decode = load_at;

		ERROR_CODE ret_val = this->decodeLine(line, load_at);

		if (pre_decode == load_at)
			load_at += sizeof(SIZE_DWORD);

		if (ret_val != 0)
			return ret_val;

		line_number++;
	}

	src_file.close();
	load_at = this->min_address;

	opcode_argument_list::iterator iter_opl;
	variable_map::iterator iter_vm;

	for (iter_opl = this->opc_list.begin(); iter_opl != this->opc_list.end(); iter_opl++) {
		if (OPC_UNPACKED_COUNT[iter_opl->first] > 1) {
			for (iter_vm = this->labels.begin(); iter_vm != this->labels.end(); iter_vm++) {
				if (!iter_vm->second.second && iter_vm->second.first > load_at) {
					uint32_t increment = (OPC_UNPACKED_COUNT[iter_opl->first] - 1) * sizeof(SIZE_DWORD);

					iter_vm->second.first += increment;
				}
			}
		}

		load_at += OPC_UNPACKED_COUNT[iter_opl->first] * sizeof(SIZE_DWORD);
	}

	load_at = this->min_address;
	ERROR_CODE err_code;

	for (iter_opl = this->opc_list.begin(); iter_opl != this->opc_list.end(); iter_opl++) {
		if (OPC_IS_PSEUDO[iter_opl->first]) {
			err_code = this->parsePseudoInstruction(iter_opl->second, load_at, iter_opl->first);

			if (err_code != NO_ERROR)
				return err_code;
		}
		else {
			err_code = this->parseInstruction(iter_opl->second, load_at, iter_opl->first);

			if (err_code != NO_ERROR)
				return err_code;

			load_at += sizeof(SIZE_DWORD);
		}
	}

	return NO_ERROR;
}

ERROR_CODE TextSectionParser::decodeLine(std::string line, mem_addr &addr) {
	opcode code;

	std::map<opcode, std::string>::iterator iter;
	for (iter = OPC_STRINGS.begin(); iter != OPC_STRINGS.end(); iter++) {
		if (line.find(iter->second) == 0) {
			code = iter->first;
			line = ltrimmed(line.substr(iter->second.length()));

			this->opc_list.push_back(std::make_pair(code, line));

			return NO_ERROR;
		}
	}

	return SS_SRC_FILE_DECODE_ERROR;
}

ERROR_CODE TextSectionParser::parseInstruction(std::string line, mem_addr &addr, opcode code) {
	ins_value_t ins_value = code;

	instruction ins = instruction();
	ins.opc = code;
	uint8_t shift_total = MEM_ADDR_BIT_SIZE_TOTAL * sizeof(ins_value_t) - MEM_ADDR_SIZE_OPC;

	std::__1::string rd, rs, rt;
	ERROR_CODE err_code;

	unsigned long split_index = line.find(',');

	variable_map::iterator iter;

	switch (OPC_TYPE_DATA[code]) {
		case TYPE_NA:
			ins_value <<= shift_total;
			this->mem->write(addr, ins_value);

			break;
		case TYPE_J:
			this->shiftOnAddress(ins_value, line);

			ins_value <<= shift_total - MEM_ADDR_SIZE_ADD;
			this->mem->write(addr, ins_value);

			break;
		case TYPE_R:
			rd = rtrimmed(line.substr(0, split_index));
			line = ltrimmed(line.substr(split_index + 1));

			split_index = line.find(',');

			rs = rtrimmed(line.substr(0, split_index));
			line = ltrimmed(line.substr(split_index + 1));

			split_index = line.find(',');

			rt = rtrimmed(line.substr(0, split_index));
			line = ltrimmed(line.substr(split_index + 1));

			err_code = this->shiftOnRegister(ins_value, rs);
			if (err_code != NO_ERROR)
				return err_code;
			shift_total -= MEM_ADDR_SIZE_REG;

			err_code = this->shiftOnRegister(ins_value, rt);
			if (err_code != NO_ERROR)
				return err_code;
			shift_total -= MEM_ADDR_SIZE_REG;

			err_code = this->shiftOnRegister(ins_value, rd);
			if (err_code != NO_ERROR)
				return err_code;
			shift_total -= MEM_ADDR_SIZE_REG;

			ins_value <<= shift_total;
			this->mem->write(addr, ins_value);

			break;
		case TYPE_I_S:
			rt = rtrimmed(line.substr(0, split_index));
			line = ltrimmed(line.substr(split_index + 1));

			err_code = this->shiftOnRegister(ins_value, 0);
			if (err_code != NO_ERROR)
				return err_code;
			shift_total -= MEM_ADDR_SIZE_REG;

			err_code = this->shiftOnRegister(ins_value, rt);
			if (err_code != NO_ERROR)
				return err_code;
			shift_total -= MEM_ADDR_SIZE_REG;

			iter = this->labels.find(line);
			if (iter != this->labels.end()) {
				this->shiftOnLabel(ins_value, line, addr);
			}
			else {
				this->shiftOnImmediate(ins_value, line);
			}
			shift_total -= MEM_ADDR_SIZE_IMM;

			ins_value <<= shift_total;
			this->mem->write(addr, ins_value);

			break;
		case TYPE_I_D:
			rt = rtrimmed(line.substr(0, split_index));
			line = ltrimmed(line.substr(split_index + 1));

			split_index = line.find(',');

			rs = rtrimmed(line.substr(0, split_index));
			line = ltrimmed(line.substr(split_index + 1));

			err_code = this->shiftOnRegister(ins_value, rs);
			if (err_code != NO_ERROR)
				return err_code;
			shift_total -= MEM_ADDR_SIZE_REG;

			err_code = this->shiftOnRegister(ins_value, rt);
			if (err_code != NO_ERROR)
				return err_code;
			shift_total -= MEM_ADDR_SIZE_REG;

			iter = this->labels.find(line);
			if (iter != this->labels.end()) {
				this->shiftOnLabel(ins_value, line, addr);
			}
			else {
				this->shiftOnImmediate(ins_value, line);
			}
			shift_total -= MEM_ADDR_SIZE_IMM;

			ins_value <<= shift_total;
			this->mem->write(addr, ins_value);

			break;
		case TYPE_I_O:
			rt = rtrimmed(line.substr(0, split_index));
			line = ltrimmed(line.substr(split_index + 1));

			std::string offset;

			if (line[0] == '(') {
				offset = "0";
				line = line.substr(1);
			}
			else {
				split_index = line.find('(');
				offset = rtrimmed(line.substr(0, split_index));
				line = ltrimmed(line.substr(split_index + 1));
			}

			rs = line.substr(0, line.find(')'));
			line = offset;

			err_code = this->shiftOnRegister(ins_value, rs);
			if (err_code != NO_ERROR)
				return err_code;
			shift_total -= MEM_ADDR_SIZE_REG;

			err_code = this->shiftOnRegister(ins_value, rt);
			if (err_code != NO_ERROR)
				return err_code;
			shift_total -= MEM_ADDR_SIZE_REG;

			this->shiftOnImmediate(ins_value, line);
			shift_total -= MEM_ADDR_SIZE_IMM;

			ins_value <<= shift_total;
			this->mem->write(addr, ins_value);

			break;
	}

	return NO_ERROR;
}

ERROR_CODE TextSectionParser::parsePseudoInstruction(std::string line, mem_addr &addr, opcode code) {
	unsigned long split_index = line.find(',');
	std::__1::string rd, rs, rt;
	ERROR_CODE err_code;

	variable_map::iterator iter;

	if (code == OPC_LA || code == OPC_LI) {
		rt = rtrimmed(line.substr(0, split_index));
		line = ltrimmed(line.substr(split_index + 1));

		mem_addr value;
		std::ostringstream line1, line2;

		iter = this->labels.find(line);
		if (iter != this->labels.end()) {
			value = iter->second.first;
		}
		else {
			value = (mem_addr)std::stoi(line);
		}

		line1 << rt << ", " << (immediate)(value >> 16);
		line2 << rt << ", " << rt << ", " << (immediate)(value << 16 >> 16);

		err_code = this->parseInstruction(line1.str(), addr, OPC_LUI);

		if (err_code != NO_ERROR)
			return err_code;

		addr += sizeof(SIZE_DWORD);

		err_code = this->parseInstruction(line2.str(), addr, OPC_ORI);

		if (err_code != NO_ERROR)
			return err_code;
	}
	else if (code == OPC_BEQZ) {
		rt = rtrimmed(line.substr(0, split_index));
		line = ltrimmed(line.substr(split_index + 1));

		std::ostringstream line1, line2;

		line1 << rt << ", $zero, " << line;

		err_code = this->parseInstruction(line1.str(), addr, OPC_BEQ);

		if (err_code != NO_ERROR)
			return err_code;
	}
	else if (code == OPC_BGE) {
		// bge $rs, $rt, Label

		// slt $at, $rs, $rt
		// beq $at, $zero, Label

		rs = rtrimmed(line.substr(0, split_index));
		line = ltrimmed(line.substr(split_index + 1));

		split_index = line.find(',');

		rt = rtrimmed(line.substr(0, split_index));
		line = ltrimmed(line.substr(split_index + 1));

		std::ostringstream line1, line2;

		line1 << "$at, " << rs << ", " << rt;
		line2 << "$at, $zero, " << line;

		err_code = this->parseInstruction(line1.str(), addr, OPC_SLT);

		if (err_code != NO_ERROR)
			return err_code;

		addr += sizeof(SIZE_DWORD);

		err_code = this->parseInstruction(line2.str(), addr, OPC_BEQ);

		if (err_code != NO_ERROR)
			return err_code;
	}
	else {
		return SS_INVALID_PSEUDO_OPCODE;
	}

	addr += sizeof(SIZE_DWORD);

	return NO_ERROR;
}

ERROR_CODE TextSectionParser::shiftOnAddress(ins_value_t &ins, std::string &label) {
	/** This code produces the same result as the uncommented code below. */
//	ins <<= MEM_ADDR_SIZE_ADD;
//	ins |= this->labels[label];

	mem_addr addr = this->labels[label].first;
	uint16_t shift_value = MEM_ADDR_BIT_SIZE_TOTAL * sizeof(SIZE_DWORD) - MEM_ADDR_SIZE_ADD - 2;
	addr <<= shift_value;
	addr >>= shift_value + 2;

	ins <<= MEM_ADDR_SIZE_ADD;
	ins |= addr;

	return NO_ERROR;
}

ERROR_CODE TextSectionParser::shiftOnLabel(ins_value_t &ins, std::string &label, mem_addr addr) {
	uint32_t value = this->labels[label].first;
	value -= addr;

	if (!this->labels[label].second)
		value >>= 2;

	ins <<= MEM_ADDR_SIZE_LAB;
	ins |= (uint16_t)value;

	return NO_ERROR;
}

ERROR_CODE TextSectionParser::shiftOnRegister(ins_value_t &ins, std::string reg_name) {
	reg_addr addr = RegisterFile::registerNameToAddress(reg_name);

	return this->shiftOnRegister(ins, addr);
}

ERROR_CODE TextSectionParser::shiftOnRegister(ins_value_t &ins, reg_addr addr) {
	if (addr == INVALID_REGISTER) {
		return RS_INVALID_REGISTER_ADDRESS;
	}

	ins <<= MEM_ADDR_SIZE_REG;
	ins |= addr;

	return NO_ERROR;
}

ERROR_CODE TextSectionParser::shiftOnImmediate(ins_value_t &ins, std::string value) {
	uint16_t imm = (uint16_t)std::stoi(value);

	ins <<= MEM_ADDR_SIZE_IMM;
	ins |= imm;

	return NO_ERROR;
}

ERROR_CODE DataSectionParser::decodeLine(std::string line, mem_addr &addr) {
	unsigned long split_index = line.find(':');

	std::string variable = rtrimmed(line.substr(0, split_index));
	std::string value = ltrimmed(line.substr(split_index + 1));

	split_index = value.find(' ');

	std::string type = value.substr(1, split_index - 1);
	value = ltrimmed(value.substr(split_index + 1));

	this->labels[variable] = std::make_pair(addr, true);

	if (type == DATA_TYPE_ASCII || type == DATA_TYPE_ASCIIZ) {
		if (value[0] != '"' || value[value.size() - 1] != '"')
			return SRC_FILE_INVALID_DATA_VALUE;

		value.erase(value.end() - 1);
		value.erase(value.begin());

		replace_substring(value, "\\n", "\n");

		std::vector<uint8_t> bytes(value.begin(), value.end());

		if (type == DATA_TYPE_ASCIIZ) {
			bytes.push_back(0);
		}

		for (std::vector<uint8_t>::iterator iter = bytes.begin(); iter != bytes.end(); iter++) {
			this->mem->write(addr++, *iter);
		}
	}
	else if (type == DATA_TYPE_BYTE || type == DATA_TYPE_HALFWORD || type == DATA_TYPE_WORD) {
		// TODO: Implement this data type.
		return SRC_FILE_INVALID_DATA_TYPE;
	}
	else if (type == DATA_TYPE_SPACE) {
		mem_addr temp_value = (mem_addr)std::stoi(value, nullptr, 10);

		addr += temp_value;
	}
	else {
		return SRC_FILE_INVALID_DATA_TYPE;
	}

	return NO_ERROR;
}
