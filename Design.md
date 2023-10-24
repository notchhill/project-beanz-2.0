# Team design document

### DESIGN

Team name: Team Beanz 2.0
Game name: Project Beanz 2.0
Contact info: Dustin, dustin.gabriel777@gmail.com

# TABLE OF CONTENTS

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
- physical design
    In the physical design we want to map the elements of our logical design to actual codable entities, in a way that will subsequently allow our team to begin implementation.

    3.1 Programming language(s) and supporting tools.
        C++, GCC, Make.

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
    - identifying the implementation method for each shared data store (database, file, etc), including format, fields, layout

        This is only input.txt I think.

    3.4 Interface for all public services provided by the element:
            - identifying the interface for all public services provided by the element:
            - publicly accessible data types and constants
            - publicly callable function names, return types, parameter lists
            - class names, public field names/types, public method names, parameters, return types

    void pushBack(GameScreenLinkedlist* node);
	void display(GameScreenLinkedList* node);
	const GameScreenLinkedList* const search(const std::string optionScreenID);
	void clear(GameScreenLinkedList* root);
	void load(const char* fileName);

    3.5 Function Layout
            - load(filename,root) function takes the name of the input.txt file to be opened as well as the first screen that the player sees
            - load reads from filename, creates a node with a screen ID and a text blurb drawn from filename as well as all the options, option descriptions, and IDs of the screens that the options lead to
            - This node is passed to pushBack(node) which inserts the node at the end of the single linked list
            - pushBack takes a gameScreenLinkedList pointer and inserts it at the end of the list
            - search(root,screenID) traverses through the entire linked list and returns the node with the same screenID as that it was passed
            - display(node) prints the screenText, optionChoiceTexts, and optionTextBlurbs to the terminal for the player's viewing
            - clear(root) Clears the entire list, freeing memory
            - input() Not part of gameScreenLinkedList class, takes input from player, and searches for and displays game screens