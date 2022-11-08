 
## Leading Question 
    Using a dataset that collects public tweets sharing IMDB movie reviews, as well as data about individual users and the genres and titles of the movies,  we will create a graph that will aim to determine the similarity of different movies by connecting movies that have been reviewed similarly by different users. We hope to see patterns emerge that will help create unique movie recommendations. For example, by inputting two different movies, we can find the shortest path between the two movies and use the movies in the middle as recommendations to the users. We will use the ratings of the movies as weights, by finding the absolute values of the differences between the ratings. The edges of the graph are users who have rated both movies. We can also use minimum spanning tree to create groups of movies that are similar, as starting at a different movie will create a different minimum spanning tree. Using BFS, if we restrict our search to only traverse down edges with a certain threshold of rating similarity, then we can find a path between two movies that will have the fewest number of movies between them, while maintaining a certain amount of similarity between movies in the path chain.
 
 
## Dataset Acquisition
We are using the MovieTweetings dataset from github (https://github.com/sidooms/MovieTweetings). There are currently 921,398 move ratings from 71,707 users about 38,018 unique items on IMDB. At this point in time, we are planning on using the entire dataset for our overall goal, but filtering it for testing and more targeted analysis. To filter our data, we would likely go by the number of ratings per movie or genre.
 
 
## Data Format
From dataset documentation:
"users.dat
Contains the mapping of the users ids on their true Twitter id in the following format: userid::twitter_id. For example:
 
1::177651718
 
We provide the Twitter id and not the Twitter @handle (username) because while the @handle can be changed, the id will always remain the same. Conversions from Twitter id to @handle can be done by means of an online tool like [Tweeterid] (http://tweeterid.com/) or simply through the Twitter API itself. The mapping provided here again facilitates additional metadata enrichment.
 
items.dat
Contains the items (i.e., movies) that were rated in the tweets, together with their genre metadata in the following format: movie_id::movie_title (movie_year)::genre|genre|genre. For example:
 
0110912::Pulp Fiction (1994)::Crime|Thriller
 
The file is UTF-8 encoded to deal with the many foreign movie titles contained in tweets.
 
ratings.dat
In this file the extracted ratings are stored in the following format: user_id::movie_id::rating::rating_timestamp. For example:
 
14927::0110912::9::1375657563
 
The ratings contained in the tweets are scaled from 0 to 10, as is the norm on the IMDb platform. To prevent information loss we have chosen to not down-scale this rating value, so all rating values of this dataset are contained in the interval [0,10]."
 
## Data Correction
Considering the fact that what we are interested in is how users have rated different movies, we will be removing all of the users from the dataset that have only reviewed one movie. Similarly, we will also remove any movies from the set that have only been reviewed by one user. To make sure all of the data is correct, we will check it against the format given by the documentation. We can also check all of the individual movies given by the dataset against IMDB to make sure that the movie in question exists.
  
 
## Data Storage
  We are storing the data as struct containing pointers to neighboring nodes, along with the corresponding weight of that edge. We will also need to store pointers to each node in an array. If the graph is dense, which is likely, as most two movies will likely have been reviewed by a single user at least once, then we will have O(V^2) storage used, where V is the number of nodes. This is most like an adjacency list in terms of algorithm implementation. Additionally, as we plan for edges to be an average of any two reviews by a given user, we plan to preprocess the list of reviews, by sorting by user (to group reviews by the same user together).
 
## Algorithm 
We are implementing a breadth-first traversal, shortest path algorithm (A* Search), and a minimum spanning tree algorithm (Prim's Algorithm).
The inputs are the movies being compared.
To convert the dataset we would have to parse the fields according to the specifications given in the github readme.
Our outputs will be, for both BFS and shortest path, be a list of movie names. We can store these movie names into a file, or print directly to the console. With the minimum spanning tree, we will print out the top 20 or so movies in the tree closest to the root using a preorder traversal, and potentially saving a larger number of movies to a file, formatted as a tree.
 
Our A* heuristic will be the weight of the direct edge between any given node, and the target, with the weight being assigned as max if there is no connection. In order for this heuristic to work at all, we assume that the graph is reasonably dense, that most movies will have at least one reviewer that has reviewed almost any other movie. Additionally, the heuristic penalizes less popular movies with fewer direct connections, which may be somewhat desirable. 
 
Assuming the graph ends up being relatively dense, we have the following complexities, where E and V are the number of edges and nodes, respectively.
BFS is O(E+V) in time, and O(V) in space.
A* Search is O(E+Vlog(V)) in time, and O(V+E) in space.
Prim’s algorithm is O(Elog(V)) in time and O(V+E) in space.
 
 
 
 
## Timeline
Check/clean data
 
Create graph structure(class/struct)
 
Parse data into graph structure		(done November 10)
 
BFS						(done November 14)
 
Shortest Path
 
Minimum spanning tree			(done November 21)
 
Create user interaction element (using command line)
 
Written report and presentation 		(done December 8)
 

