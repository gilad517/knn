# knn, server client
k nearest neighbors, server client.  

to run the program insert the wanted timeout (in seconds) to the local variable in Server.cpp file, line 89.  
compile and run the server(see "compiling and running").  
compile and run the client program(see "compiling and running").

compiling and running: to compile either use our provided CmakeLists.txt file or compile from terminal:

CmakeLists.txt file:  
while on the root dir(knn) make sure the build dir is empty(for example use: "rm -r build" and then "mkdir build")  
and then while on the root dir enterthe following commands(may take some time):  
cd build  
cmake ..  
cmake --build .  

and then to run the server from the build dir enter the command:
./Server
and to run the client from the build dir enter the command:
./Client

compiling from terminal:  
enter the following lines to the terminal:  
g++ Server.cpp CLI.cpp Commands/ClassifyingCommand.cpp Commands/ConfusionMatrixCommand.cpp Commands/DownloadCommand.cpp Commands/PrintingCommand.cpp Commands/SettingsCommand.cpp Commands/UploadCommand.cpp DefaultIO.h StandardIO.cpp Classifier.cpp Data.cpp SocketIO.cpp -lpthread -o Server.out  
g++ Client.cpp SocketIO.cpp StandardIO.cpp DefaultIO.h  -o Client.out

to run the server enter the command:  
./Server.out  
and to run the client enter the command:  
./Client.out  

to run multiple clients add another terminal and run the client again (./Client.out or ./Client)

Splitting the terminal can either be achieved by a terminal multiplexer or in VsCode using the + on the top right of the terminal window.



The classes in the program are: 
Data class which represents the Data to classify with all it's properties
and helpful functions, the classifier class which can do the wanted commands (classify, download results, get the confusion matrix...).
the commands interface which saves classifier as member (to execute the commands), execute function and description.
the commands (upload command for example) which implements the commands interface and the execute and description function according to the class name.
Default IO interface with read and write commands.
socket IO implements the Default IO interface and write and read from client socket.
CLI class with start function that accepts Default IO as parameter, creates an array of commands (according to the input that execute each function) and read input from user
and execute the wanted function, when execute the "download results" function, the execution of the function will happen in a different thread, for the client not to wait while this (maybe long) function runs.
Client that communicate with the server, only reads and writes to him in a loop (until the server ends the communication)
The server, waits for clients in a thread, while in the main thread, he checks if he should time out (using high resolution clock) and stop accepting clients. When he accepts a client, the server creates another thread to handle the client (create socket io with him and run the start() function) to let other clients connect, and let the main thread know that the last client connected now (using referance to the high resolution clock variable in the main thread). When the last client connected more than the wanted timeout seconds ago (currently 30) the server does not accepts any more clients (using referance to a boolean variable "should accept") and enter an infinite loop until there are no more running threads (using shared (by referance) int that counts the number of running threads), after that the server shutdown.
