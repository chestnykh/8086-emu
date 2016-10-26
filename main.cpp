#include <instructions.h>
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
	/*
	cout<<(int)OPCODE(i)<<'\n';
	cout<<(int)D(i)<<'\n';
	cout<<(int)W(i)<<'\n';
	cout<<(int)MOD(i)<<'\n';
	cout<<(int)REG(i)<<'\n';
	cout<<(int)RM(i)<<'\n';
	cout<<(int)LOW_DISP(i)<<'\n';
	cout<<(int)HIGH_DISP(i)<<'\n';
	cout<<(int)LOW_DATA(i)<<'\n';
	cout<<(int)HIGH_DATA(i)<<'\n';
	*/
	return 0;
}
