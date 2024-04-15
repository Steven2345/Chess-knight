# Chess-knight

**Statement:** A chess knight needs to traverse a chess board, passing through each square exactly once. Find such a traversal.\
The solution provided exhaustively searches for all possible solutions, starting from every square of the board and employing hardware multithreading to parallelize the task of backtracking over the entire board. Despite not being the 'best' solution to the problem, it is interesting from the point of view of utilizing the resources of the system as much as possible. Due to starting from everywhere all at once, the algorithm actually finds the first solution pretty quick, since there are squares that have more possible solutions than others and the user is not required to guess which would be such a square to begin the search from in the case of an unparallelized search.\
The so called 'best' solution has linear complexity and is actually a heuristic Greedy algorithm, which works with even large boards (10x10). However, the goal of this project was to be a bit more technical and to push the limits of hardware.

Lessons learnt:
- how the operating system schedules concurrent threads in a preemptive manner; this is visible with large boards (greater than 7x7) when the thread that is printing gets 'hiccups' due to constantly losing and gaining back procesor time
- how to use multiple threads of execution in C++ and how to manage resources, which can be specific to each thread (its board) or shared by all threads (solution counter and the writing permission)

Note: Because of the lines 105 and 106, it is best to compile the source with GCC or MinGW; Visual C++ does not accept that syntax.