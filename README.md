# knn
k nearest neighbors

to run the program insert the wanted paths of the output file, the classified file
and the unclassified file as local variables and run the program.
The classes in the program are: Iris class which represents the Iris with all it's properties
and helpful functions, the knn class has the main function and helpful static functions.
We implemented the assignment by reading and keeping all the Irises in the classified and unclassified
allocated arrays, then we sorted the classified array by distance to the current unclassified
Iris(we in fact sorted by the squared distance in an equal fashion), got the k'th distance value, then counted how many of
each Iris type are closer to the Iris than the k'th distance, then we classified the unclassified
Iris by the majority of the neighbors type. we did the same proccess to all the
unclassified Iris array, we then wrote the output file by the same order of the array(the original order).

p.s: for us to work together on the same code, we created a different branch for
each of us, that way we could upload the code without interruption and conflicts.
then when we agreed on the code, one of us would upload the code to the main
branch and solve the conficts as we agreed.
