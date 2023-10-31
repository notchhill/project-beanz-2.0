# Team design document

### DESIGN

Team name: Team Beanz 2.0
Game name: Project Beanz 2.0
Contact info: Dustin, dustin.gabriel777@gmail.com

# TABLE OF CONTENTS

1.0 Design Overview.
2.0 Logical Design.
3.0 Physical Design.
    3.1 Programming language(s) and supporting tools.
    3.2 Directory and file naming structure.
    3.3 Implementation method for each shared data store.
    3.4 Interface for all public services provided by the element:
    3.5 Function Layout
    3.6 File hierarchy, compilation, makefile
        3.6.1 File hierarchy
        3.6.2 Compilation
        3.6.3 Makefile

# Design

1.0 Design Overview.
    See top level (Level 0) DFD in the screenshots of our Miro flowchart board included in the repository.
    Top level DFD consists of the player providing input to the game (Beanz 2.0) and the game (Beanz 2.0) displaying information back to the player.

2.0 Logical Design.
    Level 1 DFD shown on the Miro board contains descriptions of the logical design for the player selecting an option ingame and the correct screen being loaded.

    Player enters the name of the option they wish to choose, and a player input function passes the name to a find option function.  

    Find option function takes name of the function, grabs the unique ID assigned to the screen with that name out of (5 to start) options and passes the ID to a search function

    Search function finds the next screen by searching through the single linked list containing all the game screens unti it finds the one with the screen ID matching the one it was passed

    Display function loads the appropriate screen, outputtingn the text blurb and list of options to the terminal window


    Level 2 DFD describes linked list manipulation functions

    Player runs the shell script, which runs the game binary, which in turn runs main.cpp, which calls the load() function. Load function opens the input.txt file containing the text blurbs and their associated screen IDs. Load function creates a string to hold the text as well as creating a gameScreenLinkedList node. Load function then opens input.txt. Load function now uses a loop to read the first line of input.txt and puts the text into inputStuff. The screenID of the new node is set to inputStuff. This is then repeated until load() reaches the end of the file input.txt. For each of the five options associated with a single screen, load() reads the options and their associated description out of the input.txt file and puts them into the option1, option 2 etc member variables of the node. Load() will eventually reach the end of the input.txt file once all options are put into the linked list by pushBack(). The text from inputStuff is passed to pushBack() to facilitate creating the linked list.

3.0 Physical Design.

    3.1 Programming language(s) and supporting tools.
        C++, GCC.

    3.2 Directory and file naming structure.
        >bin
            Holds the executables
        >build
            Holds the object(*.o) files
        >include
            Holds the header(*.h) files
        >resource
            Holds the input files
        >src
            Holds the source(*.cpp) files

    3.3 Implementation method for each shared data store.

        input.txt holds data in text form to be grabbed by the load() function. screenID identifies each screen. screenText is the text blurb describing the environment the player is in. The text blurb for each option describes that option. The optionChoiceText for each option is the actual word the player types in the terminal to select that option. The screenID for each option matches the screenID of the screen that the option leads to. 

        screenID;
        screenText;
        option1TextBlurb;
        option1ChoiceText;
        option1screenID;
        option2TextBlurb;
        option2ChoiceText;
        option2screenID;
        option3TextBlurb;
        option3ChoiceText;
        option3screenID;
        option4TextBlurb;
        option4ChoiceText;
        option4screenID;
        option5TextBlurb;
        option5ChoiceText;
        option5screenID;

    3.4 Interface for all public services provided by the element.
                void pushBack(GameScreenLinkedlist* node);
                void display(GameScreenLinkedList* node);
                const GameScreenLinkedList* const search(const std::string optionScreenID);
                search() returns const GameScreenLinkedList
                void clear(GameScreenLinkedList* root);
                void load(const std::string fileName);
                GameScreenLinkedList class

    3.5 Function Layout.
            - load(filename,root) function takes the name of the input.txt file to be opened as well as the first screen that the player sees
            - load reads from filename, creates a node with a screen ID and a text blurb drawn from filename as well as all the options, option descriptions, and IDs of the screens that the options lead to
            - This node is passed to pushBack(node) which inserts the node at the end of the single linked list
            - pushBack takes a gameScreenLinkedList pointer and inserts it at the end of the list
            - search(root,screenID) traverses through the entire linked list and returns the node with the same screenID as that it was passed
            - display(node) prints the screenText, optionChoiceTexts, and optionTextBlurbs to the terminal for the player's viewing
            - clear(root) Clears the entire list, freeing memory
            - input() Not part of gameScreenLinkedList class, takes input from player, and searches for and displays game screens

    3.6 Hierarchy of files, compilation, and the makefile
            3.6.1 Hierarchy of files
                    Our program will consist of 9 files, and there will also be a makefile, giving a total of 10 files.
                    Binary Executables: progx (we should probably rename this to ProjectBeans2.0 at some point). Directory: project-beans-2.0/bin
                    Object Files: main.o, gamescreenlinkedlist.o, utility.o. Directory: project-beans-2.0/build
                    Header files: gamescreenlinkedlist.h, utility.h. Directory: project-beans-2.0/include
                    Source files: main.cpp, gamescreenlinkedlist.cpp, utility.cpp. Directory: project-beans-2.0/src
                    utility.h will #include our libraries and general function definitions. It will also have #pragma once to avoid duplicate definitions
                    utility.cpp will #include utility.h and contain the implementation of the general functions
                    gamescreenlinkedlist.h will #include utility.h, and contain the GameScreenLinkedList class definition, and the definitions for its methods
                    gamescreenlinkedlist.cpp will #include gamescreenlinkedlist.h (which entails including utility.h), and contain the implementations for GameScreenLinkedList's methods
                    main.cpp will #include gamescreenlinkedlist.h (and by extension, utility.h), and contain the main routine
                    Visualization:
                    [utility.h] children: [utility.cpp] & [gamescreenlinkedlist.h]. [utility.cpp] has no children.
                    [gamescreenlinkedlist.h] children: [gamescreenlinkedlist.cpp] & [main.cpp]. Neither have children of their own.
                    NOTE: The reader may notice that #pragma once is not required in this setup. The reason we have it there, is because we have future scalability options in mind.
                            For example, if we needed another class, that class would almost certainly #include utility.h. and main.cpp would have to #include that class in addition to gamescreenlinkedlist.h
                            In this case, #pragma once would be necessary to have in utility.h.
            3.6.2 Compilation
                    The three .cpp files and the two header files will be compiled into three object files. These object files will be compiled into the game executable
                    First, main.cpp will be compiled into main.o
                    Second, gamescreenlinkedlist.h and gamescreenlinkedlist.cpp will be compiled into gamescreenlinkedlist.o
                    Third, utility.h and utility.cpp will be compiled into utility.o
                    Finally, main.o, gamescreenlinkedlist.o, and utility.o will be compiled into progx
                    All compilation will be done with g++
                    We will use -Wall, -Wextra, and -Wpedantic for our warning options
                    We will use -g to create an executable that can be easily debugged with gdb
                    We will use a makefile to mostly automate the process of compilation
                    Compilation will be done from the root directory (project-beans-2.0/)
            3.6.3 Makefile
                    Our makefile will be located in project-beans-2.0/. It will be structured as follows:
                    It will declare two variables: general and objects. "general" will contain our compiler of choice, selected warning options, and -g. (g++ -Wall -Wextra -Wpedantic -g)
                    "objects" will contain our three object files, and their directories. (build/main.o build/gamescreenlinkedlist.o build/utility.o)
                    The first listed target will be bin/progx. Its dependencies will be the object variable, so all three object files.
                        It will run: ${general} ${objects} -o $@. This will compile the exectutable into bin/progx.
                    The second target will be build/main.o. Its dependency will be src/main.cpp. 
                        It will run: ${general} -c $< -o $@. This will compile main.o into build/main.o
                    The third target will be gamescreenlinkedlist.o. Its dependencies will be src/gamescreenlinkedlist.cpp and include/gamescreenlinkedlist.h
                        It will run: ${general} -c $< -o $@. This will compile gamescreenlinkedlist.o into build/gamescreenlinkedlist.o
                    The fourth target will be utility.o. Its dependencies will be src/utility.cpp and include/utility.h
                        It will run: ${general} -c $< -o $@. This will compile utility.o into build/utility.o
                    Running 'make' will default to the first target, which itself will go through the other three targets. Thus, to compile, we only need to run 'make'.

                    Make test has also been added, which builds test.o
                    Make testclean cleans resulting files
