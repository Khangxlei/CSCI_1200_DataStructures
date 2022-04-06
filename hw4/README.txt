HOMEWORK 4: DVD LISTS


NAME:  Khang Le


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

cplusplus

Remember: Your implementation for this assignment must be done on your
Maown, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  10-15 


ORDER NOTATION:
For each function, using the variables:
  d = number of different movie DVD titles
  k = average or maximum copies of each DVD
  c = number of customers
  p = average or maximum movies ranked on each customer’s preference list
Include a short description of your order notation analysis.

dvd: O(d)
For loop goes through the inventory list, i.e. the number of different movie DVD titles

customer: O(p*d)
For loop inserts the customer's movie preferences onto a list, while having
another for loop that checks if that given movie is in the inventory.

add_preference: O(c*p)
The for loop in this function that has the most runtime is the one that loops over
the list of customers, while having 2 different for loops inside it. One for loop loops
through a list of the customer's movie possessions and the other is their preferences. There are
no variable for the customer's number of possessed movies, but in worst case would be O(cp+3) .

ship: O(c*p*d)
This is the function being given to me, so I can't reduce the order notation on this. It 
loops through list of customers, inside that is a for loop going through the customer's
list of preferences, and inside that is another for loop that iterates over the inventory list.

return_oldest: O(c*d)
This is the average case, function loops over list of customers. When it finds the given
customer, it will loop over the inventory to return the movie to the list. Best case would
just be O(c) but that would give a warning message.

return_newest: O(c*d)
Exactly the same as return_oldest function. Loops over list of customers, then
loops over the inventory case. Best case (with a warning) would be O(c).

print_customer: O(c+d+3)
Again, there is no variable for movie possessions. Function loops over list of customers first,
then loops of the customer's list of movies they're holding (worst case is 3), and lastly,
it loops over their preference list. I gave the worst case.

print_dvd: O(d)
Function simply loops through the list of inventory, when it finds the DVD it then prints
out the information related to it.



EXTRA CREDIT:
Describe the analysis you performed on customer satisfaction.  Paste
in a small amount of sample analysis output and/or specify a sample
output file.  Describe your improved algorithm and compare the
analysis results of your new algorithm.  Please be concise!



MISC. COMMENTS TO GRADER:  
Optional, please be concise!






