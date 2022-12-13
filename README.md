# CS225_Project

## Github Organization

You should describe the physical location of all major files and deliverables (code, tests, data, the written report, the presentation video, etc…)

Our main code for the project is in the code folder. The algorithms are all in separate files, and data_processing contains the methods we used for data parsing.

All of our tests are in the tests folder, with a sanity check for our data parsing in test 1.cpp and tests for the algorithms in their own files.

The dataset we used is in the data folder. The files that we use to load in the adjacency list are in the lists folder.

There is also an out folder for the output of out algorithms. The program has default files it will write to, but the user can also specify a file name of their choice.

results.md is in the main directory.

## Running Instructions

You should provide full instructions on how to build and run your executable, including how to define the input data and output location for each method. You should also have instructions on how to build and run your test suite, including a general description on what tests you have created. It is in your best interest to make the instructions (and the running of your executables and tests) as simple and straightforward as possible.

First, download the [avg_adj_list](https://drive.google.com/file/d/1q4-KmztM7peZLp7ArUfci3OI1mSA5wcE/view?usp=share_link), and place it in the lists directory. Enter  the terminal and run "mkdir build", "cd build", then "cmake .." to create the build folder.
Then, type make to compile all of the code.

Type the following commands from inside the build directory depending on the algorithm that is desired. Exact capitalization and punctuation is required. The output will be printed to the terminal or written to a file in the out folder, with a default file if the user does not provide a file name. Running each algorithm can produce different results even when providing the same movie titles as arguments.

**A\***: `./main "A_star" {starting film} {destination film} {optional file name for output}`

**Breadth-First Search**:` ./main "BFS" {starting film} {destination film} {optional file name for output}`

**Prim**: `./main "Prim" {starting film} {optional file name for output}`

Type `./test ` to run the tests. To run a specific test, run ./test with the tag for the specific test as an argument. Ex. `./test [prim4]`.

**A\* testing:**

I ran tests on manually constructed datasets, to check against manually calculated solutions. These datasets covered general, small scale cases. I also created datasets that verified whether my heuristic affected path selection. As our heuristic is not admissible, we will have non optimal paths under certain circumstances, and I tested to ensure we would be on those non optimal paths when we expect. Finally, one test case runs against the full dataset, which verifies a certain level of time complexity. I also checked edge cases like if the algorithm can't find any path.

**BFS testing:**

I ran tests of a breadth-first search from various starting nodes. Due to our use of an unordered map, my require statements checked against the distance that each node was from the starting node instead of a hard-coded path. The tests include both full traversals and BFS between two nodes that do not traverse the entire graph.

**Prim testing:**
Our Prim's Minimum Spanning Tree Algorithm was tested both by checking the output of the algorithm (A tree represented as an unordered map of the type std::unordered_map<int, std::unordered_map<int, bool>>, where the value is true if the two nodes entered have a parent/child relationship) against the minimum spanning tree of a small graph of integers. The minimum spanning tree was manually validated. The expected output was verified against the resultant output to ensure that each node appeared in the correct order. Several edge cases were tested in the same manner to ensure no unexpected behavior occured, including testing a graph consisting of a single node, a graph of two unconnected nodes, and a graph consisting of a linked chain of nodes connected by a single edge to the prior. The output of the algorithm was also tested by loading the dataset and producing a vector of movie titles representing a subsection of the minimum spanning tree resulting from a selected input to check for unexpected behavior. This was verified by checking that the vector was the correct size and consisted of only valid movie titles. To ensure that the outputs were unique, two vectors of the same were produced from two different movie titles and compared. Due to the size of the dataset, manually verifying an an MST from a single desired result was not a viable option.

**Final Presentation:**
https://drive.google.com/drive/folders/1QS6Dr5SNta4EMfvSP_wCzZVN1FMa9AV9?usp=sharing
