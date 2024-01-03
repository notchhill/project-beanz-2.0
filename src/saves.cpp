#include "../include/saves.h"

Saves::Saves(){
    this->autosaveScreenID = "";
    this->userSaveScreenID = "";
    this->userSaveHP = 100;
    this->autosaveHP = 100;
    this->saveFile = "";
}

Saves::Saves(std::string fileName){
        std::ifstream file;
        file.open(fileName);

        if(!file.fail()){
            std::getline(file, this->autosaveScreenID);
            if (this->autosaveScreenID.back() == '\r') 
			{this->autosaveScreenID.pop_back();}

            std::getline(file, this->userSaveScreenID);
            if (this->userSaveScreenID.back() == '\r') 
			{this->userSaveScreenID.pop_back();}

            file >> this->autosaveHP;
            file >> this->userSaveHP;
            std::string garbage;
            std::getline(file, garbage);
        }
			this->saveFile = fileName;

    		file.close();
}

Saves::~Saves(){
    //trunc is to discard old file, and create a new one.
    std::ofstream file (this->saveFile, std::ofstream::trunc);
    file << this->autosaveScreenID << "\n";
    file << this->userSaveScreenID << "\n";
    file << this->autosaveHP << "\n";
    file << this->userSaveHP;
    file.close();
}

void Saves::save(const GameScreenLinkedList* current, GameScreenLinkedList* head, Player* beanzGuy){
    this->userSaveScreenID = current->screenID;
    this->userSaveHP = beanzGuy->get_hp();
    head->option3.optionscreenID = current->screenID;
    head->option3.optionTextBlurb = "Load Previous Manual Save";
	head->option3.optionChoiceText = "load";
}

void Saves::autosave(GameScreenLinkedList* prev, GameScreenLinkedList* current, GameScreenLinkedList* head, Player* beanzGuy){
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
    }
}

void Saves::autosave(GameScreenLinkedList* prev, GameScreenLinkedList* current, GameScreenLinkedList* head,  GameScreenLinkedList* expectedNode, Player* beanzGuy){
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