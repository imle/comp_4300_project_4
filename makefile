CC = g++
CXXFLAGS  = -g -std=c++0x -Wall

MKDIR_P = mkdir -p
OUT_DIR = build_dir
PROG_NAME = main

.PHONY: directories

all: directories ${PROG_NAME}

directories: ${OUT_DIR}

${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}

${PROG_NAME}: ${PROG_NAME}.cpp ${OUT_DIR}/AbstractSectionParser.o ${OUT_DIR}/SectionParser.o ${OUT_DIR}/IntegerFU.o ${OUT_DIR}/FunctionalUnit.o ${OUT_DIR}/Memory.o ${OUT_DIR}/MemoryLoader.o ${OUT_DIR}/RegisterFile.o ${OUT_DIR}/ScoreBoard.o ${OUT_DIR}/Simulator.o ${OUT_DIR}/ArgumentParser.o ${OUT_DIR}/number_functions.o ${OUT_DIR}/string_functions.o ${OUT_DIR}/error_codes.o ${OUT_DIR}/types_data.o ${OUT_DIR}/opcode_data.o ${OUT_DIR}/FPAddFU.o ${OUT_DIR}/FPMemoryFU.o ${OUT_DIR}/Color.o
	$(CC) $(CXXFLAGS) -o ${PROG_NAME} ${PROG_NAME}.cpp ${OUT_DIR}/AbstractSectionParser.o ${OUT_DIR}/SectionParser.o ${OUT_DIR}/IntegerFU.o ${OUT_DIR}/FunctionalUnit.o ${OUT_DIR}/Memory.o ${OUT_DIR}/MemoryLoader.o ${OUT_DIR}/RegisterFile.o ${OUT_DIR}/ScoreBoard.o ${OUT_DIR}/Simulator.o ${OUT_DIR}/ArgumentParser.o ${OUT_DIR}/number_functions.o ${OUT_DIR}/string_functions.o ${OUT_DIR}/error_codes.o ${OUT_DIR}/types_data.o ${OUT_DIR}/opcode_data.o ${OUT_DIR}/FPAddFU.o ${OUT_DIR}/FPMemoryFU.o ${OUT_DIR}/Color.o

${OUT_DIR}/AbstractSectionParser.o: src/compiler/AbstractSectionParser.cpp
	$(CC) $(CXXFLAGS) -o ${OUT_DIR}/AbstractSectionParser.o -c src/compiler/AbstractSectionParser.cpp

${OUT_DIR}/SectionParser.o: src/compiler/SectionParser.cpp
	$(CC) $(CXXFLAGS) -o ${OUT_DIR}/SectionParser.o -c src/compiler/SectionParser.cpp

${OUT_DIR}/FPMemoryFU.o: src/functional_units/FPMemoryFU.cpp
	$(CC) $(CXXFLAGS) -o ${OUT_DIR}/FPMemoryFU.o -c src/functional_units/FPMemoryFU.cpp

${OUT_DIR}/FPAddFU.o: src/functional_units/FPAddFU.cpp
	$(CC) $(CXXFLAGS) -o ${OUT_DIR}/FPAddFU.o -c src/functional_units/FPAddFU.cpp

${OUT_DIR}/IntegerFU.o: src/functional_units/IntegerFU.cpp
	$(CC) $(CXXFLAGS) -o ${OUT_DIR}/IntegerFU.o -c src/functional_units/IntegerFU.cpp

${OUT_DIR}/FunctionalUnit.o: src/functional_units/FunctionalUnit.cpp
	$(CC) $(CXXFLAGS) -o ${OUT_DIR}/FunctionalUnit.o -c src/functional_units/FunctionalUnit.cpp

${OUT_DIR}/Memory.o: src/memory/Memory.cpp
	$(CC) $(CXXFLAGS) -o ${OUT_DIR}/Memory.o -c src/memory/Memory.cpp

${OUT_DIR}/MemoryLoader.o: src/memory/MemoryLoader.cpp
	$(CC) $(CXXFLAGS) -o ${OUT_DIR}/MemoryLoader.o -c src/memory/MemoryLoader.cpp

${OUT_DIR}/RegisterFile.o: src/register_file/RegisterFile.cpp
	$(CC) $(CXXFLAGS) -o ${OUT_DIR}/RegisterFile.o -c src/register_file/RegisterFile.cpp

${OUT_DIR}/ScoreBoard.o: src/score_board/ScoreBoard.cpp
	$(CC) $(CXXFLAGS) -o ${OUT_DIR}/ScoreBoard.o -c src/score_board/ScoreBoard.cpp

${OUT_DIR}/Simulator.o: src/simulator/Simulator.cpp
	$(CC) $(CXXFLAGS) -o ${OUT_DIR}/Simulator.o -c src/simulator/Simulator.cpp

${OUT_DIR}/ArgumentParser.o: src/util/ArgumentParser.cpp
	$(CC) $(CXXFLAGS) -o ${OUT_DIR}/ArgumentParser.o -c src/util/ArgumentParser.cpp

${OUT_DIR}/Color.o: src/util/Color.cpp
	$(CC) $(CXXFLAGS) -o ${OUT_DIR}/Color.o -c src/util/Color.cpp

${OUT_DIR}/number_functions.o: src/util/number_functions.cpp
	$(CC) $(CXXFLAGS) -o ${OUT_DIR}/number_functions.o -c src/util/number_functions.cpp

${OUT_DIR}/string_functions.o: src/util/string_functions.cpp
	$(CC) $(CXXFLAGS) -o ${OUT_DIR}/string_functions.o -c src/util/string_functions.cpp

${OUT_DIR}/error_codes.o: src/error_codes.cpp
	$(CC) $(CXXFLAGS) -o ${OUT_DIR}/error_codes.o -c src/error_codes.cpp

${OUT_DIR}/types_data.o: src/types_data.cpp
	$(CC) $(CXXFLAGS) -o ${OUT_DIR}/types_data.o -c src/types_data.cpp

${OUT_DIR}/opcode_data.o: src/opcode_data.cpp
	$(CC) $(CXXFLAGS) -o ${OUT_DIR}/opcode_data.o -c src/opcode_data.cpp

clean:
	rm -rf ${OUT_DIR} ${PROG_NAME} *.dSYM
