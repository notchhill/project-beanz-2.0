general= g++ -Wall -Wextra -Wpedantic -static -g 
objects= build/main.o build/gamescreenlinkedlist.o build/puzzle.o build/player.o build/utility.o build/saves.o #build/icon.res
objectsLinux= build/main.o build/gamescreenlinkedlist.o build/puzzle.o build/player.o build/utility.o build/saves.o
objectstest= build/test.o build/gamescreenlinkedlist.o build/puzzle.o build/utility.o build/saves.o
# output= -c $< -o $@. Yes, we can also have this variable name in here. 
# Each .o file would run ${general} ${output} instead of ${general} -c $< -o $@
# This is not much different, but I tested it in VS Code and it worked

# bin/beanz2: ${objects}
#	${general} ${objects} -o $@

build: ${objects}
	${general} ${objects} -o bin/beanz2

Linux: ${objectsLinux}
	${general} ${objectsLinux} -o bin/beanz2

test: ${objectstest}
	${general} ${objectstest} -o bin/beanz2

build/main.o: src/main.cpp
	${general} -c $< -o $@

build/test.o: src/test.cpp
	${general} -c $< -o $@

build/gamescreenlinkedlist.o: src/gamescreenlinkedlist.cpp include/gamescreenlinkedlist.h
	${general} -c $< -o $@

build/puzzle.o: src/puzzle.cpp include/puzzle.h
	${general} -c $< -o $@

build/player.o: src/player.cpp include/player.h
	${general} -c $< -o $@

build/utility.o: src/utility.cpp include/utility.h
	${general} -c $< -o $@

build/saves.o: src/saves.cpp include/saves.h
	${general} -c $< -o $@

#build/icon.res: resource/resources.rc
#windres $< -O coff -o $@

.PHONY: clean
clean:
	rm -f ${objects} bin/beanz2

.PHONY: testclean
testclean:
	rm -f ${objectstest} bin/beanz2

.PHONY: wclean
wclean:
	del build\main.o build\gamescreenlinkedlist.o build\puzzle.o build\player.o build\utility.o bin\beanz2.exe
