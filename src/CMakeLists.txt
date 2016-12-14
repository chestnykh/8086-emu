project(emu)
set(emu_SRCS 
	main.cpp
	cpu.cpp
	cpuexec.cpp
	parser.cpp
	dump.cpp)

add_executable(emu ${emu_SRCS})
set(CMAKE_CXX_FLAGS "-pipe -O2 -march=native -fstrict-aliasing -std=c++11 -flto -Wall -Wextra -Wno-unused-parameter")
target_include_directories(emu PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
