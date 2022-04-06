HOMEWORK 8: B+ TREES


NAME:  Khang Le


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

https://stackoverflow.com/questions/49582390/binary-search-tree-copy-constructor-in-c
can't remember but it was a cplusplus website that shows how to create a destructor on a 
binary search tree

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  15


TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your implementation?

Each time I would get an assertion error, I would open up gdb and set a break on that line.
I would step into the function, and before going through the program, I would print
all the values I could possibly get from my tree such as my keys in the root, its childrens 
and their keys as well. This would help me visualize the current state of my tree and know what went
wrong in my insert function. 

For corner cases, I made test cases that would add values from different sides of the trees,
some that are insanely large, some that are a lot smaller and some in the middle. When inserting
a lot of values into a node, I checked if my program correctly splitted the node by using print in gdb. 


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

