//
// Created by Steven Imle on 9/7/16.
//

#ifndef INC_1_MEMORYLOADER_H
#define INC_1_MEMORYLOADER_H


#include <string>
#include "Memory.h"
#include "../error_codes.h"
#include "../compiler/SectionParser.h"


const std::string TEMP_FILE_LOC_DATA = "data.temp";
const std::string TEMP_FILE_LOC_TEXT = "text.temp";

enum source_section {
	SECTION_NONE, SECTION_DATA, SECTION_TEXT
};

const std::string SECTION_STR_DATA = ".data";
const std::string SECTION_STR_TEXT = ".text";


class MemoryLoader {
public:
	MemoryLoader(TextSectionParser *tsp, DataSectionParser *dsp, char comment_character);

	ERROR_CODE loadFileIntoMemory(std::string file_path, Memory *mem);

private:
	TextSectionParser *tsp;
	DataSectionParser *dsp;

	char comment_character;

	std::string removeComment(std::string line);
};


#endif //INC_1_MEMORYLOADER_H
