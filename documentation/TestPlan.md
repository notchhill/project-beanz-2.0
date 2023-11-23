### TESTPLAN

The plan should be described in a TestPlan.md in your team gitlab/github repository, and should contain the following:
1.  a description of the testing techniques to be used for different aspects of the program. These techniques will vary significantly depending on the nature of the product and the tools/languages used to produce it:
    - (parts of) some projects might use programmed scripts (such as those we're writing in bash in lectures) or built-in tools to automate the running of some test cases
    - (parts of) some projects might have a descriptive user "script" detailing user actions for the test case (1. User clicks "Options" button, 2. in the resulting popup window user the user clicks the "file" field, 3. the user types the word "mydata.txt", 4. the user clicks the "submit" button)
    - (parts of) some projects might use a record/playback system to record user GUI actions for a test case, so they can be re-run at will for later testing

2.  a detailed description of the test infrastructure in use: the precise scripts/tools that will be used (if any), the directory structure and file naming system to be used for relevant test files (test case input/data files, expected output files, actual recorded output files, logs of test results, etc)

3.  a table of every test case and scenario to be applied, including for each:
    - a unique name for the test case
    - a short (one line) description of the specific requirement or functionality that test case covers
    - the names of the files/programmed scripts/user-action scripts that contain the full data for this test case/scenario (any setup instructions for the test case/scenario, precise user actions in sequence and with every input value used, precise expected outputs/results)
Note that the test cases/scenarios should cover both the handling of valid user behaviour/input and any error checking/handling the product is expected to perform.

## TESTPLAN

# Test 1 - User Test

    1.1 Testing Technique
        We will use a descriptive user script that will explain to a user acting as a tester the list of steps to properly test Beanz 2.0

    1.2 Test Infrastructure

# Test 2 - Screen Output Test

    2.1 Testing Technique
        This test will output 10 test screens and check to see if it matches the appropriate contents of expectedTest2.txt.

        Currently this is set up so that whatever text (including square brackets around choice texts and such) would be outputted to the console for the player to see is outputted to actualTest2.txt for the purposes of this test.

        Any block of screens can be output and tested by looping through the list until the desired first screen, then outputting the desired block of screens, and comparing them against the prepared expectedTest2.txt.

        While in the project-beanz-2.0 directory use the command:

            >diff resource/actualTest2.txt resource/expectedTest2.txt
        
        to compare the results with the expected results.

    2.2 Test Infrastructure

# Test 3 - Screen ID Test

    3.1 Testing Technique
        Test.cpp will take every screenID and pass it to the search() function. If the search function finds a matching screen, it's okay, if it doesn't, there's an issue. The screenIDs are passed to test.cpp via a Bash script. The Bash file will be called ba.sh, which stands for "Beanz Actualization.sh."

        Can create list of screenIDs using:

            >grep '^ *XX' input.txt >>screenIDs.txt

        where XX stands in for the screen ID (LS, BC, GC, FF, DD) and >> appends the file rather than overwrites. Note - this will have duplicated from the options.

    3.2 Test Infrastructure

# Table of Test Cases

Name               | Description                                    | Files |
------------------ | ---------------------------------------------- | -------------------------------------------- |
unique name        | (one-line) functionality that test case covers | names of the files containing the data/scripts |
User Test          | checks if game works for users  | |
Screen Output Test | checks if output is as expected | actualTest2.txt, expectedTest2.txt |
Screen ID Test     | checks if every screenID loaded | ba.sh |
