### VERSION CONTROL
Modified distributed version control system
- main branch
    - dev branch
        - branch to clone from for anyone using multiple computers
        - anyone using single computer can clone from dev branch 

We will have two primary branches. A branch for the final/client version, and one for the development version.

For low-level fixes/touch-ups, we will edit the developer branch itself. And of course, notify everyone before committing. Make sure you get approval from all team members before committing. Once it's committed, get another team member to look over your code to verify it meets the standards.

For high-level content additions, we will make a branch of the developer branch. Then, all the same procedures apply, except it refers to the newly created branch.

We make a commit for everything changes or added (code standards), and only merge new branches back into the developer branches once the whole team agrees that it's working.

We will only merge the development branch into main whenever there are no unmerged branches of the development branch. Once all of the branches created from the dev branch are merged back into it, the dev branch is merged into main. When we begin work again, we make a new dev branch and go from there. 

Merging of dev branch into main will be conducted by team lead for that week. Anyone editing dev branch is required to have Discord open to the version_control channel while editing a source code file. They will announce before committing or pushing in the version_control channel. Anyone who responds on Discord during a five-minute window after this announcement will be considered the only other ones editing and if they approve the commit/push then it's good to go forward. 

We will conduct our own testing of dev branch before a dev branch merge into main. This will consist of going through the game and trying options. 