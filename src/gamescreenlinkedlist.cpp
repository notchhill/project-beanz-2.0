/**
 * @file gamescreenlinkedlist.cpp
 * @author Trevor
 * @author Austin
 * @author Robert
 * @author Dustin
 * @author Lucas
 * @version 1.0.4
 * @date 2023/10/27
 *
 * GameScreenLinkedList method implementations.
 *
 */


#include "../include/gamescreenlinkedlist.h"

/*
@brief Displays the contents of the node it is passed to the terminal
@param GameScreenLinkedList* node ; The node to be displayed
@return void
*/
void GameScreenLinkedList::display(GameScreenLinkedList* node) {
   std::cout << node->screenText << std::endl;
   std::cout << node->option1.optionTextBlurb << " -- ";
   std::cout << node->option1.optionChoiceText << std::endl;
   std::cout << node->option2.optionTextBlurb << " -- ";
   std::cout << node->option2.optionChoiceText << std::endl;
   std::cout << node->option3.optionTextBlurb << " -- ";
   std::cout << node->option3.optionChoiceText << std::endl;
   std::cout << node->option4.optionTextBlurb << " -- ";
   std::cout << node->option4.optionChoiceText << std::endl;
   std::cout << node->option5.optionTextBlurb << " -- ";
   std::cout << node->option5.optionChoiceText << std::endl;
   std::cout << std::endl << std::endl << std::endl;
}

/*
@brief Searches for the node in the list with the screen ID it's passed. Starts at the top, from the head.
@param const string screenID ; ScreenID to be searched for.
@param GameScreenLinkedList* head ; The head node of the list
@return const GameScreenLinkedList* ; The found node
*/
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

if(file.is_open()) {
	while(!(file.eof())){
		//Just for the first time around, if the memory address of object is passed through.
		GameScreenLinkedList* ptr;
		if(head != NULL && head->screenID == "\0"){
			ptr = head;
		}else{
			ptr = new GameScreenLinkedList;
		}

		std::getline(file, ptr->screenID);
		if(!((ptr->screenID[0] == 'L' && ptr->screenID[1] == 'S') || (ptr->screenID[0] == 'B' && ptr->screenID[1] == 'C') || (ptr->screenID[0] == 'G' && ptr->screenID[1] == 'C') || 
		     (ptr->screenID[0] == 'F' && ptr->screenID[1] == 'F') || (ptr->screenID[0] == 'D' && ptr->screenID[1] == 'D'))){
			std::cout << " The input file is in an invalid format. Problem occurred around this text: " << ptr->screenID << std::endl;
			tail->next = NULL;
			if(ptr != this){
				delete ptr;
			}
			return;
		}
			
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
else{std::cout<<"didnt open"<< std::endl;}
}
