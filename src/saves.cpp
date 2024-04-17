#include "../include/saves.h"

Saves::Saves(){
    this->autosaveScreenID = "";
    this->userSaveScreenID = "";
    this->userSaveHP = 100;
    this->autosaveHP = 100;
    this->saveFile = "";
}

Saves::Saves(std::string fileName, std::string autosaveFileName){
        std::ifstream file;
        file.open(fileName);

        if(!file.fail()){
            std::getline(file, this->userSaveScreenID);
            if (this->userSaveScreenID.back() == '\r') 
			{this->userSaveScreenID.pop_back();}

            file >> this->userSaveHP;
        }
		this->saveFile = fileName;

    	file.close();

        std::ifstream autosaveFile;
        autosaveFile.open(autosaveFileName);

        if(!autosaveFile.fail()){
            std::getline(autosaveFile, this->autosaveScreenID);
            if (this->autosaveScreenID.back() == '\r') 
			{this->autosaveScreenID.pop_back();}

            autosaveFile >> this->autosaveHP;
        } 
        this->autosaveFile = autosaveFileName;
        autosaveFile.close();
}

Saves::~Saves(){
}

void Saves::save(const GameScreenLinkedList* current, GameScreenLinkedList* head, Player* beanzGuy, Inventory* inventory){
    this->userSaveScreenID = current->screenID;
    this->userSaveHP = beanzGuy->get_hp();
    head->option3.optionscreenID = current->screenID;
    head->option3.optionTextBlurb = "Load Previous Manual Save";
	head->option3.optionChoiceText = "load";
    std::ofstream file(this->saveFile);
    if(file.is_open()){
        file << current->screenID << "\n";
        file << this->userSaveHP << "\n";
        inventory->dumpInventory(&file);
        file.close();
    } else{
        std::cout << "Couldnt Open File\n";
    }


}

void Saves::autosave(GameScreenLinkedList* prev, GameScreenLinkedList* current, GameScreenLinkedList* head, Player* beanzGuy, Inventory* inventory){
	if(current != NULL && current->screenID != "LS00400"){
        GameScreenLinkedList* ptr;
        if((current->option1.optionChoiceText == "restart" || isHelpScreen(current->screenID)) && prev != NULL){
            ptr = prev;

            if(prev->screenID[7] == 'D'){
				std::string strAmount = prev->screenID.substr(8,prev->screenID.length()-7);
       			int amount = stoi(strAmount,nullptr,10);
				beanzGuy->incr_hp(amount);

			}else if(prev->screenID[7] == 'H'){
				std::string strAmount = prev->screenID.substr(8,prev->screenID.length()-7);
       			int amount = stoi(strAmount,nullptr,10);
				beanzGuy->decr_hp(amount);

            }else if(isHelpScreen(current->screenID) && beanzGuy->get_hp() <= 0){
                int minimumDamage = 999;

                if(prev->option1.optionscreenID.length() >= 8 && prev->option1.optionscreenID[7] == 'D'){
                    std::string strAmount = prev->option1.optionscreenID.substr(8,prev->option1.optionscreenID.length()-7);
       			    int amount = stoi(strAmount,nullptr,10);
                    if(amount < minimumDamage){
                        minimumDamage = amount;
                    }
                }

                if(prev->option2.optionscreenID.length() >= 8 && prev->option2.optionscreenID[7] == 'D'){
                    std::string strAmount = prev->option2.optionscreenID.substr(8,prev->option2.optionscreenID.length()-7);
       			    int amount = stoi(strAmount,nullptr,10);
                    if(amount < minimumDamage){
                        minimumDamage = amount;
                    }
                }

                if(prev->option3.optionscreenID.length() >= 8 && prev->option3.optionscreenID[7] == 'D'){
                    std::string strAmount = prev->option3.optionscreenID.substr(8,prev->option3.optionscreenID.length()-7);
       			    int amount = stoi(strAmount,nullptr,10);
                    if(amount < minimumDamage){
                        minimumDamage = amount;
                    }
                }

                if(prev->option4.optionscreenID.length() >= 8 && prev->option4.optionscreenID[7] == 'D'){
                    std::string strAmount = prev->option4.optionscreenID.substr(8,prev->option4.optionscreenID.length()-7);
       			    int amount = stoi(strAmount,nullptr,10);
                    if(amount < minimumDamage){
                        minimumDamage = amount;
                    }
                }

                if(prev->option5.optionscreenID.length() >= 8 && prev->option5.optionscreenID[7] == 'D'){
                    std::string strAmount = prev->option5.optionscreenID.substr(8,prev->option5.optionscreenID.length()-7);
       			    int amount = stoi(strAmount,nullptr,10);
                    if(amount < minimumDamage){
                        minimumDamage = amount;
                    }
                }
                
                if(minimumDamage != 999){
                    beanzGuy->incr_hp(minimumDamage);
                }
            }
        }else{
            ptr = current;
        }
        if(beanzGuy->get_hp() <= 0){
            beanzGuy->u_died(current->screenID);
        }

        this->autosaveScreenID = ptr->screenID;
        this->autosaveHP = beanzGuy->get_hp();
        head->option2.optionscreenID = ptr->screenID;
        head->option2.optionTextBlurb = "Load Previous Auto Save";
	    head->option2.optionChoiceText = "autosave";
        std::ofstream autoSavefile(this->autosaveFile, std::ofstream::trunc);
        if(autoSavefile.is_open()){
            autoSavefile << this->autosaveScreenID << "\n";
            autoSavefile << this->autosaveHP << "\n";
            inventory->dumpInventory(&autoSavefile);
            autoSavefile.close();
        } else{
            std::cout << "Couldnt Open File\n";
        }
    }
}

void Saves::autosave(GameScreenLinkedList* prev, GameScreenLinkedList* current, GameScreenLinkedList* head,  GameScreenLinkedList* expectedNode, Player* beanzGuy, Inventory* inventory){
	if(current != NULL && current->screenID != "LS00400"){
        if((current->option1.optionChoiceText == "restart" || isHelpScreen(current->screenID)) && expectedNode != NULL){

            if(expectedNode->screenID[7] == 'D'){
				std::string strAmount = expectedNode->screenID.substr(8,expectedNode->screenID.length()-7);
       			int amount = stoi(strAmount,nullptr,10);
				beanzGuy->incr_hp(amount);

			}else if(expectedNode->screenID[7] == 'H'){
				std::string strAmount = expectedNode->screenID.substr(8,expectedNode->screenID.length()-7);
       			int amount = stoi(strAmount,nullptr,10);
				beanzGuy->decr_hp(amount);

            }

        }

        this->autosaveScreenID = prev->screenID;
        this->autosaveHP = beanzGuy->get_hp();
        head->option2.optionscreenID = prev->screenID;
        head->option2.optionTextBlurb = "Load Previous Auto Save";
	    head->option2.optionChoiceText = "autosave";
        std::ofstream autoSaveFile(this->autosaveFile, std::ofstream::trunc);
        if(autoSaveFile.is_open()){
            autoSaveFile << this->autosaveScreenID << "\n";
            autoSaveFile << this->autosaveHP << "\n";
            inventory->dumpInventory(&autoSaveFile);
            autoSaveFile.close();
        } else{
            std::cout << "Couldnt Open File\n";
        }
    }
}

 //Returns autosaveScreenID
std::string Saves::getAutosaveScreenID(){
    return this->autosaveScreenID;
}

//Returns userSaveScreenID
std::string Saves::getUserSaveScreenID(){
    return this->userSaveScreenID; 
}

//Returns autosaveHP
int Saves::getAutosaveHP(){
    return autosaveHP;
}

//Returns userSaveHP
int Saves::getUserSaveHP(){
    return this->userSaveHP;
}

//Returns the directory of the savefile
std::string Saves::getSaveFile(){
    return this->saveFile;
}

void Saves::changeSaveFile(std::string newSaveFile){
    this->saveFile = newSaveFile;
}

void Saves::fixAutosaveHealth(Player* beanzGuy){
    if(this->autosaveScreenID[7] == 'D'){
	   	std::string strAmount = this->autosaveScreenID.substr(8,this->autosaveScreenID.length()-7);
	  	int amount = stoi(strAmount,nullptr,10);
	 	beanzGuy->incr_hp(amount);
	}
    else if(this->autosaveScreenID[7] == 'H'){
       std::string strAmount = this->autosaveScreenID.substr(8,this->autosaveScreenID.length()-7);
 	    int amount = stoi(strAmount,nullptr,10);
	    beanzGuy->decr_hp(amount);
    }
}

void Saves::fixUserSaveHealth(Player* beanzGuy){
    if(this->userSaveScreenID[7] == 'D'){
	   	std::string strAmount = this->userSaveScreenID.substr(8,this->userSaveScreenID.length()-7);
	  	int amount = stoi(strAmount,nullptr,10);
	 	beanzGuy->incr_hp(amount);
	}
    else if(this->userSaveScreenID[7] == 'H'){
       std::string strAmount = this->userSaveScreenID.substr(8,this->userSaveScreenID.length()-7);
 	    int amount = stoi(strAmount,nullptr,10);
	    beanzGuy->decr_hp(amount);
    }
}