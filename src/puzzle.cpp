#include "../include/puzzle.h"

Puzzle::Puzzle()
{
    for (int i = 0; i < 6; i++) state[i] = false;
    for (int i = 0; i < 6; i++) bright[i] = 0;
    for (int i = 0; i < 6; i++) pointing[i] = 4;
    state[1] = true;
    bright[4] = 1;
}

Puzzle::~Puzzle() {}

void Puzzle::UpdateStatus(std::string I, std::string &ID)
{
    if (ID[0] == 'D') {
        // should be in DD03000
        if (I == "one") current_light = 1;
        if (I == "two") current_light = 2;
        if (I == "three") current_light = 3;
        if (I == "four") current_light = 4;
        if (I == "five") current_light = 5;

        // should be at one of the lights
        if (I == "switch") {
            state[current_light] = !state[current_light];
            int delta = state[current_light] - (!state[current_light]);
            bright[pointing[current_light]] += delta;
        }
        int shape = 0;
        if (I == "triangle") shape = 3;
        if (I == "square") shape = 4;
        if (I == "pentagon") shape = 5;
        if (shape != 0) {
            bright[pointing[current_light]] -= state[current_light];
            bright[shape] += state[current_light];
            pointing[current_light] = shape;
        }

        // check if the puzzle is solved, turn off all the lights if so
        if (this->Check()) {
            ID = "DD04100";
            for (int i = 0; i < 6; i++) state[i] = false;
        }
    }
}

bool Puzzle::Check()
{
    int lights_on = 0;
    for (int i = 0; i < 6; i++) lights_on += state[i];

    if (bright[3] == 3 && lights_on == 3) return true;
    if (bright[4] == 4 && lights_on == 4) return true;
    if (bright[5] == 5 && lights_on == 5) return true;

    if (pointing[3] == 3 && pointing[4] == 4 && pointing[5] == 5) {
        if (state[3] == true && state[4] == true && state[5] == true) {
            if (state[1] == false && state[2] == false) return true;
        }
    }
    return false;
}
