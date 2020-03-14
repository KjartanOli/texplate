install: main.cpp
	g++ -std=c++17 -o /usr/local/bin/texplate main.cpp

debug: main.cpp
	g++ -g -std=c++17 -o texplate-debug main.cpp

.PHONY: uninstall
uninstall:
	rm /usr/local/bin/texplate
