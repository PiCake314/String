
main: main.cpp String.hpp String.cpp
	g++ -std=c++20 main.cpp String.cpp && ./a.out

test: main.cpp String.hpp String.cpp
	g++ -std=c++20  main.cpp String.cpp && valgrind --leak-check=full ./a.out

clear: main.cpp String.hpp String.cpp
	clear && g++ -std=c++20 main.cpp String.cpp && ./a.out