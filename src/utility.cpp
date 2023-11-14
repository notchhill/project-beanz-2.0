/**
 * @file utility.cpp
 * @author Trevor
 * @author Austin
 * @author Robert
 * @author Dustin
 * @author Lucas
 * @version 1.0.2
 * @date 2023/10/27
 *
 * Contains implementations of functions in utility.h.
 *
 */


#include "../include/utility.h"


int screenWidth = 120;


/**	@brief
*
*	@return String.
*/
std::string getPlayerIn() {
	std::string playerIn;

	std::cin >> playerIn;

	int len = playerIn.length();

	std::string newPlayerIn;

	for (int i = 0; i < len; i++) 	{
		if (playerIn[i] < 'A' || playerIn[i] > 'z'){}        // do nothing
		else if (playerIn[i] > 'Z' && playerIn[i] < 'a'){}   // do nothing
		else if (playerIn[i] >= 'A' && playerIn[i] <= 'Z')
			{newPlayerIn += playerIn[i] + 32;}           // upper to lower
		else
			{newPlayerIn += playerIn[i];}                // no change
	}

	std::cout << std::endl;

	return newPlayerIn;
}


/**	@brief
*
*	@return Void.
*/
void nicePrint(std::string text) {
	int len = text.length();
	int count = 0;
	int j = 0;
	std::string screenText;

//read text into string
for (int i = 0; i < len; i++) {
	//print when space is reached
	if (text[i] == ' ') {
		for(int a = 0; a < j; a++) {
			std::cout << screenText[a];
		}
		//std::cout << " ";
		j = 0;
	}
	//if string length + current line length > 120 print newline
	if(j + count > 120) {
		std::cout << std::endl;
		screenText.clear();
		j = 0;
		count = 0;
	}

	screenText[j] = text[i];
	j++;
	count++;

	}


/*	int numSpaces = 0;

	int len = text.length();

	for (int i = 0; i < len; i++) {
		if (text[i] == ' ') numSpaces++;

		if (numSpaces == 10) {
			std::cout << std::endl;
			numSpaces = 0;
		}

		std::cout << text[i];
	}*/
}
