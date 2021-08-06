# knn
k nearest neighbors

to run the program insert the wanted paths of the output file, the classified file
and the unclassified file as local variables and run the program.
the classes in the program are Iris class represents the Iris with all it's properties
and helpful functions, the knn class has the main function and helpful static functions.
we implemented the assignment by read and keep all the Iris in the classified and unclassified
in 2 different allocated arrays, then we sorted the classified array by distance
to current unclassified Iris, got the k'th distance value, then counted how many of
each kind are closer to the Iris than the k'th distance, than we classified the unclassified
Iris by the majority of the neighbors type. we did the same proccess to all the
unclassified Iris array, after we classified them, we writed the output file by the
same order of the array (the original order).

p.s for us to work together on the same code, we created different branches one for
each of us, that way we could upload the code without intereption and conflicts,
we made sure after we agreed on a code, one of us uploaded the code to the main
branch and will solve the confict as we agreed.
