1.1 
    Descriptive User Script

    We will use a descriptive user script that will explain to a user acting as a tester the list of steps to properly test Beanz 2.0

1.2
    Screen Output Test

    This test will output every screen in the game and check to see if it matches the appropriate contents of input.txt.

1.3 
    test.cpp

    Test.cpp will take every screenID and pass it to the search() function. If the search function finds a matching screen, it's okay, if it doesn't, there's an issue. The screenIDs are passed to test.cpp via a Bash script. The Bash file will be called ba.sh for "Beanz Actualization.sh."