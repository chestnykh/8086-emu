#pragma once

typedef union address{
	uint16_t word;
	struct{
		unsigned char lowByte;
		unsigned char highByte;	
	};
} addr_t;


/*
 в регистре ip содержится число - номер ячейки памяти
 (смещение от базы - от cs)
 */

