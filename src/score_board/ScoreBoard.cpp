//
// Created by Steven Imle on 11/28/16.
//

#include <cstdlib>
#include "ScoreBoard.h"

ScoreBoard::ScoreBoard() {
	this->cycle = 0;
}

void ScoreBoard::registerFunctionalUnit(FunctionalUnit *fu) {
	this->statuses_fu[fu] = FUS();
}

FunctionalUnit *ScoreBoard::issue(instruction ins) {
	this->cycle++;

	IS is = IS();
	is.ins = ins;
	is.issue = this->cycle;

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
			iter->second.ins = ins;

			this->statuses_ins.push_back(is);

			return iter->first;
		}
	}

	return nullptr;
}

void ScoreBoard::read(void) {
	std::map<FunctionalUnit *, FUS>::iterator iter;
	for (iter = this->statuses_fu.begin(); iter != this->statuses_fu.end(); iter++) {
		if (iter->second.available_s && iter->second.available_t) {
			iter->second.available_s = false;
			iter->second.available_t = false;
		}
	}
}

void ScoreBoard::advance(void) {
	std::map<FunctionalUnit *, FUS>::iterator iter;
	for (iter = this->statuses_fu.begin(); iter != this->statuses_fu.end(); iter++) {
		if (iter->second.busy) {
			if (iter->second.time_remaining > 0) {
				iter->second.time_remaining--;
			}
		}
		else {
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
}

std::map<FunctionalUnit *, instruction> ScoreBoard::write(void) {
	std::map<FunctionalUnit *, instruction> finished;

	std::map<FunctionalUnit *, FUS>::iterator iter;
	for (iter = this->statuses_fu.begin(); iter != this->statuses_fu.end(); iter++) {
		if (this->isFinished(iter->first)) {
			finished[iter->first] = this->statuses_fu[iter->first].ins;

			this->statuses_reg[iter->second.f_d] = nullptr;

			this->statuses_fu[iter->first] = FUS();
		}
	}

	return finished;
}

bool ScoreBoard::isFinished(FunctionalUnit *fu) {
	if (fu == nullptr)
		return false;

	return this->statuses_fu[fu].time_remaining == 0 && this->statuses_fu[fu].f_d != INVALID_REGISTER;
}
