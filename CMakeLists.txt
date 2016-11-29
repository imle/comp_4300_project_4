cmake_minimum_required(VERSION 3.6)
project(4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/register_file/RegisterFile.cpp src/register_file/RegisterFile.h src/types_data.cpp src/types_data.h src/limits.h src/error_codes.cpp src/error_codes.h src/opcode_data.cpp src/opcode_data.h src/functional_units/FunctionalUnit.h src/functional_units/FunctionalUnit.cpp src/memory/Memory.cpp src/memory/Memory.h src/memory/MemoryLoader.cpp src/memory/MemoryLoader.h src/score_board/ScoreBoard.cpp src/score_board/ScoreBoard.h src/functional_units/IntegerFU.cpp src/functional_units/IntegerFU.h src/simulator/Simulator.cpp src/simulator/Simulator.h src/compiler/AbstractSectionParser.cpp src/compiler/AbstractSectionParser.h src/util/string_functions.cpp src/util/string_functions.h src/util/number_functions.cpp src/util/number_functions.h src/compiler/SectionParser.cpp src/compiler/SectionParser.h src/util/ArgumentParser.cpp src/util/ArgumentParser.h)
add_executable(4 ${SOURCE_FILES})