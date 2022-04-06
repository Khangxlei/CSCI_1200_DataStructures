HOMEWORK 7: HALLOWEEN COSTUME MAPS


NAME:  Khang Le


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

It was mostly Lab 8 materials, the one on maps.

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  10



ORDER NOTATION ANALYSIS (ORIGINAL VERSION W/MAPS):
of each of the costume shop operations (please be concise!)

add: O(log n) - since the order complexity for a STL map is stored in a red black tree,
the notation for lookup is equal to log of n.

rent: O(log n + m) - this operation finds the number of copies of a costume
and list of customers holding that costume. Lookup for those would be log n.
Since size of list of customers holding a specific costume would be m, it would
also be + O(m). 

lookup: O(log n + m) - the operation locates the given costume inside rent notebook and inventory maps, 
both being size of n. It then prints out all the customers holding the costume, where worst case 
would be O(m), maximum number of people holding the costume.

print: O(c) - operation goes through the entire map of customers, printing their costumes. 
Doesn't go through any other containers. 

EXTRA CREDIT (W/O MAPS)
What alternate data structures did you use?  What is the order
notation of each operation without maps?  What is the expected
performance difference?  Summarize the results of your testing.

I used STL lists containers for the extra credit assignment. 

add: O(n) - goes through entire list of costumes 

rent: O(n + c) - Operation has to find the costume that is renting (which is O(n)),
it also has to find the given customer, which is O(c)

lookup: O(n+m) - goes through a list of costumes, when found it goes through a vector
of customers holding that costumes, where worst case would be the maximum copies of a costume m. 

print: O(c) - goes through list of customers and print them out 

In the map version implementation, all of our order complexity is sub-linear, making them process a lot faster
when it comes to size. As for the non-map version, almost all of them are linear to n (number of costumes),
making a list implementation a lot less effective than maps. 


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)






