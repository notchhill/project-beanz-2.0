general= g++ -Wall -Wextra -Wpedantic -g
objects= main.o gamescreenlinkedlist.o utility.o

progx: ${objects}
	${general} ${objects} -o bin/$@

main.o:
	${general} -c src/main.cpp -o build/$@

gamescreenlinkedlist.o: include/gamescreenlinkedlist.h
	${general} -c src/gamescreenlinkedlist.cpp -o build/$@

utility.o: utility.h
	${general} -c utility.cpp -o build/$@