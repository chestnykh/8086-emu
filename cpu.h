#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include "instructions.h"


typedef unsigned char uchar;


struct cpuregs
{
	uint16_t ax;
	uint16_t bx;
	uint16_t cx;
	uint16_t dx;
	uint16_t sp;
	uint16_t bp;
	uint16_t si;
	uint16_t di;
	uint16_t cs;
	uint16_t ds;
	uint16_t ss;
	uint16_t es;
	uint16_t ip;
	uint16_t flags;

};



/*
class  Cpu : public InstructionParser
{
private:
	struct cpuregs regs;

public:

};
*/

#endif /*CPU_H*/
