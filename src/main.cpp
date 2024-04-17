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
#include "../include/items.h"

int main() {
  system("mode con: cols=120 lines=40");
  system("cls");
  system("Color 0A");

  GameScreenLinkedList gameSequence;
  GameScreenLinkedList* ptr = &gameSequence;
  GameScreenLinkedList* prev = &gameSequence;
  GameScreenLinkedList* buffer = prev;
  GameScreenLinkedList* current = &gameSequence;
  GameScreenLinkedList* expectedScreen = NULL;
  Inventory inventory;
  Saves currentSave("resource/save.txt", "resource/autosave.txt");
  Puzzle p;
  std::string playerIn;
  Player beanzGuy;
  Items items;

 gameSequence.load("resource/input.txt", &gameSequence, &currentSave);


  while (playerIn != "quit") {
    system("cls");

    gameSequence.display(current, beanzGuy.get_hp());

    playerIn = getPlayerIn();

    if(playerIn == "quit"){
      break;
    }

    std::string nextScreenID = gameSequence.match(playerIn, &gameSequence, current, &currentSave, &beanzGuy, &inventory);

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

        if(nextScreenID == "LS00100"){
          if(expectedScreen != NULL){
            currentSave.autosave(prev, current, ptr, expectedScreen, &beanzGuy, &inventory);
            expectedScreen = NULL;
          }else{
            currentSave.autosave(prev, current, ptr, &beanzGuy, &inventory);
          }
          beanzGuy.set_hp(100);
        }

        if(!( isHelpScreen(buffer->getScreenID()) || isHelpScreen(current->getScreenID()) )){
          prev = current;
        }

        current = buffer;

      }else{
        if(!( isHelpScreen(buffer->getScreenID()) || isHelpScreen(current->getScreenID()) )){
          prev = current;
          expectedScreen = buffer;

        }else{
          prev = buffer; 
        }

        current = gameSequence.search(nextScreenID, &gameSequence);
      }

    }
  }
 
  if(expectedScreen != NULL){
    currentSave.autosave(prev, current, ptr, expectedScreen, &beanzGuy, &inventory);
  }else{
    currentSave.autosave(prev, current, ptr, &beanzGuy, &inventory);
  }
  
  gameSequence.clear(ptr);
  
  return 0;
}
