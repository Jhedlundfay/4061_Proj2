#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "comm.h"
#include "util.h"

/* -----------Functions that implement server functionality -------------------------*/

/*
 * Returns the empty slot on success, or -1 on failure
 */
int find_empty_slot(USER * user_list) {
	// iterate through the user_list and check m_status to see if any slot is EMPTY
	// return the index of the empty slot
    int i = 0;
	for(i=0;i<MAX_USER;i++) {
    	if(user_list[i].m_status == SLOT_EMPTY) {
			return i;
		}
	}
	return -1;
}

/*
 * list the existing users on the server shell
 */
int list_users(int idx, USER * user_list)
{
	// iterate through the user list
	// if you find any slot which is not empty, print that m_user_id
	// if every slot is empty, print "<no users>""
	// If the function is called by the server (that is, idx is -1), then printf the list
	// If the function is called by the user, then send the list to the user using write() and passing m_fd_to_user
	// return 0 on success
	int i, flag = 0;
	char buf[MAX_MSG] = {}, *s = NULL;

	/* construct a list of user names */
	s = buf;
	strncpy(s, "---connecetd user list---\n", strlen("---connecetd user list---\n"));
	s += strlen("---connecetd user list---\n");
	for (i = 0; i < MAX_USER; i++) {
		if (user_list[i].m_status == SLOT_EMPTY)
			continue;
		flag = 1;
		strncpy(s, user_list[i].m_user_id, strlen(user_list[i].m_user_id));
		s = s + strlen(user_list[i].m_user_id);
		strncpy(s, "\n", 1);
		s++;
	}
	if (flag == 0) {
		strcpy(buf, "<no users>\n");
	} else {
		s--;
		strncpy(s, "\0", 1);
	}

	if(idx < 0) {
		printf("%s",buf);
		printf("\n");
	} else {
		/* write to the given pipe fd */
		if (write(user_list[idx].m_fd_to_user, buf, strlen(buf) + 1) < 0)
			perror("writing to server shell");
	}

	return 0;
}

/*
 * add a new user
 */
int add_user(int idx, USER * user_list, int pid, char * user_id, int pipe_to_child, int pipe_to_parent)
{
  user_list[idx].m_pid = pid;
  *user_list[idx].m_user_id = user_id;
  user_list[idx].m_fd_to_user = pipe_to_child;
  user_list[idx].m_fd_to_server = pipe_to_parent;
  user_list[idx].m_status = SLOT_FULL;
  return 1;
}

/*
 * Kill a user
 */
void kill_user(int idx, USER * user_list) {
	// kill a user (specified by idx) by using the systemcall kill()
	// then call waitpid on the user
}

/*
 * Perform cleanup actions after the used has been killed
 */
void cleanup_user(int idx, USER * user_list)
{
	// m_pid should be set back to -1
	// m_user_id should be set to zero, using memset()
	// close all the fd
	// set the value of all fd back to -1
	// set the status back to empty
}

/*
 * Kills the user and performs cleanup
 */
void kick_user(int idx, USER * user_list) {
	// should kill_user()
	// then perform cleanup_user()
}

/*
 * broadcast message to all users
 */
int broadcast_msg(USER * user_list, char *buf, char *sender)
{
  //for(int i )
	//iterate over the user_list and if a slot is full, and the user is not the sender itself,
	//then send the message to that user
	//return zero on success
	//return 0;
}

/*
 * Cleanup user chat boxes
 */
void cleanup_users(USER * user_list)
{
	// go over the user list and check for any empty slots
	// call cleanup user for each of those users.
}

/*
 * find user index for given user name
 */
int find_user_index(USER * user_list, char * user_id)
{
	// go over the  user list to return the index of the user which matches the argument user_id
	// return -1 if not found
	int i, user_idx = -1;

	if (user_id == NULL) {
		fprintf(stderr, "NULL name passed.\n");
		return user_idx;
	}
	for (i=0;i<MAX_USER;i++) {
		if (user_list[i].m_status == SLOT_EMPTY)
			continue;
		if (strcmp(user_list[i].m_user_id, user_id) == 0) {
			return i;
		}
	}

	return -1;
}

/*
 * given a command's input buffer, extract name
 */
int extract_name(char * buf, char * user_name)
{
	char inbuf[MAX_MSG];
    char * tokens[16];
    strcpy(inbuf, buf);

    int token_cnt = parse_line(inbuf, tokens, " ");

    if(token_cnt >= 2) {
        strcpy(user_name, tokens[1]);
        return 0;
    }

    return -1;
}

int extract_text(char *buf, char * text)
{
    char inbuf[MAX_MSG];
    char * tokens[16];
    char * s = NULL;
    strcpy(inbuf, buf);

    int token_cnt = parse_line(inbuf, tokens, " ");

    if(token_cnt >= 3) {
        //Find " "
        s = strchr(buf, ' ');
        s = strchr(s+1, ' ');

        strcpy(text, s+1);
        return 0;
    }

    return -1;
}

/*
 * send personal message
 */
void send_p2p_msg(int idx, USER * user_list, char *buf)
{

	// get the target user by name using extract_name() function
	// find the user id using find_user_index()
	// if user not found, write back to the original user "User not found", using the write()function on pipes.
	// if the user is found then write the message that the user wants to send to that user.
}

//takes in the filename of the file being executed, and prints an error message stating the commands and their usage
void show_error_message(char *filename)
{
}


/*
 * Populates the user list initially
 */
void init_user_list(USER * user_list) {

	//iterate over the MAX_USER
	//memset() all m_user_id to zero
	//set all fd to -1
	//set the status to be EMPTY
	int i=0;
	for(i=0;i<MAX_USER;i++) {
		user_list[i].m_pid = -1;
		memset(user_list[i].m_user_id, '\0', MAX_USER_ID);
		user_list[i].m_fd_to_user = -1;
		user_list[i].m_fd_to_server = -1;
		user_list[i].m_status = SLOT_EMPTY;
	}
}

/* ---------------------End of the functions that implementServer functionality -----------------*/


/* ---------------------Start of the Main function ----------------------------------------------*/
int main(int argc, char * argv[])
{
	int nbytes;
	setup_connection("me"); // Specifies the connection point as argument.

	USER user_list[MAX_USER];
	init_user_list(user_list);   // Initialize user list

	char buf[MAX_MSG];
	fcntl(0, F_SETFL, fcntl(0, F_GETFL)| O_NONBLOCK);
	print_prompt("admin");



/* ------------------------YOUR CODE FOR MAIN-------------------------------------------------------------------------------------------*/

	int len=0;//for string length later

	while(1) {


		// Handling a new connection using get_connection
		int pipe_SERVER_reading_from_child[2];
		int pipe_SERVER_writing_to_child[2];
		char user_id[MAX_USER_ID];

		int pipe_child_writing_to_user[2];
		int pipe_child_reading_from_user[2];
		int pid=0;




		if((get_connection(user_id, pipe_child_writing_to_user,pipe_child_reading_from_user))!=-1){
			// Create two pipes for bidirectional communication with child process and create child process (via fork?)

			if (pipe(pipe_SERVER_reading_from_child) < 0 || pipe(pipe_SERVER_writing_to_child) < 0) {
				perror("Failed to create pipes\n");
				exit(-1); //?
			}

			if((pid=fork()) == -1){
				perror("Failed to fork");  //get pid add user to user_list
			}
			int curpid = getpid();
			int slot = find_empty_slot(user_list);
			if( slot == -1){
				perror("No more empty slots");
			}else{
				add_user(slot,user_list,curpid,user_id,pipe_SERVER_writing_to_child[1],pipe_SERVER_reading_from_child[0]);
			
			if(pid==0){ // Child process: poll users and SERVER
				//close unused ends
				close(pipe_child_writing_to_user[0]);
				close(pipe_child_reading_from_user[1]);

				while(1){

				if ((nbytes=read(pipe_child_reading_from_user[0],buf,MAX_MSG))>0){
					len=strlen(buf);
					write(1,"Child:",6);//for warm-up
					write(1,buf,len);   //for warm-up
					write(pipe_SERVER_reading_from_child[1],buf,len);
				}

				sleep(2);//slow down polling

			    }

			}
			else{
				// Server process: Add a new user information into an empty slot
				//close unused ends

				close(pipe_SERVER_reading_from_child[1]);
				close(pipe_SERVER_writing_to_child[0]);
				fcntl(pipe_SERVER_reading_from_child[0],F_SETFL | O_NONBLOCK);
       				 int i = 0;
				for(int i= 0; i < MAX_USER; i++){ //poll all the children(loop through user list) and read if there if available
         				 if(user_list[i].m_status == SLOT_EMPTY){
             					 continue;
          				 } // go to next iteration if no user at this position

					if((nbytes=read(user_list[i].m_fd_to_server,buf,MAX_MSG))>0){ //see if anything in pipe of for server read from current user
						//do stuff with user input here
						len=strlen(buf);
						write(1,"Server:",7); //for warm-up
						write(1,buf,len);     //for warm-up
						print_prompt("admin");//keep design
					}
					else{
						if((nbytes=read(0,buf, MAX_MSG))>0){
						print_prompt("admin");//keep design for warm-up
						}
				    			//Do stuff with admin input here later
						}

				sleep(2);//only terminate loop if admin types exit command
			    }
			}

		}




         /***Comments below are from original project file, I kept them to make sure we do all of those things above****/

		// Check max user and same user id

		// Child process: poli users and SERVER

		// Server process: Add a new user information into an empty slot
		// poll child processes and handle user commands
		// Poll stdin (input from the terminal) and handle admnistrative command

		//printf(buf);

		sleep(2);

		/* ------------------------YOUR CODE FOR MAIN------------------------------------------------------------------------------------*/
	}
}
}
/* --------------------End of the main function ----------------------------------------*/
