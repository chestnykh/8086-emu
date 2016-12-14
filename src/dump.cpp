#include <instructions.h>
#include <cstdio>
#include <bitset>
#include <iomanip>
#include <iostream>

using std::cout;
namespace Emu{


/*
void dumpHex(const struct instruction& instr)
{
	cout<<"\nHEXADECIMAL DUMP:\n";
	for(u8 i=1; i<=instr.size; i++){
		cout<<"***Byte number "<<(unsigned)i<<"***\n";
		cout<<"FULL BYTE: ";
		if(i == 1){
			printf("0x%02x\n", instr.one);
			printf("OPCODE:    0x%02x\n", OPCODE(instr));
			printf("D:         0x%02x\n", D(instr));
			printf("W:         0x%02x\n", W(instr));
		}
		if(i == 2){
			printf("0x%02x\n", instr.two);
			printf("MOD:       0x%02x\n", MOD(instr));
			printf("REG:       0x%02x\n", REG(instr));
			printf("RM:        0x%02x\n", RM(instr));
		}
		if(i == 3){
			printf("(LOW DISP)  ");
			printf("0x%02x\n",LOW_DISP(instr));
		}
		if(i == 4){
			printf("(HIGH DISP) ");
			printf("0x%02x\n", HIGH_DISP(instr));
		}
		if(i == 5){
			printf("(LOW DATA)  ");
			printf("0x%02x\n", LOW_DATA(instr));
		}
		if(i == 6){
			printf("(HIGH DATA) ");
			printf("0x%02x\n", HIGH_DATA(instr));
		}

	}
}


void dumpBin(const struct instruction& instr)
{
	cout<<"\nBINARY DUMP:\n";
	for(u8 i=1; i<instr.size; i++){
		cout<<"***Byte number "<<(unsigned)i<<"***\n";
		cout<<"FULL BYTE: ";
		if(i == 1){
			cout<<std::bitset<8>(instr.one)<<'\n';
			cout<<"OPCODE:    ";
			cout<<std::bitset<OPCODE_SIZE>(OPCODE(instr))<<'\n';
			cout<<"D:         ";
			cout<<std::bitset<D_SIZE>(D(instr))<<'\n';
			cout<<"W:         ";
			cout<<std::bitset<W_SIZE>(W(instr))<<'\n';
		}
		if(i == 2){
			cout<<std::bitset<8>(instr.two)<<'\n';
			cout<<"MOD:       ";
			cout<<std::bitset<MOD_SIZE>(MOD(instr))<<'\n';
			cout<<"REG:       ";
			cout<<std::bitset<REG_SIZE>(REG(instr))<<'\n';
			cout<<"RM:        ";
			cout<<std::bitset<RM_SIZE>(RM(instr))<<'\n';
		}
		if(i == 3){
			cout<<"(LOW DISP)  ";
			cout<<std::bitset<LOW_DISP_SIZE>(LOW_DISP(instr))<<'\n';
		}
		if(i == 4){
			cout<<"(HIGH DISP) ";
			cout<<std::bitset<HIGH_DISP_SIZE>(HIGH_DISP(instr))<<'\n';
		}
		if(i == 5){
			cout<<"(LOW DATA)  ";
			cout<<std::bitset<LOW_DATA_SIZE>(LOW_DATA(instr))<<'\n';
		}
		if(i == 6){
			cout<<"(HIGH DATA) ";
			cout<<std::bitset<HIGH_DATA_SIZE>(HIGH_DATA(instr))<<'\n';
		}
	}
}

void dumpDec(const struct instruction& instr)
{
	cout<<"\nDECIMAL DUMP:\n";
	for(u8 i=0; i<instr.size; i++){
		cout<<"***Byte number "<<(unsigned)i<<"***\n";
		cout<<"Full byte: ";
		if(i == 1){
			cout<<(unsigned)instr.one<<'\n';
			cout<<"OPCODE:    "<<(unsigned)OPCODE(instr)<<'\n';
			cout<<"D:         "<<(unsigned)D(instr)<<'\n';
			cout<<"W:         "<<(unsigned)W(instr)<<'\n';
		}
		if(i == 2){
			cout<<(unsigned)instr.two<<'\n';
			cout<<"MOD:       "<<(unsigned)MOD(instr)<<'\n';
			cout<<"REG:       "<<(unsigned)REG(instr)<<'\n';
			cout<<"RM:        "<<(unsigned)RM(instr)<<'\n';
		}
		if(i == 3){
			cout<<"(LOW DISP)  "<<(unsigned)LOW_DISP(instr)<<'\n';
		}
		if(i == 4){
			cout<<"(HIGH DISP) "<<(unsigned)HIGH_DISP(instr)<<'\n';
		}
		if(i == 5){
			cout<<"(LOW DATA)  "<<(unsigned)LOW_DATA(instr)<<'\n';
		}
		if(i == 6){
			cout<<"(HIGH DATA) "<<(unsigned)HIGH_DATA(instr)<<'\n';
		}
	}
}


void InstructionParser::dumpInstr()
{
	dumpHex(this -> current);
	dumpBin(this -> current);
	dumpDec(this -> current);
	return;

}
*/


} //namespace Emu
