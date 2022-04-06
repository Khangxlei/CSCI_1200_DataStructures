HOMEWORK 5: UNROLLED LINKED LISTS


NAME:  Khang Le


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

The dslist file that was given to use during Lab 5, it helped me out a lot.

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  16-18



TESTING & DEBUGGING STRATEGY:
I heavily relied on gdb. Every time I ran the program, I would generally receive segmentation
fault, as well as assertion errors. To debug, I would look at where the error occured, and create
a breakpoint at that line, (or before it) and would go step by step, while printing every values
I know to see if they are behaving as I intend to. 

For example, I would get assertion core dumped because my list does not have the correct
value it's supposed to. So I would look at the line of assertion on main.cpp, open gdb, create
a break at that line, and would go step by step in my function. Whilst doing so, I would realize 
my pop_back() or pop_front() function didn't have a special case for when there is
only one node, and the head and tail weren't correctly placed. Knowing the source of the issue,
I would go and fix it. 

As for the drmemory errors, since there weren't any extremely difficult arrays we have to create
in this assignment, most of them was that I didn't destroy the allocated memory properly, in which
a destructor class erased all of those errors. Running drmemory showed me which places caused
those memory leaks.



ORDER NOTATION & EVALUATION:
What is the order notation of each of the member functions in your
class? Discuss any differences between the UnrolledLL, dslist, and STL
list classes. Evaluate the memory usage of your initial implementation
in the worst case. Give a specific example sequence of operations
where the data structure is inefficient. What is the average number of
elements per node in this case? 

destroy_list() - O(n): This function uses a for loop that goes through every single node
in the list and destroys it. This is also the same for the dslist and STL list.

push_front() - O(n): Since for my UnrolledLL, I made that the function would shift every elements
to the right, and this would be the average case. This might not be efficient since the dslist
and STL lists versions are always constant, being O(1). 

pop_front() - O(n): For my pop_front(), I also made it that it would have to shift values to the left
most of the time, making it a lot less efficient compared to the STL and dslist, being O(1).

push_back() - O(1)- There are no loops in this function, all I do is access the tail node
and add an element to it. This is the same for dslist and the STL version.

pop_back() - O(1)- Again, there are no loops for this function, the same as push_back() where
I access the tail node and make the last element NULL. This is also the same for the other versions,
being O(1) as well.

print() - O(n): Print function requires a loop in order to print every single element in the list.
This is the same for STL and dslist. 

erase() - O(n): Average case is when iterator is in the middle, and the functions requires to shift
every elements in the node to the left. Runtime will depend on the size of elements in a node.
DSlist and STL versions are O(1), which is a lot more efficient than mine.

insert() - O(n): The same as erase() function, function is required to shift all elements
in the node, making the runtime dependent on the size of the elements array. The other versions
are a lot more efficient than mine, since their's are constant.

copy_list - O(n): copy_list needs to transfer all elements in the list to another one, which makes
it a for loop looping around the list. Runtime will depends on the size of the actual list. This
also applies for the other versions as well.

operators ++ and -- : O(1) The increment/decrement operators are simple, all they do is set 
the current node to the next/previous one, so it is always constant. The STL and dslist version 
is also the same.


In my initial implementation, my insert and erase function had the program looping through every
single elements for every nodes in the list, shifting all of them. This heavily slowed the 
program down, while having to allocate a new memory array every time it goes to a new node. 
The worst case would be when the main program calls:

UnrolledLL<int>::iterator itr = a.begin();
itr = a.insert(itr);

while the average number of elements per node would be 6,considering all nodes are full and I 
would have to shift all of them to the right. 



EXTRA CREDIT:
Improved memory usage implementation.  Discussion as outlined in .pdf.
My initial implementation was really inefficient in terms of memory usage. I heavily improved it 
by changing the algorithm of the functions that were expensive in memory usages. 



MISC. COMMENTS TO GRADER:  
Optional, please be concise!


