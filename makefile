main: main.o library.o
	g++ main.o library.o -o main
main.o: main.cpp library.hpp
	g++ -c main.cpp -o main.o
library.o: library.cpp library.hpp book.hpp user.hpp
	g++ -c library.cpp -o library.o
clear:
	del *.o *.exe
	