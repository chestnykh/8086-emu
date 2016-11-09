#pragma once


#include <cstdint>
#include "instructions.h"
#include "memory.h"
#include <map>


namespace Emu{


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
	unsigned ip; /*Instruction Pointer*/
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
typedef void (Cpu::*InstructionGroupHandler_t)(mem_t *);

class Cpu{

	friend class InstructionParser;
private:
	std::map <uint8_t, uint8_t> byteRegMap;
	std::map <uint8_t, uint16_t> wordRegMap;

	void ADD_GroupHandler(mem_t *addr);
	void PUSH_GroupHandler(mem_t *addr);
	void POP_GroupHandler(mem_t *addr);
	void OR_GroupHandler(mem_t *addr);
	void ADC_GroupHandler(mem_t *addr);
	void SBB_GroupHandler(mem_t *addr);
	void AND_GroupHandler(mem_t *addr);
	void DAA_GroupHandler(mem_t *addr);
	void SUB_GroupHandler(mem_t *addr);
	void DAS_GroupHandler(mem_t *addr);
	void XOR_GroupHandler(mem_t *addr);
	void AAA_GroupHandler(mem_t *addr);
	void CMP_GroupHandler(mem_t *addr);
	void AAS_GroupHandler(mem_t *addr);
	void INC_GroupHandler(mem_t *addr);
	void DEC_GroupHandler(mem_t *addr);
	void JMP_GroupHandler(mem_t *addr); /*all jumps except jcxz*/
	void TEST_GroupHandler(mem_t *addr);
	void XCHG_GroupHandler(mem_t *addr);
	void MOV_GroupHandler(mem_t *addr);
	void LEA_GroupHandler(mem_t *addr);
	void NOP_GroupHandler(mem_t *addr);
	void CBW_GroupHandler(mem_t *addr);
	void CWD_GroupHandler(mem_t *addr);
	void CALL_GroupHandler(mem_t *addr);
	void WAIT_GroupHandler(mem_t *addr);
	void SAHF_GroupHandler(mem_t *addr);
	void LAHF_GroupHandler(mem_t *addr);
	void MOVS_GroupHandler(mem_t *addr);
	void CMPS_GroupHandler(mem_t *addr);
	void STOS_GroupHandler(mem_t *addr);
	void LODS_GroupHandler(mem_t *addr);
	void SCAS_GroupHandler(mem_t *addr);
	void RET_GroupHandler(mem_t *addr);
	void LES_GroupHandler(mem_t *addr);
	void LDS_GroupHandler(mem_t *addr);
	void INT_GroupHandler(mem_t *addr);
	void INTO_GroupHandler(mem_t *addr);
	void IRET_GroupHandler(mem_t *addr);
	void ROL_GroupHandler(mem_t *addr);
	void ROR_GroupHandler(mem_t *addr);
	void RCL_GroupHandler(mem_t *addr);
	void RCR_GroupHandler(mem_t *addr);
	void SAL_SHL_GroupHandler(mem_t *addr);
	void SHR_GroupHandler(mem_t *addr);
	void SAR_GroupHandler(mem_t *addr);
	void AAM_GroupHandler(mem_t *addr);
	void AAD_GroupHandler(mem_t *addr);
	void XLAT_GroupHandler(mem_t *addr);
	void ESC_GroupHandler(mem_t *addr);
	void LOOPNE_LOOPNZ_GroupHandler(mem_t *addr);
	void LOOPE_LOOPZ_GroupHandler(mem_t *addr);
	void LOOP_GroupHandler(mem_t *addr);
	void JCXZ_GroupHandler(mem_t *addr);
	void IN_GroupHandler(mem_t *addr);
	void OUT_GroupHandler(mem_t *addr);
	void LOCK_GroupHandler(mem_t *addr); /*prefix*/
	void REPNE_REPNZ_GroupHandler(mem_t *addr);
	void REP_REPE_REPZ_GroupHandler(mem_t *addr);
	void HLT_GroupHandler(mem_t *addr);
	void CMC_GroupHandler(mem_t *addr);
	void NOT_GroupHandler(mem_t *addr);
	void NEG_GroupHandler(mem_t *addr);
	void MUL_GroupHandler(mem_t *addr);
	void IMUL_GroupHandler(mem_t *addr);
	void DIV_GroupHandler(mem_t *addr);
	void IDIV_GroupHandler(mem_t *addr);
	void CLC_GroupHandler(mem_t *addr);
	void STC_GroupHandler(mem_t *addr);
	void CLI_GroupHandler(mem_t *addr);
	void STI_GroupHandler(mem_t *addr);
	void CLD_GroupHandler(mem_t *addr);
	void STD_GroupHandler(mem_t *addr);

	void GRP_80_GroupHandler(mem_t *addr);
	void GRP_81_GroupHandler(mem_t *addr);
	void GRP_82_GroupHandler(mem_t *addr);
	void GRP_83_GroupHandler(mem_t *addr);
	void GRP_D0_GroupHandler(mem_t *addr);
	void GRP_D1_GroupHandler(mem_t *addr);
	void GRP_D2_GroupHandler(mem_t *addr);
	void GRP_D3_GroupHandler(mem_t *addr);
	void GRP_F6_GroupHandler(mem_t *addr);
	void GRP_F7_GroupHandler(mem_t *addr);
	void GRP_FE_GroupHandler(mem_t *addr);
	void GRP_FF_GroupHandler(mem_t *addr);
	void segOverridePrefixHandler(mem_t *addr);


public:
	struct cpuregs regs;


	InstructionParser *Parser;

	Cpu(uint16_t startCs , unsigned startIp);
	~Cpu();
};

} //namespace Emu

