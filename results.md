# The output and correctness of each algorithm 
You should summarize, visualize, or highlight some part of the full-scale run of each algorithm. Additionally, the report should briefly describe what tests you performed to confirm that each algorithm was working as intended.

**A\*:**

**BFS**: The full-scale run of BFS writes to a file all of the films traversed from a breadth-first search from the starting movie to the destination movie. This gives the "neighborhood" around the two input movies. A relatively small BFS is one from "The Avengers" to "The Lion King" consisting of 198 films. Here we can see a lot of superhero movies, as one might expect, such as "Thor: The Dark World" right next to it and "Batman and Harley Quinn" closer to Lion King. The movies differ more along the BFS as is expected given that the traversal is spreading out further, with action film "Angel Has Fallen", drama "The Silent Child", and children's movie "Smallfoot" all next to each other near the end of the search.

The tests used the same small example graph to perform a BFS on from different starting locations. I counted the distance of each node from the starting node of each test case and checked that each element was the correct distance from the starting node. 

**Prim:**


# The answer to your leading question
You should direct address your proposed leading question. How did you answer this question? What did you discover? If your project was ultimately unsuccessful, give a brief reflection about what worked and what you would do differently as a team.

