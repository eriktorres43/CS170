# CS170

This is the first project in Introduction to Artifical Intellegence by Dr. Eammon Keogh where we have implemented 3 algorithms: Uniform Cost Search, A* Misplaced Tiles and A* Manhattan Distace in solving an 8 puzzle.

Full Report Below: 

Erik Torres
SID: 862462457
Email: etorr153@ucr.edu
Date: Feb-13-2026

# **In this assignment, I used:

* The Blind and Heuristic Search Slides from lecture for Misplaced Tiles, Manhattan Distance heuristics, and General Search Algorithm
* The sample report for format/structure, examples, and outputs
* Used Google sheets to make graphs shown in this report (with respective data), found here: https://docs.google.com/spreadsheets/d/1aQwhdXz5Vfp8FELFRZrcspTuOqoRksQJTPJAODlMnOY/edit?usp=sharing

# **Parts of the code that are unoriginal/used for help are:

* CPlusPlus website for libraries and functions, in particular, time/clock and priority queue’s: https://cplusplus.com/reference/ctime/ https://cplusplus.com/reference/queue/priority_queue/priority_queue/

*Compiler help by providing a fix/format to the priority queue (compare property) when doing it incorrectly the first time (seen below):

<img width="992" height="175" alt="Screenshot 2026-02-13 at 5 04 00 PM" src="https://github.com/user-attachments/assets/dd288fd9-1c07-4137-849e-a8a443a68107" />

# **Outline of this Report:**

Cover Page: Page 1
Report: Pages 2 - 6
Easy Problem Example: Page 7
Hard Problem Example: Page 8
Code: Pages 10 - 12, code can also be found on github (for convenience and compiling): 

# **Introduction:**
  
  The Eight puzzle is a 3x3 square puzzle where we are given numbered tiles 1-8 and an empty square. This puzzle is then randomly arranged, and it’s our job to solve the puzzle by moving the given tiles through the empty square until we reach the solution. Typically, the solution is the puzzle ordered from 1-8 with the empty tile on the bottom furthest right, and in this case, it is. Rather than solving this problem physically, we have instead chosen to solve this problem using search algorithms learned throughout the course, which I have done in the language, C++.

  This project utilizes and implements 3 algorithms: Uniform Cost Search, A* Misplaced Tiles Heuristic and A* Manhattan Distance Heuristic, all using A*. The A* Algorithm, as stated in the slides, “Enqueue nodes in order of estimate[d] cost to goal, f(n), [where] f(n) = g(n) + h(n), g(n) is the cost to get to a node [and] h(n) is the estimated distance to the goal.” [1]

# **Uniform Cost Search:** 
  
  For Uniform Cost Search, the intuition of the algorithm is to “Expand the cheapest node. Where the cost is the cost path g(n)” [2]. We are still using the A* algorithm, but “Uniform Cost Search is just A* with h(n) hardcoded to equal zero” [3]. So, f(n) = g(n) + h(n) = g(n). Here, we assume the path to each node costs 1 unit, so the order the nodes are queued is the order they are expanded, also called Breadth-First Search. 

[1]  3__Heuristic Search (Eammon Keogh, 2026, UCR, Slides/Dropbox)
[2]  2__Blind Search_part2 (Eammon Keogh, 2026, UCR, Slides/Dropbox)
[3]  Project_1_The_Eight_Puzzle_CS_170_2026 (Eammon Keogh, 2026, UCR, Slides/Dropbox)


# **A* Misplaced Tiles Heuristic:** 
  
  A* Misplaced Tiles Heuristic is similar to Uniform Cost Search, but instead of the heuristic being 0, we now find the heuristic by counting how many tiles in the current state are in the wrong position, relative to the goal state (excluding 0). Hence, f(n) = g(n) + h(n), where h(n) ≥ 0, only expands the cheapest node. In a visual sense, we take two 8 puzzles, the current state and the goal state, and compare the values in each position. For instance:
 
   Current State                   Goal State
      1 5 4                          1 2 3  
      8 0 3                          4 5 6
      2 6 7                          7 8 0

  All but position 1 are incorrect, so our heuristic/h(n) would be 7 (excluding 0). We know that “... heuristic tells us approximately how far the state is from the goal state” [4], so the smaller the number, the better. Since we’re not at the goal state, we expand. The queueing function will have: up (f(n) = 1 + 6), left, right and down (all 3 with f(n) = 1 + 7), popping the top with each expansion and smallest f(n) on top. We repeat until we reach the goal state (not expanding repeat puzzles).

# **A* Manhattan Distance Heuristic:**

  For A* Manhattan Distance Heuristic, similarly to A* Misplaced Tiles Heuristic, determines the incorrectly placed tiles, relative to the goal state (excluding 0), but now calculates how many valid moves it takes to get to the correct position. In a visual sense, we take two 8 puzzles, the current state and the goal state, and compare the values in each position, where we move the incorrect values to the correct position, with valid moves only.  For instance:
 
<img width="1133" height="491" alt="Screenshot 2026-02-13 at 6 37 58 PM" src="https://github.com/user-attachments/assets/9fc447ff-4dd0-4043-9d3e-3f3e0830bd4f" />

  All are correct, but positions 3 and 8. It takes both states 3 and 8 three moves to get into the correct position. So our heuristic/h(n) would be 3+3 = 6. Since we’re not at the goal state, we expand. The queueing function will have: left (f(n) = 1 + 5), up (f(n) = 1 + 7), and popping the top with each expansion, with the smallest f(n) on top. We repeat until we reach the goal state (not expanding repeat puzzles).

# **Comparing the Algorithms:** 
	
  The algorithms information above can help create a hypothesis that A* Manhattan Distance heuristic will generally perform the best, followed by A* Misplaced Tiles heuristic, since A*’s runtime “... [d]epends on the quality of the heuristic” [5]. To test this hypothesis, we’ll compare the algorithms in 3 areas: nodes expanded, max queue size, and runtime to see how efficient the algorithms were for this project, through graphs (made from the test cases in the project PDF). 


# **First, let’s look at Nodes Expanded:**

<img width="742" height="464" alt="Screenshot 2026-02-13 at 1 28 04 PM" src="https://github.com/user-attachments/assets/b25d3573-3d68-4d70-aa92-76dbcd149af8" />

  What we can interpret from the graph is, the smaller the solution depth is, the more the algorithms/nodes expanded will behave similarly; however, as depth increases, the differences are apparent. Uniform Cost Search quickly expands nodes past depth 8, whereas A* Misplaced Tiles heuristic and A* Manhattan Distance heuristic begins past depth 12 and 20, respectively. For example, past depth 12, A* Manhattan Distance heuristic is 267% and 5288% (or more, depending on depth) effective against both algorithms, and A* Misplaced Tiles heuristic is 1978% (or more, depending on depth) effective against Uniform Cost Search, leaving Uniform Cost Search with the worst result (overall, seen in graph).

# **Next, let’s look at the Max Queue Size**:

<img width="811" height="500" alt="Screenshot 2026-02-13 at 1 28 23 PM" src="https://github.com/user-attachments/assets/b164aa18-6a56-4d99-8d31-8a7b49433afd" />

  What we can interpret from this graph is, the algorithms behave similarly in lower solutions depths (with max queue size); but, the deeper the solution, the max queue size will increase and differences happen. Our findings are similar to those in Expanded Nodes, where quickly growing max queue size happen past depth 8 for Uniform Cost Search, whereas A* Misplaced Tiles heuristic and A* Manhattan Distance heuristic are past 12 and 20, respectively. For example, past depth 12, A* Manhattan Distance heuristic is 226% and 4030% (or more, depending on depth) smaller than the other two algorithms, A* Misplaced Tiles heuristic is 1785% (or more, depending on depth) smaller than Uniform Cost Search, leaving Uniform Cost Search with the worst result (overall, seen in graph).

# **Finally, let’s look at the Runtime**:

<img width="599" height="371" alt="Screenshot 2026-02-13 at 1 28 49 PM" src="https://github.com/user-attachments/assets/78d04fe0-b438-4d66-be1d-13a4ab9986db" />

  What we can interpret from the graph, similar to Expanded Nodes and Max Queue Size, is that at lower solution depths, the algorithms behave similarly (in terms of runtime) and at higher solution depths is where differences become glaring. In this case, Uniform Cost Search majorly differs first at depth 12 compared to A* Misplaced Tiles heuristic and A* Manhattan Distance heuristic, which don’t until depth 16 and 24, respectively. For example, past depth 12, A* Manhattan Distance heuristic is 150% and 10000% (or more, depending on depth) faster than the other two algorithms, A* Misplaced Tiles heuristic is 6667% (or more, depending on depth) faster than Uniform Cost Search, leaving Uniform Cost Search as the worst result (overall, seen in graph).

# **Conclusion**: 
	
  Now that we have looked at the 3 given categories for all three algorithms, one conclusion we can make is that Uniform Cost Search generally performs the worst for all 3 categories past depth 2 compared to A* Misplaced Tiles heuristic and A* Manhattan Distance. When comparing the two A* algorithms, A* Misplaced Tiles heuristic and A* Manhattan Distance heuristic, it is a bit harder to compare them compared to Uniform Cost Search. When looking at the 3 categories, we can see that they have many similarities in lower depths (i.e., below depth 12), which are expanded nodes, max queue size, and runtime; but as we go deeper and deeper to find a solution, we can see that A* Manhattan Distance is the better/efficient algorithm. This is because, with fewer expanded nodes, we use less memory, hence a smaller queue size, leading to a faster algorithm compared to Uniform Cost Search and A* Misplaced Tiles heuristic. 
Therefore, if attempting to solve this problem again, or giving advice to others, I would recommend they use/solve this problem with the A* Manhattan Distance heuristic algorithm, as it performs the same (below depth 12) and better (at or past depth 12) compared to the other algorithms, while saving memory and time.

# **Examples**: 

  The next two pages contain examples of what menu and output it should present to the user. There’s are Easy and Hard puzzle examples below:

This is an example and output for an Easy Puzzle (Depth 4): 

<img width="445" height="537" alt="Screenshot 2026-02-13 at 3 02 25 PM" src="https://github.com/user-attachments/assets/f1cdb097-a20e-4345-a187-7e7bf2b2d4da" />

This is an example and output for an Hard Puzzle (Depth 24):

<img width="622" height="741" alt="Screenshot 2026-02-13 at 6 40 58 PM" src="https://github.com/user-attachments/assets/64cf8441-8759-47cf-aaf2-a450422343d2" />
