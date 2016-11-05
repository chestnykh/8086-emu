#include <instructions.h>
#include <iostream>
#include "memory.h"


using std::cout;


InstructionParser::InstructionParser(addr_t *byteStartAddr)
{
	startByte = byteStartAddr;
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

uint8_t D(addr_t *addr)
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

uint8_t W(addr_t *addr)
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

uint8_t MOD(addr_t *addr)
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

uint8_t REG(addr_t *addr)
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

uint8_t RM(addr_t *addr)
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

uint8_t LOW_DISP(addr_t *addr)
{
	return (uint8_t)(addr -> lowByte);
}

uint8_t HIGH_DISP(struct instruction instr)
{
	return (uint8_t)(instr.disp >> 8);
}

uint8_t HIGH_DISP(struct instruction *instr)
{
	return (uint8_t)((instr -> disp) >> 8);
}

uint8_t HIGH_DISP(addr_t *addr)
{
	return (uint8_t)(addr -> highByte); 
}

uint8_t LOW_DATA(struct instruction instr)
{
	return (uint8_t)(instr.data & 0xFF);
}

uint8_t LOW_DATA(struct instruction *instr)
{
	return (uint8_t)((instr -> data) & 0xFF);
}

uint8_t LOW_DATA(addr_t *addr)
{
	return (uint8_t)(addr -> lowByte);
}

uint8_t HIGH_DATA(struct instruction instr)
{
	return (uint8_t)(instr.data >> 8);
}

uint8_t HIGH_DATA(struct instruction *instr)
{
	return (uint8_t)((instr -> data) >> 8);
}

uint8_t HIGH_DATA(addr_t *addr)
{
	return (uint8_t)(addr -> highByte);
}




std::map<addr_t, void *(InstructionParser::*)(addr_t *)> InstructionParser::opcodeGroupHandlers = 
{
	/*The table below will be rewritten*/
	/*
	{"add", &InstructionParser::ADD_GroupHandler},
	{"push", &InstructionParser::PUSH_GroupHandler},
	{"pop", &InstructionParser::POP_GroupHandler},
	{"or", &InstructionParser::OR_GroupHandler},
	{"adc", &InstructionParser::ADC_GroupHandler},
	{"sbb", &InstructionParser::SBB_GroupHandler},
	{"and", &InstructionParser::AND_GroupHandler},
	{"daa", &InstructionParser::DAA_GroupHandler},
	{"sub", &InstructionParser::SUB_GroupHandler},
	{"das", &InstructionParser::DAS_GroupHandler},
	{"xor", &InstructionParser::XOR_GroupHandler},
	{"aaa", &InstructionParser::AAA_GroupHandler},
	{"cmp", &InstructionParser::CMP_GroupHandler},
	{"aas", &InstructionParser::AAS_GroupHandler},
	{"inc", &InstructionParser::INC_GroupHandler},
	{"dec", &InstructionParser::DEC_GroupHandler},
	{"jmp", &InstructionParser::JMP_GroupHandler},
	{"test", &InstructionParser::TEST_GroupHandler},
	{"xchg", &InstructionParser::XCHG_GroupHandler},
	{"mov", &InstructionParser::MOV_GroupHandler},
	{"lea", &InstructionParser::LEA_GroupHandler},
	{"nop", &InstructionParser::NOP_GroupHandler},
	{"cbw", &InstructionParser::CBW_GroupHandler},
	{"cwd", &InstructionParser::CWD_GroupHandler},
	{"call", &InstructionParser::CALL_GroupHandler},
	{"wait", &InstructionParser::WAIT_GroupHandler},
	{"sahf", &InstructionParser::SAHF_GroupHandler},
	{"lahf", &InstructionParser::LAHF_GroupHandler},
	{"movs", &InstructionParser::MOVS_GroupHandler},
	{"cmps", &InstructionParser::CMPS_GroupHandler},
	{"stos", &InstructionParser::STOS_GroupHandler},
	{"lods", &InstructionParser::LODS_GroupHandler},
	{"scas", &InstructionParser::SCAS_GroupHandler},
	{"ret", &InstructionParser::RET_GroupHandler},
	{"les", &InstructionParser::LES_GroupHandler},
	{"lds", &InstructionParser::LDS_GroupHandler},
	{"int", &InstructionParser::INT_GroupHandler},
	{"into", &InstructionParser::INTO_GroupHandler},
	{"iret", &InstructionParser::IRET_GroupHandler},
	{"rol", &InstructionParser::ROL_GroupHandler},
	{"ror", &InstructionParser::ROR_GroupHandler},
	{"rcl", &InstructionParser::RCL_GroupHandler},
	{"rcr", &InstructionParser::RCR_GroupHandler},
	{"sal", &InstructionParser::SAL_SHL_GroupHandler},
	{"shr", &InstructionParser::SHR_GroupHandler},
	{"sar", &InstructionParser::SAR_GroupHandler},
	{"aam", &InstructionParser::AAM_GroupHandler},
	{"xlat", &InstructionParser::XLAT_GroupHandler},
	{"esc", &InstructionParser::ESC_GroupHandler},
	{"loopne_loopnz", &InstructionParser::LOOPNE_LOOPNZ_GroupHandler},
	{"loope_loopz", &InstructionParser::LOOPE_LOOPZ_GroupHandler},
	{"loop", &InstructionParser::LOOP_GroupHandler},
	{"jcxz", &InstructionParser::JCXZ_GroupHandler},
	{"in", &InstructionParser::IN_GroupHandler},
	{"out", &InstructionParser::OUT_GroupHandler},
	{"lock", &InstructionParser::LOCK_GroupHandler},
	{"repne_repnz", &InstructionParser::REPNE_REPNZ_GroupHandler},
	{"rep_repe_repz", &InstructionParser::REP_REPE_REPZ_GroupHandler},
	{"hlt", &InstructionParser::HLT_GroupHandler},
	{"cmc", &InstructionParser::CMC_GroupHandler},
	{"not", &InstructionParser::NOT_GroupHandler},
	{"neg", &InstructionParser::NEG_GroupHandler},
	{"mul", &InstructionParser::MUL_GroupHandler},
	{"imul", &InstructionParser::IMUL_GroupHandler},
	{"div", &InstructionParser::DIV_GroupHandler},
	{"idiv", &InstructionParser::IDIV_GroupHandler},
	{"clc", &InstructionParser::CLC_GroupHandler},
	{"stc", &InstructionParser::STC_GroupHandler},
	{"cli", &InstructionParser::CLI_GroupHandler},
	{"sti", &InstructionParser::STI_GroupHandler},
	{"cld", &InstructionParser::CLD_GroupHandler},
	{"std", &InstructionParser::STD_GroupHandler}
	*/
};


/*
 __attribute__((must_check)) ??
 */
firstStepHandler_t InstructionParser::getGenericGroupHandler(addr_t *addr)
{
	/*addr -> lowByte in switch-statement
	 is the first byte of instruction
	 */
	switch(addr -> lowByte){
		case 0x00 ... 0x05: /*add*/
			return &InstructionParser::ADD_GroupHandler; 

		case 0x06: /*push es*/
		case 0x0E: /*push cs*/
		case 0x16: /*push ss*/
		case 0x1E: /*push ds*/
		case 0x50 ... 0x57: /*push general registers*/
		case 0x9C: /*pushf*/
			return &InstructionParser::PUSH_GroupHandler;

		case 0x07: /*pop es*/
		case 0x17: /*pop ss*/
		case 0x1F: /*pop ds*/
		case 0x58 ... 0x5E: /*pop general register*/	
		case 0x8F: /*pop reg16/mem16 */
		case 0x9D: /*popf*/
			return &InstructionParser::POP_GroupHandler;

		case 0x08 ... 0x0D: /*or*/
			return &InstructionParser::OR_GroupHandler;

		case 0x10 ... 0x15: /*adc*/
			return &InstructionParser::ADC_GroupHandler;

	
	}
	return NULL;
}


void *InstructionParser::ADD_GroupHandler(addr_t *byte)
{
	return NULL;	
}

void *InstructionParser::PUSH_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::POP_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::OR_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::ADC_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::SBB_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::AND_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::DAA_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::SUB_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::DAS_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::XOR_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::AAA_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::CMP_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::AAS_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::INC_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::DEC_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::JMP_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::TEST_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::XCHG_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::MOV_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::LEA_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::NOP_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::CBW_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::CWD_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::CALL_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::WAIT_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::SAHF_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::LAHF_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::MOVS_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::CMPS_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::STOS_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::LODS_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::SCAS_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::RET_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::LES_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::LDS_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::INT_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::INTO_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::IRET_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::ROL_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::ROR_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::RCL_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::RCR_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::SAL_SHL_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::SHR_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::SAR_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::AAM_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::XLAT_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::ESC_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::LOOPNE_LOOPNZ_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::LOOPE_LOOPZ_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::LOOP_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::JCXZ_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::IN_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::OUT_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::LOCK_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::REPNE_REPNZ_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::REP_REPE_REPZ_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::HLT_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::CMC_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::NOT_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::NEG_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::MUL_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::IMUL_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::DIV_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::IDIV_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::CLC_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::STC_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::CLI_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::STI_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::CLD_GroupHandler(addr_t *byte)
{
	return NULL;
}

void *InstructionParser::STD_GroupHandler(addr_t *byte)
{
	return NULL;
}

