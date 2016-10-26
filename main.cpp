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
	//if(typeid (&i) == typeid(struct instruction *)) cout<<"!!!\n";
	//decltype(&i) j;
	//j -> one = 45;
	//A.dumpInstr();
	//cout<<std::showbase<<std::setiosflags(std::ios::internal)<<std::setfill('0')<<std::setw(2)<<std::internal<<std::hex<<12<<'\n';
	
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
	
	

	return 0;
}
