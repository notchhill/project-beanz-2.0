
#include "../include/gamescreenlinkedlist.h"
#include "../include/utility.h"

 // My test version of main. If it isnt here, it probs hasnt been tested
int main() {
/*
* TEST 2
*/
	GameScreenLinkedList gameSequence;
	GameScreenLinkedList* current = &gameSequence;

	//load the game(create linked list)
	gameSequence.load("resource/input.txt", &gameSequence);

	/* Use this loop to skip screens to reach the desired block*/
	/*for(int i = 0; i < 10; i++) {
		current = current->nextNode(current);
	}*/

	//opens the output file
	std::ofstream outputFile; 
	outputFile.open("resource/actualTest2.txt");

	std::stringstream ss;
	auto old_buf = std::cout.rdbuf(ss.rdbuf());

	//iterate through the first 10 screens
	for(int i = 0; i < 10; i++) {
		current->display(current);
		current = current->nextNode(current);
	}

    std::cout.rdbuf(old_buf); //reset

	outputFile << ss.str();
	
	outputFile.close();
/*
* END TEST 2
*/

/*
* TEST 3
*/
	//Taking only screenIDs from a master file of screenIDs
	// and passing them all to search(). If search() finds a matching screen it's good, if it doesn't, it's not
	// screenIDs should be passed to test.cpp via  a Bash script in a file called ba.sh (Beanz Actualization.sh)
	std::string string_beans = "";

	while(string_beans != "exit") {
		std::cin >> string_beans;

		current = gameSequence.search(string_beans, &gameSequence);

		if(current == NULL) std::cout << "Error screen is " << string_beans;
	}
/*
* END TEST 3
*/

	return 0;	
}

