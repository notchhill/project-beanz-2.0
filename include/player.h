#pragma once
#include "../include/utility.h"

class Player {
private:
    int hp;
    int maxHP = PLAYER_MAX_HP;

public:
    Player();
    ~Player();

    void UpdatePlayer(std::string &ID);

    int get_hp();

    void incr_hp(int amount);
    void decr_hp(int amount);
    void set_hp(int amount);

    void u_died(std::string &ID);
};
