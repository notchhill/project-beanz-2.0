# Team design document
Before work starts on the implementation (coding), we want to ensure a clean design has been agreed upon by all team members, and that we have documented our design in a single shared resource (the Design.md file).

This will be the largest and most fundamental document for this phase of the project, and involves documenting in detail both the logical and physical design of the product.

This is to be provided in a Design.md file in the master branch of your team repo, along with any necessary images or other resources linked from the document.

The document is the one your team (and the instructor and other teams) will be using as a reference point when they need to decide how/what the final product code elements are supposed to be doing/implementing, so needs to be well organized, consistent, and as complete, up to date, and error free as possible. (Your team will be responsible for keeping the document up to date as the project progresses and you refine your ideas on the product design.)

The actual format of the document is left largely to the team's discretion, but discussion of the expected content is provided below, and the lab3 page provides links to the course notes and examples relevant to design modeling.

However the document is actually structured/ordered, the following information (at a minimum) needs to be present:
- team and project name, contact info (the contact info is just a single point of contact in case a reader has questions or feedback)
- table of contents (optional but nice to have)
- design overview
    This provides an intuitive overview of the high level logical design, preferably with a context diagram (the top level DFD), and also of the key transformations/decisions going from the logical to the physical design.
- logical design
    In the logical design we need to specify the decomposition of our system into smaller components from a logical (code-independent) perspective. The logical design should reflect a layered/top-down approach, first clearly describing the division of the overall system into smaller elements, then clearly describing the decompositions of those, etc. A medium-sized project might involve dividing the overall system into several interacting subsystems, dividing each subsystem into several interacting modules, dividing each module into a number of interacting components, etc.

    Since different subsystems/modules/components will likely be developed by different people, it is important that as a team we clearly establish the responsibilities of each element and how they will interact with others. Thus for each level of decomposition I strongly recommend the inclusion of a data flow diagram (DFD), with clear supporting explanation.

    Each element of the system (i.e. each subsystem, module, component, etc) should contain clear, easily referenced descriptions of:
        - its overall purpose
        - each of the services it provides for other elements of the same DFD level (what will it implement that is used by other portions of the system?) 
            - this should show the information exchanged during that process
        - the interactions between it and the user(s) and any other external systems
        - any persistent data it will need to store, giving each data component a name and identifying the type and restrictions on the data (e.g. "vehicle weight will be stored as a non-negative real number of kilos, rounded to the nearest kilo)
        
As discussed in lectures, we are seeking a division into elements that are cohesive yet loosely coupled, and we want to ensure that all aspects of the overall product functionality are captured somewhere within our design.

- physical design
    In the physical design we want to map the elements of our logical design to actual codable entities, in a way that will subsequently allow our team to begin implementation.

    Key elements to capture in the physical design include:
        - identifying the programming language(s) and any supporting tools to be used
        - identifying the directory and file naming structure to be used within the code repository: identifying the files/directories/subdirectories we use to store the different actual code elements
        - identifying the implementation method for each shared data store (database, file, etc), including format, fields, layout
        - identifying the interface for all public services provided by the element:
            - publicly accessible data types and constants
            - publicly callable function names, return types, parameter lists
            - class names, public field names/types, public method names, parameters, return types
        This gets very close to the level of code skeletons, but does not yet need to be expressed as actual code in the target language.

- glossary: if a term is specific to the product or is unlikely to be known by the average reader (e.g. a random second year CS student) then include an entry for it.

- appendices (if/as needed)

Note that all elements of all figures/diagrams should be accompanied by associated text descriptions.