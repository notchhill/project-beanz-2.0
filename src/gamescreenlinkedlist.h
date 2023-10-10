/**
 * @file gamescreenlinkedlist.h
 * @author Trevor
 * @author Austin
 * @author Robert
 * @author Dustin
 * @author Lucas
 * @version 1.0.0
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

		std::string option1Text;
		std::string option2Text;
		std::string option3Text;
		std::string option4Text;
		std::string option5Text;

		std::string option1screenID;
		std::string option2screenID;
		std::string option3screenID;
		std::string option4screenID;
		std::string option5screenID;
		

	public:

		GameScreenLinkedList();// Default Constructor
		//Create an empty list with its front pointing to NULL.


		~GameScreenLinkedList();// Destructor
		//Remove all the nodes from the linked list and release memory from them.


		void pushFront(const std::string screenID);
		//Insert the 'screenID' at the beginning of the list.


		void insert(const std::string beforeID, const std::string screenID);
		//Loop through the list to find a node whose screenID is equal to parameter 'beforeID'.
		//If no such node is found, do nothing.
		//Otherwise, create a new node using 'screenID' and insert the new node after the
		//found node.


		const GameScreenLinkedList* const search(const std::string screenID);
		//Loop through the list and campare the screenID of each node with parameter 'screenID'
		//If a node matches, return it.
		//Otherwise, return NULL.


		const std::string getData() const {return screenText;}			


		GameScreenLinkedList* getNext() const {return next;}


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