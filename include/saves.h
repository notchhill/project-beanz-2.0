#pragma once

#include "player.h"
#include "gamescreenlinkedlist.h"

class GameScreenLinkedList;

class Saves {
    protected:
        std::string autosaveScreenID;
        int autosaveHP;
        std::string userSaveScreenID;
        int userSaveHP;
        std::string saveFile;

        public:

        friend class GameScreenLinkedList;
        
        Saves();
        //Default Constructor
        //Automatically loads values from saves.txt

        Saves(std::string fileName);
        //Constructor
        //Gets parameters from fileName

        ~Saves();
        //Default Destructor
        //Automatically stores values in saves.txt

        std::string getAutosaveScreenID();
        //Returns autosaveScreenID

        std::string getUserSaveScreenID();
        //Returns userSaveScreenID

        int getAutosaveHP();
        //Returns autosaveHP

        int getUserSaveHP();
        //Returns userSaveHP

        std::string getSaveFile();
        //Returns the directory of the savefile

        void changeSaveFile(std::string newSaveFile);
        //change the save file to directory in newSaveFile

        void save(const GameScreenLinkedList* current, GameScreenLinkedList* head, Player* beanzGuy);
        //Open the file named 'filename' in write only mode.
		//Saves the screen ID of current screen in current to the file.

		void autosave(GameScreenLinkedList* prev, GameScreenLinkedList* current, GameScreenLinkedList* head, Player* beanzGuy);
		//Open the file named 'filename' in write only mode.
		//Saves the screen ID of current screen in current to the file.
		//If current is a death screen, writes prev instead.

        void fixUserSaveHealth(Player* beanzGuy);
        //updates the health of the SAVE specified in the UserSaveHP based on UserSaveScreenID
        //This function is used to undo any extra damage you take by loading into the screen
        //if after the screen ID there is a D, deals damage equal to number after it
        //if after the screenID is H, heals for the amount specified after it

        void fixAutosaveHealth(Player* beanzGuy);
        //updates the health of the SAVE specified in the autosaveHP based on autosaveScreenID
        //This function is used to undo any extra damage you take from loading into the screen
        //if after the screen ID there is a D, deals damage equal to number after it
        //if after the screenID is H, heals for the amount specified after it
};