#include <cpu.h>
#include "memory.h"

Cpu::Cpu(addr_t *instrAddr)
{
	Cpu::Parser = new InstructionParser(instrAddr);
}

Cpu::~Cpu()
{

}
