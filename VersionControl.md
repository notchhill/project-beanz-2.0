###
Modified distributed version control system
- main branch
    - dev branch
        - branch to clone from for anyone using multiple computers
        - anyone using single computer can just clone from dev branch

More elaborate description: 

We will have two primary branches. A branch for the final/client version, and one for the development version.

For low-level fixes/touch-ups, we will edit the developer branch itself. And of course, notify everyone before committing. Make sure you get approval from all team members before committing. Once it's committed, get another team member to look over your code to verify it meets the standards.

For high-level content additions, we will make a branch of the developer branch. Then, all the same procedures apply, except it refers to the newly created branch.

We make a commit for everything changes or added (code standards), and only merge new branches back into the developer branches once the whole team agrees that it's working.

We will only merge the development branch into main whenever there are no unmerged branches of the development branch. Once all of the branches created from the dev branch are merged back into it, the dev branch is merged into main. When we begin work again, we make a new dev branch and go from there