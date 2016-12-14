#pragma once


#include <cstdint>
#include "instructions.h"
#include "memory.h"
#include <map>
#include <array>


typedef uint16_t u16;
typedef uint8_t u8;

typedef u8* breg_t;
typedef u16* wreg_t;

namespace Emu{


struct cpuregs
{
	union{
		u16 ax;
		struct{
			u8 al;
			u8 ah;
		};
	} ax;

	union{
		u16 bx;
		struct{
			u8 bl;
			u8 bh;
		};
	} bx;

	union{
		u16 cx;
		struct{
			u8 cl;
			u8 ch;
		};
	} cx;
	
	union{
		u16 dx;
		struct{
			u8 dl;
			u8 dh;
		};
	} dx;

	u16 sp;
	u16 bp;
	u16 si;
	u16 di;
	u16 cs;
	u16 ds;
	u16 ss;
	u16 es;
	unsigned ip; /*Instruction Pointer*/
	u16 flags;
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
typedef u16 (Cpu::*EffAddrCalc_t)(struct instruction&);



/*for getRegister()*/
#define REG_FIELD 0
#define RM_FIELD 1



/*set bits in flags register*/
#define SETCF(flags) (flags |= 1<<0)
#define SETPF(flags) (flags |= 1<<2)
#define SETAF(flags) (flags |= 1<<4)
#define SETZF(flags) (flags |= 1<<6)
#define SETSF(flags) (flags |= 1<<7)
#define SETTF(flags) (flags |= 1<<8)
#define SETIF(flags) (flags |= 1<<9)
#define SETDF(flags) (flags |= 1<<10)
#define SETOF(flags) (flags |= 1<<11)


/*clear bits in flags register*/
#define CLRCF(flags) (flags &= ~(1<<0))
#define CLRPF(flags) (flags &= ~(1<<2))
#define CLRAF(flags) (flags &= ~(1<<4))
#define CLRZF(flags) (flags &= ~(1<<6))
#define CLRSF(flags) (flags &= ~(1<<7))
#define CLRTF(flags) (flags &= ~(1<<8))
#define CLRIF(flags) (flags &= ~(1<<9))
#define CLRDF(flags) (flags &= ~(1<<10))
#define CLROF(flags) (flags &= ~(1<<11))


class Cpu{

	friend class InstructionParser;
private:

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

	u16 RM0_EffAddr(struct instruction& cur);
	u16 RM1_EffAddr(struct instruction& cur);
	u16 RM2_EffAddr(struct instruction& cur);
	u16 RM3_EffAddr(struct instruction& cur);
	u16 RM4_EffAddr(struct instruction& cur);
	u16 RM5_EffAddr(struct instruction& cur);
	u16 RM6_EffAddr(struct instruction& cur);
	u16 RM7_EffAddr(struct instruction& cur);

	u16 getEffectiveAddress(struct instruction& cur);
	InstructionParser *Parser;

	std::array<EffAddrCalc_t , 8> addrCalculator;
	std::map <u8, u8 *> byteRegMap;
	std::map <u8, u16 *> wordRegMap;

public:
	Cpu(u16 startCs , unsigned startIp);
	~Cpu();
	void flagsState();


	/*some of these interface methods
	  may be temporary
   	 */
	inline u16 word(mem_t *addr){
		return (u16)(*addr) + (u16)((*(addr+1)) << 8);
	}

	struct cpuregs regs;


	template <typename T>
	T* getRegister(u8 field, struct instruction& cur);
	//reg_t& getReg(u8 field, const struct instruction& cur);


	void dump();
};


} //namespace Emu

