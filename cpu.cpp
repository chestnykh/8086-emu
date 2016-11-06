#include <cpu.h>
#include "memory.h"

Cpu::Cpu(uint16_t startCs, mem_t *startIp)
{
	Cpu::Parser = new InstructionParser(startIp);
	regs.cs = startCs;
	regs.ip = startIp;
}

Cpu::~Cpu()
{

}
