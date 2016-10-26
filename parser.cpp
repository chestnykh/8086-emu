#include "instructions.h"
#include <iostream>
#include <cstdio>

using std::cout;


InstructionParser::InstructionParser(struct instruction *next)
{
	current = *next;
}
InstructionParser::~InstructionParser()
{
	
}


uint8_t OPCODE(struct instruction instr)
{
	return instr.one & 0x3F;
}

uint8_t OPCODE(struct instruction *instr)
{
	return (instr -> one) & 0x3F;
}

uint8_t D(struct instruction instr)
{
	return (instr.one >> 6) & 0x01;
}
uint8_t D(struct instruction *instr)
{
	return ((instr -> one) >> 6) & 0x01;
}

uint8_t W(struct instruction instr)
{
	return instr.one >> 7;
}
uint8_t W(struct instruction *instr)
{
	return (instr -> one) >> 7;
}

uint8_t MOD(struct instruction instr)
{
	return instr.two & 0x03;
}
uint8_t MOD(struct instruction *instr)
{
	return (instr -> two) & 0x03;
}

uint8_t REG(struct instruction instr)
{
	return (instr.two >> 2) & 0x07;
}
uint8_t REG(struct instruction *instr)
{
	return ((instr -> two) >> 2) & 0x07;
}

uint8_t RM(struct instruction instr)
{
	return instr.two >> 5;
}
uint8_t RM(struct instruction *instr)
{
	return (instr -> two) >> 5;
}

uint8_t LOW_DISP(struct instruction instr)
{
	return (uint8_t)(instr.disp & 0xFF);
}
uint8_t LOW_DISP(struct instruction *instr)
{
	return uint8_t((instr -> disp) & 0xFF);
}

uint8_t HIGH_DISP(struct instruction instr)
{
	return (uint8_t)(instr.disp >> 8);
}
uint8_t HIGH_DISP(struct instruction *instr)
{
	return (uint8_t)((instr -> disp) >> 8);
}

uint8_t LOW_DATA(struct instruction instr)
{
	return (uint8_t)(instr.data & 0xFF);
}

uint8_t LOW_DATA(struct instruction *instr)
{
	return (uint8_t)((instr -> data) & 0xFF);
}

uint8_t HIGH_DATA(struct instruction instr)
{
	return (uint8_t)(instr.data >> 8);
}

uint8_t HIGH_DATA(struct instruction *instr)
{
	return (uint8_t)((instr -> data) >> 8);
}

/*
void dumpHex(struct instruction *instr)
{
	struct instruction current = *instr;

	cout<<"HEXADECIMAL:\n";
	for(int i=1; i<=current.size; i++){
		cout<<"***Byte number "<<i<<"***\n";
		cout<<"Full byte: ";
		if(i == 1){
			printf("0x%02x\n", current.one);
			printf("Opcode:    0x%02x\n", OPCODE(current));
			printf("D:         0x%02x\n", D(current));
			printf("W:         0x%02x\n", W(current));
		}
		if(i == 2){
			printf("0x%02x\n", current.two);
			printf("MOD:       0x%02x\n", MOD(current));
			printf("REG:       0x%02x\n", REG(current));
			printf("RM:        0x%02x\n", RM(current));
		}
		if(i == 3){
			printf("0x%02x\n",LOW_DISP(current));
		}
		if(i == 4){
			printf("0x%02x\n", HIGH_DISP(current));
		}
		if(i == 5){
			printf("0x%02x\n", LOW_DATA(current));
		}
		if(i == 6){
			printf("0x%02x\n", HIGH_DATA(current));
		}

	}


}
*/

void InstructionParser::dumpInstr()
{
	//dumpHex();
	return;

}
