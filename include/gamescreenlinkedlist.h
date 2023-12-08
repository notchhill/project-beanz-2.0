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

class Saves;

#include "../include/utility.h"
#include "../include/saves.h"



/*
 * GameScreenLinkedList class definition
 */
class GameScreenLinkedList {
	private:
		
		GameScreenLinkedList* next;

	protected:

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

		friend class Saves;

		GameScreenLinkedList(){}// Default Constructor
		//Create an empty list with its front pointing to NULL.


		~GameScreenLinkedList(){}// Destructor
		//Remove all the nodes from the linked list and release memory from them.


		void display(GameScreenLinkedList* node, int hp);
		//Displays the screen text in node parameter, along with the option texts, and the text blurbs/descriptions for each option


		GameScreenLinkedList* nextNode(GameScreenLinkedList* head);
		//returns the next node
		

		GameScreenLinkedList* search(const std::string screenID, GameScreenLinkedList* head);
		//Loop through the list and campare the screenID of each node with parameter 'screenID'
		//If a node matches, return it.
		//Otherwise, return NULL.


		std::string match(const std::string playerInput, GameScreenLinkedList* head, const GameScreenLinkedList* currentNode, Saves* saves, Player* beanzGuy);
		//Matches the input that the player has entered with the input for each option of currentNode.
		//If it matches, return the associated screenID.
		//If player input is 'save' then save the screen ID in option 3 in head
		//Otherwise, return NULL.


		void clear(GameScreenLinkedList* &head);
		//Remove all nodes from the list and release memory from all nodes.


		void load(const std::string fileName, GameScreenLinkedList* head, Saves* saves);
		//Open the file named 'filename' in read only mode.
		//Opens the file 'saveFile' in read only mode if it, and 'filename' exists, otherwise ignores it.
		//Read the data from the file and insert them in the list.
		//Close the file after all data have been inserted.

};


#endif
