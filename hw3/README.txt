HOMEWORK 3: JAGGED ARRAY


NAME:  Khang Le


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

StackOverflow, cplusplus, GeeksforGeeks, w3schools, it was a lot of online reference

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  25+ hours



ORDER NOTATION:
For each function, for each version (packed vs. unpacked).  
b = the number of bins
e = the number of elements
k = the number of elements in the largest bin

numElements
 unpacked: O(1)
 packed: O(1)

numBins
 unpacked: O(1)
 packed: O(1)

numElementsInBin
 unpacked: O(1)
 packed: O(1)

getElement
 unpacked: O(1)
 packed: O(1)

isPacked
 unpacked: O(1)
 packed: O(1)

clear
 unpacked: O(b)
 packed: N/A

addElement
 unpacked: O(b*k)
 packed: N/A
 
removeElement
 unpacked: O(k)
 packed: N/A

pack
 unpacked: O(b*k)
 packed: N/A

unpack
 unpacked: N/A
 packed: O(b*k)

print 
 unpacked: O(k*b)
 packed: O(b+e)

constructor w/ integer argument
 unpacked: O(b)
 packed: O(b)

copy constructor
 unpacked: O(b) 
 packed: O(b+e)

destructor
 unpacked: O(b)
 packed: O(b)

assignment operator
 unpacked: O(b) 
 packed: O(b+e)




MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


