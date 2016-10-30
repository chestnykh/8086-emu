#include <instructions.h>
#include <iostream>

using std::cout;


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


void InstructionParser::decodeInstr(unsigned char *startByte)
{

}


std::map<string, void*(*)()> InstructionParser::opcodeGroupHandlers = 
{
	{"add", ADD_GroupHandler},
	{"push", PUSH_GroupHandler}
};


void *ADD_GroupHandler()
{
	return NULL;
}

void *PUSH_GroupHandler()
{
	return NULL;
}

