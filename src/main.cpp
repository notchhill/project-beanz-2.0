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
#include "../include/player.h"


int main() {
  system("mode con: cols=120 lines=20");
  system("cls");

  GameScreenLinkedList gameSequence;
  GameScreenLinkedList* prev = &gameSequence;
  GameScreenLinkedList* buffer = prev;
  GameScreenLinkedList* current = &gameSequence;
  Puzzle p;
  std::string playerIn;
  std::string saveFile = "resource/save.txt";
  Player beanzGuy;

  gameSequence.load("resource/input.txt", saveFile, &gameSequence);

  while (playerIn != "quit") {
    system("cls");
    prev = buffer;
    buffer = current;
    gameSequence.display(current);

    playerIn = getPlayerIn();

    std::string nextScreenID = gameSequence.match(playerIn, &gameSequence, current);

    if(nextScreenID == "") {
        //std::cout << "Invalid Input! Please Try Again.\n";
        continue;
    }else {
      p.UpdateStatus(playerIn, nextScreenID);

      int nextLen = nextScreenID.length();
      nextLen = abs(nextLen);
      for(int i=2; i<nextLen; i++) {
        if(nextScreenID[i] == 'D') {
          int strAmountLen = 0;

          if(nextLen == 9) {
            strAmountLen = 2;
          } else if(nextLen == 10) {
            strAmountLen = 3;
          }

          std::string strAmount = nextScreenID.substr(7,strAmountLen); 
          int amount = stoi(strAmount,nullptr,10);
          beanzGuy.decr_hp(amount);

          if(beanzGuy.get_hp() <= 0) {
            beanzGuy.u_died(nextScreenID);
          }
        }
      }

      current = gameSequence.search(nextScreenID, &gameSequence);
    }
  }

  GameScreenLinkedList* ptr = &gameSequence;
 
  gameSequence.save(prev, current, &gameSequence, saveFile);

  gameSequence.clear(ptr);
  
  return 0;
}