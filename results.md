# The output and correctness of each algorithm 
You should summarize, visualize, or highlight some part of the full-scale run of each algorithm. Additionally, the report should briefly describe what tests you performed to confirm that each algorithm was working as intended.

**A\*:** A* finds some reasonably short path between two movies, though as a result of our flawed heuristic (which is not admissible or consistent), this is often not the shortest path. However, using the heuristic tends to be significantly faster than if the heuristic was simply returned a constant, which is as expected. With regards to testing, we tested both small scale, hand designed datasets made to specifically test certain aspects, such as the effectiveness of the heuristic or its handling of not finding any path between two vertices, and tests using the whole dataset, which ensures a certain level of speed. The full scale run of A* prints to the console and saves the path from a given starting movie to the end movie, as well as the cumulative "distance" along this path.

**BFS**: The full-scale run of BFS writes to a file all of the films traversed from a breadth-first search from the starting movie to the destination movie. This gives the "neighborhood" around the two input movies. A relatively small BFS is one from "The Avengers" to "The Lion King" consisting of 198 films. Here we can see a lot of superhero movies, as one might expect, such as "Thor: The Dark World" right next to it and "Batman and Harley Quinn" closer to Lion King. The movies differ more along the BFS as is expected given that the traversal is spreading out further, with action film "Angel Has Fallen", drama "The Silent Child", and children's movie "Smallfoot" all next to each other near the end of the search.

The tests used the same small example graph to perform a BFS on from different starting locations. I counted the distance of each node from the starting node of each test case and checked that each element was the correct distance from the starting node. 

**Prim:**


# The answer to your leading question
You should direct address your proposed leading question. How did you answer this question? What did you discover? If your project was ultimately unsuccessful, give a brief reflection about what worked and what you would do differently as a team.

Our leading question was to create a graph that will aim to determine the similarity of different movies by connecting movies that have been reviewed similarly by different users. We answered this question by taking the average difference in rating by the same user between each movie in our graph. This allowed us to see how movies were rated differently by people with similar tastes. We saw that the output of our algorithms did not really follow along strict genre lines, which could be useful for providing recommendations that people may be originally unaware of. However, we suspect that our data set was too small, with too few reviews across too many movies to give a reliable measure of similarity.

BFS answers the leading question by providing a variety of movies that were given ratings by the same people, with the ability to restrict how many movies you want to see by choosing movies that are closer or further away to the beginning to increase the spread of the traversal. This allows users to see a lot of movies and also could be helpful in challenging their ideas about what movies are grouped together.
