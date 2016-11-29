//
// Created by Steven Imle on 11/27/16.
//

#ifndef INC_4_REGISTERFILE_H
#define INC_4_REGISTERFILE_H


#include <string>
#include "../types_data.h"
#include "../limits.h"

class RegisterFile {
public:
	static reg_addr registerNameToAddress(std::string name);

	reg_value read(reg_addr addr);

	void write(reg_addr addr, reg_value value);

	void print(void);

protected:
	static const std::map<std::string, reg_addr> REGISTER_NAME_MAP;
	static const char *REGISTER_NAME_BASE;

	reg_value values[MAX_ADDRESS_FP];
	bool register_changes[MAX_ADDRESS_FP];
};


#endif //INC_4_REGISTERFILE_H
