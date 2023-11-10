### SPECIFICATIONS

Team name: Team Beanz 2.0
Game name: Project Beanz 2.0
Contact info: Dustin, dustin.gabriel777@gmail.com

# TABLE OF CONTENTS

1.0 Overall Description of the Game.
    1.1 Purpose.
    1.2 Theme.
        1.2.1 Beancouver.
        1.2.2 Giant's Castle.
        1.2.3 Fractal Forest.
        1.2.4 Desert.
    1.3 Goals.
    1.4 Target Audience.

2.0 Description of the Overall Sequence of Events for Beanz 2.0.
    2.1 Conditions for Winning and Losing.
    2.1 Player Goals.
    2.3 Scoring Systems.

3.0 Menus, Screens, and Control Systems.
    3.1 Loading Screen.
    3.2 Main Menu.
    3.3 Intro Screen.
    3.4 Help Screen.
    3.5 Game Interface.
    3.5 Game Over Screen.
    3.6 Victory Screen.

4.0 Descriptions and Flowchart of the Levels.
    4.1 What is in Each Level.
        4.1.1 Beancouver.
        4.1.2 Giant's Castle.
        4.1.3 Fractal Forest.
        4.1.4 Desert.
    4.2 The Layout.
    4.3 Key Features.
        4.1.1 Beancouver.
        4.1.2 Giant's Castle.
        4.1.3 Fractal Forest.
        4.1.4 Desert.
    4.4 Characters.
        4.1.1 Beancouver.
        4.1.2 Giant's Castle.
        4.1.3 Fractal Forest.
        4.1.4 Desert.
    4.5 Sequence of Actions/Puzzles/Steps Associated With the Level.

5.0 The Characters.
    5.1 The Hero.
    5.2 Chef Garbanzo.
    5.3 Other Characters.

6.0 Priority for Scalability.
    6.1 Core Features.
    6.2 Secondary Features.
    6.3 Teriary Features.

7.0 Non-functional Requirements.
    7.1 Core Features.
    7.2 Secondary Features.
    7.3 Teriary Features.

# SPECIFICATIONS

1.0 Overall Description of the Game.

    1.1 Purpose.
        To provide entertainment through a text-based adventure experience, providing a unique kind of gaming adventure

    1.2 Theme.
        Each of the adventure areas the player can access have slightly different fantasy-style, but the closest thing the game has to an overall theme is beans.

        In this fictional world Planet Beanz (a bean-shaped planet) and is tidally locked (meaning one side always faces towards the sun and the other side always faces away.) This affects the biomes and the inhabitants. On the "hot" side (facing towards sun) there is an arid desert environment. On the cold side, there is the fractal forest, with a colder environment inhabited by forest gnomes. The cold side only gets light from the moon, which is reflected light from the sun. The fractal trees, with fractal-like leaves, developed in this environment to maximize their surface area for collecting light for photosynthesis. On the polar equator between the hot and cold sides is the Beancouver. Residing in Beancouver is Chef Garbanzo, who runs the Michelin 5 Star restaurant Chef Garbanzo's Lean Bean Cuisine. Rising above Beancouver is the giant beanstalk that leads to the giant's castle in the sky. The player has to hunt for beans to be used in a delicious dish being prepared by Chef Garbanzo. 
        
        1.2.1 Beancouver.
              A peaceful bean farming village laying in the shadow of a giant's castle. This village consists of a restaurant, a village square, and a bean farm.
              
        1.2.2 Giant's Castle.
              The Giant's castle features a giant beanstalk leading up to the huge castle where the giant resides. In the castle a visitor will find a kitchen, a basement, and a bathroom.

        1.2.3 Fractal Forest.
              The fractal forest area contains trees with fractal-like leaves, a hut, a giant hollowed out tree to be explored, and of course, a treehouse.

        1.2.4 Desert.
              The Desert area features dunes, oasis, a palace, and glass tunnels in a desert environment.

    1.3 Goals.
        A linear adventure game running in the terminal using text/ASCII to present the story, visuals, and possible decisions that the user can make. User can influence the story based on their decisions, taking different paths to the success or failure.

        This application will be developed with the C++ programming language. This application can be built and run on a system with GCC compiler. This program will use a creative commons license for free software.
    
    1.4 Target Audience.
        The target audience is players of adventure story games. It will lack visual violence and gore, but contain mentions of violence so the target audience can include youths. Further scaling will add content that can appeal to more users: people who enjoy exploration or statistics and character building for example.


2.0 Description of the Overall Sequence of Events for Beanz 2.0.

    2.1 Conditions for Winning and Losing.
        Winning - for first iteration of the game the player will have to collect all the beans and bring them back to Chef Garbanzo in Beancouver in order to win.
        Losing - die to some mishap, for example die in combat with a forest gnome due to a poor decision.

    2.1 Player Goals.
        In the core release the players goal is to survive and collect 3 beans.

    2.3 Scoring Systems.
        Based on the number of beans collected. 

3.0 Menus, Screens, and Control Systems.

    3.1 Loading Screen.
        +---------------------------------------------------------------------------------------------+
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                Beanz 2.0                                                    |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                               Press any key to continue                                     |
        |                                                                                             |
        |                                                                                             |
        +---------------------------------------------------------------------------------------------+

    3.2 Main Menu.
        +---------------------------------------------------------------------------------------------+
        | Welcome to Beanz 2.0!                          [start] to start the game                    |
        |                                                [quit] to exit the game                      |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                 Enter your choice                           |
        |                                                >                                            |
        +---------------------------------------------------------------------------------------------+
    
    3.3 Intro Screen.
        +---------------------------------------------------------------------------------------------+
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                             A story will be displayed here                                  |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                               Press any key to continue                                     |        +---------------------------------------------------------------------------------------------+
    
    3.4 Help Screen.
        +---------------------------------------------------------------------------------------------+
        |                                                                                             |
        |                                                                                             |
        |                      Keywords:                                                              |
        |                      To return to the main menu enter [quit]                                |
        |                      To exit the game enter [exit]                                          |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                               Press any key to continue                                     |          +---------------------------------------------------------------------------------------------+
    
    3.5 Game Interface.
        +---------------------------------------------------------------------------------------------+
        | You see a darkened room in front of you,       [chest] to open chest                        |
        | with a chest lying on the ground               [door] to go through the door                |
        | and a door to the shed in the back.                                                         |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                 Enter your choice                           |
        |                                                >                                            |
        +---------------------------------------------------------------------------------------------+

    3.5 Game Over Screen.
        +---------------------------------------------------------------------------------------------+
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                             A game over message will be displayed here                      |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                               Press any key to continue                                     |        +---------------------------------------------------------------------------------------------+

    3.6 Victory Screen.
        +---------------------------------------------------------------------------------------------+
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                             A victory message will be displayed here                        |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                                                                                             |
        |                               Press any key to continue                                     |        +---------------------------------------------------------------------------------------------+

4.0 Descriptions and Flowchart of the Levels.

    4.1 What is in Each Level.
        
        4.1.1 Beancouver.
              This level is inhabited by the villages, the chef, and the player character. If features the restaurant, the village square, and the bean farm.
        
        4.1.2 Giant's Castle.
              This level is inhabited by a magical dust bunny and a giant. It features three areas: the kitchen, the basement, and the bathroom.
        
        4.1.3 Fractal Forest.
              This level is inhabited by giant frogs and forest gnomes. It features a giant hollowed out log, a treehouse, and a hut.
        
        4.1.4 Desert.
              This level is mysteriously uninhabited. It features dunes, oasis, cactuses, a palace, and glass tunnels.

    4.2 The Layout.
        All of the information regarding how these levels are mechanically interlinked is displayed in our Miro chart: https://miro.com/app/board/uXjVNf2YUow=/?share_link_id=426117059493
        
        Each square denotes a screen which might be displayed to the player. Note that each square contains a rough outline of what the player will see on each screen. They will see a text blurb (written within each screen between two curly braces), multiple options (the options for each screen are written inside the squares), and they will be prompted to give input in the terminal. The arrows from one square to the next indicate which screen the player will go to next based on the option they chose. Note that the arrows contain a letter (A, B, C, etc) in their midsection. This represents the option which will take the player along this arrow.

        The Miro chart is divided roughly into two sections. The one higher up is a high-level logical flow of how the player will traverse through the parts of the game. This diagram contains comparatively few details than the diagram lower down. The lower diagram showcases every screen which the player can come across throughout gameplay. Notice that the chart begins at the very left with the loading screens. The options chosen by the player will lead them along the arrows. Each of the overall areas (Giant's Castle, Fractal Forest, The Desert) have various paths available for the players to take. Notice how each of these paths will converge at the end, and lead linearly into the next general area. The player will start in the loading screen, go to the village, then the Giant's Castle, then Fractal Forest, then The Desert, and finally the player will arrive at the ending of the game. There they will trade the beans they found with Chef Garbonzo, and receive a final score based on the number of beans.

    4.3 Key Features.
        
        4.1.1 Beancouver.
              This is the starting area.
        
        4.1.2 Giant's Castle.
              This area features a giant with sensitive hearing.
        
        4.1.3 Fractal Forest.
              This area features a dig mechanic where you need a specific tool to dig up the bean.
        
        4.1.4 Desert.
              This area features exploration and a puzzle.

    4.4 Characters.

        4.1.1 Beancouver.
              Chef Garbanzo, villagers, the player character.
        
        4.1.2 Giant's Castle.
              Magical Dust Bunny, Giant.
        
        4.1.3 Fractal Forest.
              Giant Frogs, Forest Gnomes.
        
        4.1.4 Desert.
              Uninhabited.

    4.5 Sequence of Actions/Puzzles/Steps Associated with the Level.
        See 4.2.

5.0 The Characters.

    5.1 The Hero.
        This is the players character. He is the hero of the adventure and is tasked with saving the three beans.

    5.2 Chef Garbanzo.
        Chef Garbanzo is the most important NPC, the player's main task in the game is to collect special beans for his ultimate dish and bring them back to his resturaunt in Beancouver. The player will talk to Chef Garbanzo at the beginning of the game

    5.3 Other Characters.
        Dust Bunny - a magical bunny that resides in the Giant's Castle.
        The Giant - an unnamed giant that the player must avoid.
        Giant Frogs - large humanoid frogs that inhabit the Giant Hollowed Out Log.
        Forest Gnomes - inhabitants of the Fractal Forest that may be located around the Hut.

6.0 Priority for Scalability.

    6.1 Core Features.
        The core tier will include the three basic adventure areas the player can explore (Giant's Castle, Fractal Forest, Desert) and the basic input system where the player is given a text blurb and some options to choose from.

    6.2 Secondary Features.
        Some features of secondary importance include the game being made non-linear. To start with, the player will progress through the three basic adventure areas one after the other, but later we could allow the player to complete them in whatever order they want, accessing each from Beancouver, the hub/starting area where Chef Garbanzo is located (at his gourmet resturaunt, Chef Garbanzo's Lean Bean Cuisine.) Also of secondary importance would be player attributes (health, inventory, progression system) and a combat system.

    6.3 Teriary Features.
        Nice-to-have features if time permits would include a map the player can view showing where they are, drawn with ASCII art.

7.0 Non-functional Requirements.
    
    7.1 Spelling and Grammar.
        The text shown in game must be written with no spelling or grammatical errors. More specifically, putting all of the text though a spell-checker should return no errors.

    7.2 Intuitive Design.

        7.2.1 Controls.
              The options the player has available to them must be clearly defined and intuitively grasped. For this game, that means 90% of third party testers must be able to work out the controls without any assistance.

        7.2.2 Game Flow.
              Likewise, all third party testers should report that they understood what was happening during gameplay at least 90% of the time. Also, all third party testers must understand what the goal of the game is. Demonstrated by an ability to explain the setting and plot of the game consistent with our outline in this specs doc.

    7.3 Performance.

        7.3.1 Response Time.
              The game must provide feedback to the player's inputs in under 0.5s 99% of the time.

        7.3.2 Code Quality.
                There must be minimal or no bugs in the code. More specifically, each function should do what is intended to do (as outlined in our design specs), and the player should not be able to crash or softlock the program. Also, the code must be able to be understood by a third party (the prof.). The code must reflect what is indicated in the design specs.
        
        7.3.3 Requirements.
              The game must be able to run on terminal. The game should take up no more than (x storage units), and should require no more than (basically any) ram.

    7.4 Fun.
        The game must be enjoyable to play. For our purposes, this means 75% or more of third party testers must consider the game at least somewhat enjoyable.
