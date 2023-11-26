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


#include "../include/gamescreenlinkedlist.h"
#include "../include/puzzle.h"


int main() {
  system("mode con: cols=120 lines=20");
  system("cls");

  GameScreenLinkedList gameSequence;
  GameScreenLinkedList* current = &gameSequence;
  Puzzle p;
  std::string playerIn;
  std::string saveFile = "resource/save.txt";

  gameSequence.load("resource/input.txt", saveFile, &gameSequence);

  // We decided to just have Ctrl + c as killing the program for now.
  while (playerIn != "quit") {
    system("cls");

    gameSequence.display(current);

    playerIn = getPlayerIn();

    std::string nextScreenID = gameSequence.match(playerIn, current);

    if(nextScreenID == "") {
        //std::cout << "Invalid Input! Please Try Again.\n";
        continue;
    }else {
      p.UpdateStatus(playerIn, nextScreenID);
      current = gameSequence.search(nextScreenID, &gameSequence);
    }
  }

  GameScreenLinkedList* ptr = &gameSequence;
  gameSequence.save(current, saveFile);

  gameSequence.clear(ptr);
  
  return 0;
}
