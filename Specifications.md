
### Info from Dave
Links to examples at bottom of http://csci.viu.ca/~wesselsd/courses/csci265/labs/lab2.html


### Info from Dave
However the document is actually structured/ordered, the following information (at a minimum) needs to be present:

- team and project name, contact info (the contact info is just a single point of contact in case a reader has questions or feedback)
- table of contents (optional but nice to have)
- product overview
    This is essentially a revised version of the phase 1 product proposal, detailing the overall purpose of the product, its target audience and reason for being, the scope of the product, its key features, the planned operating environment(s)/platform(s).
- product behaviour/features
    This section needs to provide a complete description of all the product features and behaviour: what services it provides and how.
    The description here needs to be in sufficient detail to allow independent readers to all come to the same conclusions as to what the program does when using each feature: how the user invokes the feature, what kinds of information the user provides, what the program does in response, any limitations on the data that can be accepted/processed, how any errors are handled, etc.
    This portion of the document may be integrated with the user interfaces section listed below, or may be separate but with cross-references to the relvant screens/images/sketches in the user interfaces section.
    This portion of the document is likely to be fairly lengthy, and will require good organization (e.g. intuitive use of sections, subsections, subsubsections etc) to allow the reader both to read the document as a whole and to jump quickly to sections of interest if there is something particular they're looking for.
- user interfaces/product visualizations
    Here the goal is to provide sketches of every screen/popup/menu the user might have to interact with while using the product, with all the key elements on the screen, and how those elements and actions relate to the product features and behaviour detailed in the previous section. (Note that markdown allows you to link/include images from within the document, so you can drop the relevant images in your team repo along with the Specifications.md.)
- key use cases/scenarios
    The use cases walk the reader through the different possible ways someone might actually use the product and its features, while scenarios provide examples using fictional users and data. For example, the use cases might detail a suite of cases like "sign in, make a deposit, make a withdrawal, check account balance, etc", whereas a scenario might look like "Dave wants to check his balance then withdraw all but $100 then sign out, so the exact sequence of steps he goes through are as follows..." and then walks through every step, every user input, and every system output along the way.
- any non-functional requirements
    This details any requirements beyond the actual feature set, e.g. performance requirements (response times, throughput, memory/disk footprints), software quality requirements, safety/security requirements, etc.
- glossary: if a term is specific to the product or is unlikely to be known by the average reader (e.g. a random second year CS student) then include an entry for it.
- appendices (if/as needed)


### Info from Dave - A note on specifications for game projects
Specs for game projects are a bit of a special beast, and might be structured in a different format. The goal is still to describe exactly what is going to be built before we begin trying to design how to build it, but the components might be organized differently.

Key things that need to appear in game specifications typically include:
- the team/game name, contact info, table of contents (as with other software products),
- an overall description of the game purpose, theme, goals, and target audience (like the product overview for other software products),
- description of the overall flow/sequence of events for the game, conditions for winning/losing, player goals and scoring systems
- detailed descriptions and sketches of each of the control systems, menus, screens, and interfaces the player will interact with,
- detailed descriptions and sketches of each of the game levels (if any), what is in each level, the layout, key features, characters, and sequence of actions/puzzles/steps associated with the level,
- detailed descriptions of the key characters, attributes, and items present within the game (if any), and the interactions between them,
- priority tiers for the levels, features, characters, etc (which ones are core, which ones are secondary, which ones are just nice-to-have extras if time permits)
- non-functional requirements, glossary, and appendices (as with the other software products).