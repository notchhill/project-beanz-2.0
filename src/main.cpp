/**
 * @file main.cpp
 * @author Trevor
 * @author Austin
 * @author Robert
 * @author Dustin
 * @author Lucas
 * @version 1.0.3
 * @date 2023/10/27
 *
 * The main routine. Contains the game loop.
 *
 */


#include "../include/gamescreenlinkedlist.h"
#include "../include/puzzle.h"


int main() {
  system("mode con: cols=120 lines=40");
  system("cls");
  system("Color 0A");

  GameScreenLinkedList gameSequence;
  GameScreenLinkedList* prev = &gameSequence;
  GameScreenLinkedList* buffer = prev;
  GameScreenLinkedList* current = &gameSequence;
  Saves currentSave("../resource/save.txt");
  Puzzle p;
  std::string playerIn;
  Player beanzGuy;

  gameSequence.load("../resource/input.txt", &gameSequence, &currentSave);

  while (playerIn != "quit") {
    system("cls");
    prev = buffer;
    buffer = current;
    gameSequence.display(current, beanzGuy.get_hp());

    playerIn = getPlayerIn();

    std::string nextScreenID = gameSequence.match(playerIn, &gameSequence, current, &currentSave, &beanzGuy);

    if(nextScreenID == "") {
        //std::cout << "Invalid Input! Please Try Again.\n";
        continue;
    }else {
      p.UpdateStatus(playerIn, nextScreenID);
      beanzGuy.UpdatePlayer(nextScreenID);
      current = gameSequence.search(nextScreenID, &gameSequence);
      if(nextScreenID == "LS00100"){
        beanzGuy.set_hp(100);
      }
    }
  }

  GameScreenLinkedList* ptr = &gameSequence;
 
  currentSave.autosave(prev, current, ptr, &beanzGuy);

  gameSequence.clear(ptr);
  
  return 0;
}
