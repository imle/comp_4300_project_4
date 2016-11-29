//
// Created by Steven Imle on 9/28/16.
//

#include "number_functions.h"

int roundToMultipleOf(int number, int multiple) {
	return ((number + multiple / 2) / multiple) * multiple;
}
