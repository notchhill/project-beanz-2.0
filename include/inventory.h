#pragma once
#include "../include/items.h"
#include "../include/utility.h"
#include "../include/player.h"

class Items;

class Inventory {
private:
    std::list<Items*> inventory;

public:
    Inventory();
    ~Inventory();

    friend class Items;

    // Adds an item to the inventory 
    void add_item(std::string name);
    //Removes an item from the inventory
    void rem_item(Items* item, int quantity);
    //Forcefully removes an item from the inventory.
    void force_rem_item(Items* item, int quantity);
    //Checks the inventory to see if you have an item with the name that is in 'name', if so returns the item pointer if not returns null
    Items* checkInventory(std::string name);
    //inserts ptr into the inventory of the player
    void insertIntoInventory(Items* ptr);
    //Displays the name, quantity and description of all items in the inventory
    void displayInventory(Player* beanzGuy);
    //Removes everything in the current inventory, and replaces it with the saved inventory.
    void resetInventory(std::string saveFile);
    //Dumps the contents of the inventory into a file
    void dumpInventory(std::ofstream* file);
    //Takes the command that the user entered in the inventory and processes it accordingly. returns the name of the command it just processed
    std::string processCommand(std::string playerInput, Player* beanzGuy);
    //Adds and removes items to/from the inventory depending on the story
    void updateInventory(std::string screenID);
};