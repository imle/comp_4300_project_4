//
// Created by Steven Imle on 11/28/16.
//

#ifndef INC_4_OPCODE_DATA_H
#define INC_4_OPCODE_DATA_H


#include <string>
#include <unordered_map>
#include <map>
#include <vector>

enum opcode {
	OPC_INVALID = 0, OPC_ADD = 1, OPC_MULT = 2, OPC_LI = 3, OPC_ADDI = 4, OPC_B = 5, OPC_BEQZ = 6,
	OPC_BGE = 7, OPC_BNE = 8, OPC_LA = 9, OPC_LB = 10, OPC_SUBI = 11, OPC_SYSCALL = 12, OPC_NOP = 13,
	OPC_LUI = 14, OPC_ORI = 15, OPC_BEQ = 16, OPC_SLT = 17,
	OPC_SD = 18, OPC_LD = 19, OPC_FADD = 20, OPC_FSUB = 21, OPC_FMUL = 22
};

enum OPC_TYPE {
	TYPE_R,     // R-Type   |   op $rd, $rs, $rt
	TYPE_J,     // J-Type   |   op imm
	TYPE_I_S,   // I-Type   |   $rt, imm
	TYPE_I_D,   // I-Type   |   $rt, $rs, imm
	TYPE_I_O,   // I-Type   |   op $rt, imm($rs)
	TYPE_NA     // NA
};

enum OPC_FU_TYPE {
	FU_NONE,    // NA
	FU_INT,     // Integer Functional Unit
	FU_MULT,    // Floating Point Multiply
	FU_ADD,     // Floating Point Add/Subtract
	FU_MEM,     // Load/Store Memory
};

struct EnumClassHash {
	template<typename T>
	std::size_t operator()(T t) const {
		return static_cast<std::size_t>(t);
	}
};

static std::map<opcode, std::string> OPC_STRINGS = {
		{ OPC_SYSCALL,  "syscall" },
		{ OPC_FADD,     "fadd" },
		{ OPC_FSUB,     "fsub" },
		{ OPC_FMUL,     "fmul" },
		{ OPC_MULT,     "mult" },
		{ OPC_ADDI,     "addi" },
		{ OPC_BEQZ,     "beqz" },
		{ OPC_SUBI,     "subi" },
		{ OPC_NOP,      "nop" },
		{ OPC_SD,       "s.d" },
		{ OPC_LD,       "l.d" },
		{ OPC_ADD,      "add" },
		{ OPC_BGE,      "bge" },
		{ OPC_BNE,      "bne" },
		{ OPC_LUI,      "lui" },
		{ OPC_ORI,      "ori" },
		{ OPC_BEQ,      "beq" },
		{ OPC_SLT,      "slt" },
		{ OPC_LI,       "li" },
		{ OPC_LA,       "la" },
		{ OPC_LB,       "lb" },
		{ OPC_B,        "b" },
};

// Order matters here.
static std::vector<opcode> OPC_STRING_ORDER = {
		OPC_SYSCALL, OPC_FADD, OPC_FSUB, OPC_FMUL, OPC_MULT, OPC_ADDI, OPC_BEQZ,
		OPC_SUBI, OPC_NOP, OPC_SD, OPC_LD, OPC_ADD, OPC_BGE, OPC_BNE, OPC_LUI,
		OPC_ORI, OPC_BEQ, OPC_SLT, OPC_LI, OPC_LA, OPC_LB, OPC_B,
};

static std::map<opcode, OPC_FU_TYPE> OPC_FU = {
		// Should be none, but need INT pipeline's access to memory.
		{ OPC_SYSCALL,  FU_INT },
		{ OPC_NOP,      FU_INT },
		{ OPC_B,        FU_INT },
		{ OPC_BNE,      FU_INT },
		{ OPC_BEQ,      FU_INT },

		{ OPC_MULT,     FU_INT },
		{ OPC_ADDI,     FU_INT },
		{ OPC_SUBI,     FU_INT },
		{ OPC_ADD,      FU_INT },
		{ OPC_SLT,      FU_INT },

		{ OPC_LUI,      FU_INT },
		{ OPC_ORI,      FU_INT },
		{ OPC_LB,       FU_INT },

		{ OPC_SD,       FU_MEM },
		{ OPC_LD,       FU_MEM },
		{ OPC_FADD,     FU_ADD },
		{ OPC_FSUB,     FU_ADD },
		{ OPC_FMUL,     FU_MULT },

		// pseudo opcodes
		{ OPC_LI,       FU_NONE },
		{ OPC_BEQZ,     FU_NONE },
		{ OPC_BGE,      FU_NONE },
		{ OPC_LA,       FU_NONE },
};

static std::map<opcode, uint8_t> OPC_CYCLE_DATA = {
		{ OPC_LI,      3 },
		{ OPC_ADDI,    6 },
		{ OPC_B,       4 },
		{ OPC_BEQZ,    5 },
		{ OPC_BGE,     5 },
		{ OPC_BNE,     5 },
		{ OPC_LA,      5 },
		{ OPC_LB,      6 },
		{ OPC_SUBI,    6 },

		{ OPC_ADD,     0 },
		{ OPC_MULT,    0 },

		{ OPC_INVALID, 0 },
		{ OPC_SYSCALL, 0 },
		{ OPC_NOP,     0 },

		{ OPC_LUI,     0 },
		{ OPC_ORI,     0 },
		{ OPC_BEQ,     0 },
		{ OPC_SLT,     0 },

		{ OPC_SD,      0 },
		{ OPC_LD,      0 },
		{ OPC_FADD,    0 },
		{ OPC_FSUB,    0 },
		{ OPC_FMUL,    0 },
};

static std::map<opcode, OPC_TYPE> OPC_TYPE_DATA = {
		{ OPC_ADDI,    TYPE_I_D },
		{ OPC_B,       TYPE_J   },
		{ OPC_BNE,     TYPE_I_D },
		{ OPC_LUI,     TYPE_I_S },
		{ OPC_ORI,     TYPE_I_D },
		{ OPC_LB,      TYPE_I_O },
		{ OPC_SUBI,    TYPE_I_D },
		{ OPC_BEQ,     TYPE_I_D },
		{ OPC_SLT,     TYPE_R   },

		{ OPC_ADD,     TYPE_R   },
		{ OPC_MULT,    TYPE_R   },

		{ OPC_INVALID, TYPE_NA  },
		{ OPC_SYSCALL, TYPE_NA  },
		{ OPC_NOP,     TYPE_NA  },

		// pseudo opcodes
		{ OPC_LI,      TYPE_I_S },
		{ OPC_BEQZ,    TYPE_I_S },
		{ OPC_BGE,     TYPE_I_D },
		{ OPC_LA,      TYPE_I_S },

		{ OPC_SD,      TYPE_I_O },
		{ OPC_LD,      TYPE_I_O },
		{ OPC_FADD,    TYPE_R   },
		{ OPC_FSUB,    TYPE_R   },
		{ OPC_FMUL,    TYPE_R   },
};

static std::map<opcode, bool> OPC_IS_PSEUDO = {
		{ OPC_ADDI,    false },
		{ OPC_B,       false },
		{ OPC_BNE,     false },
		{ OPC_LUI,     false },
		{ OPC_ORI,     false },
		{ OPC_LB,      false },
		{ OPC_SUBI,    false },
		{ OPC_BEQ,     false },
		{ OPC_SLT,     false },

		{ OPC_ADD,     false },
		{ OPC_MULT,    false },

		{ OPC_INVALID, false },
		{ OPC_SYSCALL, false },
		{ OPC_NOP,     false },

		// pseudo opcodes
		{ OPC_LI,      true },
		{ OPC_BEQZ,    true },
		{ OPC_BGE,     true },
		{ OPC_LA,      true },

		{ OPC_SD,      false },
		{ OPC_LD,      false },
		{ OPC_FADD,    false },
		{ OPC_FSUB,    false },
		{ OPC_FMUL,    false },
};

static std::map<opcode, uint8_t> OPC_UNPACKED_COUNT = {
		{ OPC_ADDI,    1 },
		{ OPC_B,       1 },
		{ OPC_BNE,     1 },
		{ OPC_LUI,     1 },
		{ OPC_ORI,     1 },
		{ OPC_LB,      1 },
		{ OPC_SUBI,    1 },
		{ OPC_BEQ,     1 },
		{ OPC_SLT,     1 },

		{ OPC_ADD,     1 },
		{ OPC_MULT,    1 },

		{ OPC_SYSCALL, 1 },
		{ OPC_NOP,     1 },

		{ OPC_SD,      1 },
		{ OPC_LD,      1 },
		{ OPC_FADD,    1 },
		{ OPC_FSUB,    1 },
		{ OPC_FMUL,    1 },

		// pseudo opcodes
		{ OPC_LI,      2 },
		{ OPC_BEQZ,    1 },
		{ OPC_BGE,     2 },
		{ OPC_LA,      2 },
};

typedef std::tuple<bool, bool, bool, bool, bool, bool, bool> control_signal_tuple;

static std::map<opcode, control_signal_tuple> OPC_CONTROL_SIGNALS = {
		{ OPC_ADDI,    std::make_tuple(true, false, false, false, false, true, false) },
		{ OPC_B,       std::make_tuple(false, false, true, false, false, false, false) },
		{ OPC_BNE,     std::make_tuple(false, false, false, false, false, false, false) },
		{ OPC_LUI,     std::make_tuple(true, false, false, false, false, true, false) },
		{ OPC_ORI,     std::make_tuple(true, false, false, false, false, true, false) },
		{ OPC_LB,      std::make_tuple(true, true, false, false, true, true, false) },
		{ OPC_SUBI,    std::make_tuple(true, false, false, false, false, true, false) },
		{ OPC_BEQ,     std::make_tuple(false, false, false, false, false, false, false) },
		{ OPC_SLT,     std::make_tuple(true, false, false, false, false, false, true) },

		{ OPC_ADD,     std::make_tuple(true, false, false, false, false, false, true) },
		{ OPC_MULT,    nullptr },

		{ OPC_SYSCALL, std::make_tuple(false, false, false, false, false, false, false) },
		{ OPC_NOP,     std::make_tuple(false, false, false, false, false, false, false) },

		// pseudo opcodes
		{ OPC_LI,      std::make_tuple(false, false, false, false, false, false, false) },
		{ OPC_BEQZ,    std::make_tuple(false, false, false, false, false, false, false) },
		{ OPC_BGE,     std::make_tuple(false, false, false, false, false, false, false) },
		{ OPC_LA,      std::make_tuple(false, false, false, false, false, false, false) },

		{ OPC_SD,      std::make_tuple(false, false, false, false, false, false, false) },
		{ OPC_LD,      std::make_tuple(false, false, false, false, false, false, false) },
		{ OPC_FADD,    std::make_tuple(false, false, false, false, false, false, true) },
		{ OPC_FSUB,    std::make_tuple(false, false, false, false, false, false, true) },
		{ OPC_FMUL,    std::make_tuple(false, false, false, false, false, false, true) },
};

const std::string DATA_TYPE_ASCII = "ascii";        // str
const std::string DATA_TYPE_ASCIIZ = "asciiz";      // str
const std::string DATA_TYPE_BYTE = "byte";          // b1, ..., bn
const std::string DATA_TYPE_HALFWORD = "halfword";  // h1, ..., hn
const std::string DATA_TYPE_WORD = "word";          // w1, ..., wn
const std::string DATA_TYPE_FLOAT = "float";        // f1, ..., fn
const std::string DATA_TYPE_DOUBLE = "double";      // d1, ..., dn
const std::string DATA_TYPE_SPACE = "space";        // numBytes

std::string getOpcName(opcode opc);


#endif //INC_4_OPCODE_DATA_H
