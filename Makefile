all: debug
	g++ main.cpp src/main_class.cpp src/mkdir.cpp src/rm.cpp src/cp.cpp src/mv.cpp src/cd.cpp src/ls.cpp -O2 -lstdc++fs -std=c++20

debug:
	g++ main.cpp src/main_class.cpp src/mkdir.cpp src/rm.cpp src/cp.cpp src/mv.cpp src/cd.cpp src/ls.cpp -Wall -g -lstdc++fs -std=c++20 -o output.out