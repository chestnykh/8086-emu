XX = g++
CXXFLAGS = -pipe -O2 -march=native -I include/ -fstrict-aliasing -std=c++11 -Wall -Wextra -Wno-unused-parameter

TARGET=8086-emu

INCLUDEDIR=include

OBJECTS = main.o \
	  parser.o \
	  cpu.o \
	  dump.o


.PHONY: run clean

run: $(TARGET)
	./$<

$(TARGET): $(OBJECTS)
	$(CXX) $^ -o $@;


.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

main.o:	main.cpp $(INCLUDEDIR)/instructions.h
parser.o: parser.cpp $(INCLUDEDIR)/instructions.h
dump.o: dump.cpp $(INCLUDEDIR)/instructions.h
cpu.o: cpu.cpp $(INCLUDEDIR)/cpu.h


clean:
	rm -f $(TARGET) $(OBJECTS)
