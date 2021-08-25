# knn
k nearest neighbors, server client.

to run the program insert the wanted paths of the classified file
as local variables at both udp and tcp servers, compile and run both servers.
compile and run the client program.

The classes in the program are: Iris class which represents the Iris with all it's properties
and helpful functions, the classifier class which classify the unclassified Iris file, gets the classified file path in the constructor
and the unclassified and output file path plus the k (in the knn) in the classify function which classifiy the unclassified file
to the output file according to the given k, the udp and tcp server which is a server, when gets query from the client (in udp or tcp protocol)
classify the given unclassified file in the given output file, the client which get input of protocol, unclassified file to classify the output file
from user, send request to one of the servers (depends on the wanted protocol) to classify the unclassified file.

We implemented the assignment by connect the client to the tcp server, and send a message to the udp server (we wanted him to have the client's adress
for us to get connection approvel), sent connection approvel from both servers and read the input from user (cin>>), then, according to the wanted protocol, we sent
a query for the server to classify the unclassified file we got from user to the output file the user inserted using the classifier class,
closed both sockets (on client side, each was meant to sent the query to different server) and both servers remains, waits for their next client.
