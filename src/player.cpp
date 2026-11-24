#include "../include/player.h"

/*
@brief Default constructor for Player class. Sets player health to 100 by default.
@param N/A
@return N/A
*/
Player::Player() {
    hp = 100;
}

/*
@brief Destructor for Player class.
@param N/A
@return N/A
*/
Player::~Player() {

}

void Player::UpdatePlayer(std::string &ID)
{
    
    unsigned int nextLen = ID.length();
    if(ID[7] == 'D' || ID[7] == 'H') {
        int strAmountLen = 0;
        if(nextLen == 9) {
            strAmountLen = 2;
        } else if(nextLen == 10) {
            strAmountLen = 3;
        }
        std::string strAmount = ID.substr(8,strAmountLen);
        int amount = stoi(strAmount,nullptr,10);

        if (ID[7] == 'D') this->decr_hp(amount);
        if (ID[7] == 'H') this->incr_hp(amount);

        if (this->get_hp() > 100) this->set_hp(100);
        if (this->get_hp() <= 0) this->u_died(ID);
    }
}

int Player::get_hp() {
    return hp;
}

/*
@brief Increments player health (hp) by amount passed.
@param int amount ; Amount to increment health of player by
@return void;
*/
void Player::incr_hp(int amount) {
    hp = hp + amount;
    if(hp > PLAYER_MAX_HP){
        set_hp(PLAYER_MAX_HP);
    }
}

/*
@brief Decrements player health by amount it is passed.
@param int amount ; Amount to decrement player health by
@return void ;
*/
void Player::decr_hp(int amount) {
    hp = hp - amount;
}

void Player::set_hp(int amount){
    hp = amount;
}

/*
@brief Warps the player to a death scren if they are dead
@param string &ID ; ID of next screen
@return void ; 
*/
void Player::u_died(std::string &ID) {
    ID = "LSLLLLL";
}
