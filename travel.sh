#!bin/bash

#######################################################
##                    USER MANUAL                    ##
##---------------------------------------------------##
## This script takes 1 argument. The argument given  ##
##    by the user corresponds to a location within   ##
##    the game. e.g., "kitchen" will take you to the ##
##    entrance of the Giant's Castle (the kitchen).  ##
##    See the variables below and their comments to  ##
##    see which variable corresponds with which      ##
##    location. Type the name of the variable as the ##
##    first argument to warp to the area which       ##
##    correspoends with that variable.               ##
#######################################################

executable="./bin/beanz2"
path=""

kitchen="start start start restaurant square ask go"                                     # warps the player to Kitchen Part 1
basement="enter talk bean explore chair push look lumos explore"                         # warps the player to Basement
bathroom="broom rug broom dryer vent"                                                    # warps the player to Bathroom
kitchen2="crawl sink climb climb"                                                        # warps the player to Kitchen Part 2
log="plant dirt water plant climb beanstalk descend"                                     # warps the player to Hollowed-Out Log
treehouse="confront quest thank"                                                         # warps the player to Treehouse
hut="ask bow throne warrior wizard map"                                                  # warps the player to The Hut
desert="shed shovel stick search trowel marked desert"                                   # warps the player to Desert
palace="west west palace"                                                                # warps the player to Mirror Palace
tunnels="door lights two switch back lights three switch back lights four switch down"   # warps the player to Glass Tunnels
end="forward forward bean escape walk jump next slam next next return"                   # warps the player to Beancouver (end)

path+=" ${kitchen}"
if [ $1 == "kitchen" ]; then
    echo "$path" | $executable
fi

path+=" ${basement}"
if [ $1 == "basement" ]; then
    echo "$path" | $executable
fi

path+=" ${bathroom}"
if [ $1 == "bathroom" ]; then
    echo "$path" | $executable
fi

path+=" ${kitchen2}"
if [ $1 == "kitchen2" ]; then
    echo "$path" | $executable
fi

path+=" ${log}"
if [ $1 == "log" ]; then
    echo "$path" | $executable
fi

path+=" ${treehouse}"
if [ $1 == "treehouse" ]; then
    echo "$path" | $executable
fi

path+=" ${hut}"
if [ $1 == "hut" ]; then
    echo "$path" | $executable
fi

path+=" ${desert}"
if [ $1 == "desert" ]; then
    echo "$path" | $executable
fi

path+=" ${palace}"
if [ $1 == "palace" ]; then
    echo "$path" | $executable
fi

path+=" ${tunnels}"
if [ $1 == "tunnels" ]; then
    echo "$path" | $executable
fi

path+=" ${end}"
if [ $1 == "end" ]; then
    echo "$path" | $executable
fi
