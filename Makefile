general= g++ -Wall -Wextra -Wpedantic -g
objects= build/main.o build/gamescreenlinkedlist.o build/utility.o

progx: ${objects}
	${general} ${objects} -o bin/$@

main.o: src/main.cpp
	${general} -c src/main.cpp -o build/$@

gamescreenlinkedlist.o: src/gamescreenlinkedlist.cpp include/gamescreenlinkedlist.h
	${general} -c src/gamescreenlinkedlist.cpp -o build/$@

utility.o: src/utility.cpp include/utility.h
	${general} -c src/utility.cpp -o build/$@
