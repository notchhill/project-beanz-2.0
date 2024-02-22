/**
 * @file utility.h
 * @author Trevor
 * @author Austin
 * @author Robert
 * @author Dustin
 * @author Lucas
 * @version 1.0.2
 * @date 2023/10/27
 *
 * Includes libraries and any functions not tied to a class (functions that should be usable by all files in the program)
 * Also includes constants
 *
 */


#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <windows.h>
#include <list>
#include <sstream>

#define PLAYER_MAX_HP 150
#define ITEM_FILE_NAME "../resource/items.txt"

const int screenWidth = 100;  // width of the terminal
const int align = 18;         // number of spaces needed to align option blurbs
const int zones = 7;          // number of zones/main areas in the game

const std::string ID_MARKERS[zones] = {"LS","BC","GC","FF","DD","RE","IK"};
// array of the starts of each main zones' ID

std::string getPlayerIn();
// gets a string from the user, and copies it into another string (initially empty), character-by-character, 
    //based on several conditions
//    if the next character is a lowercase letter, it gets concatenated onto the second string
//    if the next character is an uppercase letter, it gets converted into a lowercase letter, 
    //and then concatenated onto the second string
//    if the next character is a symbol, the character is not concatenated onto the second string

void nicePrint(std::string text, bool isOption = false);
// this function will be passed a string. It will print the string character-by-character, 
//and insert a newline every 10th ' ' character.

bool isHelpScreen(std::string screenID);
//This function takes in the screenID and returns 1 if it is a help screen, and 0 if not.