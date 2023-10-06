#ifndef __HEADER__
#define __HEADER__

#include <iostream>

class gameScreen
{
    private:
        struct option{
            gameScreen* pointer;
            string optionDiscription;
            string optionText;
        };

        string textBlurb; 
        option choice1;
        option choice2;
        option choice3;
        option choice4;
        option choice5;

    public:
        getOption(string choice);
};
#endif
