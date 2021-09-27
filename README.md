# knn, server client
k nearest neighbors, server client.  

to run the program insert the wanted paths of the classified file  
as local variables at both udp and tcp servers, compile and run both servers(see "compiling and running").  
compile and run the client program(see "compiling and running").

compiling and running: to compile either use the CMakeLists.txt file we provided or enter the following lines to the terminal:  
g++ TcpServer.cpp CLI.cpp Commands/ClassifyingCommand.cpp Commands/ConfusionMatrixCommand.cpp Commands/DownloadCommand.cpp Commands/PrintingCommand.cpp Commands/SettingsCommand.cpp Commands/UploadCommand.cpp DefaultIO.h StandardIO.cpp Classifier.cpp Data.cpp SocketToQueue.cpp QueueToSocketIO.cpp SocketIO.cpp -lpthread -o Server.out

when using our provided CMakeLists.txt file, use these commands to run(in that order, each in a different terminal - use split, and have your working directory be "build"):  
./TcpServer  
./Client  
otherwise, use these commands to run(in that order, each in a different terminal - use split):  
./TcpServer.out  
./UdpServer.out  
./Client.out  

Splitting the terminal can either be achieved by a terminal multiplexer or in VsCode using the + on the top right of the terminal window.

The classes in the program are: Iris class which represents the Iris with all it's properties
and helpful functions, the classifier class which classifies the unclassified Iris file, gets the classified file path in the constructor
and the unclassified and output file paths plus the k (from the knn) in the classify function which classifies the unclassified file
to the output file according to the given k.  
The udp and tcp servers get a query from the client (in udp or tcp protocol) and classify the given unclassified file to the given output file,
the client receives from the user an input of protocol(TCP or UDP), and then the paths of the unclassified file to classify and the output file,
it then sends a request to one of the servers (depending on the given protocol) to classify the unclassified file to the output file.

We implemented the assignment by first connecting the client to the tcp server, and sending a message to the udp server (we wanted it to have the client's adress
for us to get connection approvel) and after making sure the servers are up(by connecting to the tcp server and getting a message from the udp server),
read the input from user (cin>>), then, according to the given protocol, we sent a query for the corresponding server
to classify the unclassified file we got from the user to the output file the user inserted using the classifier class from milestone 1,
and finally(after classifying the wanted file and after the server printed "classified successfully"),
we closed both sockets on the client side(each was meant to sent a query to its server).  
Both servers still remain, patiently waiting for their next client.
