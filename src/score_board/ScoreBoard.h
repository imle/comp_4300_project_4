//
// Created by Steven Imle on 11/28/16.
//

#ifndef INC_4_SCOREBOARD_H
#define INC_4_SCOREBOARD_H


#include <vector>
#include "../opcode_data.h"
#include "../types_data.h"
#include "../functional_units/FunctionalUnit.h"
#include "../register_file/RegisterFile.h"

class ScoreBoard {
private:
	struct FUS {
		FUS() : busy(false), opc(OPC_INVALID), f_d(INVALID_REGISTER), f_s(INVALID_REGISTER), f_t(INVALID_REGISTER),
		        wait_on_fu_s(nullptr), wait_on_fu_t(nullptr), available_s(true), available_t(true),
		        time_remaining(0), was_started(0) {};

		bool busy;
		opcode opc;
		reg_addr f_d;                   // Fi
		reg_addr f_s;                   // Fj
		reg_addr f_t;                   // Fk
		FunctionalUnit *wait_on_fu_s;   // Qj
		FunctionalUnit *wait_on_fu_t;   // Qk
		bool available_s;               // Rj
		bool available_t;               // Rk

		uint16_t time_remaining;        // Rk
		instruction ins;
		bool was_started;
	};

	struct IS {
		IS() : issue(0), read(0), exec(0), write(0) {};

		instruction ins;
		uint32_t issue;
		uint32_t read;
		uint32_t exec;
		uint32_t write;
	};

	std::map<FunctionalUnit *, FUS> statuses_fu;

	std::map<reg_addr, FunctionalUnit *> statuses_reg;

	std::vector<IS> statuses_ins;

	uint32_t cycle;

public:
	ScoreBoard();

	FunctionalUnit *issue(instruction ins);

	void read(void);

	void advance(void);

	std::map<FunctionalUnit *, instruction> write(void);

	void registerFunctionalUnit(FunctionalUnit *fu);

	bool isFinished(FunctionalUnit *fu);

	bool allFinished(void);

	bool allIdle(void);
};


#endif //INC_4_SCOREBOARD_H
