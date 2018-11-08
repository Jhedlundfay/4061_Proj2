#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include "comm.h"

/* -------------------------Main function for the client ----------------------*/
void main(int argc, char * argv[]) {

	int pipe_user_reading_from_server[2], pipe_user_writing_to_server[2];

	// You will need to get user name as a parameter, argv[1].

	if(connect_to_server("YOUR_UNIQUE_ID", argv[1], pipe_user_reading_from_server, pipe_user_writing_to_server) == -1) {
		exit(-1);
	}


	/* -------------- YOUR CODE STARTS HERE ----------------------------------------------------------------------------------------*/


	//printf("asdf");
	fcntl(0, F_SETFL, fcntl(0, F_GETFL)| O_NONBLOCK);
	int nbytes=0;
	int len=0;
	char buf[MAX_MSG]; 

	while(1){

		if((nbytes=read(0,buf,MAX_MSG))>0){
			//send user input to child
			len=strlen(buf);
			write(pipe_user_writing_to_server[1],buf,len);
		}

	sleep(2);//only terminate loop if user types exit command - do later

	}
	
 /***Comments below are from original project file, I kept them to make sure we do all of those things above****/
	// poll pipe retrieved and print it to sdiout

	// Poll stdin (input from the terminal) and send it to server (child process) via pipe

		
	/* -------------- YOUR CODE ENDS HERE ------------------------------------------------------------------------------------------------*/
}

/*--------------------------End of main for the client --------------------------*/


