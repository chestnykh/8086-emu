CXX = g++
CXXFLAGS = -pipe -O2 -march=native

TARGET=8086-emu

OBJECTS = main.o

$(TARGET): $(OBJECTS)
	echo $^;
	$(CXX) $^ -o $@;


.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

main.o: main.cpp instructions.h


clean:
	rm -f $(TARGET) $(OBJECTS)
