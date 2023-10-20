/**
 * @file gamescreenlinkedlist.h
 * @author Trevor
 * @author Austin
 * @author Robert
 * @author Dustin
 * @author Lucas
 * @version 1.0.2
 * @date 2023/10/08
 *
 * GameScreenLinkedList class definition.
 *
 */


#ifndef __GAMESCREEN_LINKED_LIST_HEADER__
#define __GAMESCREEN_LINKED_LIST_HEADER__


#include <string>


/*
 * GameScreenLinkedList class definition
 */
class GameScreenLinkedList {
	private:
		
		GameScreenLinkedList* next;

		std::string screenID;
        std::string screenText;

		struct option {
			std::string optionTextBlurb;
			std::string optionChoiceText;
			std::string optionscreenID;
		};

		option option1;
		option option2;
		option option3;
		option option4;
		option option5;
		

	public:

		GameScreenLinkedList();// Default Constructor
		//Create an empty list with its front pointing to NULL.


		~GameScreenLinkedList();// Destructor
		//Remove all the nodes from the linked list and release memory from them.


		void pushBack(const std::string screenID);
		//Insert the 'screenID' at the end of the list.



		const GameScreenLinkedList* const search(const std::string screenID);
		//Loop through the list and campare the screenID of each node with parameter 'screenID'
		//If a node matches, return it.
		//Otherwise, return NULL.



		void clear();
		//Remove all nodes from the list and release memory from all nodes.


		void load(const char* fileName);
		//Open the file named 'filename' in read only mode.
		//Read the data from the file and insert them in the list.
		//Close the file after all data have been inserted.


		//void save(const char* fileName);
		//Open the file named 'filename' in write only mode.
		//Write the something into a file named 'filename' to save the game.
};


#endif