#include "../include/inventory.h"
#include "../include/items.h"


/*
@brief Default constructor for Inventory class
@param N/A
@return N/A
*/
Inventory::Inventory() {

}

/*
@brief Destructor for Inventory class
@param N/A
@return N/A
*/
Inventory::~Inventory() {
    while(!inventory.empty()){
        delete inventory.back();
        inventory.pop_back();
    }
    inventory.clear();
}


/*
@brief Removes the passed item from the player inventory
@param Items* item ; Item to be removed
@param int quantity ; the amount of items to be removed
@return void
*/
void Inventory::rem_item(Items* item, int quantity) {
    if(item == NULL || item->canBeRemoved == 0){
        return;
    }

    if(item->numberOfUsages > quantity){
        item->numberOfUsages -= quantity;
    }

    this->inventory.remove(item);
    delete item;
    item = NULL;
}

/*
@brief Inserts a item into the players inventory
@param Items* item ; The item to be inserted into the players inventory
@return void
*/
void Inventory::insertIntoInventory(Items* item){
    this->inventory.push_back(item);
}

/*
@brief Checks to see if the player has an item with the same name as 'name'
@param std::string name ; the name of the item you are looking for
@return Items* ; The pointer to the item if it exists, otherwise NULL
*/
Items* Inventory::checkInventory(std::string name){
    for(auto& it : this->inventory){
        if(it->itemName == name){
            return it;
        }
    }
    return NULL;
}

void Inventory::displayInventory(){
    std::cout << "\n";
    for(auto& it : this->inventory){
        std::cout << it->itemName << ": " << it->itemClass << " item. ";
        if(it->itemClass == "Restoritive"){
            std::cout << "Restores " << it->restoreAmount << " HP. ";
        }else{ 
            //Future Use
        }
        if(it->numberOfUsages == 1){
            std::cout << it->numberOfUsages << " use remaining.\n";
        }else{
            std::cout << it->numberOfUsages << " uses remaining.\n";
        }
        std::cout << it->description << "\n\n";
    }
}


void Inventory::add_item(std::string name)
{
    std::ifstream file;
    file.open(ITEM_FILE_NAME);
    std::string fileOutput;
    while(!file.eof() && fileOutput != name){
        std::getline(file, fileOutput);
    }
    if(file.eof()){
        return;
    }

    std::string itemType;
    std::getline(file, itemType);
    Items* item = checkInventory(name);
    if(item != NULL){
        int count;
        file >> count;
        item->numberOfUsages += count;
        return;
    }else{
        Items* item = new Items;
        item->itemName = name;
        item->itemClass = itemType;
        int count;
        file >> count;
        item->numberOfUsages = count;
        std::getline(file, itemType);
        item->description = itemType;
        bool boolean;
        file >> count;
        boolean = (count != 0);
        item->canBeRemoved = boolean;

        if(item->itemClass == "Restoritive"){
            file >> count;
            item->restoreAmount = count;
        }else{
            //Future Use
        }

    }
}