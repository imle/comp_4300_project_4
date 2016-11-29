//
// Created by Steven Imle on 11/28/16.
//

#include "FunctionalUnit.h"

OPC_FU_TYPE FunctionalUnit::getFUType() {
	return this->fu_type;
}

uint8_t FunctionalUnit::getCyclesNeeded(void) {
	return this->cycles_needed;
}
