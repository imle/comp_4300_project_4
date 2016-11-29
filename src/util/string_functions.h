//
// Created by Steven Imle on 9/6/16.
//

#ifndef INC_1_STRING_FUNCTIONS_H
#define INC_1_STRING_FUNCTIONS_H

#include <string>

void ltrim(std::string &s);

void rtrim(std::string &s);

void trim(std::string &s);

void replace_substring(std::string &subject, const std::string &search, const std::string &replace);

std::string ltrimmed(std::string s);

std::string rtrimmed(std::string s);

std::string trimmed(std::string s);

#endif //INC_1_STRING_FUNCTIONS_H
