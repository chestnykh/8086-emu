#include <instructions.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cpu.h>
#include <memory.h>
#include <typeinfo>

using std::cout;


addr_t memory[(1<<20)/2];




int main(int argc, char *argv[])
{
	struct instruction i = 
	{
		.one = 2,
		.two = 7,
		.disp = 65535-255,
		.data = 65535-255, 
		.size = 6
	};
	struct cpuregs r = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	std::ifstream inp(argv[1], std::ios::binary);
	inp.seekg(0, inp.end);
	int len = inp.tellg();
	inp.seekg(0, inp.beg);
	inp.read((char*)memory, len);

	//Cpu A(r);
	//unsigned char a = 0x03;
	//void *p = (A.*f)(NULL);

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
