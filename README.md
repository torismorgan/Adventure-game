# Template for CPSC2720 Major Project: Text Based Adventure Game
Last Updated: 2024-10-21 by Nicole Wilson &lt;n.wilson@uleth.ca&gt;

Notes:

* The Makefile and .gitlab-ci.yml files are set up to run on Ubuntu.
* The .gitlab-ci.yml file uses the targets in the Makefile.
* These are the tools/commands/apps used:
  * Compiler: g++
  * Style Check: cpplint
  * Static Check: cppcheck
  * Coverage Check: gcov/lcov
  * Memory Check: valgrind
  * Unit Test: gtest 
  * Documentation: doxygen
* See the version report on the pipeline.

Certain assumptions have been made:
* One repo contains the files for one project.
* All unit testing files are found in <code>test/</code> including <code>main.cpp</code>.
* All header files for the project are found in <code>include/</code> and named <code>*.hpp</code>, every class must have a header file.
* All project source files for the project are named <code>*.cpp</code>.
  * Any needed source files that correspond to header files are found in <code>src/</code>.
  * There is a <code>main.cpp</code> found in <code>src/project/</code>.

# Project Name
Manor of Mysteries
 

## Design Phase


### Team Member Contributions 

#### Ayo Olasupo

- Set up the `Room` and `Item` classes with basic properties and functions.

- Organized how `Room` classes relate to each other, following good design rules.

- Made the first version of the UML diagram to show class connections.

 

#### Chidera Okeke

- Created the `Player` and `Game` classes, detailing what they do.

- Built the inventory system for `Player`, including ways to pick up and use items.

- Worked on how `Player` interacts with `Room` objects.

 

#### Chidalu Okeke

- Designed the `NPC` and `Puzzle` classes, adding key properties and functions.

- Set up how `NPCs` interact with `Player`, including special behaviors for `Ghost` and `WhisperingVoice`.

- Added puzzle features and linked them to specific rooms.

 

#### Orisakite Morgan-Owiriwa

- Reviewed and improved the UML diagram with team feedback.

- Checked for repeated functions in similar classes to keep the design simple.

- Helped organize the README file and project layout.

 