#include "../include/utility.h"

class Player {
private:
    int hp;

public:
    Player();
    ~Player();

    int get_hp();

    void incr_hp(int amount);
    void decr_hp(int amount);

    void check_hp();

    void u_died(std::string &ID);
};