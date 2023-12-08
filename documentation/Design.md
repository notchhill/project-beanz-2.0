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
    3.4 Classes and class methods. Including parameters and return value/type.
    3.5 Function and Class Implementations.
        3.5.1 GameScreenLinkedList class
            Variables
            Methods
                Load Method
                Display Method
                Match Method
                Search Method
                Clear Method
        3.5.2 Puzzle class
            Variables
            Methods
                UpdateStatus method
                Check method
                PrintLights method
        3.5.3 Player class
            Update Player method
        3.5.4 Functions
            Main Routine
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

    Player runs the shell script, which runs the game binary, which in turn runs main.cpp, which calls the load() function. Load function opens the input.txt file containing the text blurbs and their associated screen IDs. Load function creates a string to hold the text as well as creating a gameScreenLinkedList node. Load function then opens input.txt. Load function now uses a loop to read the first line of input.txt and puts the text into inputStuff. The screenID of the new node is set to inputStuff. This is then repeated until load() reaches the end of the file input.txt. For each of the five options associated with a single screen, load() reads the options and their associated description out of the input.txt file and puts them into the option1, option 2 etc member variables of the node. Load() will eventually reach the end of the input.txt, close the file, and then end.

3.0 Physical Design.

    3.1 Programming language(s) and compiler.
        C++, g++.

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

        input.txt holds data in text form to be grabbed by the load() function. screenID identifies each screen. screenText is the text blurb describing the environment the player is in. The text blurb for each option describes that option. The optionChoiceText for each option is the actual word the player types in the terminal to select that option. The screenID for each option matches the screenID of the screen that the option leads to. There is a blank line at the bottom to seperae screens. Any options not used on a screen are left as blank lines.

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

    3.4 Class, class method, function, and global constant declarations.
                CLASSES:
                    class: GameScreenLinkedList{};
                    class: Puzzle{};
                METHODS: (For GameScreenLinkedList)
                    void display(GameScreenLinkedList* node);
                    GameScreenLinkedList* search(const std::string screenID, const GameScreenLinkedList* head);
                    std::string match(const std::string playerInput, const GameScreenLinkedList* currentNode);
                    void clear(GameScreenLinkedList* head);
                    void load(const std::string fileName, GameScreenLinkedList* head)
                METHODS: (for Puzzle)
                    Puzzle();
                    ~Puzzle();
                    void UpdateStatus(std::string I, std::string ID);
                    bool Check();
                    void PrintLights();
                FUNCTIONS:
                    std::string getPlayerIn();
                    void nicePrint(std::string text);
                GLOBAL CONSTANTS:
                    const int screenWidth = 100;
                    const int align = 18;
                    const int zones = 6;
                    const std::string ID_MARKERS[zones] = {"LS","BC","GC","FF","DD","RE"};

    3.5 Function and Class Implementations.
        3.5.1 GameScreenLinkedList class
            Variables
                - GameScreenLinkedList contains nine variables, all of which are private. 
                - It has a GameScreenLinkedList pointer that points to the next GameScreenLinkedList in the list
                - It has two strings: an ID, and a string for area description.
                - It will have an 'option' datatype in the form of a struct. 
                - The struct contains three strings: 
                - One for text to display to the player which described the option,
                - One single-word string which indicates to the player what to type in to select the option,
                - And the third string will contain an ID which will match with a GameScreenLinkedList somewhere in the data.
                - Each GameScreenLinkedList will contain five option variables. These may or may not be blank.
            Methods
                Load Method
                    - Open the file named fileName, using standard library functions to open files, detect end of files, and close files.
                    - Create a new GameScreenLinkedList object.
                    - Read and insert the next line into the next GameScreenLinkedList string variable (listed in order in 3.3)
                    - Loop through the step above 17 times (once for each variable), and then push the new GameScreenLinkedList object into the back of the list.
                    - The first GameScreenLinkedList that gets created will be the first screen of the game, and the head of the list. The order of the others does not matter.
                    - Continue doing that until end of file, then exit. No return value.
                Display Method
                    - Display the node's screenText, first option's blurb and text, second option's blurb and text, etc... until all of the options have been displayed.
                    - Before printing a given text variable, display checks for the first instance of a character that isn't a space or a tab. If this exists, it prints. Otherwise it will ignore it. Done with 'find_first_not_of' from string library
                    - Done using simple couts, endls. The screenText is specially printed with the nicePrint function, then each option and associated text are displayed a line down from the previous.
                    - In other words, the player will see the screenText, and below that see option 1, then below that, option 2. Then below that, option 3, and so on.
                    - The text associated with each option will be displayed after the option, encased in square brackets, and separated from the option via two hyphens. ("option blurb" -- [text])
                    - All printed to the terminal
                Match Method
                    - The main routine will grab input from the player, and pass it here, along with the current GameScreenLinkedList position the player is at.
                    - Match will compare the player's input to each of the GameScreenLinkedList's option texts. If it finds a match, it returns that option's ID. Otherwise, it returns an empty string.
                    - Match accommodates the possibility of the player inputting an invalid string, but will recognize the option text even if it is obscured by typos as long as all the correct letters are present
                    - Done with five if..else statements. e.g. "If the player's input matches the first option's text, return first option's ID", and so on for all five options. Returns an empty string if no matches exist
                Search Method
                    - The search method is passed the head GameScreenLinkedList, and the ID returned from the match method
                    - Search checks if the ID it was passed, matches the head's ID (hopefully not, because that would take the player back to the beginning)
                    - If it doesn't, it moves on to the head's next pointer, and compares the ID it was passed to that
                    - This process is repeated until it eventually finds the correct GameScreenLinkedList, in which case it'll return a pointer to that GameScreenLinkedList.
                    - If search fails to find a matching GameScreenLinkedList, something has gone horribly wrong.
                Clear Method
                    - The clear method is passed the head of the GameScreenLinkedList.
                    - Clear will delete that GameScreenLinkedList (as it was dynamically allocated by the load function), and then move on to its next.
                    - It will repeat that procedure until it reaches the end of the list, then it will exit and return nothing.
        3.5.2 Puzzle class
            Variables
                - Each puzzle object has four variables. One int, two arrays of ints, and one array of bools.
                - The int is called current_light, and it denotes the current light the player is modifying (e.g. if current_light = 4, then the player is modifying light #4)
                - The array of bools denotes the on/off state of each light. There are five lights, but the array is of size 6. This is so the index will match up with the light number
                - Both arrays of ints are setup in a similar way, where the ith element in the array corresponds to the ith object, rather than the (i+1)th object
                - The first int array counts how many lights are currently pointed at a shape. There are three shapes to point to. The only elements in this array that are considered are 3, 4, and 5
                - The second int array denotes which light is pointing at which shape. The index represents the ith light, and the value at that index represents the shape it's pointing at.
            Methods
                Constructor & Destructor
                    - The destructor doesn't do anything, as this class doesn't dynamically allocate any memory
                    - The constructor first initializes all lights to be off (done by setting each bool in the bool array to false)
                    - Then, it initializes all shapes to have zero lights pointing at them (done by setting each int in the first int array to zero)
                    - Then, it initializes all the lights to be pointing at the square (done by setting each int in the second int array to four)
                    - Note that 3 = triangle, 4 = square, and 5 = pentagon (this makes sense if you follow the Miro chart I think)
                    - Finally, light#1 is set to on (bool array at index 1 is set to true), and the number of lights pointing at the square is set to 1 (first int array at index 4 is set to 1)
                UpdateStatus method
                    - This method takes two strings as parameters. These are obtained from main, and correspond to the player's input (I), and the next screen ID (ID) passed-by-reference
                    - First, the method checks if the first character of the ID is a 'D'. If so, we are in the desert, which means we might be in the Mirror Palace, so the rest of the program is run
                    - If the first character is not 'D', then everything is skipped over
                    - The method then checks if the player's input is equal to any of: "one", "two", "three", "four", "five", "switch", "triangle", "square", "pentagon", and runs code based on this
                    - If the player's input isn't any of these, everything will be skipped over except the ending
                    - No areas in the desert have the player input any of those strings except in the puzzle area, so the method will only have to do stuff then (entering them elsewhere fails match)
                    - If the player's input is "one"/"two"/"three"/"four"/"five", it will set current_light to be equal to one, two, three, four, or five. Nothing else happens, except the ending
                    - If the input is "switch", the current light is set to the opposite of what it currently is, then the brightness of the light it's currently pointing at has 1 added or taken away
                        - Done by setting the bool value at index of current_light in the bool array to be equal to NOT(itself)
                        - Then defining an integer called delta, which is set to: the newly updated bool value at index of current_light, subtracted by the bool value of NOT(itself)
                        - Finally, it takes the first int array at the following index: "the value of the second int array at index of the current light", and adds delta to that.
                    - If the input is "triangle"/"square"/"pentagon", then an int variable called shape (initialized to 0) is set to either 3, 4, or 5
                    - Next, if shape isn't 0, then the brightness of the light currently being pointed at is decreased by the bool value of whether or not it's on or off
                        - Then, the brightness of the shape to be pointed to (denoted by the shape int) is increased by the bool value of whether or not the current light is on or off
                        - Finally, the shape that the current light is pointing to is set to the shape
                    - At the end of this method, the Check method is run on 'this'. If it returns true, the ID passed is changed to "DD04100" (ID for end of Mirror Palace), and all the lights are turned off
                        - Done by, as you may have guessed, setting all the bools in the bool array to false
                Check method
                    - the Check method only returns a bool. It is passed no parameters.
                    - first it declares a variable called lights_on, which will be set to the sum of all the bool values in the bool array (equivalent to the number of lights that are on)
                    - Next, it checks to see if the player has solved the puzzle. The puzzle was designed by Austin, and there are 2 (or 4 depending on how you look at it) solutions
                    - Solutions: 3 lights are pointing at the triangle (others are off), 4 lights are pointing at the square (others are off), 5 lights are pointing at the pentagon,
                        - light #3 is pointing at the triangle + light #4 is pointing at the square + light #5 is pointing at the pentagon (others are off). Any of these should work
                    - The first solution is checked by seeing if there are 3 lights pointing at the triangle AND if lights_on is 3. If this is true, return true
                    - The second solution is checked by seeing if there are 4 lights pointing at the square AND if lights_on is 4. If this is true, return true
                    - The third solution is checked by seeing if there are 5 lights pointing at the triangle AND if lights_on is 5. If this is true, return true
                        - Each done by checking if the first int array at index 3/4/5 is equal to 3/4/5
                    - The fourth solution is checked by first seeing if light#3 is pointing at the triangle AND light#4 is pointed at the square AND light#5 is pointed at the pentagon,
                        - Next, it checks if light#3, light#4, and light#5 are on
                        - And finally, it checks if light#1 and light#2 are turned off. If all that is true, return true
                        - Done by: checking if the second int array at index 3/4/5 is equal to 3/4/5, then checking if the bool array at 3/4/5 are all true, and the ones at 1/2 are both false
                    - If none of these checks check out, then false is returned
                PrintLights method
                    - We define two strings. One to represent the on/off state of each light, and one to represent the shape a given light is pointing at
                    - We go through a loop, which increments a counter. The counter represents the nth light, so it will incrememnt from 1 to 5
                    - The first string will be made equal to "on" or "off" based on the value in the counter-th number in state[] array
                    - The second string will be made equal to "triangle", "square", or "pentagon" based on the value of the counter-th number in pointing[]. 3 = triangle, 4 = square, 5 = pentagon
                    - It will print "Light #" (counter) "is" (on or off), "and pointing at the following shape: " (trangle/square/pentagon)
        3.5.3 Player Class
            - This class will include the libraries, functions, and constants defined in utility.h
            - Player contains one private variable called hp, which denotes how much health the user has. Set to 100
            - It uses the default constructor and destructor methods
            - It has methods that: increase hp, decrease hp, set hp, and return player hp
                - methods that increase, decrease, and set hp take an integer as a parameter. The player's hp is increased/decreased by/set to the passed integer
            - It has a method that warps to a generic death screen. This method takes a string, which should be the next screen ID passed-by-reference
                - This method will modify the string it was passed, converting it to the ID of a generic death screen. In main, the player will then be sent to this ID
            UpdatePlayer method
                - It will take the next screen ID (obtained when match is called in main) passed-by-reference
                - If the seventh character in the ID is 'D' or 'H', it enters an if statement, otherwise it exits the method
                - The method then grabs the characters after the 'D' or 'H' in the ID (using substr). They should form a valid integer
                - Using stoi, it converts that substring into an integer
                - If the seventh character was 'D', it will pass that integer to the method that decreases hp
                - If the seventh character was 'H', it will pass the integer to the method that increases hp
                - It uses the method that returns the player's current hp. 
                    - If it is greater than 100, it passes 100 to the method that sets hp
                    - If it is less than 0, the method that warps you to a death screen is called
        3.5.4 Functions
            Main Routine
                - It will define a GameScreenLinkedList, which will serve as the head of the linked list.
                - Then, it will define a GameScreenLinkedList pointer, which points to the head
                - Next, it defines a Puzzle object
                - The main routine then runs the load method on the head, passing input.txt and the head pointer.
                - It then enters the main while loop. The while loop will loop until the player use ctrl+c to end the program.
                - In the loop, it will call display on the current GameScreenLinkedList, then get the player's input using getPlayerIn.
                - A new string will be defined, which will be set to the return value of match called on current. (it should return a valid GameScreenLinkedList ID.)
                - If that string is empty, we notify the player, and then return to the beginning of the while loop to try again. (The player entered something invalid)
                - If that string isn't empty:
                    - Main first called UpdateStatus on the puzzle object. If the player has solved the puzzle, the string will be changed to "DD04100". Otherwise no changes are made
                    - Then the string will be passed to search (called on current) in order to locate the associated GameScreenLinkedList.
                - The current GameScreenLinkedList will be set to that newly found one, and that is the final execution within the while loop.
                - Outside of the while loop, we will run the clear method on the GameScreenLinkedList head to free up memory, then return 0 to end the main routine.
            getPlayerIn
                - This function will define two strings. The first one will receive user input via cin, and the second will be left empty.
                - An integer is then defined from the length of the first string. It will use the .length() method from the string library to do this.
                - It will then enter a for loop, with i starting at 0, and going up by one until it reaches the length of the first string minus one.
                - Then there are a series of if checks to determine what to do in the for loop.
                - If the first string's ith character is a symbol, don't do anything.
                - If the first string's ith character is an uppercase letter, add 32 to it and concatenate that onto the second string from before. Note that adding 32 to an uppercase letter transforms it into a lowercase letter.
                - If the first string's ith character is anything else, we simply concatenate it to the second string.
                - Once this is done, a newline is printed (for legibility purposes), and then we return the second string. This ensures that any symbols from the user's input are removed, and any uppercase letters are made into lowercase letters.
            nicePrint
                - This function assumes the string passed to it is a large, single-line string. This function will print it in a more legible way.
                - It defines two integers. One being the length of the string passed, gotten using .length from the string library, and one called numSpaces, which is set to 0.
                - It will enter a for loop, and iterate on i from 0 up to the length of the passed string minus one.
                - First, it checks if the argument's ith character is a space. If so, numSpaces is incremented by one.
                - Next, it checks if numSpaces is equal to 10. If so, print a newline and set numSpaces to 0.
                - Finally, it will print the argument's ith character.

    3.6 Hierarchy of files, compilation, and the makefile
            3.6.1 Hierarchy of files
                    Our program will consist of 12 files, and there will also be a makefile, giving a total of 13 files.
                    Binary Executables: progx (we should probably rename this to ProjectBeans2.0 at some point). Directory: project-beans-2.0/bin
                    Object Files: main.o, gamescreenlinkedlist.o, puzzle.o, utility.o. Directory: project-beans-2.0/build
                    Header files: gamescreenlinkedlist.h, puzzle.h, utility.h. Directory: project-beans-2.0/include
                    Source files: main.cpp, gamescreenlinkedlist.cpp, puzzle.cpp, utility.cpp. Directory: project-beans-2.0/src
                    utility.h will #include our libraries, general function definitions, and global constants. It will also have #pragma once to avoid duplicate definitions
                    utility.cpp will #include utility.h and contain the implementation of the general functions
                    gamescreenlinkedlist.h will #include utility.h, and contain the GameScreenLinkedList class definition, and the definitions for its methods
                    gamescreenlinkedlist.cpp will #include gamescreenlinkedlist.h, and contain the implementations for GameScreenLinkedList's methods
                    puzzle.h will #include utility.h, and contain the Puzzle class definition, and the definitions of its methods
                    puzzle.cpp will #include puzzle.h, and contain implementations of Puzzle's methods
                    main.cpp will #include gamescreenlinkedlist.h, puzzle.h, and contain the main routine
                    Visualization:
                    [utility.h] children: [utility.cpp] & [gamescreenlinkedlist.h] & [puzzle.h]. [utility.cpp] has no children
                    [gamescreenlinkedlist.h] children: [gamescreenlinkedlist.cpp] & [main.cpp]. Neither child has children of their own
                    [puzzle.h] children: [puzzle.cpp] & [main.cpp]. Neither child has children of their own
            3.6.2 Compilation
                    The six .cpp files and the four header files will be compiled into six object files. These object files will be compiled into the game executable
                    First, main.cpp will be compiled into main.o
                    Second, gamescreenlinkedlist.h and gamescreenlinkedlist.cpp will be compiled into gamescreenlinkedlist.o
                    Third, puzzle.h and puzzle.cpp will be compiled into puzzle.o
                    Fourth, player.h and player.cpp will be compiled into player.o
                    Fifth, saves.h and saves.cpp will be compiled into saves.o
                    Sixth, utility.h and utility.cpp will be compiled into utility.o
                    Finally, main.o, gamescreenlinkedlist.o, puzzle.o, and utility.o will be compiled into beanz2
                    All compilation will be done with g++
                    We will use -Wall, -Wextra, and -Wpedantic for our warning options
                    We will use -static to include necessary dependencies inside the executable
                    We will use -g to create an executable that can be easily debugged with gdb
                    We will use a makefile to mostly automate the process of compilation
                    Compilation will be done from the root directory (project-beans-2.0/)
            3.6.3 Makefile
                    Our makefile will be located in project-beans-2.0/. It will be structured as follows:
                    It will declare two variables: general and objects. "general" will contain our compiler of choice, selected warning options, a static flag, and -g. (g++ -Wall -Wextra -Wpedantic -static -g)
                    "objects" will contain our five object files, and their directories. (build/main.o build/gamescreenlinkedlist.o build/puzzle.o build/player.o build/saves.o build/utility.o)
                    The first listed target will be bin/progx. Its dependencies will be the object variable, so all three object files.
                        It will run: ${general} ${objects} -o $@. This will compile the exectutable into bin/progx.
                    The second target will be build/main.o. Its dependency will be src/main.cpp. 
                        It will run: ${general} -c $< -o $@. This will compile main.o into build/main.o
                    The third target will be gamescreenlinkedlist.o. Its dependencies will be src/gamescreenlinkedlist.cpp and include/gamescreenlinkedlist.h
                        It will run: ${general} -c $< -o $@. This will compile gamescreenlinkedlist.o into build/gamescreenlinkedlist.o
                    The fourth target will be puzzle.o. Its dependencies will be src/puzzle.cpp and include/puzzle.h
                        It will run: ${general} -c $< -o $@. This will compile puzzle.o into build/puzzle.o
                    The fifth target will be player.o. Its dependences will be src/player.cpp and include/player.h
                        It will run: ${general} -c $< -o $@. This will compile player.o into build/player.o
                    The sixth target will be saves.o. Its dependencies will be src/saves.cpp and include/saves.h
                        It will run: ${general} -c $< -o $@. This will compile saves.o into build/saves.o
                    The seventh target will be utility.o. Its dependencies will be src/utility.cpp and include/utility.h
                        It will run: ${general} -c $< -o $@. This will compile utility.o into build/utility.o
                    Running 'make' will default to the first target, which itself will go through the other three targets. Thus, to compile, we only need to run 'make'.

                    Make test has also been added, which builds test.o
                    Make testclean cleans resulting files
