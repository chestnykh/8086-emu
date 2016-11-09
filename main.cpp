#include <instructions.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cpu.h>
#include <memory.h>
#include <typeinfo>

using std::cout;

namespace Emu{

mem_t memory[1<<19];


} //namespace Emu


using namespace Emu;


int main(int argc, char *argv[])
{
	struct cpuregs r = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	std::ifstream inp(argv[1], std::ios::binary);
	inp.seekg(0, inp.end);
	int len = inp.tellg();
	inp.seekg(0, inp.beg);
	Cpu A(0, 0);
	memory[0].lowByte = 3;
	memory[0].highByte = 7;
	memory[1].lowByte = 78;
	memory[1].highByte = 32;
	memory[2].lowByte = 21;
	memory[2].highByte = 54;
	A.Parser -> setCurrentInstrFields(memory);
	mem_t *p = memory;
	//InstructionGroupHandler_t h = A.Parser -> getGenericGroupHandler(p);
	//(A.*h)(NULL);
	//A.Parser -> startByte -> word = 78;
	//cout<<A.Parser -> startByte -> word<<'\n';

	return 0;
}

