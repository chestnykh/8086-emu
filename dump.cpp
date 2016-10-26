#include "instructions.h"
#include <cstdio>
#include <bitset>
#include <iomanip>
#include <iostream>

using std::cout;

void dumpHex(struct instruction *instr)
{

	cout<<"HEXADECIMAL:\n";
	for(uint8_t i=1; i<=instr -> size; i++){
		cout<<"***Byte number "<<(unsigned)i<<"***\n";
		cout<<"Full byte: ";
		if(i == 1){
			printf("0x%02x\n", instr -> one);
			printf("Opcode:    0x%02x\n", OPCODE(instr));
			printf("D:         0x%02x\n", D(instr));
			printf("W:         0x%02x\n", W(instr));
		}
		if(i == 2){
			printf("0x%02x\n", instr -> two);
			printf("MOD:       0x%02x\n", MOD(instr));
			printf("REG:       0x%02x\n", REG(instr));
			printf("RM:        0x%02x\n", RM(instr));
		}
		if(i == 3){
			printf("(Low Disp) ");
			printf("0x%02x\n",LOW_DISP(instr));
		}
		if(i == 4){
			printf("(High Disp) ");
			printf("0x%02x\n", HIGH_DISP(instr));
		}
		if(i == 5){
			printf("(Low Data) ");
			printf("0x%02x\n", LOW_DATA(instr));
		}
		if(i == 6){
			printf("(High Data) ");
			printf("0x%02x\n", HIGH_DATA(instr));
		}

	}
}


void dumpBin(struct instruction *instr)
{
	cout<<"BINARY:\n";
	for(uint8_t i=1; i<instr->size; i++){
		cout<<"***Byte number "<<(unsigned)i<<"***\n";
		cout<<"Full byte: ";
		if(i == 1){
			cout<<std::bitset<8>(instr -> one)<<'\n';
			cout<<"Opcode:    ";
			cout<<std::bitset<OPCODE_SIZE>(OPCODE(instr))<<'\n';
			cout<<"D:         ";
			cout<<std::bitset<D_SIZE>(D(instr))<<'\n';
			cout<<"W:         ";
			cout<<std::bitset<W_SIZE>(W(instr))<<'\n';
		}
		if(i == 2){
			cout<<std::bitset<8>(instr -> two)<<'\n';
			cout<<"MOD:       ";
			cout<<std::bitset<MOD_SIZE>(MOD(instr))<<'\n';
			cout<<"REG:       ";
			cout<<std::bitset<REG_SIZE>(REG(instr))<<'\n';
			cout<<"RM:        ";
			cout<<std::bitset<RM_SIZE>(RM(instr))<<'\n';
		}
		if(i == 3){
			cout<<"(Low Disp) ";
			cout<<std::bitset<LOW_DISP_SIZE>(LOW_DISP(instr))<<'\n';
		}
		if(i == 4){
			cout<<"(High Disp) ";
			cout<<std::bitset<HIGH_DISP_SIZE>(HIGH_DISP(instr))<<'\n';
		}
		if(i == 5){
			cout<<"(Low Data) ";
			cout<<std::bitset<LOW_DATA_SIZE>(LOW_DATA(instr))<<'\n';
		}
		if(i == 6){
			cout<<"(High Data) ";
			cout<<std::bitset<HIGH_DATA_SIZE>(HIGH_DATA(instr))<<'\n';
		}
	}
}


void InstructionParser::dumpInstr()
{
	dumpHex(&this -> current);
	dumpBin(&this -> current);
	return;

}
