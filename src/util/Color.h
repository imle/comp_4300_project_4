//
// Created by Steven Imle on 9/29/16.
//

#ifndef INC_1_COLOR_H
#define INC_1_COLOR_H


#include <ostream>
#include <iostream>
//#include <curses.h>
//#include <term.h>

namespace Color {
	static int supported = -1;

	enum Code {
		FG_RED = 31,
		FG_GREEN = 32,
		FG_BLUE = 34,
		FG_DEFAULT = 39,
		BG_RED = 41,
		BG_GREEN = 42,
		BG_BLUE = 44,
		BG_DEFAULT = 49
	};

	std::ostream &operator<<(std::ostream &os, Code code);
}


#endif //INC_1_COLOR_H
