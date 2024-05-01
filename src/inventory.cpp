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
    if(this->inventory.empty()){
        return NULL;
    }
    for(auto& it : this->inventory){
        if(it->itemName == name){
            return it;
        }
    }
    return NULL;
}

void Inventory::displayInventory(Player* beanzGuy){
    system("cls");
    bool empty = true;
    for(auto& it : this->inventory){
        empty = false;
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

    if(empty){
        std::cout << "No Items to Display!\n";
    }

    std::string playerInput = "";
    while(playerInput != "exit" && playerInput != "quit"){
        std::cout << "Type Help for a list of commands, or exit to go back to the game: ";
        playerInput = getPlayerIn();
        playerInput = processCommand(playerInput, beanzGuy);
    }

}

std::string Inventory::processCommand(std::string playerInput, Player* beanzGuy){
    std::string commands[NUMBER_OF_HELP_COMMANDS] = {"use", "remove", "exit", "help", "quit"};
    bool isValidCommand = false;
    int i;
    for(i = 0; i < NUMBER_OF_HELP_COMMANDS; ++i){
        if(playerInput == commands[i]){
            isValidCommand = true;
            break;
        }
    }
    if(!isValidCommand){
        return "";
    }

    switch(i){
        case 3:
        {
            std::cout << "\n\nUse <item_name> <item_quantity>    |  Uses an item.\n"
                      << "Remove <item_name> <item_quantity> |  Removes an item.\n"
                      << "Exit                               | Exits this screen.\n"
                      << "Help                               | Shows this screen.";
            return "";
            break;
        }
        case 2:
        case 4:
        {
            return playerInput;
            break;
        }
        default:
            break;
    }

    playerInput = getPlayerIn();

    std::string intWannabe;
    std::cin >> intWannabe;
    auto it = intWannabe.begin();
    for(; it != intWannabe.end() && (*it >= '0' && *it <= '9'); ++it){
    }
    if(it != intWannabe.end()){
        std::cout << "Invalid Amount!\n";
        return "";
    }
    
    if(intWannabe == ""){
        std::cout << "The Provided Command requires an Amount!\n";
        return intWannabe;
    }

    int number = std::stoi(intWannabe);
    Items* item = checkInventory(playerInput);
    if(item == NULL){
        std::cout << "Invalid Item! Please try again!\n";
        return "";
    }

    switch(i){
        case 0:
        {
            bool success = item->use(number, beanzGuy, this);
            if(success){
                std::cout << "Item Sucessfully Used!\n";
            }else{
                std::cout << "Couldn't Use the specified Item\n";
            }
            break;
        }
        case 1:
        {
            rem_item(item, number);
            break;
        }
        default:
            std::cout << "Invalid Command!\n";
            break;
    }
    return "";
}


void Inventory::add_item(std::string name)
{
    std::ifstream file;
    file.open("resource/items.txt");
    std::string fileOutput;
    int loops = 0;
    while(!file.eof()){
        std::getline(file >> std::ws, fileOutput);
        if(loops++ % 10 == 0){
            if (fileOutput.back() == '\r') 
		    {fileOutput.pop_back();}
            if(fileOutput == name){
                break;
            }
        }
    }
    if(file.eof()){
        file.close();
        return;
    }

    std::string itemType;
    std::getline(file >> std::ws, itemType);
    if (itemType.back() == '\r') 
		{itemType.pop_back();}
    Items* item = checkInventory(name);
    if(item != NULL){
        int count;
        file >> count;
        item->numberOfUsages += count;
        file.close();
        return;
    }else{
        Items* item = new Items;
        item->itemName = name;
        item->itemClass = itemType;
        int count;
        file >> count;
        item->numberOfUsages = count;
        std::getline(file >> std::ws, itemType);
        if (itemType.back() == '\r') 
		    {itemType.pop_back();}
        item->description = itemType;
        bool boolean;
        file >> count;
        boolean = (count != 0);
        item->canBeRemoved = boolean;

        file >> count;
        item->restoreAmount = count;

        //Future Use

        insertIntoInventory(item);
        file.close();
    }
}



void Inventory::resetInventory(std::string fileName){
    std::ifstream inputFile;
    inputFile.open(fileName);


    while(!inventory.empty()){
        delete inventory.back();
        inventory.pop_back();
    }


    std::string garbage;
    std::getline(inputFile >> std::ws, garbage);

    std::getline(inputFile >> std::ws, garbage);


    while(!(inputFile.eof())){

        Items* it = new Items;
        std::getline(inputFile >> std::ws, it->itemName);  
        if (it->itemName.back() == '\r') 
		    {it->itemName.pop_back();}
        if(it->itemName == ""){
            break;
        }

        std::getline(inputFile >> std::ws, it->itemClass);
        if (it->itemClass.back() == '\r') 
		    {it->itemClass.pop_back();} 

        inputFile >> it->numberOfUsages;


        std::getline(inputFile >> std::ws, it->description);
        if (it->description.back() == '\r') 
		    {it->description.pop_back();} 

        int x;
        inputFile >> x;
        it->canBeRemoved = (x != 0);
        inputFile >> it->restoreAmount;
        std::getline(inputFile >> std::ws, garbage);
        std::getline(inputFile >> std::ws, garbage);
        std::getline(inputFile >> std::ws, garbage);
        std::getline(inputFile >> std::ws, garbage);
        this->inventory.push_back(it);
    }
    inputFile.close();
}

void Inventory::dumpInventory(std::ofstream* outputFile){
    for(auto& it : this->inventory){
        *outputFile << it->itemName << "\n";
        *outputFile << it->itemClass << "\n";
        *outputFile << it->numberOfUsages << "\n";
        *outputFile << it->description << "\n";
        *outputFile << it->canBeRemoved << "\n";
        *outputFile << it->restoreAmount << "\n";
        *outputFile << "\n"; //Future Use
        *outputFile << "\n";
        *outputFile << "\n";
        *outputFile << "\n";
    }
}

void Inventory::updateInventory(std::string screenID){
	if(screenID[7] == 'A'){
		this->add_item(screenID.substr(8));
	}

	if(screenID[7] == 'R'){
		Items* item = this->checkInventory(screenID.substr(8));
		this->rem_item(item, 1);
	}
}