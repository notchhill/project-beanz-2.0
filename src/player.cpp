#include "../include/player.h"

Player::Player() {
    hp = 0;
}

Player::~Player() {

}

void Player::incr_hp(int amount) {
    hp = hp + amount;
}

void Player::decr_hp(int amount) {
    hp = hp - amount;
}

void Player::check_hp() {
    
}