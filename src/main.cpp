/**
 * @file main.cpp
 * @author Trevor
 * @author Austin
 * @author Robert
 * @author Dustin
 * @author Lucas
 * @version 1.0.2
 * @date 2023/10/27
 *
 * The main routine. Contains the game loop.
 *
 */

#include <stdlib.h>



#include "../include/gamescreenlinkedlist.h"

int main()
{
  system("mode con: cols=120 lines=20");
  system("cls");
  /*
  std::cout << "You find a quaint forest gnome's hut nestled in the heart of the enchanting forest. ";
  std::cout << "The trees have fractal-like leaves, and the hut, with its charming design, boasts a basement, a ";
  std::cout << "ladder to the roof, a well-tended garden out front, and a small storage shed behind it." << std::endl;

  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << "[a] option1" << std::endl;
  std::cout << "[b] option2" << std::endl;
  std::cout << "[c] option2" << std::endl;

  std::cout << std::endl;
  std::cout << std::endl;

  int i;
  std::cin >> i; 
  */

  GameScreenLinkedList gameSequence;
  GameScreenLinkedList* current = &gameSequence;
  gameSequence.load("input.txt", &gameSequence);
  // We decided to just have Ctrl + c as killing the program for now.
  while (1) {
    gameSequence.display(current);
    std::string playerIn;
    std::cin >> playerIn;
    std::string nextScreenID = gameSequence.match(playerIn, current);
    if(nextScreenID != ""){
      current = gameSequence.search(nextScreenID, &gameSequence);
    }
  }
  GameScreenLinkedList* ptr = &gameSequence;
  gameSequence.clear(ptr);
  
  return 0;
}
