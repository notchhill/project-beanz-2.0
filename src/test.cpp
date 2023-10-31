
#include "../include/gamescreenlinkedlist.h"
#include "../include/utility.h"

 // My test version of main. If it isnt here, it probs hasnt been tested
int main(){
	GameScreenLinkedList gameScreen;
	GameScreenLinkedList* ptr = &gameScreen;
	gameScreen.load("./resource/input.txt", ptr);



	/*while(ptr != NULL){
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
	}*/
	return 0;	
}

