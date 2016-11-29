//
// Created by Steven Imle on 11/27/16.
//

#include <cstdlib>
#include <iostream>
#include "error_codes.h"

void printError(ERROR_CODE error_code) {
	switch (error_code) {
		case SS_INVALID_OPCODE_CAST:
			fprintf(stderr, "error: SS_INVALID_OPCODE_CAST\r\n");
			break;
		case INVALID_COMMAND_LINE_ARGUMENT:
			fprintf(stderr, "error: INVALID_COMMAND_LINE_ARGUMENT\r\n");
			break;
		case SS_INVALID_PSEUDO_OPCODE:
			fprintf(stderr, "error: SS_INVALID_PSEUDO_OPCODE\r\n");
			break;
		case SS_MEMORY_STACK_OVERFLOW:
			fprintf(stderr, "error: SS_MEMORY_STACK_OVERFLOW\r\n");
			break;
		case SS_SRC_FILE_READ_ERROR:
			fprintf(stderr, "error: SS_SRC_FILE_READ_ERROR\r\n");
			break;
		case SS_SRC_FILE_DECODE_ERROR:
			fprintf(stderr, "error: SS_SRC_FILE_DECODE_ERROR\r\n");
			break;
		case IFU_INVALID_FLAG_TYPE:
			fprintf(stderr, "error: IFU_INVALID_FLAG_TYPE\r\n");
			break;
		case IFU_INVALID_OPC_TYPE:
			fprintf(stderr, "error: IFU_INVALID_OPC_TYPE\r\n");
			break;
		case SRC_FILE_HAS_TOO_MANY_INSTRUCTIONS:
			fprintf(stderr, "error: SRC_FILE_HAS_TOO_MANY_INSTRUCTIONS\r\n");
			break;
		case SRC_FILE_HAS_TOO_MUCH_DATA:
			fprintf(stderr, "error: SRC_FILE_HAS_TOO_MUCH_DATA\r\n");
			break;
		case SRC_FILE_INVALID_DATA_TYPE:
			fprintf(stderr, "error: SRC_FILE_INVALID_DATA_TYPE\r\n");
			break;
		case INVALID_INPUT_FILE_ERROR:
			fprintf(stderr, "error: INVALID_INPUT_FILE_ERROR\r\n");
			break;
		case SRC_FILE_INVALID_DATA_VALUE:
			fprintf(stderr, "error: SRC_FILE_INVALID_DATA_VALUE\r\n");
			break;
		case INVALID_READ_VALUE:
			fprintf(stderr, "error: INVALID_READ_VALUE\r\n");
			break;
		case NO_SECTION_PARSER_PROVIDED:
			fprintf(stderr, "error: NO_SECTION_PARSER_PROVIDED\r\n");
			break;
		case RS_INVALID_REGISTER_ADDRESS:
			fprintf(stderr, "error: RS_INVALID_REGISTER_ADDRESS\r\n");
			break;
		case RS_INVALID_SYSCALL:
			fprintf(stderr, "error: RS_INVALID_SYSCALL\r\n");
			break;
		case RS_INVALID_FUNCTIONAL_UNIT:
			fprintf(stderr, "error: RS_INVALID_FUNCTIONAL_UNIT\r\n");
			break;
		case NO_ERROR:
			break;
	}
}
