/**
 * @file gamescreennode.h
 * @author Trevor
 * @author Austin
 * @author Robert
 * @author Dustin
 * @author Lucas
 * @version 1.0.0
 * @date 2023/10/08
 *
 * Defines GameScreenNode class.
 * GameScreenNode objects are used to build a gamescreen linked list.
 *
 */ 


#ifndef __GAMESCREEN_NODE_HEADER__
#define __GAMESCREEN_NODE_HEADER__


#include <string>


/*
 * GameScreenNode class definition
 */
class GameScreenNode {
	private:

		std::string optionText;											//Data of the node
		GameScreenNode* next;											//Pointer to the next node


	public:

		GameScreenNode(std::string optionText, GameScreenNode* next):	//Constructor 
			optionText(optionText), next(next) {}


		~GameScreenNode() {}											//Destructor


		const std::string getData() const {return optionText;}			//Returns the option's text


		GameScreenNode* getNext() const {return next;}					//Returns the attached node


		friend class GameScreenLinkedList;
};


#endif