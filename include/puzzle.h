#include "../include/utility.h"

class Puzzle
{

private:
    int current_light = 0;
    bool state[6];           // is the light on or off
    int bright[6];           // how many lights are shining on each shape
    int pointing[6];         // index = light, value = pointing at

public:
    Puzzle();
    ~Puzzle();
    void UpdateStatus(std::string I, std::string &ID);
    bool Check();
};
