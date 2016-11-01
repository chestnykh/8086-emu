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


class InstructionParser;
typedef void *(InstructionParser::*firstStepHandler_t)(unsigned char *);





class InstructionParser
{

protected:
	unsigned char *startByte;


	struct instruction current;
	static std::map <string, void *(InstructionParser::*)(unsigned char *)> opcodeGroupHandlers;
	void *ADD_GroupHandler(unsigned char *byte);
	void *PUSH_GroupHandler(unsigned char *byte);
	void *POP_GroupHandler(unsigned char *byte);
	void *OR_GroupHandler(unsigned char *byte);
	void *ADC_GroupHandler(unsigned char *byte);
	void *SBB_GroupHandler(unsigned char *byte);
	void *AND_GroupHandler(unsigned char *byte);
	void *DAA_GroupHandler(unsigned char *byte);
	void *SUB_GroupHandler(unsigned char *byte);
	void *DAS_GroupHandler(unsigned char *byte);
	void *XOR_GroupHandler(unsigned char *byte);
	void *AAA_GroupHandler(unsigned char *byte);
	void *CMP_GroupHandler(unsigned char *byte);
	void *AAS_GroupHandler(unsigned char *byte);
	void *INC_GroupHandler(unsigned char *byte);
	void *DEC_GroupHandler(unsigned char *byte);
	void *JMP_GroupHandler(unsigned char *byte); /*all jumps except jcxz*/
	void *TEST_GroupHandler(unsigned char *byte);
	void *XCHG_GroupHandler(unsigned char *byte);
	void *MOV_GroupHandler(unsigned char *byte);
	void *LEA_GroupHandler(unsigned char *byte);
	void *NOP_GroupHandler(unsigned char *byte);
	void *CBW_GroupHandler(unsigned char *byte);
	void *CWD_GroupHandler(unsigned char *byte);
	void *CALL_GroupHandler(unsigned char *byte);
	void *WAIT_GroupHandler(unsigned char *byte);
	void *SAHF_GroupHandler(unsigned char *byte);
	void *LAHF_GroupHandler(unsigned char *byte);
	void *MOVS_GroupHandler(unsigned char *byte);
	void *CMPS_GroupHandler(unsigned char *byte);
	void *STOS_GroupHandler(unsigned char *byte);
	void *LODS_GroupHandler(unsigned char *byte);
	void *SCAS_GroupHandler(unsigned char *byte);
	void *RET_GroupHandler(unsigned char *byte);
	void *LES_GroupHandler(unsigned char *byte);
	void *LDS_GroupHandler(unsigned char *byte);
	void *INT_GroupHandler(unsigned char *byte);
	void *INTO_GroupHandler(unsigned char *byte);
	void *IRET_GroupHandler(unsigned char *byte);
	void *ROL_GroupHandler(unsigned char *byte);
	void *ROR_GroupHandler(unsigned char *byte);
	void *RCL_GroupHandler(unsigned char *byte);
	void *RCR_GroupHandler(unsigned char *byte);
	void *SAL_SHL_GroupHandler(unsigned char *byte);
	void *SHR_GroupHandler(unsigned char *byte);
	void *SAR_GroupHandler(unsigned char *byte);
	void *AAM_GroupHandler(unsigned char *byte);
	void *XLAT_GroupHandler(unsigned char *byte);
	void *ESC_GroupHandler(unsigned char *byte);
	void *LOOPNE_LOOPNZ_GroupHandler(unsigned char *byte);
	void *LOOPE_LOOPZ_GroupHandler(unsigned char *byte);
	void *LOOP_GroupHandler(unsigned char *byte);
	void *JCXZ_GroupHandler(unsigned char *byte);
	void *IN_GroupHandler(unsigned char *byte);
	void *OUT_GroupHandler(unsigned char *byte);
	void *LOCK_GroupHandler(unsigned char *byte); /*prefix*/
	void *REPNE_REPNZ_GroupHandler(unsigned char *byte);
	void *REP_REPE_REPZ_GroupHandler(unsigned char *byte);
	void *HLT_GroupHandler(unsigned char *byte);
	void *CMC_GroupHandler(unsigned char *byte);
	void *NOT_GroupHandler(unsigned char *byte);
	void *NEG_GroupHandler(unsigned char *byte);
	void *MUL_GroupHandler(unsigned char *byte);
	void *IMUL_GroupHandler(unsigned char *byte);
	void *DIV_GroupHandler(unsigned char *byte);
	void *IDIV_GroupHandler(unsigned char *byte);
	void *CLC_GroupHandler(unsigned char *byte);
	void *STC_GroupHandler(unsigned char *byte);
	void *CLI_GroupHandler(unsigned char *byte);
	void *STI_GroupHandler(unsigned char *byte);
	void *CLD_GroupHandler(unsigned char *byte);
	void *STD_GroupHandler(unsigned char *byte);


	void *segOverridePrefixHandler();


public:
	/*constructor parameter should be a pointer to memory the instruction located in */
	InstructionParser(unsigned char *byteStartAddr);

	/*overloaded constructor, for child classes*/
	InstructionParser();

	~InstructionParser();
	void dumpInstr();

	/*address of memory array first member + (cpuregs.cs << 4 + cpuregs.ip)
	 will be the most usable argument I think*/
	firstStepHandler_t instrDecodingFirstStep(unsigned char *startByte);
	void decodeInstr(struct instruction instr);
	

	friend void dumpHex(const struct instruction& instr);
	friend void dumpBin(const struct instruction& instr);
	friend void dumpDec(const struct instruction& instr);
};
	

