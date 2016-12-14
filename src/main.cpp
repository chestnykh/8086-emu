#include <instructions.h>
#include <iostream>
#include <fstream>
#include <cpu.h>
#include <memory.h>

using std::cout;

namespace Emu{

mem_t memory[1<<20];


} //namespace Emu


using namespace Emu;

typedef uint16_t u16;
typedef uint8_t u8;


int main(int argc, char *argv[])
{
	struct cpuregs r = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	std::ifstream inp(argv[1], std::ios::binary);
	inp.seekg(0, inp.end);
	int len = inp.tellg();
	inp.seekg(0, inp.beg);
	Cpu A(0, 0);
	A.regs.ax.ax = 15;
	struct instruction i = {
		.Opcode = 0,
		.d = 0,
		.w = 0,
		.mod = 0,
		.reg = 0,
		.rm = 0,
		.disp = 0,
		.data = 0
	};
	wreg_t reg = A.getRegister<u16>(0, i);
	A.dump();
	*reg = 86;
	A.dump();
	//cout<<memory+1<<'\n';
	//cout<<memory+2<<'\n';
	//u16 *ptr = A.getRegister<uint16_t>(REG_FIELD, A.Parser -> getCurrentInstr());
	//какая-то блять хуйня сука!!!

	//InstructionGroupHandler_t h = A.Parser -> getGenericGroupHandler(p);
	//(A.*h)(NULL);
	//A.Parser -> startByte -> word = 78;
	//cout<<A.Parser -> startByte -> word<<'\n';

	return 0;
}

