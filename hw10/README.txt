HOMEWORK 10:  PERFORMANCE & BIG O NOTATION


NAME:  Khang Le


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

http://www.cplusplus.com/reference/queue/priority_queue/


Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  10



COMPLEXITY ANALYSIS
n = number of elements in the input
f = requested number of values in output (first sorted only)
l = maximum length of any string element

Neatly fill in the table below with the Big O Notation for running time.

First row is the running time and second row is memory usage.
--------------------------------------------------------------------------------------------
|          |          | remove   |          | closest  | first f       | longest           |
|          | sort     | dups     | mode     | pair     | sorted        | substr            | 
--------------------------------------------------------------------------------------------
|          |O(n log n)|O(n^2)    |  O(n)    |O(n log n)|O(f + n log n) |O(l^2*n^2)         |
| vector   | O(30n+8) | O(13+30n)| O(54+30n)|O(20+4n)  |O(8+30n)       |O(75+30n+(20+(2l)))|
--------------------------------------------------------------------------------------------
|          |O(n log n)|O(n^2)    |O(n log n)|O(n log n)|O(f + n log n) |O(l^2*n^2)         |
| list     | O(12+30n)|O(16+30n) | O(54+30n)|O(20+4n)  |O(12+30n)      |O(184+6l+30n)      |
--------------------------------------------------------------------------------------------
|          |O(n)      |O(n log n)|   O(n)   | O(n)     |    O(f)       |O(l^2*n^2)         |        
| bst      |O(47+30n) |O(30n+4)  | O(46+30n)|O(40+30n) |O(47+30n)      |O(150+10l+30n)     |
--------------------------------------------------------------------------------------------
|          |  O(n)    |     X    |   O(n)   |  O(n)    |    O(f)       |          X        |
| pq       | O(43+30n)|     X    |O(102+30n)| O(32+30n)| O(43+30n)     |          X        |
--------------------------------------------------------------------------------------------
|          |  O(n!)   |  O(n)    |   O(n)   |  O(n^2)  |   O(n! + f)   |O(l^2*n^2)         |
| hash     | O(59+30n)| O(20+30n)| O(50+30n)|O(48+30n) | O(59+30n)     |  O(176+12l)       |
--------------------------------------------------------------------------------------------

RESULTS
For each data type and each operation, run several sufficiently large
tests and collect the operation time output by the program. Organize
these timing measurements in your README.txt file and estimate the
coefficients for the dominant term of your Big ‘O’ Notation.

-----------------
sort operation  |
-----------------
vector: 0.59s, k =  1.38*10^-6
list: 0.672s, k = 1.49*10^-6
bst: 0.64s, k = 1.979*10^-5
pq: 0.64s, k = 2.16*10^-5
hash: 9.04, input size is too large we can't calculate the factorial of it


-------------------
remove_duplicates |
-------------------
vector: 5.984s, k = 9.57*10^-9
list: 8.703s, k = 1.392*10^-9
bst: 0.609s, k = 1.67*10^-6
pq: infeasible
hash: 0.68s, k = 2.72*10^-5

------
mode |
------
vector: 0.0156s, k = 6.24*10^-7
list: 0.03125s, k = 8.556*10^-8
bst: 0.3125s, k = 8.556*10^-8
pq: 0.0157s, k = 6.28*10^-7
hash: 0.0156s, k = 6.24*10^-7

--------------
closest_pair |
--------------
vector: 0.0156s, k = 4.948*10^-8
list: 0.0156s, k = 4.948*10^-8
bst: 0.0156s, k = 7.134*10^-7
pq: 0.0156s, k = 7.134*10^-7
hash: 5.359, k = 1.121*10^-8

----------------
first f sorted | f = 30
----------------
vector: 0.015625, k = 4.278*10^-8
list: 0.03125s, k = 8.555*10^-8
bst: 0.03125s, k = 1.042*10^-3
pq: 0.0156s, k = 0.00052
hash: 0.0469s, can't calculate k because order notation consists of factorial

-------------------
longest_substring | 
-------------------
vector: 73.70s, k = 4.717*10^-9
list: 92.875s, k = 5.94*10^-9
bst: 84.372s, k = 5.3998*10^-9
pq: infeasible
hash: 90.7031s, k = 1.68*10^-10


DISCUSSION
Do these measurements and the overall performance match your predicted
Big ‘O‘ Notation for the data type and operation? Did you update your
initial answers for the Big ‘O‘ Notation of any cell in the table?

Compare the relative coefficients for different data types that have
the same Big ‘O’ Notation for a specific operation. Do these match
your intuition? Are you surprised by any of the results? Will these
results impact your data structure choices for future programming
projects?

Use well-written, complete sentences.  Approximately 250-500 words.  


The time measurement results somewhat did match my predicted order notation, in the sense that
the data structures that had an expensive performance would resulted in a much higher operation time.
However, I did not update any of my results on the cell because I feel like the measurements
matched my predictions.

The operation sort for both vector and list uses the same sorting algorithm. Although 
that means they had the same order notation, the vector operation time seemed to always
surpassed the list's operation. I was surprised by those results, but thinking again, this
might be due to additional operations in between that we didn't account for, considering
we only estimated the highest/expensive performance order notation. 

Through this assignment, I've learned that specific operations are better with different data structures,
and will definitely help me with whatever STL containers I will use for future projects.

MISC. COMMENTS TO GRADER:  
Optional, please be concise!
