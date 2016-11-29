//
// Created by Steven Imle on 9/29/16.
//

#include "Color.h"

std::ostream &::Color::operator<<(std::ostream &os, Color::Code code) {
	return os << "\033[" << static_cast<int>(code) << "m";
}
