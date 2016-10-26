#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <cstdint>
#include "cpu.h"
#include <typeinfo>

/*
 This file contains routines which
 can parse six-byte 8086-instruction
 */

typedef struct instruction
{
	uint8_t		one;    /*1st byte of the instruction*/
	uint8_t		two;    /*2nd byte of the instruction*/
	uint16_t	disp;   /*3rd and 4th bytes of the instruction - optional displacement*/ 
	uint16_t	data;	/*5th and 6th bytes of the instruction - optional immediate constant*/
	uint8_t		size:3;	/*real size of instruction from 1 to 6*/
} instr_t;	


uint8_t OPCODE(struct instruction instr);
uint8_t OPCODE(struct instruction *instr);

uint8_t D(struct instruction instr);
uint8_t D(struct instruction *instr);

uint8_t W(struct instruction instr);
uint8_t W(struct instruction *instr);

uint8_t MOD(struct instruction instr);
uint8_t MOD(struct instruction *instr);

uint8_t REG(struct instruction instr);
uint8_t REG(struct instruction *instr);

uint8_t RM(struct instruction instr);
uint8_t RM(struct instruction *instr);

uint8_t LOW_DISP(struct instruction instr);
uint8_t LOW_DISP(struct instruction *instr);

uint8_t HIGH_DISP(struct instruction instr);
uint8_t HIGH_DISP(struct instruction *instr);

uint8_t LOW_DATA(struct instruction instr);
uint8_t LOW_DATA(struct instruction *instr);

uint8_t HIGH_DATA(struct instruction instr);
uint8_t HIGH_DATA(struct instruction *instr);





/*
 */




class InstructionParser
{

private:
	struct instruction current;

public:
	/*constructor parameter should be a pointer to memory the instruction located in*/
	InstructionParser(struct instruction *next);
	~InstructionParser();
	void dumpInstr();

	friend void dumpHex(struct instruction *instr);
	friend void dumpBin();
	friend void dumpDec();
};



#endif /*INSTRUCTIONS_H*/
