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


bool Items::use(int numberUsed, Player* beanzGuy, Inventory* inventory)
{
    if(this->numberOfUsages == 0){
        std::cout << "No Usages Reamining\n";
        return false;
    }

    if(numberUsed <= 0){
        std::cout << "You cannot use a non-positive amount. Type \"Exit\" to leave this screen\n";
        return false;
    }

    if(this->numberOfUsages < numberUsed){
        numberUsed = this->numberOfUsages;
    }

    //Checking to see if any items dont need to be used, and prevents the player from wasting them
    int temp = PLAYER_MAX_HP - beanzGuy->get_hp();
    while (temp <= numberUsed--*this->restoreAmount){
    }
    ++numberUsed;
    if(numberUsed <= 0){
        std::cout << "You have hit the HP Cap! Any items used and had no effect have been returned to you.\n";
        return false;
    }
    beanzGuy->incr_hp(this->restoreAmount*numberUsed);

    inventory->rem_item(this, numberUsed);


    return true;
}

int Items::getRestoreAmount(){
    return this->restoreAmount;
}

int Items::getUsages(){
    return this->numberOfUsages;
}
