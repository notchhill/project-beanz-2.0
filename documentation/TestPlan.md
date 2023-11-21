1.1 
# Test 1 - Descriptive User Script

    We will use a descriptive user script that will explain to a user acting as a tester the list of steps to properly test Beanz 2.0

1.2
# Test 2 - Screen Output Test

    This test will output 10 test screens and check to see if it matches the appropriate contents of expectedTest2.txt.

    Currently this is set up so that whatever text (including square brackets around choice texts and such) would be outputted to the console for the player to see is outputted to actualTest2.txt for the purposes of this test.

    Any block of screens can be output and tested by looping through the list until the desired first screen, then outputting the desired block of screens, and comparing them against the prepared expectedTest2.txt.

    While in the project-beanz-2.0 directory use the command:

        >diff resource/actualTest2.txt resource/expectedTest2.txt
    
    to compare the results with the expected results.

1.3 
# Test 3 - test.cpp

    Test.cpp will take every screenID and pass it to the search() function. If the search function finds a matching screen, it's okay, if it doesn't, there's an issue. The screenIDs are passed to test.cpp via a Bash script. The Bash file will be called ba.sh, which stands for "Beanz Actualization.sh."

    Can create list of screenIDs using:

        >grep '^ *XX' input.txt >>screenIDs.txt

    where XX stands in for the screen ID (LS, BC, GC, FF, DD) and >> appends the file rather than overwrites. Note - this will have duplicated from the options.