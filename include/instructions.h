#pragma once

#include <cstdint>
#include <map>
#include <string>
#include "memory.h"

using std::string;

namespace Emu{


/*
 This file contains routines which
 can parse six-mem 8086-instruction
 */

typedef struct instruction
{
	uint8_t Opcode;
	uint8_t d;
	uint8_t w;
	uint8_t mod;
	uint8_t reg;
	uint8_t rm;

	union{
		uint16_t disp;
		struct{
			uint8_t lowDisp;
			uint16_t highDisp;
		};
	} disp;

	union{
		uint16_t data;
		struct{
			uint8_t lowData;
			uint16_t highData;
		};
	} data;
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


/*
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

*/

uint8_t D(mem_t *addr);
uint8_t W(mem_t *addr);
uint8_t MOD(mem_t *addr);
uint8_t REG(mem_t *addr);
uint8_t RM(mem_t *addr);
uint8_t LOW_DISP(mem_t *addr);
uint8_t HIGH_DISP(mem_t *addr);
uint8_t LOW_DATA(mem_t *addr);
uint8_t HIGH_DATA(mem_t *addr);



class Cpu;
typedef void (Cpu::*InstructionGroupHandler_t)(mem_t *);


class InstructionParser{
private:
	struct instruction current;
//	static std::map <mem_t, void *(InstructionParser::*)(addr_t *)> opcodeGroupHandlers;


public:
	mem_t *startAddr;

	void setCurrentInstrFields(mem_t *baseAddr);
	struct instruction getCurrentInstr() const;
	/*constructor parameter should be a pointer to memory the instruction located in */
	InstructionParser(mem_t *addr);

	/*overloaded constructor, for child classes*/
	InstructionParser();

	~InstructionParser();
	void dumpInstr();
	InstructionGroupHandler_t getGenericGroupHandler(mem_t *addr);

	/*memess of memory array first member + (cpuregs.cs << 4 + cpuregs.ip)
	 will be the most usable argument I think*/
	void decodeInstr(struct instruction instr);


	/*baseAddr means the startAddress of instruction (first 2 bytes)*/
	bool isRegSource(); //check whether REG field identifies source operand or dest operand
	bool regRegCommand();
	uint8_t defRegField();

	friend void dumpHex(const struct instruction& instr);
	friend void dumpBin(const struct instruction& instr);
	friend void dumpDec(const struct instruction& instr);
};
	

} //namespace Emu
