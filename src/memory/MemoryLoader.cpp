//
// Created by Steven Imle on 9/7/16.
//

#include <fstream>
#include "MemoryLoader.h"
#include "../util/string_functions.h"

MemoryLoader::MemoryLoader(TextSectionParser *tsp, DataSectionParser *dsp, char comment_character) {
	this->tsp = tsp;
	this->dsp = dsp;
	this->comment_character = comment_character;
}

ERROR_CODE MemoryLoader::loadFileIntoMemory(std::string file_path, Memory *mem) {
	std::ifstream src_file;
	src_file.open(file_path);

	std::ofstream temp_file_data;
	temp_file_data.open(TEMP_FILE_LOC_DATA);

	std::ofstream temp_file_text;
	temp_file_text.open(TEMP_FILE_LOC_TEXT);

	if (!src_file.is_open() || !src_file.good())
		return SS_SRC_FILE_READ_ERROR;

	source_section section = SECTION_NONE;

	std::string line;
	while (std::getline(src_file, line)) {
		line = this->removeComment(line);
		line = trimmed(line);

		if (line.length() == 0)
			continue;

		if (line.compare(SECTION_STR_DATA) == 0) {
			section = SECTION_DATA;
			continue;
		}

		if (line.compare(SECTION_STR_TEXT) == 0) {
			section = SECTION_TEXT;
			continue;
		}

		for (int i = 0; line[i] != '\0'; i++) {
			line[i] = (char)tolower(line[i]);
		}

		if (section == SECTION_DATA)
			temp_file_data << line << std::endl;

		if (section == SECTION_TEXT)
			temp_file_text << line << std::endl;
	}

	src_file.close();
	temp_file_data.close();
	temp_file_text.close();

	this->dsp->parse(TEMP_FILE_LOC_DATA);

	this->tsp->parse(TEMP_FILE_LOC_TEXT);

	std::remove(TEMP_FILE_LOC_TEXT.c_str());
	std::remove(TEMP_FILE_LOC_DATA.c_str());

	return NO_ERROR;
}

std::string MemoryLoader::removeComment(std::string line) {
	return line.substr(0, line.find(this->comment_character));
}