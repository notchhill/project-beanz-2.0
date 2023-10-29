#include "../include/gamescreenlinkedlist.h"

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
void GameScreenLinkedList::load(const std::string fileName, GameScreenLinkedList* head){

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

/*
@brief Deletes all elements from the list, and frees their memory, if necessary.
@param: GameScreenLinkedList* head. The pointer to the head of the list. 
@return void
*/
void GameScreenLinkedList::clear(GameScreenLinkedList* &head){
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
 * My test version of main. If it isnt here, it probs hasnt been tested
int main(){
	GameScreenLinkedList gameScreen;
	GameScreenLinkedList* ptr = &gameScreen;
	gameScreen.load("input.txt", ptr);

	while(ptr != NULL){
	std::cout << ptr->screenID << '\n'
		  << ptr->screenText << '\n'
		  << ptr->option1.optionTextBlurb << '\n'
		  << ptr->option1.optionChoiceText << '\n'
		  << ptr->option1.optionscreenID << '\n'
		  << ptr->option2.optionTextBlurb << '\n'
		  << ptr->option2.optionChoiceText << '\n'
		  << ptr->option2.optionscreenID << '\n'
		  << ptr->option3.optionTextBlurb << '\n'
		  << ptr->option3.optionChoiceText << '\n'
		  << ptr->option3.optionscreenID << '\n'
		  << ptr->option4.optionTextBlurb << '\n'
		  << ptr->option4.optionChoiceText << '\n'
		  << ptr->option4.optionscreenID << '\n'
		  << ptr->option5.optionTextBlurb << '\n'
		  << ptr->option5.optionChoiceText << '\n'
		  << ptr->option5.optionscreenID << '\n';
		if(ptr->next != NULL){
			ptr = ptr->next;
		}else{
			break;
		}
	}
	gameScreen.clear(ptr);

	if(ptr == NULL){
		std::cout << "Cleared";
	}else{
		// Still can be a mem leak if it goes to cleared, but there definately is one if this prints.
		std::cout << "MEM LEAK";
	}
	return 0;	
}
*/
