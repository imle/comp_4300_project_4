//
// Created by Steven Imle on 11/28/16.
//

#ifndef INC_4_ABSTRACTSECTIONPARSER_H
#define INC_4_ABSTRACTSECTIONPARSER_H


#include <string>
#include "Memory.h"
#include "../types_data.h"
#include "../memory/Memory.h"
#include "../error_codes.h"


typedef std::pair<mem_addr, bool> label_pair;
typedef std::map<std::string, label_pair> variable_map;

class AbstractSectionParser {
protected:
	mem_addr min_address;
	mem_addr max_address;

	variable_map labels;

	Memory *mem;

public:
	AbstractSectionParser(Memory *mem, mem_addr min_address, mem_addr max_address);

	virtual ERROR_CODE parse(std::string file_path);

	virtual ERROR_CODE decodeLine(std::string line, mem_addr &addr) = 0;

	variable_map getVariableMap(void);
};

class AbstractDataSectionParser : public AbstractSectionParser {
	friend class AbstractTextSectionParser;
public:
	virtual ERROR_CODE decodeLine(std::string line, mem_addr &addr) = 0;

	AbstractDataSectionParser(Memory *mem, mem_addr min_address, mem_addr max_address);
};

class AbstractTextSectionParser : public AbstractSectionParser {
protected:
	AbstractDataSectionParser *dsp;

public:
	AbstractTextSectionParser(Memory *mem, mem_addr min_address, mem_addr max_address, AbstractDataSectionParser *dsp);

	ERROR_CODE parse(std::string file_path);
};


#endif //INC_4_ABSTRACTSECTIONPARSER_H
