
#include "../include/gamescreenlinkedlist.h"
#include "../include/utility.h"

#include <sstream>
#include <iostream>
#include <string>

 // My test version of main. If it isnt here, it probs hasnt been tested
int main(){
	/*system("mode con: cols=120 lines=20");
	system("cls");*/
  

/*
* TEST 2
*/
	GameScreenLinkedList gameSequence;
	GameScreenLinkedList* current = &gameSequence;

	gameSequence.load("resource/input.txt", &gameSequence);

//iterate through the whole list and output it to testoutput.txt
	std::ofstream outputFile; 
	outputFile.open("resource/test2output.txt");




	std::stringstream ss;

	auto old_buf = std::cout.rdbuf(ss.rdbuf()); 

	//all the std::cout goes to ss
	while(current != NULL) {
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

	return 0;	
}

