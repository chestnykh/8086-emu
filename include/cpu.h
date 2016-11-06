#pragma once


#include <cstdint>
#include "instructions.h"
#include "memory.h"



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
	uint16_t *ip; /*Instruction Pointer*/
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

class Cpu;
typedef void (Cpu::*InstructionGroupHandler_t)(addr_t *);

class Cpu{

private:
	struct cpuregs regs;



	void ADD_GroupHandler(addr_t *addr);
	void PUSH_GroupHandler(addr_t *addr);
	void POP_GroupHandler(addr_t *addr);
	void OR_GroupHandler(addr_t *addr);
	void ADC_GroupHandler(addr_t *addr);
	void SBB_GroupHandler(addr_t *addr);
	void AND_GroupHandler(addr_t *addr);
	void DAA_GroupHandler(addr_t *addr);
	void SUB_GroupHandler(addr_t *addr);
	void DAS_GroupHandler(addr_t *addr);
	void XOR_GroupHandler(addr_t *addr);
	void AAA_GroupHandler(addr_t *addr);
	void CMP_GroupHandler(addr_t *addr);
	void AAS_GroupHandler(addr_t *addr);
	void INC_GroupHandler(addr_t *addr);
	void DEC_GroupHandler(addr_t *addr);
	void JMP_GroupHandler(addr_t *addr); /*all jumps except jcxz*/
	void TEST_GroupHandler(addr_t *addr);
	void XCHG_GroupHandler(addr_t *addr);
	void MOV_GroupHandler(addr_t *addr);
	void LEA_GroupHandler(addr_t *addr);
	void NOP_GroupHandler(addr_t *addr);
	void CBW_GroupHandler(addr_t *addr);
	void CWD_GroupHandler(addr_t *addr);
	void CALL_GroupHandler(addr_t *addr);
	void WAIT_GroupHandler(addr_t *addr);
	void SAHF_GroupHandler(addr_t *addr);
	void LAHF_GroupHandler(addr_t *addr);
	void MOVS_GroupHandler(addr_t *addr);
	void CMPS_GroupHandler(addr_t *addr);
	void STOS_GroupHandler(addr_t *addr);
	void LODS_GroupHandler(addr_t *addr);
	void SCAS_GroupHandler(addr_t *addr);
	void RET_GroupHandler(addr_t *addr);
	void LES_GroupHandler(addr_t *addr);
	void LDS_GroupHandler(addr_t *addr);
	void INT_GroupHandler(addr_t *addr);
	void INTO_GroupHandler(addr_t *addr);
	void IRET_GroupHandler(addr_t *addr);
	void ROL_GroupHandler(addr_t *addr);
	void ROR_GroupHandler(addr_t *addr);
	void RCL_GroupHandler(addr_t *addr);
	void RCR_GroupHandler(addr_t *addr);
	void SAL_SHL_GroupHandler(addr_t *addr);
	void SHR_GroupHandler(addr_t *addr);
	void SAR_GroupHandler(addr_t *addr);
	void AAM_GroupHandler(addr_t *addr);
	void AAD_GroupHandler(addr_t *addr);
	void XLAT_GroupHandler(addr_t *addr);
	void ESC_GroupHandler(addr_t *addr);
	void LOOPNE_LOOPNZ_GroupHandler(addr_t *addr);
	void LOOPE_LOOPZ_GroupHandler(addr_t *addr);
	void LOOP_GroupHandler(addr_t *addr);
	void JCXZ_GroupHandler(addr_t *addr);
	void IN_GroupHandler(addr_t *addr);
	void OUT_GroupHandler(addr_t *addr);
	void LOCK_GroupHandler(addr_t *addr); /*prefix*/
	void REPNE_REPNZ_GroupHandler(addr_t *addr);
	void REP_REPE_REPZ_GroupHandler(addr_t *addr);
	void HLT_GroupHandler(addr_t *addr);
	void CMC_GroupHandler(addr_t *addr);
	void NOT_GroupHandler(addr_t *addr);
	void NEG_GroupHandler(addr_t *addr);
	void MUL_GroupHandler(addr_t *addr);
	void IMUL_GroupHandler(addr_t *addr);
	void DIV_GroupHandler(addr_t *addr);
	void IDIV_GroupHandler(addr_t *addr);
	void CLC_GroupHandler(addr_t *addr);
	void STC_GroupHandler(addr_t *addr);
	void CLI_GroupHandler(addr_t *addr);
	void STI_GroupHandler(addr_t *addr);
	void CLD_GroupHandler(addr_t *addr);
	void STD_GroupHandler(addr_t *addr);

	void GRP_80_GroupHandler(addr_t *addr);
	void GRP_81_GroupHandler(addr_t *addr);
	void GRP_82_GroupHandler(addr_t *addr);
	void GRP_83_GroupHandler(addr_t *addr);
	void GRP_D0_GroupHandler(addr_t *addr);
	void GRP_D1_GroupHandler(addr_t *addr);
	void GRP_D2_GroupHandler(addr_t *addr);
	void GRP_D3_GroupHandler(addr_t *addr);
	void GRP_F6_GroupHandler(addr_t *addr);
	void GRP_F7_GroupHandler(addr_t *addr);
	void GRP_FE_GroupHandler(addr_t *addr);
	void GRP_FF_GroupHandler(addr_t *addr);
	void segOverridePrefixHandler(addr_t *addr);


public:
	friend class InstructionParser;
	InstructionParser *Parser;

	Cpu(addr_t *instrAddr);
	~Cpu();
};


