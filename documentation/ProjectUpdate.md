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

- ### CHANGES SINCE PHASE 3

- Added a description of how the game's files will be organized in design.md
- Detailed how the game will be compiled in design.md
- Gave physical design of the makefile that will be used to compile our game
- Created a Makefile to assist with compilation, and created the proper directories for all of our files
- Added make test, make testclean (it's supposed to be one word) to our Makefile
- Removed references to 'root' and replaced it with references to 'head'; we are using a linked list, not a tree
- Removed pushBack method and input function. pushBack's functionatlity has been incorporated into the load method, and input's functionality has been incorporated into the main routine
- Edited section 3.0 of design.md to include a more fleshed out description of how our classes/functions will be implemented. Specifically, section 3.5 got a huge update, with 3.4 getting some minor touches.
- The search method is now split into two methods called search (but a new version of search), and match.
