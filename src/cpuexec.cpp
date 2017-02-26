#include <cpu.h>
#include <iostream>

using std::cout;

namespace Emu{

extern mem_t memory[1<<19];


void Cpu::AAD_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::GRP_80_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::GRP_81_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::GRP_82_GroupHandler(mem_t *addr)
{
	return ;
}


void Cpu::GRP_83_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::GRP_D0_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::GRP_D1_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::GRP_D2_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::GRP_D3_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::GRP_F6_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::GRP_F7_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::GRP_FE_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::GRP_FF_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::segOverridePrefixHandler(mem_t *addr)
{
	return ;
}

void Cpu::ADD_GroupHandler(mem_t *addr)
{
	ISize = 1;
	Parser -> fillInstruction(addr);
	struct instruction ICur = Parser -> getCurrentInstr();
	!ICur.w ? b_op = true : b_op = false;
	if(b_op){
		if(!ICur.d)
			src8 = getRegister<u8>(REG_FIELD, ICur);
		else
			dst8 = getRegister<u8>(REG_FIELD, ICur);
	}
	else{
		if(!ICur.d)
			src16 = getRegister<u16>(REG_FIELD, ICur);
		else
			dst16 = getRegister<u16>(REG_FIELD, ICur);
	}
	//^
	//|
	//|
	//IBegin();
	if(ICur.mod == 3){
		if(b_op){
			if(!ICur.d)
				dst8 = getRegister<u8>(RM_FIELD, ICur);
			else
				src8 = getRegister<u8>(RM_FIELD, ICur);
		}
		else{
			if(!ICur.d)
				dst16 = getRegister<u16>(RM_FIELD, ICur);
			else
				src16 = getRegister<u16>(RM_FIELD, ICur);
		}
		if(b_op){
			*dst8 += *src8;
			//flags();
			return;
		}
		*dst16 += *src16;
		//flags();
		return;
	}
	return;
	u16 memOperandAddr = getEffectiveAddress(ICur);
	/*
	 тут должен точно определяться адрес операнда в memory-массиве. 
	 как-то с помощью регистра ds или ss или es
	 */
	return ;	
}

void Cpu::PUSH_GroupHandler(mem_t *addr)
{	
	
	cout<<"PUSH\n";
	return ;
}

void Cpu::POP_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::OR_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::ADC_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::SBB_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::AND_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::DAA_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::SUB_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::DAS_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::XOR_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::AAA_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::CMP_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::AAS_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::INC_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::DEC_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::JMP_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::TEST_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::XCHG_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::MOV_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::LEA_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::NOP_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::CBW_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::CWD_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::CALL_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::WAIT_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::SAHF_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::LAHF_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::MOVS_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::CMPS_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::STOS_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::LODS_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::SCAS_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::RET_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::LES_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::LDS_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::INT_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::INTO_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::IRET_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::ROL_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::ROR_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::RCL_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::RCR_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::SAL_SHL_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::SHR_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::SAR_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::AAM_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::XLAT_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::ESC_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::LOOPNE_LOOPNZ_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::LOOPE_LOOPZ_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::LOOP_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::JCXZ_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::IN_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::OUT_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::LOCK_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::REPNE_REPNZ_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::REP_REPE_REPZ_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::HLT_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::CMC_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::NOT_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::NEG_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::MUL_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::IMUL_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::DIV_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::IDIV_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::CLC_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::STC_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::CLI_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::STI_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::CLD_GroupHandler(mem_t *addr)
{
	return ;
}

void Cpu::STD_GroupHandler(mem_t *addr)
{
	return ;
}


} //namespace Emu
