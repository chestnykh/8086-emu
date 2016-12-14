#include <cpu.h>
#include <memory.h>
#include <iostream>


typedef uint16_t u16;
typedef uint8_t u8;

namespace Emu{

extern mem_t memory[1<<20];


Cpu::Cpu(u16 startCs, unsigned startIp)
{
	Cpu::Parser = new InstructionParser(memory+startIp);
	regs.cs = startCs;
	regs.ip = startIp;
	byteRegMap = {
		{0, &regs.ax.al},
		{1, &regs.cx.cl},
		{2, &regs.dx.dl},
		{3, &regs.bx.bl},
		{4, &regs.ax.ah},
		{5, &regs.cx.ch},
		{6, &regs.dx.dh},
		{7, &regs.bx.bh}
	};

	wordRegMap = {
		{0, &regs.ax.ax},
		{1, &regs.cx.cx},
		{2, &regs.dx.dx},
		{3, &regs.bx.bx},
		{4, &regs.sp},
		{5, &regs.bp},
		{6, &regs.si},
		{7, &regs.di}
	};
	
	addrCalculator[0] = &Cpu::RM0_EffAddr;
	addrCalculator[1] = &Cpu::RM1_EffAddr;
	addrCalculator[2] = &Cpu::RM2_EffAddr;
	addrCalculator[3] = &Cpu::RM3_EffAddr;
	addrCalculator[4] = &Cpu::RM4_EffAddr;
	addrCalculator[5] = &Cpu::RM5_EffAddr;
	addrCalculator[6] = &Cpu::RM6_EffAddr;
	addrCalculator[7] = &Cpu::RM7_EffAddr;
}

Cpu::~Cpu()
{
	delete Cpu::Parser;
}

void Cpu::dump()
{
	std::cout<<"AX: "<<regs.ax.ax<<' '<<(unsigned)regs.ax.al<<' '<<(unsigned)regs.ax.ah<<'\n';
	std::cout<<"BX: "<<regs.bx.bx<<' '<<(unsigned)regs.bx.bl<<' '<<(unsigned)regs.bx.bh<<'\n';
	std::cout<<"CX: "<<regs.cx.cx<<' '<<(unsigned)regs.cx.cl<<' '<<(unsigned)regs.cx.ch<<'\n';
	std::cout<<"DX: "<<regs.dx.dx<<' '<<(unsigned)regs.dx.dl<<' '<<(unsigned)regs.dx.dh<<'\n';
}



u16 Cpu::RM0_EffAddr(struct instruction& cur)
{
	if(cur.mod == 3){
		std::cerr<<"Bad MOD value to call this function\n";
		return (u16)-1; //65535
	}
	return cur.mod == 0 ? regs.bx.bx + regs.si :
	       cur.mod == 1 ? regs.bx.bx + regs.si + cur.disp.lowDisp :
	       regs.bx.bx + regs.si + cur.disp.disp; //cur.mod == 2
}

u16 Cpu::RM1_EffAddr(struct instruction& cur)
{
	if(cur.mod == 3){
		std::cerr<<"Bad MOD value to call this function\n";
		return (u16)-1; //65535
	}
	return cur.mod == 0 ? regs.bx.bx + regs.di :
	       cur.mod == 1 ? regs.bx.bx + regs.di + cur.disp.lowDisp :
	       regs.bx.bx + regs.di + cur.disp.disp;
}

u16 Cpu::RM2_EffAddr(struct instruction& cur)
{
	if(cur.mod == 3){
		std::cerr<<"Bad MOD value to call this function\n";
		return (u16)-1; //65535
	}
	return cur.mod == 0 ? regs.bp + regs.si :
	       cur.mod == 1 ? regs.bp + regs.si + cur.disp.lowDisp :
	       regs.bp + regs.si + cur.disp.disp;
}

u16 Cpu::RM3_EffAddr(struct instruction& cur)
{
	if(cur.mod == 3){
		std::cerr<<"Bad MOD value to call this function\n";
		return (u16)-1; //65535
	}
	return cur.mod == 0 ? regs.bp + regs.di :
	       cur.mod == 1 ? regs.bp + regs.di + cur.disp.lowDisp :
	       regs.bp + regs.di + cur.disp.disp;
}

u16 Cpu::RM4_EffAddr(struct instruction& cur)
{
	if(cur.mod == 3){
		std::cerr<<"Bad MOD value to call this function\n";
		return (u16)-1; //65535
	}
	return cur.mod == 0 ? regs.si :
	       cur.mod == 1 ? regs.si + cur.disp.lowDisp :
	       regs.si + cur.disp.disp;
}

u16 Cpu::RM5_EffAddr(struct instruction& cur)
{
	if(cur.mod == 3){
		std::cerr<<"Bad MOD value to call this function\n";
		return (u16)-1; //65535
	}
	return cur.mod == 0 ? regs.di :
	       cur.mod == 1 ? regs.di + cur.disp.lowDisp :
	       regs.di + cur.disp.disp;

}

u16 Cpu::RM6_EffAddr(struct instruction& cur)
{
	if(cur.mod == 3){
		std::cerr<<"Bad MOD value to call this function\n";
		return (u16)-1; //65535
	}
	return cur.mod == 0 ? cur.disp.disp :
	       cur.mod == 1 ? regs.bp + cur.disp.lowDisp :
	       regs.bp + cur.disp.disp;
}

u16 Cpu::RM7_EffAddr(struct instruction& cur)
{
	if(cur.mod == 3){
		std::cerr<<"Bad MOD value to call this function\n";
		return (u16)-1; //65535
	}
	return cur.mod == 0 ? regs.bx.bx :
	       cur.mod == 1 ? regs.bx.bx + cur.disp.lowDisp :
	       regs.bx.bx + cur.disp.disp;
}

u16 Cpu::getEffectiveAddress(struct instruction& cur)
{
	return (this ->* addrCalculator[cur.rm])(cur);
}


template <>
u8 *Cpu::getRegister<u8>(u8 field, struct instruction& cur)
{
	if(field == REG_FIELD)
		return byteRegMap.find(cur.reg) -> second;

	return byteRegMap.find(cur.rm) -> second;
}

template <>
u16 *Cpu::getRegister<u16>(u8 field, struct instruction& cur)  
{
	if(field == REG_FIELD)
		return wordRegMap.find(cur.reg) -> second;

	return wordRegMap.find(cur.rm) -> second;
}


void Cpu::flagsState()
{
	int flags = 0;
	std::cout<<"flags = "<<flags<<'\n';
}






} //namespace Emu
