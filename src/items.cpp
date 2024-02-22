#include "../include/items.h"
#include "../include/player.h"
#include "../include/inventory.h"

Items::Items(){
    this->itemName = "";
    this->numberOfUsages = 0;
    this->canBeRemoved = 1;
    this->restoreAmount = 0;
}

Items::Items(std::string name, std::string itemClass, std::string description, int numberOfUsages){
    this->itemName = name;
    this->itemClass = itemClass;
    this->description = description;
    this->numberOfUsages = numberOfUsages;
    this->canBeRemoved = 1;
    this->restoreAmount = 0;
}

Items::~Items(){}


bool Items::use(Items* item, int numberUsed, Player* beanzGuy, Inventory* inventory)
{
    if(item == NULL || item->numberOfUsages == 0){
        return false;
    }

    if(numberUsed <= 0){
        return false;
    }

    if(item->numberOfUsages < numberUsed){
        numberUsed = item->numberOfUsages;
    }

    //Checking to see if any items dont need to be used, and prevents the player from wasting them
    int temp = PLAYER_MAX_HP - beanzGuy->get_hp();
    while (temp <= numberUsed--*item->restoreAmount){
    }
    ++numberUsed;
    if(numberUsed <= 0){
        return false;
    }
    beanzGuy->incr_hp(item->restoreAmount*numberUsed);

    inventory->rem_item(item, numberUsed);


    return true;
}


