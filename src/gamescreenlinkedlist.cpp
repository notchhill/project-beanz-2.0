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

/**	@brief Displays the contents of the node it is passed to the terminal
*
*	@param GameScreenLinkedList* node ; The node to be displayed
*	@return Void.
*/
void GameScreenLinkedList::display(GameScreenLinkedList* node) {
	nicePrint(node->screenText); 

	std::cout << std::endl << std::endl;

	if (node->option1.optionTextBlurb.find_first_not_of(" \t") != std::string::npos) {
		std::cout << "[" << node->option1.optionChoiceText << "] -- ";
		std::cout << node->option1.optionTextBlurb << std::endl;
	}

	if (node->option2.optionTextBlurb.find_first_not_of(" \t") != std::string::npos) {
		std::cout << "[" << node->option2.optionChoiceText << "] -- ";
		std::cout << node->option2.optionTextBlurb << std::endl;
	}

	if (node->option3.optionTextBlurb.find_first_not_of(" \t") != std::string::npos) {
		std::cout << "[" << node->option3.optionChoiceText << "] -- ";
		std::cout << node->option3.optionTextBlurb << std::endl;
	}

	if (node->option4.optionTextBlurb.find_first_not_of(" \t") != std::string::npos) {
		std::cout << "[" << node->option4.optionChoiceText << "] -- ";
		std::cout << node->option4.optionTextBlurb << std::endl;
	}

	if (node->option5.optionTextBlurb.find_first_not_of(" \t") != std::string::npos) {
		std::cout << "[" << node->option5.optionChoiceText << "] -- ";
		std::cout << node->option5.optionTextBlurb << std::endl;
	}
	
	std::cout << std::endl << std::endl;
}

/*
@brief Searches for the node in the list with the screen ID it's passed. Starts at the top, from the head.
@param const string screenID ; ScreenID to be searched for.
@param GameScreenLinkedList* head ; The head node of the list
@return const GameScreenLinkedList* ; The found node
*/
GameScreenLinkedList* GameScreenLinkedList::search(const std::string screenID, GameScreenLinkedList* head) {  
    GameScreenLinkedList* search = head;
    
    while(search != NULL && search->screenID!=screenID) search = search->next;

    return search;
}

/**	@brief Matches player's inputted text with the appropriate optionChoiceText
*
*	@param string playerInput ; the player's inputted text
*	@param const GameScreenLinkedList* currentNode ; Node to have its options examined for a match with the player's input
*	@return string GameScreenLinkedList ; ScreenID of matching option
*/
std::string GameScreenLinkedList::match(const std::string playerInput, const GameScreenLinkedList* currentNode){
	if(currentNode == NULL || playerInput == ""){
		return "";
	}

	if(playerInput == currentNode->option1.optionChoiceText){
		return currentNode->option1.optionscreenID;
	}
	if(playerInput == currentNode->option2.optionChoiceText){
		return currentNode->option2.optionscreenID;
	}
	if(playerInput == currentNode->option3.optionChoiceText){
		return currentNode->option3.optionscreenID;
	}
	if(playerInput == currentNode->option4.optionChoiceText){
		return currentNode->option4.optionscreenID;
	}
	if(playerInput == currentNode->option5.optionChoiceText){
		return currentNode->option5.optionscreenID;
	}
	return "";
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
			if (ptr->screenID.back() == '\r') 
			{ptr->screenID.pop_back();}
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
			if (ptr->screenText.back() == '\r') 
			{ptr->screenText.pop_back();}
			
			std::getline(file, ptr->option1.optionTextBlurb);
			if (ptr->option1.optionTextBlurb.back() == '\r') 
			{ptr->option1.optionTextBlurb.pop_back();}
			
			std::getline(file, ptr->option1.optionChoiceText);
			if (ptr->option1.optionChoiceText.back() == '\r') 
			{ptr->option1.optionChoiceText.pop_back();}
			
			std::getline(file, ptr->option1.optionscreenID);
			if (ptr->option1.optionscreenID.back() == '\r') 
			{ptr->option1.optionscreenID.pop_back();}
			
			std::getline(file, ptr->option2.optionTextBlurb);
			if (ptr->option2.optionTextBlurb.back() == '\r') 
			{ptr->option2.optionTextBlurb.pop_back();}
			
			std::getline(file, ptr->option2.optionChoiceText);
			if (ptr->option2.optionChoiceText.back() == '\r') 
			{ptr->option2.optionChoiceText.pop_back();}
			
			std::getline(file, ptr->option2.optionscreenID);
			if (ptr->option2.optionscreenID.back() == '\r') 
			{ptr->option2.optionscreenID.pop_back();}
			
			std::getline(file, ptr->option3.optionTextBlurb);
			if (ptr->option3.optionTextBlurb.back() == '\r') 
			{ptr->option3.optionTextBlurb.pop_back();}
			
			std::getline(file, ptr->option3.optionChoiceText);
			if (ptr->option3.optionChoiceText.back() == '\r') 
			{ptr->option3.optionChoiceText.pop_back();}
			
			std::getline(file, ptr->option3.optionscreenID);
			if (ptr->option3.optionscreenID.back() == '\r') 
			{ptr->option3.optionscreenID.pop_back();}
			
			std::getline(file, ptr->option4.optionTextBlurb);
			if (ptr->option4.optionTextBlurb.back() == '\r') 
			{ptr->option4.optionTextBlurb.pop_back();}
			
			std::getline(file, ptr->option4.optionChoiceText);
			if (ptr->option4.optionChoiceText.back() == '\r') 
			{ptr->option4.optionChoiceText.pop_back();}
			
			std::getline(file, ptr->option4.optionscreenID);
			if (ptr->option4.optionscreenID.back() == '\r') 
			{ptr->option4.optionscreenID.pop_back();}
			
			std::getline(file, ptr->option5.optionTextBlurb);
			if (ptr->option5.optionTextBlurb.back() == '\r') 
			{ptr->option5.optionTextBlurb.pop_back();}
			
			std::getline(file, ptr->option5.optionChoiceText);
			if (ptr->option5.optionChoiceText.back() == '\r') 
			{ptr->option5.optionChoiceText.pop_back();}
			
			std::getline(file, ptr->option5.optionscreenID);
			if (ptr->option5.optionscreenID.back() == '\r') 
			{ptr->option5.optionscreenID.pop_back();}

			std::string garbage;
			std::getline(file, garbage);
			if (garbage.back() == '\r') {garbage.pop_back();}

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


GameScreenLinkedList* GameScreenLinkedList::nextNode(GameScreenLinkedList* head) {
	return head->next;
}
