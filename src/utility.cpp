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
  std::string fixedInput;
  for (int i = 0; i < len; i++)
  {
    if (playerIn[i] < 'A' || playerIn[i] > 'z'){}      // symbol
    else if (playerIn[i] > 'Z' && playerIn[i] < 'a'){} // symbol
    else if (playerIn[i] >= 'A' && playerIn[i] <= 'Z') // uppercase
      {fixedInput += playerIn[i]+32;}
    else                                               // lowercase
      {fixedInput += playerIn[i];}
  }
  std::cout << std::endl;
  return fixedInput;
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
