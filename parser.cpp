#include <instructions.h>
#include <iostream>
#include "memory.h"
#include <cpu.h>

using std::cout;


InstructionParser::InstructionParser(mem_t *addr)
{
	startAddr = addr;
}

InstructionParser::InstructionParser()
{

}

InstructionParser::~InstructionParser()
{
	
}



uint8_t OPCODE(struct instruction instr)
{
	return instr.one >> 2;
}

uint8_t OPCODE(struct instruction *instr)
{
	return (instr -> one) >> 2;
}


uint8_t D(struct instruction instr)
{
	return (instr.one >> 1) & 0x01;
}
uint8_t D(struct instruction *instr)
{
	return ((instr -> one) >> 1) & 0x01;
}

uint8_t D(mem_t *addr)
{
	return ((addr -> lowByte) >> 1) & 0x01;
}

uint8_t W(struct instruction instr)
{
	return instr.one & 0x01;
}
uint8_t W(struct instruction *instr)
{
	return (instr -> one) & 0x01;
}

uint8_t W(mem_t *addr)
{
	return (addr -> lowByte) & 0x01;
}

uint8_t MOD(struct instruction instr)
{
	return instr.two >> 6;
}
uint8_t MOD(struct instruction *instr)
{
	return (instr -> two) >> 6;
}

uint8_t MOD(mem_t *addr)
{
	return (addr -> highByte) >> 6;
}

uint8_t REG(struct instruction instr)
{
	return (instr.two >> 3) & 0x07;
}
uint8_t REG(struct instruction *instr)
{
	return ((instr -> two) >> 3) & 0x07;
}

uint8_t REG(mem_t *addr)
{
	return ((addr -> highByte) >> 3) & 0x07;
}

uint8_t RM(struct instruction instr)
{
	return instr.two & 0x07;
}
uint8_t RM(struct instruction *instr)
{
	return (instr -> two) & 0x07;
}

uint8_t RM(mem_t *addr)
{
	return (addr -> highByte) & 0x07;
}

uint8_t LOW_DISP(struct instruction instr)
{
	return (uint8_t)(instr.disp & 0xFF);
}

uint8_t LOW_DISP(struct instruction *instr)
{
	return uint8_t((instr -> disp) & 0xFF);
}

uint8_t LOW_DISP(mem_t *addr)
{
	return addr -> lowByte;
}

uint8_t HIGH_DISP(struct instruction instr)
{
	return (uint8_t)(instr.disp >> 8);
}

uint8_t HIGH_DISP(struct instruction *instr)
{
	return (uint8_t)((instr -> disp) >> 8);
}

uint8_t HIGH_DISP(mem_t *addr)
{
	return addr -> highByte; 
}

uint8_t LOW_DATA(struct instruction instr)
{
	return (uint8_t)(instr.data & 0xFF);
}

uint8_t LOW_DATA(struct instruction *instr)
{
	return (uint8_t)((instr -> data) & 0xFF);
}

uint8_t LOW_DATA(mem_t *addr)
{
	return addr -> lowByte;
}

uint8_t HIGH_DATA(struct instruction instr)
{
	return (uint8_t)(instr.data >> 8);
}

uint8_t HIGH_DATA(struct instruction *instr)
{
	return (uint8_t)((instr -> data) >> 8);
}

uint8_t HIGH_DATA(mem_t *addr)
{
	return addr -> highByte;
}




//std::map<mem_t, void *(Cpu::*)(addr_t *)> Cpu::opcodeGroupHandlers = 
//{
	/*The table below will be rewritten*/
	/*
	{"add", &Cpu::ADD_GroupHandler},
	{"push", &Cpu::PUSH_GroupHandler},
	{"pop", &Cpu::POP_GroupHandler},
	{"or", &Cpu::OR_GroupHandler},
	{"adc", &Cpu::ADC_GroupHandler},
	{"sbb", &Cpu::SBB_GroupHandler},
	{"and", &Cpu::AND_GroupHandler},
	{"daa", &Cpu::DAA_GroupHandler},
	{"sub", &Cpu::SUB_GroupHandler},
	{"das", &Cpu::DAS_GroupHandler},
	{"xor", &Cpu::XOR_GroupHandler},
	{"aaa", &Cpu::AAA_GroupHandler},
	{"cmp", &Cpu::CMP_GroupHandler},
	{"aas", &Cpu::AAS_GroupHandler},
	{"inc", &Cpu::INC_GroupHandler},
	{"dec", &Cpu::DEC_GroupHandler},
	{"jmp", &Cpu::JMP_GroupHandler},
	{"test", &Cpu::TEST_GroupHandler},
	{"xchg", &Cpu::XCHG_GroupHandler},
	{"mov", &Cpu::MOV_GroupHandler},
	{"lea", &Cpu::LEA_GroupHandler},
	{"nop", &Cpu::NOP_GroupHandler},
	{"cbw", &Cpu::CBW_GroupHandler},
	{"cwd", &Cpu::CWD_GroupHandler},
	{"call", &Cpu::CALL_GroupHandler},
	{"wait", &Cpu::WAIT_GroupHandler},
	{"sahf", &Cpu::SAHF_GroupHandler},
	{"lahf", &Cpu::LAHF_GroupHandler},
	{"movs", &Cpu::MOVS_GroupHandler},
	{"cmps", &Cpu::CMPS_GroupHandler},
	{"stos", &Cpu::STOS_GroupHandler},
	{"lods", &Cpu::LODS_GroupHandler},
	{"scas", &Cpu::SCAS_GroupHandler},
	{"ret", &Cpu::RET_GroupHandler},
	{"les", &Cpu::LES_GroupHandler},
	{"lds", &Cpu::LDS_GroupHandler},
	{"int", &Cpu::INT_GroupHandler},
	{"into", &Cpu::INTO_GroupHandler},
	{"iret", &Cpu::IRET_GroupHandler},
	{"rol", &Cpu::ROL_GroupHandler},
	{"ror", &Cpu::ROR_GroupHandler},
	{"rcl", &Cpu::RCL_GroupHandler},
	{"rcr", &Cpu::RCR_GroupHandler},
	{"sal", &Cpu::SAL_SHL_GroupHandler},
	{"shr", &Cpu::SHR_GroupHandler},
	{"sar", &Cpu::SAR_GroupHandler},
	{"aam", &Cpu::AAM_GroupHandler},
	{"xlat", &Cpu::XLAT_GroupHandler},
	{"esc", &Cpu::ESC_GroupHandler},
	{"loopne_loopnz", &Cpu::LOOPNE_LOOPNZ_GroupHandler},
	{"loope_loopz", &Cpu::LOOPE_LOOPZ_GroupHandler},
	{"loop", &Cpu::LOOP_GroupHandler},
	{"jcxz", &Cpu::JCXZ_GroupHandler},
	{"in", &Cpu::IN_GroupHandler},
	{"out", &Cpu::OUT_GroupHandler},
	{"lock", &Cpu::LOCK_GroupHandler},
	{"repne_repnz", &Cpu::REPNE_REPNZ_GroupHandler},
	{"rep_repe_repz", &Cpu::REP_REPE_REPZ_GroupHandler},
	{"hlt", &Cpu::HLT_GroupHandler},
	{"cmc", &Cpu::CMC_GroupHandler},
	{"not", &Cpu::NOT_GroupHandler},
	{"neg", &Cpu::NEG_GroupHandler},
	{"mul", &Cpu::MUL_GroupHandler},
	{"imul", &Cpu::IMUL_GroupHandler},
	{"div", &Cpu::DIV_GroupHandler},
	{"idiv", &Cpu::IDIV_GroupHandler},
	{"clc", &Cpu::CLC_GroupHandler},
	{"stc", &Cpu::STC_GroupHandler},
	{"cli", &Cpu::CLI_GroupHandler},
	{"sti", &Cpu::STI_GroupHandler},
	{"cld", &Cpu::CLD_GroupHandler},
	{"std", &Cpu::STD_GroupHandler}
	*/
//};



InstructionGroupHandler_t InstructionParser::getGenericGroupHandler(mem_t *addr)
{
	/*mem -> lowByte in switch-statement
	 is the first mem of instruction
	 */
	switch(addr -> lowByte){
		case 0x00 ... 0x05: /*add*/
			return &Cpu::ADD_GroupHandler; 

		case 0x06: /*push es*/
		case 0x0E: /*push cs*/
		case 0x16: /*push ss*/
		case 0x1E: /*push ds*/
		case 0x50 ... 0x57: /*push general registers*/
		case 0x9C: /*pushf*/
			return &Cpu::PUSH_GroupHandler;

		case 0x07: /*pop es*/
		case 0x17: /*pop ss*/
		case 0x1F: /*pop ds*/
		case 0x58 ... 0x5E: /*pop general register*/	
		case 0x8F: /*pop reg16/mem16 */
		case 0x9D: /*popf*/
			return &Cpu::POP_GroupHandler;

		case 0x08 ... 0x0D: /*or*/
			return &Cpu::OR_GroupHandler;

		case 0x10 ... 0x15: /*adc*/
			return &Cpu::ADC_GroupHandler;

		case 0x18 ... 0x1D:
			return &Cpu::SBB_GroupHandler;

		case 0x20 ... 0x25:
			return &Cpu::AND_GroupHandler;

		case 0x26:
		case 0x2E:
		case 0x36:
		case 0x3E:
			return &Cpu::segOverridePrefixHandler;

		case 0x27:
			return &Cpu::DAA_GroupHandler;	

		case 0x28 ... 0x2D:
			return &Cpu::SUB_GroupHandler;

		case 0x2F:
			return &Cpu::DAS_GroupHandler;

		case 0x30 ... 0x35:
			return &Cpu::XOR_GroupHandler;

		case 0x37:
			return &Cpu::AAA_GroupHandler;

		case 0x38 ... 0x3D:
			return &Cpu::CMP_GroupHandler;

		case 0x3F:
			return &Cpu::AAS_GroupHandler;

		case 0x40 ... 0x47:
		       return &Cpu::INC_GroupHandler;

		case 0x48 ... 0x4F:
			return &Cpu::DEC_GroupHandler;

		case 0x70 ... 0x7F:
		case 0xE9 ... 0xEB:
			return &Cpu::JMP_GroupHandler;

		case 0x80:
			return &Cpu::GRP_80_GroupHandler;

		case 0x81:
			return &Cpu::GRP_81_GroupHandler;

		case 0x82:
			return &Cpu::GRP_82_GroupHandler;

		case 0x83:
			return &Cpu::GRP_82_GroupHandler;

		case 0x84 ... 0x85:
		case 0xA8 ... 0xA9:
			return &Cpu::TEST_GroupHandler;

		case 0x86 ... 0x87:
		case 0x91 ... 0x97:
			return &Cpu::XCHG_GroupHandler;

		case 0x90:
		       return &Cpu::NOP_GroupHandler;	

		case 0x88 ... 0x8C:
		case 0x8E:
		case 0xA0 ... 0xA3:
		case 0xB0 ... 0xBF:
		case 0xC6 ... 0xC7: 
			return &Cpu::MOV_GroupHandler;	       

		case 0x8D:
			return &Cpu::LEA_GroupHandler;

		case 0x98:
			return &Cpu::CBW_GroupHandler;

		case 0x99:
			return &Cpu::CWD_GroupHandler;

		case 0x9A:
		case 0xE8:
			return &Cpu::CALL_GroupHandler;

		case 0x9B:
			return &Cpu::WAIT_GroupHandler;

		case 0x9E:
			return &Cpu::SAHF_GroupHandler;

		case 0x9F:
			return &Cpu::LAHF_GroupHandler;

		case 0xA4 ... 0xA5:
			return &Cpu::MOVS_GroupHandler;

		case 0xA6 ... 0xA7:
			return &Cpu::CMPS_GroupHandler;

		case 0xAA ... 0xAB:
			return &Cpu::STOS_GroupHandler;	

		case 0xAC ... 0xAD:
			return &Cpu::LODS_GroupHandler;

		case 0xAE ... 0xAF:
			return &Cpu::SCAS_GroupHandler;

		case 0xC2 ... 0xC3:
		case 0xCA ... 0xCB:
			return &Cpu::RET_GroupHandler;

		case 0xC4:
			return &Cpu::LES_GroupHandler;

		case 0xC5:
			return &Cpu::LDS_GroupHandler;

		case 0xCC ... 0xCD:
			return &Cpu::INT_GroupHandler;

		case 0xCE:
			return &Cpu::INTO_GroupHandler;

		case 0xCF:
			return &Cpu::IRET_GroupHandler;

		case 0xD0:
			return &Cpu::GRP_D0_GroupHandler;

		case 0xD1:
			return &Cpu::GRP_D1_GroupHandler;

		case 0xD2:
			return &Cpu::GRP_D2_GroupHandler;

		case 0xD3:
			return &Cpu::GRP_D3_GroupHandler;

		case 0xD4:
			return &Cpu::AAM_GroupHandler;

		case 0xD5:
			return &Cpu::AAD_GroupHandler;

		case 0xD7:
			return &Cpu::XLAT_GroupHandler;

		//??
		case 0xD8:
			return &Cpu::ESC_GroupHandler;

		case 0xE0:
			return &Cpu::LOOPNE_LOOPNZ_GroupHandler;

		case 0xE1:
			return &Cpu::LOOPE_LOOPZ_GroupHandler;

		case 0xE2:
			return &Cpu::LOOP_GroupHandler;

		case 0xE3:
			return &Cpu::JCXZ_GroupHandler;

		case 0xE4 ... 0xE5:
		case 0xEC ... 0xED:
			return &Cpu::IN_GroupHandler;

		case 0xE6 ... 0xE7:
		case 0xEE ... 0xEF:
			return &Cpu::OUT_GroupHandler;

		case 0xF0:
			return &Cpu::LOCK_GroupHandler;

		case 0xF2: 
			return &Cpu::REPNE_REPNZ_GroupHandler;

		case 0xF3:
			return &Cpu::REP_REPE_REPZ_GroupHandler;

		case 0xF4:
			return &Cpu::HLT_GroupHandler;

		case 0xF5:
			return &Cpu::CMC_GroupHandler;

		case 0xF6:
			return &Cpu::GRP_F6_GroupHandler;

		case 0xF7:
			return &Cpu::GRP_F7_GroupHandler;

		case 0xF8:
			return &Cpu::CLC_GroupHandler;

		case 0xF9:
			return &Cpu::STC_GroupHandler;

		case 0xFA:
			return &Cpu::CLI_GroupHandler;

		case 0xFB:
			return &Cpu::STI_GroupHandler;

		case 0xFC:
			return &Cpu::CLD_GroupHandler;

		case 0xFD:
			return &Cpu::STD_GroupHandler;

		case 0xFE:
			return &Cpu::GRP_FE_GroupHandler;

		case 0xFF:
			return &Cpu::GRP_FF_GroupHandler;
	}
	return NULL;
}

