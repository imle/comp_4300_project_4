//
// Created by Steven Imle on 11/17/16.
//

#include <cstdlib>
#include <getopt.h>
#include <sstream>
#include "ArgumentParser.h"
#include "../error_codes.h"

ArgumentParser::ArgumentParser(int argc, char *argv[]) {
	if (argc < 2) {
		printError(INVALID_INPUT_FILE_ERROR);
		std::exit(INVALID_INPUT_FILE_ERROR);
	}

	bool flag_d = false;

	int opt;
	while ((opt = getopt(argc, argv, "d")) != -1) {
		switch (opt) {
			case 'd':
				flag_d = true;
				break;
			case '?':
				if (optopt == 'f')
					fprintf(stderr, "Option -%c requires an argument.\n", optopt);
				else if (isprint(optopt))
					fprintf(stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);

				std::exit(INVALID_COMMAND_LINE_ARGUMENT);
			default:
				abort();
		}
	}

	this->mode = flag_d ? MODE_DEBUG : MODE_RUN;

	if (optind >= argc) {
		fprintf(stderr, "Missing necessary filename argument.\r\n");

		std::exit(INVALID_COMMAND_LINE_ARGUMENT);
	}
	else if (argc - optind == 1) {
		std::stringstream stream;

		stream << argv[optind];

		this->run_file = stream.str();
	}
	else {
		fprintf(stderr, "Too many arguments provided.\r\n");

		std::exit(INVALID_COMMAND_LINE_ARGUMENT);
	}
}

const std::string &ArgumentParser::getRunFile() const {
	return run_file;
}

SIM_MODE ArgumentParser::getMode() const {
	return mode;
}
