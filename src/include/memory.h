#pragma once

namespace Emu{

typedef union memUnit{
	uint16_t word;
	struct{
		unsigned char lowByte;
		unsigned char highByte;	
	};
} mem_t;


} //namespace Emu
