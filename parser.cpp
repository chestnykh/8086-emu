#include <instructions.h>
#include <iostream>

using std::cout;


InstructionParser::InstructionParser(unsigned char *byteStartAddr)
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

uint8_t D(unsigned char *byte)
{
	return ((*byte) >> 1) & 0x01;
}

uint8_t W(struct instruction instr)
{
	return instr.one & 0x01;
}
uint8_t W(struct instruction *instr)
{
	return (instr -> one) & 0x01;
}

uint8_t W(unsigned char *byte)
{
	return (*byte) & 0x01;
}

uint8_t MOD(struct instruction instr)
{
	return instr.two >> 6;
}
uint8_t MOD(struct instruction *instr)
{
	return (instr -> two) >> 6;
}

uint8_t MOD(unsigned char *byte)
{
	return (*byte) >> 6;
}

uint8_t REG(struct instruction instr)
{
	return (instr.two >> 3) & 0x07;
}
uint8_t REG(struct instruction *instr)
{
	return ((instr -> two) >> 3) & 0x07;
}

uint8_t REG(unsigned char *byte)
{
	return ((*byte) >> 3) & 0x07;
}


uint8_t RM(struct instruction instr)
{
	return instr.two & 0x07;
}
uint8_t RM(struct instruction *instr)
{
	return (instr -> two) & 0x07;
}

uint8_t RM(unsigned char *byte)
{
	return (*byte) & 0x07;
}

uint8_t LOW_DISP(struct instruction instr)
{
	return (uint8_t)(instr.disp & 0xFF);
}

uint8_t LOW_DISP(struct instruction *instr)
{
	return uint8_t((instr -> disp) & 0xFF);
}

uint8_t LOW_DISP(uint16_t *word)
{
	return (uint8_t)((*word) & 0xFF);
}

uint8_t HIGH_DISP(struct instruction instr)
{
	return (uint8_t)(instr.disp >> 8);
}

uint8_t HIGH_DISP(struct instruction *instr)
{
	return (uint8_t)((instr -> disp) >> 8);
}

uint8_t HIGH_DISP(uint16_t *word)
{
	return (uint8_t)((*word) >> 8); 
}

uint8_t LOW_DATA(struct instruction instr)
{
	return (uint8_t)(instr.data & 0xFF);
}

uint8_t LOW_DATA(struct instruction *instr)
{
	return (uint8_t)((instr -> data) & 0xFF);
}

uint8_t LOW_DATA(uint16_t *word)
{
	return (uint8_t)((*word) & 0xFF);
}

uint8_t HIGH_DATA(struct instruction instr)
{
	return (uint8_t)(instr.data >> 8);
}

uint8_t HIGH_DATA(struct instruction *instr)
{
	return (uint8_t)((instr -> data) >> 8);
}

uint8_t HIGH_DATA(uint16_t *word)
{
	return (uint8_t)((*word) >> 8);
}




std::map<string, void *(InstructionParser::*)(unsigned char *)> InstructionParser::opcodeGroupHandlers = 
{
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
};



firstStepHandler_t InstructionParser::instrDecodingFirstStep(unsigned char *startByte)
{
	return &InstructionParser::ADD_GroupHandler;
}


void *InstructionParser::ADD_GroupHandler(unsigned char *byte)
{
	cout<<"ADD\n";
	return NULL;	
}

void *InstructionParser::PUSH_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::POP_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::OR_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::ADC_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::SBB_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::AND_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::DAA_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::SUB_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::DAS_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::XOR_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::AAA_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::CMP_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::AAS_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::INC_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::DEC_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::JMP_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::TEST_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::XCHG_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::MOV_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::LEA_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::NOP_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::CBW_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::CWD_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::CALL_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::WAIT_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::SAHF_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::LAHF_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::MOVS_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::CMPS_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::STOS_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::LODS_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::SCAS_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::RET_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::LES_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::LDS_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::INT_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::INTO_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::IRET_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::ROL_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::ROR_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::RCL_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::RCR_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::SAL_SHL_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::SHR_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::SAR_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::AAM_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::XLAT_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::ESC_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::LOOPNE_LOOPNZ_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::LOOPE_LOOPZ_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::LOOP_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::JCXZ_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::IN_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::OUT_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::LOCK_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::REPNE_REPNZ_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::REP_REPE_REPZ_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::HLT_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::CMC_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::NOT_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::NEG_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::MUL_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::IMUL_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::DIV_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::IDIV_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::CLC_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::STC_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::CLI_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::STI_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::CLD_GroupHandler(unsigned char *byte)
{
	return NULL;
}

void *InstructionParser::STD_GroupHandler(unsigned char *byte)
{
	return NULL;
}

