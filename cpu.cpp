#include <cpu.h>
#include "memory.h"

namespace Emu{

extern mem_t memory[1<<19];


Cpu::Cpu(uint16_t startCs, unsigned startIp)
{
	Cpu::Parser = new InstructionParser(memory+startIp);
	regs.cs = startCs;
	regs.ip = startIp;
	byteRegMap = {
		{0, regs.ax.al},
		{1, regs.cx.cl},
		{2, regs.dx.dl},
		{3, regs.bx.bl},
		{4, regs.ax.ah},
		{5, regs.cx.ch},
		{6, regs.dx.dh},
		{7, regs.bx.bh}
	};

	wordRegMap = {
		{0, regs.ax.ax},
		{1, regs.cx.cx},
		{2, regs.dx.dx},
		{3, regs.bx.bx},
		{4, regs.sp},
		{5, regs.bp},
		{6, regs.si},
		{7, regs.di}
	};
}

Cpu::~Cpu()
{

}




} //namespace Emu
