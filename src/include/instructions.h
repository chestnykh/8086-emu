#pragma once

#include <cstdint>
#include <map>
#include <string>
#include "memory.h"

using std::string;

typedef uint16_t u16;
typedef uint8_t u8;

namespace Emu{


/*
 This file contains routines which
 can parse six-mem 8086-instruction
 */

typedef struct instruction
{
	u8 Opcode;
	u8 d;
	u8 w;
	u8 mod;
	u8 reg;
	u8 rm;

	union{
		u16 disp;
		struct{
			u8 lowDisp;
			u16 highDisp;
		};
	} disp;

	union{
		u16 data;
		struct{
			u8 lowData;
			u16 highData;
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
u8 OPCODE(struct instruction instr);
u8 OPCODE(struct instruction *instr);

u8 D(struct instruction instr);
u8 D(struct instruction *instr);

u8 W(struct instruction instr);
u8 W(struct instruction *instr);

u8 MOD(struct instruction instr);
u8 MOD(struct instruction *instr);

u8 REG(struct instruction instr);
u8 REG(struct instruction *instr);

u8 RM(struct instruction instr);
u8 RM(struct instruction *instr);

u8 LOW_DISP(struct instruction instr);
u8 LOW_DISP(struct instruction *instr);

u8 HIGH_DISP(struct instruction instr);
u8 HIGH_DISP(struct instruction *instr);

u8 LOW_DATA(struct instruction instr);
u8 LOW_DATA(struct instruction *instr);

u8 HIGH_DATA(struct instruction instr);
u8 HIGH_DATA(struct instruction *instr);

*/

u8 D(mem_t *addr);
u8 W(mem_t *addr);
u8 MOD(mem_t *addr);
u8 REG(mem_t *addr);
u8 RM(mem_t *addr);
u8 LOW_DISP(mem_t *addr);
u8 HIGH_DISP(mem_t *addr);
u8 LOW_DATA(mem_t *addr);
u8 HIGH_DATA(mem_t *addr);



class Cpu;
typedef void (Cpu::*InstructionGroupHandler_t)(mem_t *);


class InstructionParser{
private:
	struct instruction current;
	struct instruction& curlink = current;


public:
	mem_t *startAddr;

	void setCurrentInstrFields(mem_t *baseAddr);
	struct instruction& getCurrentInstr() const;
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
	//u8 getRegField();

	friend void dumpHex(const struct instruction& instr);
	friend void dumpBin(const struct instruction& instr);
	friend void dumpDec(const struct instruction& instr);
};
	

} //namespace Emu
