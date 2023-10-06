# Team design document


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


Note that all elements of all figures/diagrams should be accompanied by associated text descriptions.


### DESIGN

Team name: Team Beanz 2.0
Game name: Project Beanz 2.0
Contact info: Dustin, dustin.gabriel777@gmail.com

# TABLE OF CONTENTS

1.0 Design Overview.

2.0 Logical Design.

3.0 Physical Design.

    3.1 Programming language(s) and supporting tools.
        C++, GCC, Make(?).

    3.2 Directory and file naming structure.
        >bin
            Holds the executables
        >build
            Holds the object(*.o) files
        >include
            Holds the header(*.h) files
        >resource
            Holds the input files
        >src
            Holds the source(*.cpp) files

    3.3 Implementation method for each shared data store.
    3.4 Interface for all public services provided by the element:
            - publicly accessible data types and constants
            - publicly callable function names, return types, parameter lists
            - class names, public field names/types, public method names, parameters, return types

# DESIGN
