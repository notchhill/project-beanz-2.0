#pragma once
#include "../include/items.h"
#include "../include/utility.h"

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
    //Checks the inventory to see if you have an item with the name that is in 'name', if so returns the item pointer if not returns null
    Items* checkInventory(std::string name);
    //inserts ptr into the inventory of the player
    void insertIntoInventory(Items* ptr);
    //Displays the name, quantity and description of all items in the inventory
    void displayInventory();
};