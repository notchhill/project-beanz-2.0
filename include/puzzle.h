#include "../include/utility.h"

class Puzzle
{

private:
    int current_light = 0;
    bool state[6];           // is the ith light on or off (0 is ignored)
    int bright[6];           // how many lights are shining on the ith shape (0-2 are ignored)
    int pointing[6];         // what shape is the ith light pointing at (0 ignored)

public:
    Puzzle();
    ~Puzzle();
    void UpdateStatus(std::string I, std::string &ID);
    bool Check();
};
