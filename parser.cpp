#include "instructions.h"
#include <iostream>
#include <stdio.h>

using std::cout;

InstructionParser::InstructionParser(struct instruction *next)
{
	current = *next;
}
InstructionParser::~InstructionParser()
{
	
}

void InstructionParser::dumpInstr()
{
	cout<<"HEXADECIMAL:\n";
	for(int i=1; i<=current.size;i++){
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
	}

}
