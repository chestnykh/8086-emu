#include "instructions.h"
#include <iostream>

using std::cout;


InstructionParser::InstructionParser(struct instruction *next)
{
	current = *next;
}
InstructionParser::~InstructionParser()
{
	
}



uint8_t OPCODE(struct instruction instr)
{
	return instr.one & 0x3F;
}

uint8_t OPCODE(struct instruction *instr)
{
	return (instr -> one) & 0x3F;
}

uint8_t D(struct instruction instr)
{
	return (instr.one >> 6) & 0x01;
}
uint8_t D(struct instruction *instr)
{
	return ((instr -> one) >> 6) & 0x01;
}

uint8_t W(struct instruction instr)
{
	return instr.one >> 7;
}
uint8_t W(struct instruction *instr)
{
	return (instr -> one) >> 7;
}

uint8_t MOD(struct instruction instr)
{
	return instr.two & 0x03;
}
uint8_t MOD(struct instruction *instr)
{
	return (instr -> two) & 0x03;
}

uint8_t REG(struct instruction instr)
{
	return (instr.two >> 2) & 0x07;
}
uint8_t REG(struct instruction *instr)
{
	return ((instr -> two) >> 2) & 0x07;
}

uint8_t RM(struct instruction instr)
{
	return instr.two >> 5;
}
uint8_t RM(struct instruction *instr)
{
	return (instr -> two) >> 5;
}

uint8_t LOW_DISP(struct instruction instr)
{
	return (uint8_t)(instr.disp & 0xFF);
}
uint8_t LOW_DISP(struct instruction *instr)
{
	return uint8_t((instr -> disp) & 0xFF);
}

uint8_t HIGH_DISP(struct instruction instr)
{
	return (uint8_t)(instr.disp >> 8);
}
uint8_t HIGH_DISP(struct instruction *instr)
{
	return (uint8_t)((instr -> disp) >> 8);
}

uint8_t LOW_DATA(struct instruction instr)
{
	return (uint8_t)(instr.data & 0xFF);
}

uint8_t LOW_DATA(struct instruction *instr)
{
	return (uint8_t)((instr -> data) & 0xFF);
}

uint8_t HIGH_DATA(struct instruction instr)
{
	return (uint8_t)(instr.data >> 8);
}

uint8_t HIGH_DATA(struct instruction *instr)
{
	return (uint8_t)((instr -> data) >> 8);
}


