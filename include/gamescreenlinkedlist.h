/**
 * @file gamescreenlinkedlist.h
 * @author Trevor
 * @author Austin
 * @author Robert
 * @author Dustin
 * @author Lucas
 * @version 1.0.3
 * @date 2023/10/08
 *
 * GameScreenLinkedList class definition.
 *
 */


#ifndef __GAMESCREEN_LINKED_LIST_HEADER__
#define __GAMESCREEN_LINKED_LIST_HEADER__


#include "../include/utility.h"


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

		GameScreenLinkedList(){}// Default Constructor
		//Create an empty list with its front pointing to NULL.


		~GameScreenLinkedList(){}// Destructor
		//Remove all the nodes from the linked list and release memory from them.


		void display(GameScreenLinkedList* node);
		//Displays the screen text in node parameter, along with the option texts, and the text blurbs/descriptions for each option


		GameScreenLinkedList* nextNode(GameScreenLinkedList* head);
		//returns the next node
		

		GameScreenLinkedList* search(const std::string screenID, GameScreenLinkedList* head);
		//Loop through the list and campare the screenID of each node with parameter 'screenID'
		//If a node matches, return it.
		//Otherwise, return NULL.


		std::string match(const std::string playerInput, const GameScreenLinkedList* currentNode);
		//Matches the input that the player has entered with the input for each option of currentNode.
		//If it matches, return the associated screenID.
		//Otherwise, return NULL.


		void clear(GameScreenLinkedList* &head);
		//Remove all nodes from the list and release memory from all nodes.


		void load(const std::string fileName, std::string saveFile, GameScreenLinkedList* head);
		//Open the file named 'filename' in read only mode.
		//Opens the file 'saveFile' in read only mode if it, and 'filename' exists, otherwise ignores it.
		//Read the data from the file and insert them in the list.
		//Close the file after all data have been inserted.


		void save(GameScreenLinkedList* current, std::string fileName);
		//Open the file named 'filename' in write only mode.
		//Write the something into a file named 'filename' to save the game.
};


#endif