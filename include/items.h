#pragma once
#include "../include/inventory.h"
#include "../include/player.h"

class Items : public Inventory {
    protected:
        std::string itemName;
        std::string itemClass;
        int numberOfUsages;
        std::string description;
        bool canBeRemoved;
        int restoreAmount;

    public:
        Items();
        Items(std::string name, std::string itemClass, std::string description, int numberOfUsages);
        ~Items();
        friend class Inventory;

        bool use(Items* item, int quantityUsed, Player* beanzGuy, Inventory* inventory);
        // If the item is able to be used, use and increment the HP of beanzGuy by restoreAmount
        // Decrease the amount of useages by quantity used
        // if the player uses too much, use only what is needed

};


