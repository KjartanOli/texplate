all: file.o args.o main.o

.PHONY: uninstall install debug
uninstall:
	rm /usr/local/bin/texplate

install: main.o file.o args.o
	g++ -std=c++17 -o /usr/local/bin/texplate main.o file.o args.o

debug: main.cpp
	g++ -g -std=c++17 -o texplate-debug main.cpp


file.o: file.cpp file.hpp
	g++ -std=c++17 -c file.cpp

args.o: args.cpp args.hpp
	g++ -std=c++17 -c args.cpp

main.o: main.cpp file.hpp args.hpp
	g++ -std=c++17 -c main.cpp
