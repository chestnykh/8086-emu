#pragma once


#include <cstdint>
#include "instructions.h"


extern unsigned char memory[1<<20];

struct cpuregs
{
	union{
		uint16_t ax;
		struct{
			uint8_t al;
			uint8_t ah;
		};
	} ax;

	union{
		uint16_t bx;
		struct{
			uint8_t bl;
			uint8_t bh;
		};
	} bx;

	union{
		uint16_t cx;
		struct{
			uint8_t cl;
			uint8_t ch;
		};
	} cx;
	
	union{
		uint16_t dx;
		struct{
			uint8_t dl;
			uint8_t dh;
		};
	} dx;

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


/*The numbers that can identify register in REG and R/M fields of instruction
 The MOD field tells us what register in pair is used 
 */

enum regCodes{
	AL = 0,
	AX = 0,
	CL = 1,
	CX = 1,
	DL = 2,
	DX = 2,
	BL = 3,
	BX = 3,
	AH = 4,
	SP = 4,
	CH = 5,
	BP = 5,
	DH = 6,
	SI = 6,
	BH = 7,
	DI = 7
};


class Cpu : public InstructionParser
{
private:

public:
	struct cpuregs regs;
	Cpu(struct cpuregs startState) : InstructionParser(){};
	~Cpu(){};
};


