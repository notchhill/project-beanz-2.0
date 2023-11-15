1.1 
# Test 1 - Descriptive User Script

    We will use a descriptive user script that will explain to a user acting as a tester the list of steps to properly test Beanz 2.0

1.2
# Test 2 - Screen Output Test

    This test will output every screen in the game and check to see if it matches the appropriate contents of input.txt.
    Currently this is set up so that whatever text (including square brackets around choice texts and such) would be outputted to the console for the player to see is outputted to test2output.txt for the purposes of this test. 

1.3 
# Test 3 - test.cpp

    Test.cpp will take every screenID and pass it to the search() function. If the search function finds a matching screen, it's okay, if it doesn't, there's an issue. The screenIDs are passed to test.cpp via a Bash script. The Bash file will be called ba.sh, which stands for "Beanz Actualization.sh."