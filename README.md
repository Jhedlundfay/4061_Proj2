/* CSci4061 F2018 Assignment 2
* section: o4
* date: 11/10/2018
* name: John Hedlund-Fay, Zaffer Hussein, Christopher Pieper (for partner)
* id: hedlu131 5181960, husse147 5236353, piepe072 5160800 */

1. This project consists of two main executables: the client and the server. Users can use the client executable to connect to the server and use commands to interact with other users and the server and send messages to other users and the server.
2. John Hedlund-Fay was responsible for creating a git repository that everyone in the group could use in order to make collaboration more reasonable. Additionally, he also contributed to implementing kicking and listing and fixed errors with how the buffers were being read in that were interfering with recognizing commands from the user. He also wrote the readme. Christopher Pieper completed the warm-up assignment and was responsible for setting up a lot of the preliminary code structure that was necessary for the project to get started. Additionally, he set up p2p communications. Zaffer Hussein was responsible for figuring out approaches to many of the commands and was able to create many of the early versions of the server commands that allowed his partners to improve on and implement fixes to the code. He also created the setup for how the code handles commands. Since most of the coding was done on the server side, everyone contributed equally to coding both files since it seemed unfair to try and break it up into working on the server program and the client program.
3. The Makefile works correctly. Running make clean should be unnecessary because the objects and executables shouldn't be included in the zip but in case they running make clean removes all such objects and executables. Running make compiles the server and client. 
4. The client can be run by ./client and the server can be run by ./server. If one attempts to run ./client without a username it will produce and error message. If one attempts to run ./client without first starting ./server it will print out an error message.
5. Typing \list as either the admin (server) or client will print out a list of all currently connected users. Typing \kick and a valid username as admin will disconnect that user from the server. Typing \exit as a user will end that user's connection and end the process. Typing \exit as admin will end that admin process and disconnect all current users from the server. Typing \p2p with a valid username and a non-empty message will send a message to another user on the server. All other text is braodcasted to the server and to all other users.
6. Since the provided skeleton code seeemed to indicate that the user process should only return when the user types \exit, we designed \kick to disconnect the user and purge their info from the relevant data structures (they dont appear in the list, other users can connect with that username and to that id) and they cannot communicate with the server or other users any more, it doesn't cause the user program to exit because we assumed that only \exit (as user) should do that. Similarly if \exit is called (as admin) it clears all user data and exits the server but the user program(s) stay open until they enter \exit.
7. Our approach to most error handling was to notify the user/admin without neccessarily ending the program by using perror.
