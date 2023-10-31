/**
 * @file gamescreenlinkedlist.cpp
 * @author Trevor
 * @author Austin
 * @author Robert
 * @author Dustin
 * @author Lucas
 * @version 1.0.1
 * @date 2023/10/27
 *
 * GameScreenLinkedList method implementations.
 *
 */


#include "../include/gamescreenlinkedlist.h"


void display(GameScreenLinkedList* node) {
   std::cout << Node->screenText << std::endl;
   std::cout << Node->option1.optionTextBlurb << " -- ";
   std::cout << Node->option1.optionChoiceText << std::endl;
   std::cout << Node->option2.optionTextBlurb << " -- ";
   std::cout << Node->option2.optionChoiceText << std::endl;
   std::cout << Node->option3.optionTextBlurb << " -- ";
   std::cout << Node->option3.optionChoiceText << std::endl;
   std::cout << Node->option4.optionTextBlurb << " -- ";
   std::cout << Node->option4.optionChoiceText << std::endl;
   std::cout << Node->option5.optionTextBlurb << " -- ";
   std::cout << Node->option5.optionChoiceText << std::endl;
   std::cout << std::endl << std::endl << std::endl;
}


const GameScreenLinkedList* GameScreenLinkedList::search(const std::string screenID,  GameScreenLinkedList* head) const {  
    /*for(GameScreenLinkedList* temp = root; temp->next != nullptr; temp = temp->next)
    {
        if(temp->screenID == screenID)
        {
            return temp;
        }
    }*/

    GameScreenLinkedList* search = head;
    
    while(search != NULL && search->screenID!=screenID) search = search->next;

    return search;
}


/*
@brief Deletes all elements from the list, and frees their memory, if necessary.
@param: GameScreenLinkedList* head. The pointer to the head of the list. 
@return void
*/
void GameScreenLinkedList::clear(GameScreenLinkedList* &head) {
	if(head == this){
		head = head->next;
	}
	while(head != NULL){
		GameScreenLinkedList* victim = head;
		if(head->next != NULL){
			head = head->next;
		}
		delete victim;
		head = NULL;
	}
}


/*
This function loads the contents from filename, into a linked list of GameScreens.
@param: std::string fileName: The name of the input file formatted in the following way:

Screen ID
Screen Text: Descripion about whats happening, and the background for the upcoming choice
Option1 Text Blurb: The text outlining what this option does, and what the user should enter
Option1 Choice Text: What the user should enter
Option1 screen ID: The screen ID of the option the user selected.
Option2 Text Blurb: The text outlining what this option does, and what the user should enter
Option2 Choice Text: What the user should enter
Option2 screen ID: The screen ID of the option the user selected.
Option3 Text Blurb: The text outlining what this option does, and what the user should enter
Option3 Choice Text: What the user should enter
Option3 screen ID: The screen ID of the option the user selected.
Option4 Text Blurb: The text outlining what this option does, and what the user should enter
Option4 Choice Text: What the user should enter
Option4 screen ID: The screen ID of the option the user selected.
Option5 Text Blurb: The text outlining what this option does, and what the user should enter
Option5 Choice Text: What the user should enter
Option5 screen ID: The screen ID of the option the user selected.

There should be one blank line in between every game screen.
If you want fewer options, just leave that many lines blank, plus the one that should always be blank.
@param GameScreenLinkedList* head, the first element of the linked list.
@return void
*/  
void GameScreenLinkedList::load(const std::string fileName, GameScreenLinkedList* head) {

	std::ifstream file; 
	file.open(fileName);
	GameScreenLinkedList* tail = head;

	while(!(file.eof())){
		//Just for the first time around, if the memory address of object is passed through.
		GameScreenLinkedList* ptr;
		if(head != NULL && head->screenID == "\0"){
			ptr = head;
		}else{
			ptr = new GameScreenLinkedList;
		}

		std::getline(file, ptr->screenID);
		std::getline(file, ptr->screenText);
		std::getline(file, ptr->option1.optionTextBlurb);
		std::getline(file, ptr->option1.optionChoiceText);
		std::getline(file, ptr->option1.optionscreenID);
		std::getline(file, ptr->option2.optionTextBlurb);
		std::getline(file, ptr->option2.optionChoiceText);
		std::getline(file, ptr->option2.optionscreenID);
		std::getline(file, ptr->option3.optionTextBlurb);
		std::getline(file, ptr->option3.optionChoiceText);
		std::getline(file, ptr->option3.optionscreenID);
		std::getline(file, ptr->option4.optionTextBlurb);
		std::getline(file, ptr->option4.optionChoiceText);
		std::getline(file, ptr->option4.optionscreenID);
		std::getline(file, ptr->option5.optionTextBlurb);
		std::getline(file, ptr->option5.optionChoiceText);
		std::getline(file, ptr->option5.optionscreenID);

		std::string garbage;
		std::getline(file, garbage);

		if(head == NULL){
			head = ptr;
			tail = head;
		}else{
			tail->next = ptr;
			tail = ptr;
		}
	}
	
	file.close();
}
