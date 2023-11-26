all:
	g++ main.cpp src/main_class.cpp src/mkdir.cpp src/rm.cpp src/cp.cpp src/mv.cpp src/cd.cpp src/ls.cpp -lstdc++fs -std=c++20