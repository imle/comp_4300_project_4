//
// Created by Steven Imle on 11/28/16.
//

#include <cstdlib>
#include "ScoreBoard.h"
#include "../error_codes.h"

ScoreBoard::ScoreBoard() {
	this->cycle = 0;
	this->current_ins_num = 0;
}

void ScoreBoard::registerFunctionalUnit(FunctionalUnit *fu) {
	this->statuses_fu[fu] = FUS();
}

FunctionalUnit *ScoreBoard::issue(instruction ins) {
	IS is = IS();
	is.ins = ins;

	OPC_FU_TYPE fu_type = OPC_FU[ins.opc];

	if (this->statuses_reg[ins.rd] != nullptr)
		return nullptr;

	std::map<FunctionalUnit *, FUS>::iterator iter;
	for (iter = this->statuses_fu.begin(); iter != this->statuses_fu.end(); iter++) {
		if (iter->first->getFUType() == fu_type && !iter->second.busy) {
			iter->second.busy = true;
			iter->second.f_d = ins.rd;
			iter->second.f_s = ins.rs;
			iter->second.f_t = ins.rt;
			iter->second.wait_on_fu_s = this->statuses_reg[ins.rs];
			iter->second.wait_on_fu_t = this->statuses_reg[ins.rt];
			iter->second.available_t = iter->second.wait_on_fu_t == nullptr;
			iter->second.available_s = iter->second.wait_on_fu_s == nullptr;
			iter->second.time_remaining = iter->first->getCyclesNeeded();

			this->statuses_ins.push_back(is);

			return iter->first;
		}
	}

	return nullptr;
}

bool ScoreBoard::read(void) {
	std::map<FunctionalUnit *, FUS>::iterator iter;
	for (iter = this->statuses_fu.begin(); iter != this->statuses_fu.end(); iter++) {
		if (iter->second.available_s && iter->second.available_t) {
			iter->second.available_s = false;
			iter->second.available_t = false;
		}
	}

	return false;
}

void ScoreBoard::advance(void) {
	std::map<FunctionalUnit *, FUS>::iterator iter;
	for (iter = this->statuses_fu.begin(); iter != this->statuses_fu.end(); iter++) {
		if (iter->second.time_remaining > 0) {
			iter->second.time_remaining--;
		}

		if (this->isFinished(iter->second.wait_on_fu_s)) {
			iter->second.wait_on_fu_s = nullptr;
			iter->second.available_s = true;
		}

		if (this->isFinished(iter->second.wait_on_fu_t)) {
			iter->second.wait_on_fu_t = nullptr;
			iter->second.available_t = true;
		}
	}
}

void ScoreBoard::write(void) {
	std::map<FunctionalUnit *, FUS>::iterator iter;
	for (iter = this->statuses_fu.begin(); iter != this->statuses_fu.end(); iter++) {
		if (this->isFinished(iter->first)) {
			this->statuses_reg[iter->second.f_d] = nullptr;

			this->statuses_fu[iter->first] = FUS();
		}
	}
}

bool ScoreBoard::isFinished(FunctionalUnit *fu) {
	if (fu == nullptr)
		return false;

	return this->statuses_fu[fu].time_remaining == 0;
}

reg_addr ScoreBoard::getDestinationRegister(FunctionalUnit *fu) {
	if (fu == nullptr) {
		printError(RS_INVALID_FUNCTIONAL_UNIT);
		exit(RS_INVALID_FUNCTIONAL_UNIT);
	}

	return this->statuses_fu[fu].f_d;
}
