//
// Created by Steven Imle on 11/17/16.
//

#ifndef INC_1_ARGUMENTPARSER_H
#define INC_1_ARGUMENTPARSER_H


#include "../types_data.h"

class ArgumentParser {
private:

	std::string run_file;
public:
	const std::string &getRunFile() const;

	SIM_MODE getMode() const;

private:
	SIM_MODE mode;

public:
	ArgumentParser(int argc, char *argv[]);
};


#endif //INC_1_ARGUMENTPARSER_H
