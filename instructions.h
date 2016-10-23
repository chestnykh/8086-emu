#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <cstdint>
#include "cpu.h"

/*
 This file contains routines which
 can parse six-byte 8086-instruction
 */

struct instruction
{
	uint8_t		one;    /*1st byte of the instruction*/
	uint8_t		two;    /*2nd byte of the instruction*/
	uint16_t	disp;   /*3rd and 4th bytes of the instruction - optional displacement*/ 
	uint16_t	data;	/*5th and 6th bytes of the instruction - optional immediate constant*/
	uint8_t		size:3;	/*real size of instruction from 1 to 6*/
};	


#define OPCODE(instr)		(instr.one & 0x3F) 
#define D(instr)		((instr.one >> 6) & 0x01)
#define W(instr)		(instr.one >> 7)
#define MOD(instr)		(instr.two & 0x03)
#define REG(instr)		((instr.two >> 2) & 0x07)
#define RM(instr)		((instr.two >> 5))
#define LOW_DISP(instr)		(instr.disp & 0xFF)
#define HIGH_DISP(instr)	(instr.disp >> 8)
#define LOW_DATA(instr)		(instr.data & 0xFF)
#define HIGH_DATA(instr)	(instr.data >> 8)



/*
 Создадим карту: имя инструкции - адрес функции - обработчика.
 Функция - обработчик будет в дальнейшем принимать 
 в качестве аргумента саму инструкцию, регистры процессора, память, и выполнять
 указанную в инструкции операцию.
 Пока что ограничимся 
 */




class InstructionParser
{

private:
	struct instruction current;

public:
	/*constructor parameter should be a pointer to memory the instruction located in*/
	InstructionParser(struct instruction *next);
	~InstructionParser();
	void dumpInstr();


};



#endif /*INSTRUCTIONS_H*/
