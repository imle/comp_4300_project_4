//
// Created by Steven Imle on 11/28/16.
//

#ifndef INC_4_SECTIONPARSER_H
#define INC_4_SECTIONPARSER_H


#include <vector>
#include "AbstractSectionParser.h"

typedef std::vector<std::pair<opcode, std::string>> opcode_argument_list;

class TextSectionParser : public AbstractTextSectionParser {
private:
	opcode_argument_list opc_list;

protected:
	ERROR_CODE shiftOnRegister(ins_value_t &ins, std::string reg_name);

	ERROR_CODE shiftOnRegister(ins_value_t &ins, reg_addr addr);

	ERROR_CODE shiftOnAddress(ins_value_t &ins, std::string &label);

	ERROR_CODE shiftOnLabel(ins_value_t &ins, std::string &label, mem_addr addr);

	ERROR_CODE shiftOnImmediate(ins_value_t &ins, std::string value);

	ERROR_CODE parseInstruction(std::string line, mem_addr &addr, opcode code);

	ERROR_CODE parsePseudoInstruction(std::string line, mem_addr &addr, opcode code);

public:

	TextSectionParser(Memory *mem, mem_addr min_address, mem_addr max_address, AbstractDataSectionParser *dsp);

	ERROR_CODE decodeLine(std::string line, mem_addr &addr) override;

	ERROR_CODE parse(std::string file_path) override;

};

class DataSectionParser : public AbstractDataSectionParser {
public:

	DataSectionParser(Memory *mem, mem_addr min_address, mem_addr max_address);

	ERROR_CODE decodeLine(std::string line, mem_addr &addr) override;
};


#endif //INC_4_SECTIONPARSER_H
