#include <instructions.h>
#include <iostream>
#include <cpu.h>

using std::cout;

namespace Emu{

InstructionParser::InstructionParser(mem_t *addr)
{
	startAddr = addr;
	current = {0,0,0,0,0,0,0,0};
}

InstructionParser::InstructionParser()
{

}

InstructionParser::~InstructionParser()
{
	
}


/*
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

*/

uint8_t D(mem_t *addr)
{
	return ((addr -> lowByte) >> 1) & 0x01;
}

/*
uint8_t W(struct instruction instr)
{
	return instr.one & 0x01;
}
uint8_t W(struct instruction *instr)
{
	return (instr -> one) & 0x01;
}
*/

uint8_t W(mem_t *addr)
{
	return (addr -> lowByte) & 0x01;
}

/*
uint8_t MOD(struct instruction instr)
{
	return instr.two >> 6;
}
uint8_t MOD(struct instruction *instr)
{
	return (instr -> two) >> 6;
}
*/

uint8_t MOD(mem_t *addr)
{
	return (addr -> highByte) >> 6;
}


/*
uint8_t REG(struct instruction instr)
{
	return (instr.two >> 3) & 0x07;
}
uint8_t REG(struct instruction *instr)
{
	return ((instr -> two) >> 3) & 0x07;
}
*/

uint8_t REG(mem_t *addr)
{
	return ((addr -> highByte) >> 3) & 0x07;
}

/*
uint8_t RM(struct instruction instr)
{
	return instr.two & 0x07;
}
uint8_t RM(struct instruction *instr)
{
	return (instr -> two) & 0x07;
}

*/
uint8_t RM(mem_t *addr)
{
	return (addr -> highByte) & 0x07;
}

/*
uint8_t LOW_DISP(struct instruction instr)
{
	return (uint8_t)(instr.disp & 0xFF);
}

uint8_t LOW_DISP(struct instruction *instr)
{
	return uint8_t((instr -> disp) & 0xFF);
}
*/

uint8_t LOW_DISP(mem_t *addr)
{
	return addr -> lowByte;
}

/*
uint8_t HIGH_DISP(struct instruction instr)
{
	return (uint8_t)(instr.disp >> 8);
}

uint8_t HIGH_DISP(struct instruction *instr)
{
	return (uint8_t)((instr -> disp) >> 8);
}
*/

uint8_t HIGH_DISP(mem_t *addr)
{
	return addr -> highByte; 
}

/*
uint8_t LOW_DATA(struct instruction instr)
{
	return (uint8_t)(instr.data & 0xFF);
}

uint8_t LOW_DATA(struct instruction *instr)
{
	return (uint8_t)((instr -> data) & 0xFF);
}
*/

uint8_t LOW_DATA(mem_t *addr)
{
	return addr -> lowByte;
}

/*
uint8_t HIGH_DATA(struct instruction instr)
{
	return (uint8_t)(instr.data >> 8);
}

uint8_t HIGH_DATA(struct instruction *instr)
{
	return (uint8_t)((instr -> data) >> 8);
}
*/

uint8_t HIGH_DATA(mem_t *addr)
{
	return addr -> highByte;
}


void InstructionParser::setCurrentInstrFields(mem_t *baseAddr)
{
	current.d = D(baseAddr);
	current.w = W(baseAddr);
	current.mod = MOD(baseAddr);
	current.reg = REG(baseAddr);
	current.rm = RM(baseAddr);
	current.disp.lowDisp = LOW_DISP(baseAddr + 1);
	current.disp.highDisp = HIGH_DISP(baseAddr + 1);
	current.data.lowData = LOW_DATA(baseAddr + 2);
	current.data.highData = HIGH_DATA(baseAddr + 2);

	cout<<(unsigned)current.d<<'\n';
	cout<<(unsigned)current.w<<'\n';
	cout<<(unsigned)current.mod<<'\n';
	cout<<(unsigned)current.reg<<'\n';
	cout<<(unsigned)current.rm<<'\n';
	cout<<(unsigned)current.disp.lowDisp<<'\n';
	cout<<(unsigned)current.disp.highDisp<<'\n';
	cout<<(unsigned)current.data.lowData<<'\n';
	cout<<(unsigned)current.data.highData<<'\n';
}

struct instruction& InstructionParser::getCurrentInstr() const
{
	return curlink;
}


bool InstructionParser::isRegSource()
{
	return !current.d;
}

/*
uint8_t InstructionParser::getRegField()
{

	if(!current.w){
		return current.reg == 0 ? AL : 
		       current.reg == 1 ? CL :
		       current.reg == 2 ? DL :
		       current.reg == 3 ? BL :
		       current.reg == 4 ? AH :
		       current.reg == 5 ? CH :
		       current.reg == 6 ? DH :
		       BH;
	}
	return current.reg == 0 ? AX : 
	       current.reg == 1 ? CX :
	       current.reg == 2 ? DX :
	       current.reg == 3 ? BX :
	       current.reg == 4 ? SP :
	       current.reg == 5 ? BP :
	       current.reg == 6 ? SI :
	       DI;
}
*/

bool InstructionParser::regRegCommand()
{
	return current.mod == 3;
}



InstructionGroupHandler_t InstructionParser::getGenericGroupHandler(mem_t *baseAddr)
{
	/*mem -> lowByte in switch-statement
	 is the first mem of instruction
	 */
	switch(baseAddr -> lowByte){
		case 0x00 ... 0x05:
			return &Cpu::ADD_GroupHandler; 

		case 0x06: 
		case 0x0E: 
		case 0x16: 
		case 0x1E: 
		case 0x50 ... 0x57: 
		case 0x9C:
			return &Cpu::PUSH_GroupHandler;

		case 0x07:
		case 0x17:
		case 0x1F:
		case 0x58 ... 0x5E:
		case 0x8F: 
		case 0x9D: 
			return &Cpu::POP_GroupHandler;

		case 0x08 ... 0x0D: 
			return &Cpu::OR_GroupHandler;

		case 0x10 ... 0x15: 
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

} //namespace Emu
