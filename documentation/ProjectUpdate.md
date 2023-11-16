### Team/project update
This is intended to be a short summary of key alterations to previous project plans, and belongs in a file named ProjectUpdate.md in the master branch of your team repository.

For this phase, that includes any changes to
- the team composition (member adds/drops),
- the planned team structure/organization (roles/responsibilities, conflict resolution process),
- team contact information,
- planned meeting time(s),
- major changes to the targetted project (just major changes in direction need to be outlined in this area, as the project specifications document in this phase will be spelling out the precise details of the planned product)


### CHANGES SINCE PHASE 1

- changed name of main town from Bean Village to Beancouver

### CHANGES SINCE PHASE 2

- Changed design of terminal window input screen to be laid out vertically instead of horizontally, i.e text blurb, then below it the player's options
- Changed quintery linked list to single linked list for loading screens
- Removed any chance based aspects from the fractal forest. It now will work or it won't.
- Removed hydration/thirst from desert area

- Changed version control process, detailed in VersionControl.md, as well as testing process
- Updated specifications.md to better reflect the information on the Miro flowchart
- Removed makefile sections from specifications.md and design.md

### CHANGES SINCE PHASE 3

- Added a description of how the game's files will be organized in design.md
- Detailed how the game will be compiled in design.md
- Gave physical design of the makefile that will be used to compile our game
- Created a Makefile to assist with compilation, and created the proper directories for all of our files
- Added make test, make testclean (it's supposed to be one word) to our Makefile
- Removed references to 'root' and replaced it with references to 'head'; we are using a linked list, not a tree
- Removed pushBack method and input function. pushBack's functionatlity has been incorporated into the load method, and input's functionality has been incorporated into the main routine
- Edited section 3.0 of design.md to include a more fleshed out description of how our classes/functions will be implemented. Specifically, section 3.5 got a huge update, with 3.4 getting some minor touches
- The search method is now split into two methods called search (but a new version of search), and match
- The official name of the game is now Project Beanz 2.0: Refried Beans. Note that the names of the files, directories, and executables will not change
- Added getPlayerIn and nicePrint functions. The first converts a player's input into lowercase letters. The second prints a string with a newline added every ten ' ' characters.
- The Display method now uses nicePrint to ensure the text prints in a more legible format. Display also now ignores any strings that are only composed of spaces or tabs.
- Match now returns an empty string instead of NULL
- The load method now has support for both Windows and Linux (hopefully)
- Added various shortcuts to the game sequence (detailed in the Miro Chart if you can find them) for demonstration purposes. The Miro Chart also now contains information on who authored which parts of the game

### CHANGES SINCE PHASE 4

- added iomanip library
- added two const ints in utility.h. One is the screenWidth, one is the fixed amount of space mentioned above
- added a loop at the end of nicePrint that prints any remaining chars that don't end with punctuation
- modified nicePrint. It now has a bool argument as well, with a default value of false.
  - if it's false, it works the same as before
  - if it's true, it adds alignment to the text it's printing, treating it like an optionBlurb

- Added back a puzzle to the Desert area with its appropriate puzzle class