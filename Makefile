CXX = g++
CXXFLAGS = -pipe -O2 -march=native -fstrict-aliasing -std=c++14 -Wall -Wextra -Wattributes

TARGET=8086-emu

OBJECTS = main.o \
	  parser.o \


.PHONY: run

run: $(TARGET)
	./$<

$(TARGET): $(OBJECTS)
	$(CXX) $^ -o $@;


.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

main.o:	main.cpp instructions.h
parser.o: parser.cpp instructions.h		 


clean:
	rm -f $(TARGET) $(OBJECTS)
