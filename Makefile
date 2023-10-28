general= g++ -Wall -Wextra -Wpedantic -g
objects= build/main.o build/gamescreenlinkedlist.o build/utility.o
# output= -c $< -o $@. Yes, we can also have this variable name in here. 
# Each .o file would run ${general} ${output} instead of ${general} -c $< -o $@
# This is not much different, but I tested it in VS Code and it worked

bin/beans2: ${objects}
	${general} ${objects} -o $@

build/main.o: src/main.cpp
	${general} -c $< -o $@

build/gamescreenlinkedlist.o: src/gamescreenlinkedlist.cpp include/gamescreenlinkedlist.h
	${general} -c $< -o $@

build/utility.o: src/utility.cpp include/utility.h
	${general} -c $< -o $@

.PHONY: clean
clean:
	rm -f ${objects} bin/beans2
