#pragma once

#include <cstdint>
#include <map>
#include <string>
#include "memory.h"

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


uint8_t D(addr_t *addr);
uint8_t W(addr_t *addr);
uint8_t MOD(addr_t *addr);
uint8_t REG(addr_t *addr);
uint8_t RM(addr_t *addr);
uint8_t LOW_DISP(addr_t *addr);
uint8_t HIGH_DISP(addr_t *addr);
uint8_t LOW_DATA(addr_t *addr);
uint8_t HIGH_DATA(addr_t *addr);



/*
 prototype of function that execute the instruction:
 void execute(uint8_t code, uint8_t second, uint16_t *disp = NULL, uint16_t *data = NULL)
 */


class InstructionParser;
typedef void *(InstructionParser::*firstStepHandler_t)(addr_t *);





class InstructionParser
{

protected:
	addr_t *startByte;


	struct instruction current;
	static std::map <addr_t, void *(InstructionParser::*)(addr_t *)> opcodeGroupHandlers;
	void *ADD_GroupHandler(addr_t *byte);
	void *PUSH_GroupHandler(addr_t *byte);
	void *POP_GroupHandler(addr_t *byte);
	void *OR_GroupHandler(addr_t *byte);
	void *ADC_GroupHandler(addr_t *byte);
	void *SBB_GroupHandler(addr_t *byte);
	void *AND_GroupHandler(addr_t *byte);
	void *DAA_GroupHandler(addr_t *byte);
	void *SUB_GroupHandler(addr_t *byte);
	void *DAS_GroupHandler(addr_t *byte);
	void *XOR_GroupHandler(addr_t *byte);
	void *AAA_GroupHandler(addr_t *byte);
	void *CMP_GroupHandler(addr_t *byte);
	void *AAS_GroupHandler(addr_t *byte);
	void *INC_GroupHandler(addr_t *byte);
	void *DEC_GroupHandler(addr_t *byte);
	void *JMP_GroupHandler(addr_t *byte); /*all jumps except jcxz*/
	void *TEST_GroupHandler(addr_t *byte);
	void *XCHG_GroupHandler(addr_t *byte);
	void *MOV_GroupHandler(addr_t *byte);
	void *LEA_GroupHandler(addr_t *byte);
	void *NOP_GroupHandler(addr_t *byte);
	void *CBW_GroupHandler(addr_t *byte);
	void *CWD_GroupHandler(addr_t *byte);
	void *CALL_GroupHandler(addr_t *byte);
	void *WAIT_GroupHandler(addr_t *byte);
	void *SAHF_GroupHandler(addr_t *byte);
	void *LAHF_GroupHandler(addr_t *byte);
	void *MOVS_GroupHandler(addr_t *byte);
	void *CMPS_GroupHandler(addr_t *byte);
	void *STOS_GroupHandler(addr_t *byte);
	void *LODS_GroupHandler(addr_t *byte);
	void *SCAS_GroupHandler(addr_t *byte);
	void *RET_GroupHandler(addr_t *byte);
	void *LES_GroupHandler(addr_t *byte);
	void *LDS_GroupHandler(addr_t *byte);
	void *INT_GroupHandler(addr_t *byte);
	void *INTO_GroupHandler(addr_t *byte);
	void *IRET_GroupHandler(addr_t *byte);
	void *ROL_GroupHandler(addr_t *byte);
	void *ROR_GroupHandler(addr_t *byte);
	void *RCL_GroupHandler(addr_t *byte);
	void *RCR_GroupHandler(addr_t *byte);
	void *SAL_SHL_GroupHandler(addr_t *byte);
	void *SHR_GroupHandler(addr_t *byte);
	void *SAR_GroupHandler(addr_t *byte);
	void *AAM_GroupHandler(addr_t *byte);
	void *XLAT_GroupHandler(addr_t *byte);
	void *ESC_GroupHandler(addr_t *byte);
	void *LOOPNE_LOOPNZ_GroupHandler(addr_t *byte);
	void *LOOPE_LOOPZ_GroupHandler(addr_t *byte);
	void *LOOP_GroupHandler(addr_t *byte);
	void *JCXZ_GroupHandler(addr_t *byte);
	void *IN_GroupHandler(addr_t *byte);
	void *OUT_GroupHandler(addr_t *byte);
	void *LOCK_GroupHandler(addr_t *byte); /*prefix*/
	void *REPNE_REPNZ_GroupHandler(addr_t *byte);
	void *REP_REPE_REPZ_GroupHandler(addr_t *byte);
	void *HLT_GroupHandler(addr_t *byte);
	void *CMC_GroupHandler(addr_t *byte);
	void *NOT_GroupHandler(addr_t *byte);
	void *NEG_GroupHandler(addr_t *byte);
	void *MUL_GroupHandler(addr_t *byte);
	void *IMUL_GroupHandler(addr_t *byte);
	void *DIV_GroupHandler(addr_t *byte);
	void *IDIV_GroupHandler(addr_t *byte);
	void *CLC_GroupHandler(addr_t *byte);
	void *STC_GroupHandler(addr_t *byte);
	void *CLI_GroupHandler(addr_t *byte);
	void *STI_GroupHandler(addr_t *byte);
	void *CLD_GroupHandler(addr_t *byte);
	void *STD_GroupHandler(addr_t *byte);


	void *segOverridePrefixHandler();


public:
	/*constructor parameter should be a pointer to memory the instruction located in */
	InstructionParser(addr_t *byteStartAddr);

	/*overloaded constructor, for child classes*/
	InstructionParser();

	~InstructionParser();
	void dumpInstr();

	/*address of memory array first member + (cpuregs.cs << 4 + cpuregs.ip)
	 will be the most usable argument I think*/
	firstStepHandler_t getGenericGroupHandler(addr_t *addr);
	void decodeInstr(struct instruction instr);
	

	friend void dumpHex(const struct instruction& instr);
	friend void dumpBin(const struct instruction& instr);
	friend void dumpDec(const struct instruction& instr);
};
	

