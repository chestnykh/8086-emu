#include "instructions.h"
#include <iostream>
#include <iomanip>


using std::cout;

int main(int argc, char *argv[])
{
	
	struct instruction i = 
	{
		.one = 127,
		.two = 224,
		.disp = 65535-255,
		.data = 65535-255, 
		.size = 6
	};
	InstructionParser A(&i);
	A.dumpInstr();
	//cout<<std::showbase<<std::setiosflags(std::ios::internal)<<std::setfill('0')<<std::setw(2)<<std::internal<<std::hex<<12<<'\n';
	/*
	cout<<OPCODE(i)<<'\n';
	cout<<D(i)<<'\n';
	cout<<W(i)<<'\n';
	cout<<MOD(i)<<'\n';
	cout<<REG(i)<<'\n';
	cout<<RM(i)<<'\n';
	cout<<LOW_DISP(i)<<'\n';
	cout<<HIGH_DISP(i)<<'\n';
	cout<<LOW_DATA(i)<<'\n';
	cout<<HIGH_DATA(i)<<'\n';
	*/
	

	return 0;
}
