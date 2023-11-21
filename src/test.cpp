
#include "../include/gamescreenlinkedlist.h"
#include "../include/utility.h"

#include <sstream>
#include <iostream>
#include <string>

 // My test version of main. If it isnt here, it probs hasnt been tested
int main(){
/*
* TEST 2
*/
	GameScreenLinkedList gameSequence;
	GameScreenLinkedList* current = &gameSequence;

	//load the game(create linked list)
	gameSequence.load("resource/input.txt", &gameSequence);

	//opens the output file
	std::ofstream outputFile; 
	outputFile.open("resource/actualTest2.txt");

	std::stringstream ss;
	auto old_buf = std::cout.rdbuf(ss.rdbuf());
	
	//iterate through the whole list and output it to testoutput.txt
	//all the std::cout goes to ss
	/*while(current != NULL) {
		current->display(current);
		current = current->nextNode(current);
	}*/

	//iterate through the first 10 screens
	for(int i = 0; i < 10; i++) {
		current->display(current);
		current = current->nextNode(current);
	}

    std::cout.rdbuf(old_buf); //reset

    /*std::cout << "<redirected-output>\n" 
              << ss.str() 
              << "</redirected-output>" << std::endl;*/

	outputFile << ss.str();
	
	outputFile.close();
	
	/*if(outputFile.is_open()) {
		while(current != NULL) {
			//outputFile << current->screenID;
			//outputFile << current->display(current);
			//current = current->nextNode(current);
		}

        //close the file
        outputFile.close();
    }*/
/*
* END TEST 2
*/

/*
* TEST 3
*/

	//Taking only screenIDs from input.txt or else a master file of screenIDs
	// and passing them all to search(). If search() finds a matching screen it's good, if it doesn't, it's not
	// screenIDs should be passed to test.cpp via  a Bash script in a file called ba.sh (Beanz Actualization.sh)

/*
* END TEST 3
*/

	return 0;	
}

