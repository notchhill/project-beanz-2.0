general= g++ -Wall -Wextra -Wpedantic -g
objects= build/main.o build/gamescreenlinkedlist.o build/utility.o

bin/progx: ${objects}
	${general} ${objects} -o $@

build/main.o: src/main.cpp
	${general} -c $< -o $@

build/gamescreenlinkedlist.o: src/gamescreenlinkedlist.cpp include/gamescreenlinkedlist.h
	${general} -c $< -o $@

build/utility.o: src/utility.cpp include/utility.h
	${general} -c $< -o $@
