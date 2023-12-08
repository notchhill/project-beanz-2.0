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
        if(current->option1.optionChoiceText == "restart" && prev != NULL){
            ptr = prev;
            if(prev->screenID[7] == 'D'){
				std::string strAmount = prev->screenID.substr(8,prev->screenID.length()-7);
       			int amount = stoi(strAmount,nullptr,10);
				beanzGuy->incr_hp(amount);
			}else if(prev->screenID[7] == 'H'){
				std::string strAmount = prev->screenID.substr(8,prev->screenID.length()-7);
       			int amount = stoi(strAmount,nullptr,10);
				beanzGuy->decr_hp(amount);
            }
        }else{
            ptr = current;
        }
        if(beanzGuy->get_hp() <= 0){
            beanzGuy->u_died(current->screenID);
        }

        this->autosaveScreenID = ptr->screenID;
        this->autosaveHP = beanzGuy->get_hp();
        head->option3.optionscreenID = current->screenID;
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