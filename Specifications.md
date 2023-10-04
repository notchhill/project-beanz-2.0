### SPECIFICATIONS

Team name: Team Beanz 2.0
Game name: Project Beanz 2.0
Contact info: Dustin, dustin.gabriel777@gmail.com

# TABLE OF CONTENTS
1.0 an overall description of the game purpose, theme, goals, and target audience (like the product overview for other software products)
    1.1 Game Purpose
        To provide entertainment through a text-based adventure experience, providing a unique kind of gaming adventure
    1.2 Theme
        Each of the adventure areas the player can access have slightly different fantasy-style, but the closest thing the game has to an overall theme is beanz

        In this fictional world Planet Beanz (a bean-shaped planet) and is tidally locked (meaning one side always faces towards the sun and the other side always faces away.) This affects the biomes and the inhabitants. On the "hot" side (facing towards sun) there is an arid desert environment. On the cold side, there is the fractal forest, with a colder environment inhabited by forest gnomes. The cold side only gets light from the moon, which is reflected light from the sun. The fractal trees, with fractal-like leaves, developed in this environment to maximize their surface area for collecting light for photosynthisis. On the polar equator between the hot and cold sides is the Beancouver. Residing in Beancouver is Chef Garbanzo, who runs the Michelin 5 Star resturaunt Chef Garbanzo's Lean Bean Cuisine. Rising above Beancouver is the giant beanstalk that leads to the giant's castle in the sky. The player has to hunt for beans to be used in a delicious dish being prepared by Chef Garbanzo. 
        
        1.2.1 
        Desert area features a mirror and glass tunnels in a desert environment

        1.2.2 
        Giant's castle features a giant beanstalk leading up to the huge castle where the giant resides

        1.2.3 
        The fractal forest area contains trees with fractal-like leaves, a hut, a giant hollowed out tree to be explored, and of course, a treehouse

    1.3 Goals
        Out goal is to create the best and most functional game we can

2.0 description of the overall flow/sequence of events for the game, conditions for winning/losing, player goals and scoring systems
    - conditions for winning/losing, 
        - winning - collect the beans
        - losing - die to some mishap, for example die in combat with a forest gnome due to a poor decision
    - player goals
        - collect the beans
    - scoring systems
        number of beans collected, for first iteration of the game player will have to collect all the beans and bring them back to Chef Garbanzo in Beancouver in order to win
3.0 detailed descriptions and sketches of each of the control systems, menus, screens, and interfaces the player will interact with
    - a list of options to choose from
    - keywords to enter

    Being a text adventure, the game will take place and be played in a text-based terminal window. Below is an ASCII drawing of a sample terminal window where the player has the environment they're in described to them and is given a list of options/things they can do:

    +---------------------------------------------------------------------------------------------+
    | You see a darkened room in front of you,       [chest] to open chest                        |
    | with a chest lying on the ground               [door] to go through the door                |      
    | and a door to the shed in the back.                                                         |
    |                                                                                             |
    |                                                                                             |
    +---------------------------------------------------------------------------------------------+

4.0 detailed descriptions and sketches of each of the game levels (if any), what is in each level, the layout, key features, characters, and sequence of actions/puzzles/steps associated with the level
    - All of the above are described on the flowchart below, which you (Dave) should be able to view
    - https://miro.com/app/board/uXjVNf2YUow=/?share_link_id=426117059493

5.0 detailed descriptions of the key characters, attributes, and items present within the game (if any), and the interactions between them
    - the player character
        + The basic framework of the game won't include any real attributes for the player, but a major part of the scalability of the game will be player attributes that can be added later
        + E.g. health, progression system/levels/skills, an inventory/holding items, etc
    - The chef
        + Chef Garbanzo is the most important NPC, the player's main task in the game is to collect special beans for his ultimate dish and bring them back to his resturaunt in Beancouver
        + The player will talk to Chef Garbanzo at the beginning of the game
    - Other characters:
        + Some of the tasks in the three adventure areas (to start with) will involve talking to various NPCs
        + The other important NPCs are the frogs the player can fight in the giant log (located in the Forest area), and the forest gnomes the player can fight in the hut (within the Fractal Forest area)

6.0 priority tiers for the levels, features, characters, etc (which ones are core, which ones are secondary, which ones are just nice-to-have extras if time permits)
    6.1
    The top priority tier will include the three basic adventure areas the player can explore (Giant's Castle, Fractal Forest, Desert) and the basic input system where the player is given a text blurb and some options to choose from

    6.2 
    Some features of secondary importance include the game being made non-linear. To start with, the player will progress through the three basic adventure areas one after the other, but later we could allow the player to complete them in whatever order they want, accessing each from Beancouver, the hub/starting area where Chef Garbanzo is located (at his gourmet resturaunt, Chef Garbanzo's Lean Bean Cuisine.) Also of secondary importance would be player attributes (health, inventory, progression system) and a combat system

    6.3 
    Nice-to-have features if time permits would include a map the player can view showing where they are, drawn with ASCII art

7.0 non-functional requirements, glossary, and appendices (as with the other software products)