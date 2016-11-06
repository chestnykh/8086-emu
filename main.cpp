#include <instructions.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cpu.h>
#include <memory.h>
#include <typeinfo>

using std::cout;


mem_t memory[(1<<20)/2];




int main(int argc, char *argv[])
{
	struct cpuregs r = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	std::ifstream inp(argv[1], std::ios::binary);
	inp.seekg(0, inp.end);
	int len = inp.tellg();
	inp.seekg(0, inp.beg);
	Cpu A(0, memory);
	mem_t *p = memory;
	memory[0].word = 0x0e;
	InstructionGroupHandler_t h = A.Parser -> getGenericGroupHandler(p);
	(A.*h)(NULL);
	//A.Parser -> startByte -> word = 78;
	//cout<<A.Parser -> startByte -> word<<'\n';

	return 0;
}
