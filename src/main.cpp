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
  GameScreenLinkedList* prev = &gameSequence;
  GameScreenLinkedList* current = &gameSequence;
  std::string userSave = "";
  Puzzle p;
  std::string playerIn;
  std::string saveFile = "resource/save.txt";

  gameSequence.load("resource/input.txt", saveFile, &gameSequence);

  while (playerIn != "quit") {
    system("cls");
    prev = current;
    gameSequence.display(current);

    playerIn = getPlayerIn();

    std::string nextScreenID = gameSequence.match(playerIn, userSave, current);

    if(nextScreenID == "") {
        //std::cout << "Invalid Input! Please Try Again.\n";
        continue;
    }else {
      p.UpdateStatus(playerIn, nextScreenID);
      current = gameSequence.search(nextScreenID, &gameSequence);
    }
  }

  GameScreenLinkedList* ptr = &gameSequence;

 
  gameSequence.save(prev, current, userSave, saveFile);

  gameSequence.clear(ptr);
  
  return 0;
}
