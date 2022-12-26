
main: main.cpp string.hpp string.cpp
	g++ main.cpp string.cpp && ./a.out

test: main.cpp string.hpp string.cpp
	g++ main.cpp string.cpp && valgrind --leak-check=full ./a.out