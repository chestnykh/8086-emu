#pragma once

typedef union memUnit{
	uint16_t word;
	struct{
		unsigned char lowByte;
		unsigned char highByte;	
	};
} mem_t;


#define PA(addr) (this -> cpuregs.cs << 4 + this -> cpuregs.ip)

/*
 в регистре ip содержится число - номер ячейки памяти
 (смещение от базы - от cs)
 */

