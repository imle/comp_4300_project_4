//
// Created by Steven Imle on 11/28/16.
//

#include <sstream>
#include <iomanip>
#include "opcode_data.h"


std::string getOpcName(opcode opc) {
	std::ostringstream stream;

	stream << std::left << std::setw(7) << std::setfill(' ');

	switch (opc) {
		case OPC_ADD:
			stream << "ADD";
			break;
		case OPC_MULT:
			stream << "MULT";
			break;
		case OPC_LI:
			stream << "LI";
			break;
		case OPC_ADDI:
			stream << "ADDI";
			break;
		case OPC_B:
			stream << "B";
			break;
		case OPC_BEQZ:
			stream << "BEQZ";
			break;
		case OPC_BGE:
			stream << "BGE";
			break;
		case OPC_BNE:
			stream << "BNE";
			break;
		case OPC_LA:
			stream << "LA";
			break;
		case OPC_LB:
			stream << "LB";
			break;
		case OPC_SUBI:
			stream << "SUBI";
			break;
		case OPC_SYSCALL:
			stream << "SYSCALL";
			break;
		case OPC_NOP:
			stream << "NOP";
			break;
		case OPC_LUI:
			stream << "LUI";
			break;
		case OPC_ORI:
			stream << "ORI";
			break;
		case OPC_BEQ:
			stream << "BEQ";
			break;
		case OPC_SLT:
			stream << "SLT";
			break;
		default:
		case OPC_INVALID:
			stream << "INVALID";
			break;
	}

	return stream.str();
}
