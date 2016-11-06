#pragma once

#include <cstdint>
#include <map>
#include <string>
#include "memory.h"

using std::string;

/*
 This file contains routines which
 can parse six-addr 8086-instruction
 */

typedef struct instruction
{
	uint8_t		one;    /*1st addr of the instruction*/
	uint8_t		two;    /*2nd addr of the instruction*/
	uint16_t	disp;   /*3rd and 4th addrs of the instruction - optional displacement*/ 
	uint16_t	data;	/*5th and 6th addrs of the instruction - optional immediate constant*/
	uint8_t		size:3;	/*real size of instruction from 1 to 6*/
} instr_t;	


/*
 Enumeration of instruction
 fields sizes
 */


enum instructionFieldsSizes{
	OPCODE_SIZE = 6,
	D_SIZE = 1,
	W_SIZE = 1,
	MOD_SIZE = 2,
	REG_SIZE = 3,
	RM_SIZE = 3,
	LOW_DISP_SIZE = 8,
	HIGH_DISP_SIZE = 8,
	LOW_DATA_SIZE = 8,
	HIGH_DATA_SIZE = 8
};



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


uint8_t D(addr_t *addr);
uint8_t W(addr_t *addr);
uint8_t MOD(addr_t *addr);
uint8_t REG(addr_t *addr);
uint8_t RM(addr_t *addr);
uint8_t LOW_DISP(addr_t *addr);
uint8_t HIGH_DISP(addr_t *addr);
uint8_t LOW_DATA(addr_t *addr);
uint8_t HIGH_DATA(addr_t *addr);


class Cpu;
typedef void (Cpu::*InstructionGroupHandler_t)(addr_t *);


class InstructionParser{
private:
	struct instruction current;
//	static std::map <addr_t, void *(InstructionParser::*)(addr_t *)> opcodeGroupHandlers;


public:
	addr_t *startByte;
	/*constructor parameter should be a pointer to memory the instruction located in */
	InstructionParser(addr_t *addrStartAddr);

	/*overloaded constructor, for child classes*/
	InstructionParser();

	~InstructionParser();
	void dumpInstr();
	InstructionGroupHandler_t getGenericGroupHandler(addr_t *addr);

	/*address of memory array first member + (cpuregs.cs << 4 + cpuregs.ip)
	 will be the most usable argument I think*/
	void decodeInstr(struct instruction instr);


	friend void dumpHex(const struct instruction& instr);
	friend void dumpBin(const struct instruction& instr);
	friend void dumpDec(const struct instruction& instr);
};
	

