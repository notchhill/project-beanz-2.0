#include "../include/utility.h"

class Player {
private:
    int hp;

public:
    Player();
    ~Player();

    void incr_hp(int amount);
    void decr_hp(int amount);

    void check_hp();
};