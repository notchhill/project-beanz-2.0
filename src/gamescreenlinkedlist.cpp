/**
 * @file gamescreenlinkedlist.cpp
 * @author Trevor
 * @author Austin
 * @author Robert
 * @author Dustin
 * @author Lucas
 * @version 1.0.1
 * @date 2023/10/27
 *
 * GameScreenLinkedList method implementations.
 *
 */

#include "../include/gamescreenlinkedlist.h"

/*void pushBack(GameScreenLinkedList node, GameScreenLinkedList root) {
   GameScreenLinkedList iterator = root;
    while(iterator != NULL) {
        iterator = iterator.next;
    }  
}
*/

const GameScreenLinkedList* GameScreenLinkedList::search(const std::string screenID, const std::GameScreenLinkedList* root) const
{  
    for(GameScreenLinkedList* temp = root; temp->next != nullptr; temp = temp->next)
    {
        if(temp->screenID == screenID)
        {
            return temp;
        }
    }
}

