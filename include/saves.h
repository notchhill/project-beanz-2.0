#pragma once

#include "player.h"
#include "gamescreenlinkedlist.h"
#include "inventory.h"

class GameScreenLinkedList;

class Saves {
    protected:
        std::string autosaveScreenID;
        int autosaveHP;
        std::string userSaveScreenID;
        int userSaveHP;
        std::string saveFile;
        std::string autosaveFile;
        std::string userSaveData;

        public:

        friend class GameScreenLinkedList;
        
        Saves();
        //Default Constructor
        //Initializes empty save state.

        Saves(std::string savefileName, std::string autosaveFileName);
        //Constructor
        //Loads web manual saves from the browser bridge, otherwise from the save file.
        //Loads autosave data from the configured autosave file.

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

        std::string getUserSaveData();
        //Returns the serialized user save data

        void changeSaveFile(std::string newSaveFile);
        //change the save file to directory in newSaveFile

        bool save(const GameScreenLinkedList* current, GameScreenLinkedList* head, Player* beanzGuy, Inventory* inventory);
        //Stores manual save data in the browser in web mode, otherwise writes it to the save file.
        //Returns false if persistence fails.

		void autosave(GameScreenLinkedList* prev, GameScreenLinkedList* current, GameScreenLinkedList* head, Player* beanzGuy, Inventory* inventory);
		//Open the file named 'filename' in write only mode.
		//Saves the screen ID of current screen in current to the file.
		//If current is a death screen, writes prev instead.

        void autosave(GameScreenLinkedList* prev, GameScreenLinkedList* current, GameScreenLinkedList* head, GameScreenLinkedList* expectedScreen, Player* beanzGuy, Inventory* inventory);
		//Open the file named 'filename' in write only mode.
		//Saves the screen ID of current screen in current to the file.
        //Saves the current health of the player in the file.
		//If current is a death screen, writes prev instead.
        //This version is for if the player decides to quit to the title screen while on a death screen.

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

        void fixUserSaveInventory(Inventory* inventory, Player* beanzGuy);
        //Prevents the player from using their savefile and endlessly obtaining items

        void fixAutoSaveInventory(Inventory* inventory, Player* beanzGuy);
        //Prevents the player from using their savefile and endlessly obtaining items

};