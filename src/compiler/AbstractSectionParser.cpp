//
// Created by Steven Imle on 11/28/16.
//

#include <fstream>
#include "AbstractSectionParser.h"
#include "../util/string_functions.h"


AbstractSectionParser::AbstractSectionParser(Memory *mem, mem_addr min_address, mem_addr max_address) {
	this->mem = mem;
	this->min_address = min_address;
	this->max_address = max_address;
}

AbstractDataSectionParser::AbstractDataSectionParser(Memory *mem, mem_addr min_address, mem_addr max_address)
		: AbstractSectionParser(mem, min_address, max_address) {}

AbstractTextSectionParser::AbstractTextSectionParser(Memory *mem, mem_addr min_address, mem_addr max_address,
                                                     AbstractDataSectionParser *dsp)
		: AbstractSectionParser(mem, min_address, max_address) {
	this->dsp = dsp;
}

ERROR_CODE AbstractSectionParser::parse(std::string file_path) {
	mem_addr load_at = this->min_address;

	std::ifstream src_file;
	src_file.open(file_path);

	std::string line;
	for (mem_addr line_number = 0; std::getline(src_file, line); line_number++) {
		if (load_at > this->max_address)
			return SRC_FILE_HAS_TOO_MUCH_DATA;

		mem_addr pre_decode = load_at;

		ERROR_CODE ret_val = this->decodeLine(line, load_at);

		if (pre_decode == load_at)
			load_at += sizeof(SIZE_DWORD);

		if (ret_val != 0)
			return ret_val;
	}

	src_file.close();

	return NO_ERROR;
}

variable_map AbstractSectionParser::getVariableMap(void) {
	return this->labels;
}

ERROR_CODE AbstractDataSectionParser::decodeLine(std::string line, mem_addr &addr) {
	unsigned long split_index = line.find('=');

	std::string variable = rtrimmed(line.substr(0, split_index));
	std::string value = ltrimmed(line.substr(split_index + 1));

	mem_addr temp_value = (mem_addr)std::stoi(value, nullptr, 10);

	this->labels[variable] = std::make_pair(addr, true);

	this->mem->write(addr, temp_value);

	return NO_ERROR;
}

ERROR_CODE AbstractTextSectionParser::parse(std::string file_path) {
	this->labels.insert(this->dsp->labels.begin(), this->dsp->labels.end());

	return AbstractSectionParser::parse(file_path);
}
