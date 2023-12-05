## TESTPLAN

# Test 1 - User Test

    1.1 Testing Technique
        We will use a descriptive user script that will explain to a user acting as a tester the list of steps to properly test Beanz 2.0. The script is explained in test1instructions.txt. Testers can document the results of their entered commands for the devs to evaluate.

    1.2 Test Infrastructure
        Using Test1Instructions.txt and test1results.txt.

# Test 2 - Screen Output Test

    2.1 Testing Technique
        This test will output 10 test screens and check to see if it matches the appropriate contents of expectedTest2.txt.

        The first 10 screens were chosen as an example to avoid having to test all 7,000 lines of input.txt. Working with the expected output required manual copy-pasting, which would be difficult to do for the entirety of input.txt. There is a code block in test.cpp that allows chunks of screens to be skipped in order to test further parts of the game.

        The 10 screens are produced through test.cpp, in the Test 2 section. The expected results were produced through manual copy-pasting of the expected text output from input.txt. This includes re-formatting to match against the actual expected appearance in the terminal window. Only 10 screens were chosen to make sure the output process functions properly in general, since if one output is correct it's most likely that all 7,000 work properly. 

        Currently this is set up so that whatever text (including square brackets around choice texts and such) would be outputted to the console for the player to see is outputted to actualTest2.txt for the purposes of this test.

        Any block of screens can be output and tested by looping through the list until the desired first screen, then outputting the desired block of screens, and comparing them against the prepared expectedTest2.txt.

    2.2 Test Infrastructure
        Using actualTest2.txt, expectedTest2.txt, and test.cpp.

        While in the project-beanz-2.0 directory use the command:

            >diff resource/actualTest2.txt resource/expectedTest2.txt
        
        to compare the results with the expected results.

# Test 3 - Screen ID Test

    3.1 Testing Technique
        Test.cpp will take every screenID and pass it to the search() function. If the search function finds a matching screen, it's okay, if it doesn't, there's an issue. The screenIDs are passed to test.cpp via a Bash script. The Bash file will be called ba.sh, which stands for "Beanz Actualization.sh."

    3.2 Test Infrastructure
        Using screenIDs.txt and ba.sh.

        Can create list of screenIDs using:

            >grep '^ *XX' input.txt >> screenIDs.txt

        where XX stands in for the screen ID (LS, BC, GC, FF, DD) and >> appends the file rather than overwrites. Note - this will have duplicated from the options.

# Test 4 - Screen ID Test 2

    4.1 Testing Technique
        This test is designed to check that the game contains the same screens and option links as the flowchart. A tester will compare the contents, screenIDs and optionIDs, for each screen in input.txt to the contents of the matching tile on our flowchart, hosted on Miro. 

    4.2 Test Infrastructure
        The Miro chart contains tiles that have all the screens in the game. This can easily be compared against input.txt which has all the screens actually written out in the correct format.

# Table of Test Cases

Name               | Description                              | Files |
------------------ | ---------------------------------------- | -------------------------------------------- |
User Test          | checks if game works for users           | test1.txt                                    |
Screen Output Test | checks if output is as expected          | actualTest2.txt, expectedTest2.txt, test.cpp |
Screen ID Test     | checks if every screenID loaded          | ba.sh, screenIDs.txt                         |
Screen ID Test 2   | checks if the game matches the flowchart | input.txt, miro flowchart                    |