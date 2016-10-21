#include "instructions.h"
#include <iostream>


using std::cout;

int main(int argc, char *argv[])
{
	struct instruction i = 
	{
		.one = 127,
		.two = 224,
		.disp = 65535-255,
		.data = 65535-255
	};

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

	return 0;
}
