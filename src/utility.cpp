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
	screenText[j] = text[i];
	j++;
	count++;

	//print when space is reached - no something else instead
	if (text[i] == ' ' || text[i] == '.' || text[i] == '!' || text[i] == '?') {
		for(int a = 0; a < j; a++) {
			std::cout << screenText[a];
		}
		screenText.clear();
		j = 0;
	}
	//if string length + current line length > 120 print newline
	if(j + count > screenWidth) {
		std::cout << std::endl;
		count = 0;
	}



	}
	// catch any remaining text that doesn't end with punctuation
	for(int a = 0; a < j; a++) {
		std::cout << screenText[a];
	}
}
