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
  GameScreenLinkedList* ptr = &gameSequence;
  GameScreenLinkedList* prev = &gameSequence;
  GameScreenLinkedList* buffer = prev;
  GameScreenLinkedList* current = &gameSequence;
  Saves currentSave("resource/save.txt");
  Puzzle p;
  std::string playerIn;
  Player beanzGuy;

 gameSequence.load("resource/input.txt", &gameSequence, &currentSave);


  while (playerIn != "quit") {
    system("cls");

    gameSequence.display(current, beanzGuy.get_hp());

    playerIn = getPlayerIn();

    if(playerIn == "quit"){
      break;
    }

    std::string nextScreenID = gameSequence.match(playerIn, &gameSequence, current, &currentSave, &beanzGuy);

    //Maybe could do something with this in the future (Used only for exiting help screen right now)
    if(nextScreenID == "Previous"){
      current = prev;
      continue;
    }

    if(nextScreenID == "") {
        continue;
    }else {
      p.UpdateStatus(playerIn, nextScreenID);
      std::string temp = nextScreenID;
      buffer = gameSequence.search(nextScreenID, &gameSequence);
      beanzGuy.UpdatePlayer(nextScreenID);

      if(nextScreenID == temp){
        if(buffer == current){
          continue;
        }
        if(!(isHelpScreen(current->getScreenID()))){
          prev = current;
        }

        if(nextScreenID == "LS00100"){
         currentSave.autosave(prev, current, ptr, &beanzGuy);
         beanzGuy.set_hp(100);
        }

        current = buffer;

      }else{
        current = gameSequence.search(nextScreenID, &gameSequence);
        prev = buffer;
      }

    }
  }
 
  currentSave.autosave(prev, current, ptr, &beanzGuy);

  gameSequence.clear(ptr);
  
  return 0;
}
