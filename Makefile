CXX = g++
CXXFLAGS = -pipe -O2 -march=native -fstrict-aliasing -std=c++11 -Wall -Wextra

TARGET=8086-emu

OBJECTS = main.o \
	  parser.o \
	  dump.o


.PHONY: run

run: $(TARGET)
	./$<

$(TARGET): $(OBJECTS)
	$(CXX) $^ -o $@;


.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

main.o:	main.cpp instructions.h
parser.o: parser.cpp instructions.h
dump.o: dump.cpp dump.h


clean:
	rm -f $(TARGET) $(OBJECTS)
