#include <iostream>
#include "src/util/ArgumentParser.h"
#include "src/simulator/Simulator.h"

int main(int argc, char *argv[]) {
	ArgumentParser *ap = new ArgumentParser(argc, argv);

	Memory *mem = new Memory();

	DataSectionParser *dsp = new DataSectionParser(mem, MEM_ADDR_MIN_USER_DATA, MEM_ADDR_MAX_USER_DATA);
	TextSectionParser *tsp = new TextSectionParser(mem, MEM_ADDR_MIN_USER_TEXT, MEM_ADDR_MAX_USER_TEXT, dsp);

	MemoryLoader *ml = new MemoryLoader(tsp, dsp, ';');

	Simulator *sim = new Simulator(mem, ml);
	ERROR_CODE result;

	sim->setMode(ap->getMode());
	result = sim->run(ap->getRunFile());

	mem->print();

	printError(result);

	return result;
}