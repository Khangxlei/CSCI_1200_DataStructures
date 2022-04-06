HOMEWORK 9: MINIBLAST


NAME:  Khang Le


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  15


HASH FUNCTION DESCRIPTION

My hash function was inspired from this website: http://www.isthe.com/chongo/tech/comp/fnv/. It uses
2 variables, both of them are large, prime numbers that ensures that a different number that multiplies by it
will return a different number every time. The hash starts with one prime number, and multiplies the other prime number
while each time xor the number value of each ith index of the kmer string. 



HASH TABLE IMPLEMENTATION

I first create an empty hash table with the given size. When inserting a given kmer to the hash table, 
I use the hash function to determine the index that we will insert the kmer in the hash table. Each index
holds a specific kmer with a vector that contains all the starting positions for that specific kmer. 

In a case of collision, we use linear probing to go through the hash table, either finding a same kmer as the one 
we're inserting, and simply append its starting location into the vector, or finding an empty index and inserting 
the kmer into that index.

There is a rehash function that doubles the table size and repositions the values inside the table with the new table size.

ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

L = length of the genome sequence
q - query length
p - number of different locations where key is found
k - key size (k-mer size)

How much memory will the hash table data structure require (order notation for memory use)?
Additional variable (x = number of distinct k-mers)

(L-(k-1))*(22) + (L-(k-1))*(4x+4p) - A given table with length L will hold L-(k-1) k-mers. Each of these kmers has a string that
takes up 22 bytes. Table also holds a vector that contains the starting locations. Each distinct kmer holds a vector (a vector holds 4 bytes), 
and each vector holds a "p" number of different locations where the key is found, which takes up 4 bytes each.



What is the order notation for performance (running time) of each of
the commands? What about for the hash table's insert, find, and resize?

genome - O(L) : goes through the length of the genome sequence and add it into a string.

table_size - O(table size) : creates an empty table of table size

occupancy - O(1) : set occupancy as the float value

kmer - O(L - (k-1) + k + n)) : L-(k-1) is how much kmers there is in the table. Hash goes through k length string. 
n accounts for linear probing, where n = no. of collisions. 

query - O(k +n + p*q) :  hash function goes the kmer length string. It then use linear probe in the case of collisions, so n 
is the number of collisions. Finally, it goes through all the unique locations where the key is found, each time 
creating a string of query length and goes through it to find for mismatches. 

quit - O(1) : simply quits


insert - O(k+n) : Function uses hash function which goes through kmer length string. It then linear probes
and again, n accounts for number of collisions. 
hash - O(k) : Function goes through the length of the kmer to hash it
rehash - O((n*(k+c+p)/x) : 
	n = original table size
	c = number of collisions
	x = number of distinct kmers

	Function goes through n table size, each time it finds a kmer, it uses the hash function which 
	goes through k size of string, linear probes that goes through c number of collisions, and transfer
	the vector over which is p number of locations it is found. This only applies when we find a kmer in 
	the table, which is why it is divided by x number of distinct kmers. 


EXTRA CREDIT
Add a new command to implement the database using one of the other
 data structures that we have covered so far in the course: 
vectors, lists, arrays etc. 

Compare the performance your alternative method to the homework method
by making a table of run times for each of the genomes and query 
sets provided with the homework  and compare the times to build
the index and the times to process the queries. 
Document any new commands you have added in your README file.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


