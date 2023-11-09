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

std::string getPlayerIn()
{
	std::string playerIn;
	std::cin >> playerIn;
	int len = playerIn.length();
	std::string newPlayerIn;
	for (int i = 0; i < len; i++)
	{
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

void nicePrint(std::string text)
{
	int numSpaces = 0;
	int len = text.length();
	for (int i = 0; i < len; i++)
	{
		if (text[i] == ' ') {numSpaces++;}
		if (numSpaces == 10) {std::cout << std::endl; numSpaces = 0;}
		std::cout << text[i];
	}
}
