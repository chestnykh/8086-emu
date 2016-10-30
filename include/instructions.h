#pragma once

#include <cstdint>
#include <map>
#include <string>

using std::string;

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


uint8_t D(unsigned char *byte);
uint8_t W(unsigned char *byte);
uint8_t MOD(unsigned char *byte);
uint8_t REG(unsigned char *byte);
uint8_t RM(unsigned char *byte);
uint8_t LOW_DISP(uint16_t *word);
uint8_t HIGH_DISP(uint16_t *word);
uint8_t LOW_DATA(uint16_t *word);
uint8_t HIGH_DATA(uint16_t *word);



/*
 prototype of function that execute the instruction:
 void execute(uint8_t code, uint8_t second, uint16_t *disp = NULL, uint16_t *data = NULL)
 */


/*This group of functions will return the void pointer that will
 cast to specific instruction handler address*/



void *ADD_GroupHandler();
void *PUSH_GroupHandler();



class InstructionParser
{

protected:
	struct instruction current;
	static std::map <string, void *(*)()> opcodeGroupHandlers;


public:
	/*constructor parameter should be a pointer to memory the instruction located in*/
	InstructionParser();
	~InstructionParser();
	void dumpInstr();

	/*address of memory array first member + (cpuregs.cs << 4 + cpuregs.ip)
	 will be the most usable argument I think*/
	void decodeInstr(unsigned char *startByte);
	void decodeInstr(struct instruction instr);
	

	friend void dumpHex(const struct instruction& instr);
	friend void dumpBin(const struct instruction& instr);
	friend void dumpDec(const struct instruction& instr);
};




