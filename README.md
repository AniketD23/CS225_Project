# CS225_Project

## Github Organization
You should describe the physical location of all major files and deliverables (code, tests, data, the written report, the presentation video, etc…)

Our main code for the project is in the code folder. The algorithms are all in separate files, and data_processing contains the methods we used for data parsing.

All of our tests are in the tests folder, with a sanity check for our data parsing in test 1.cpp and tests for the algorithms in their own files.

The dataset we used is in the data folder. The files that we use to load in the adjacency list are in the lists folder. 


## Running Instructions
You should provide full instructions on how to build and run your executable, including how to define the input data and output location for each method. You should also have instructions on how to build and run your test suite, including a general description on what tests you have created. It is in your best interest to make the instructions (and the running of your executables and tests) as simple and straightforward as possible.

Type make to compile all of the code.

Type the following commands depending on the algorithm that is desired. Proper capitalization and punctuation is required. The output will be printed to the terminal.

**A\***: ./main "A_star" {starting film} {destination film}

**Breadth-First Search**: ./main "BFS" {starting film} {destination film}

**Prim**: ./main "Prim" {starting film}

Type ./test to run the tests


**A\* testing:**

**BFS testing:**

I ran tests of a breadth-first search from various starting nodes. Due to our use of an unordered map, my require statements checked against the distance that each node was from the starting node instead of a hard-coded path. The tests include both full traversals and BFS between two nodes that do not traverse the entire graph.

**Prim testing:**
