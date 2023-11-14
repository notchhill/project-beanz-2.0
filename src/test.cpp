
#include "../include/gamescreenlinkedlist.h"
#include "../include/utility.h"

 // My test version of main. If it isnt here, it probs hasnt been tested
int main(){
	system("mode con: cols=120 lines=20");
	system("cls");
  

/*
* TEST 2
*/
	GameScreenLinkedList gameSequence;
	GameScreenLinkedList* current = &gameSequence;

	gameSequence.load("resource/input.txt", &gameSequence);

//iterate through the whole list and output it to testoutput.txt
	std::ofstream outputFile; 
	outputFile.open("resource/test2output.txt");

	if(outputFile.is_open()) {
		while(current != NULL) {
			//outputFile << current->screenID;
			current = current->nextNode(current);
		}

        //close the file
        outputFile.close();
    }
/*
* END TEST 2
*/

	return 0;	
}

