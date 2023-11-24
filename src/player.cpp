#include "../include/player.h"

/*
@brief Default constructor for Player class.
@param N/A
@return N/A
*/
Player::Player() {
    hp = 0;
}

/*
@brief Destructor for Player class.
@param N/A
@return N/A
*/
Player::~Player() {

}

/*
@brief Increments player health (hp) by amount passed.
@param int amount ; Amount to increment health of player by
@return void ;
*/
void Player::incr_hp(int amount) {
    hp = hp + amount;
}

/*
@brief Decrements player health by amount it is passed.
@param int amount ; Amount to decrement player health by
@return void ;
*/
void Player::decr_hp(int amount) {
    hp = hp - amount;
}

/*
@brief Allows player to check their health by displaying current health to them.
@param N/A
@return void ;
*/
void Player::check_hp() {

}