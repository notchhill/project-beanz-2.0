general= g++ -Wall -Wextra -Wpedantic -g
objects= build/main.o build/gamescreenlinkedlist.o build/utility.o
objectstest= build/test.o build/gamescreenlinkedlist.o build/utility.o
# output= -c $< -o $@. Yes, we can also have this variable name in here. 
# Each .o file would run ${general} ${output} instead of ${general} -c $< -o $@
# This is not much different, but I tested it in VS Code and it worked

# bin/beans2: ${objects}
#	${general} ${objects} -o $@

build: ${objects}
	${general} ${objects} -o bin/beans2

test: ${objectstest}
	${general} ${objectstest} -o bin/beans2

build/main.o: src/main.cpp
	${general} -c $< -o $@

build/test.o: src/test.cpp
	${general} -c $< -o $@

build/gamescreenlinkedlist.o: src/gamescreenlinkedlist.cpp include/gamescreenlinkedlist.h
	${general} -c $< -o $@

build/utility.o: src/utility.cpp include/utility.h
	${general} -c $< -o $@

.PHONY: clean
clean:
	rm -f ${objects} bin/beans2

.PHONY: testclean
testclean:
	rm -f ${objectstest} bin/beans2

.PHONY: wclean
wclean:
	del build\main.o build\gamescreenlinkedlist.o build\utility.o bin\beans2.exe
