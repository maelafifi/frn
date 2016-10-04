/* Name: Mitchell McPartland
   Instructor: Gregory Benson
   Class: Operating Systems
   Program: usfsh (Project 2)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_BUF_LEN 128
#define MAX_ARGS 128

void print_prompt();
void read_command_line(char *buf);
void parse_command_line(char *buf, char **args);
int get_command_type(char **args);
void execute_simple_command(char *program, char **args, int size);
void make_sec_args(char **args, char **sec_args);
int get_args_size(char **args);
void execute_cd_command(char *new_directory);
void remove_apostrophe(char *directory);
void execute_file_redirection(char *program, char **args, int loc);
int get_output_loc(char **args, int loc);
void get_redirect_args(char **args, int loc);
void get_pipe_args(char **og_args, char **new_args, int loc);
void execute_pipe_redirection(char *program, char **args, int loc);
void remove_newlines(char **args);
void run_command(int command, char **args, char **sec_args, int loc, int args_size);

/* Function: Main
   Description: First, this function initializes the 'command' variable
     to -1, so that the condition in the while-loop will not fail the
     first time the user runs the program.  In the while-loop, I create
     a buffer, an array of args, an integer called args_size, and an
     integer called loc.  The buffer is used to read in the characters
     from the command line.  The args array will be passed in to
     parse_command_line, where it will be filled with all of the
     arguments.  The variable, args_size, will be used to initialize
     a new args array, which is much smaller than the original args
     array. My function, get_command_type, is called to get the "type"
     of command that the user entered.  My function, run_command is called
     with all of the necessary data, five arguments, and the command runs.
*/ 

int main(int argc, char *argv[]) {
 	int command = -1;

 	while(command != 5) {
 		char buf[MAX_BUF_LEN];
 		char *args[MAX_ARGS];
 		int args_size;
 		int loc;

 		print_prompt();
		read_command_line(buf);
		parse_command_line(buf, args);
		remove_newlines(args);

		command = get_command_type(args);

		args_size = get_args_size(args);
		char *sec_args[args_size - 1];
		make_sec_args(args, sec_args);

		run_command(command, args, sec_args, loc, args_size);
	}
 	return 0;
}

/* Function: print_prompt
   Description: This function is called at the beginning of my while-loop
     in the main() function. It simply uses the write() system call to
     print out the "$"" with a space.
*/ 

void print_prompt() {
	int rv;
 	rv = write(1, "$ ", 2);
 	if(rv < 0) {
 		printf("write() failed \n");
 		exit(-1);
 	}
}

/* Function: read_command_line
   Description: This function is called after print_prompt in my
     while-loop in the main() function.  It uses the read() system
     call to read in the information from the command line and it
     places this information in the buffer that is passed in as an
     argument.
*/ 

void read_command_line(char *buf) {
 	int rv;
 	rv = read(0, buf, (MAX_BUF_LEN - 1));
 	if(rv < 0) {
 		printf("read() failed \n");
 		exit(-1);
 	}
 	buf[rv] = '\0';
}

/* Function: parse_command_line
   Description: This function is called after my read_command_line
     in the while-loop of my main() function.  It uses strtok() to
     split up each argument.  Then, this function places each
     argument into the args array that is passed in as a parameter.    
*/ 

void parse_command_line(char *buf, char **args) {
 	int i = 0;
 	args[i] = strtok(buf, " ");
 	i++;
 	while((args[i] = strtok(NULL, " ")) != NULL) {
 		i++;
 	}
}

/* Function: get_command_type
   Description: This function returns an integer that signifies
     the type of command that the user wants to run.  It returns
     a 5 if the user wants to exit; a 2 for a simple command;
     a 0 for a file redirection; and a 1 for pipe redirection.    
*/ 

int get_command_type(char **args) {
 	int i;

    if(strcmp(args[0], "exit") == 0) {
    	return 5;
    }
 	for(i = 0 ; args[i] != NULL ; i++) {
 		if(strcmp(args[i], ">") == 0) {
 			return 0;
 		} else if(strcmp(args[i], "|") == 0) {
 			return 1;
 		}
 	}
 	return 2;
}

/* Function: execute_simple_command
   Description: This function executes any simple commands that
     the user may enter, such as "echo" or "wc".  I check the
     the size of the args array to make it easier to use
     execvp when there is a command without arguments.  I check
     to see if the user typed in the "cd" command and, if he or
     she did, I call my execute_cd_command function.  I use
     fork() to create a child process; and then I run the simple
     command with execvp in the child process.    
*/ 

void execute_simple_command(char *program, char **args, int size) {
	pid_t pid;
	int status;

	if(program[0] == '\0') {
		return;	
	}

	if(size > 2) {
    	if(strcmp(program, "cd") == 0) {
    		execute_cd_command(args[1]);
    		return;
    	}	
		if((pid = fork()) < 0) {
			printf("Error");
			exit(1);
		} else if(pid == 0) {
			if(execvp(program, args) < 0) {
				printf("%s: command not found\n", program);
				exit(1);
			}
		} else {
			while(wait(&status) != pid);
		}
	} else {
    	if(strcmp(program, "cd") == 0) {
    		execute_cd_command(args[1]);
    		return;
    	}
		char *simple[] = {program, NULL};
		if((pid = fork()) < 0) {
			printf("Error");
			exit(1);
		} else if(pid == 0) {
			if(execvp(program, simple) < 0) {
				printf("%s: command not found\n", program);
				exit(1);
			}
		} else {
			while(wait(&status) != pid);
		}
	}
}

/* Function: make_sec_args
   Description: This function is used to simply make the
     original args array smaller when passing it in to
     my execvp commands.    
*/ 

void make_sec_args(char **args, char **sec_args) {
	int f = 0;
	while(args[f] != NULL) {
		sec_args[f] = args[f];
		f++; 
	}
	sec_args[f] = args[f];
}

/* Function: get_args_size
   Description: This function is used to simply return
     the true size of the original args array; meaning,
     it returns the size of the array up to the NULL
     spot.  I then use this size to make the smaller
     array.    
*/ 

int get_args_size(char **args) {
	int l = 0;
	while(args[l] != NULL) {
		l++;
	}
	return l+1;
}

/* Function: execute_cd_command
   Description: This function is obviously used to
     change directories when the user attempts to
     run the "cd" command.  I first initialize
     the current directory.  Then, I check if there
     are any quotes or apostophres in the new
     directory that the user entered.  If there is,
     I call my remove_apostophe function.  I then
     combine the current directory with the new
     directory and I call chdir() to change the
     directory.    
*/ 

void execute_cd_command(char *new_directory) {
	char the_directory[1024];
	int result;
	if(new_directory[0] == '"' || new_directory[0] == '\'') {
		remove_apostrophe(new_directory);
	}
	if(getcwd(the_directory, sizeof(the_directory)) != NULL) {
		strcat(the_directory, "/");
		strcat(the_directory, new_directory);
		result = chdir(the_directory);
	}
	if(result != 0) {
		printf("Not a valid directory\n");
	}
}

/* Function: remove_apostrophe
   Description: This function is used to remove any
     apostrophes or quotes that are in the new directory
     that the user wants to change to.  In order to make
     chdir() work fully, I had to create this function
     to remove any apostrophes or quotes that could
     appear in the directory that the user enters.    
*/ 

void remove_apostrophe(char *directory) {
	int m;
	directory[0] = directory[1];
	for(m = 1 ; directory[m] != '\'' ; m++) {
		if(directory[m + 1] == ' ' || directory[m + 1] == '\0') {
			directory[m] = ' ';
		} else {
			directory[m] = directory[m + 1];
		}
	}
	directory[m] = '\0';
	directory[m - 1] = '\0';
}

/* Function: execute_file_redirection
   Description: This function is used to write the output
     of one function to an output file.  I use the "loc"
     variable, which is passed in as a parameter, to
     indicate where the output file is located in the
     args array.  I use fork() to create a child process,
     and then I get the output file descriptor by calling
     the open() system call.  I pass the output file
     descriptor in to dup2 to make it so the output of the
     first command gets redirected to the output file.  I also
     have to call my get_redirect_args() function to get the
     correct arguments for the first command to pass in to
     execvp; otherwise, I am passing in extra information
     that will cause execvp to crash.  Then, in the child 
     process, I call execvp to run the first command.    
*/ 

void execute_file_redirection(char *program, char **args, int loc) {
	pid_t pid;
	int status;

	if((pid = fork()) < 0) {
		printf("Error in fork() \n");
		exit(1);
	} else if(pid == 0) {
		int output_fd = open(args[loc], O_CREAT|O_WRONLY, 0777);
		if(output_fd == -1) {
			printf("Error opening output file \n");
			return;
		}
		dup2(output_fd, 1);
		close(output_fd);
		get_redirect_args(args, loc);
		if(execvp(program, args) < 0) {
			printf("%s: command not found \n", program);
			return;
		}
	}
}

/* Function: get_output_loc
   Description: This function is used to get the location
     of the output file in the args array when the user
     is attempting to run a command with file redirection.    
*/ 

int get_output_loc(char **args, int find) {
	int m = 0;
	if(find == 0) {
		while(strcmp(args[m], ">") != 0) {
			m++;
		}
		return m + 1;
	} else {
		while(strcmp(args[m], "|") != 0) {
			m++;
		}
		return m + 1;
	}
}

/* Function: get_redirect_args
   Description: This function corrects the args array
     when the user attempts to run a file redirection
     command.  If I didn't change the array, then execvp
     would fail.  So, I pass in loc to know where the
     output file is.  Then, I set args[loc - 1] to
     NULL so that execvp can run.    
*/ 

void get_redirect_args(char **args, int loc) {
	args[loc - 1] = NULL;
}

/* Function: execute_pipe_redirection
   Description: This function creates two child processes
     for the pipe.  First, I get the size of my first args
     array and use it for the intialization of my pipe_args
     array.  My pipe_args will have the arguments for the
     second command.  I then call my get_redirect_args
     function to shorten the args array so that it can
     properly work with execvp.  I then create my fd array
     and call the pipe() system call with it.  In the first
     child, I begin by closing standard out.  Then I call dup
     on the second file descriptor; after which I close both
     file deescriptors.  I then call execvp for the first
     command.  In the second child, I first close standard
     in.  Then I call dup on the first file descriptor; after
     which I then close both file descriptors.  I then call
     execvp for the second command.  Lastly, I close both file
     descriptors.
*/ 
	
void execute_pipe_redirection(char *program, char **args, int loc) {
	int args_size = get_args_size(args);
	char *pipe_args[args_size];
	get_pipe_args(args, pipe_args, loc);
	get_redirect_args(args, loc);

	int fd[2];
	if(pipe(fd) == -1) {
		printf("Error in pipe \n");
		exit(1);
	}

	// first child
	if(fork() == 0) {
		close(STDOUT_FILENO);
		dup(fd[1]);
		close(fd[0]);
		close(fd[1]);
		execvp(program, args);
		exit(1);
	}
	// second child
	if(fork() == 0) {
		close(STDIN_FILENO);
		dup(fd[0]);
		close(fd[1]);
		close(fd[0]);
		execvp(pipe_args[0], pipe_args);
		exit(1);
	}
	close(fd[0]);
	close(fd[1]);
	wait(0);
	wait(0);

}

/* Function: get_pipe_args
   Description: This function creates the proper args
     array for the second command that the user enters
     for a pipe redirection.  I use the "loc" variable
     to know where the second command is located in the
     original args array.  With this information, I
     create the new args array that will be passed
     in to execvp to run the second command.   
*/ 
	
void get_pipe_args(char **og_args, char **new_args, int loc) {
	int f;
	int l = 0;
	for(f = loc ; og_args[f] != NULL ; f++) {
		new_args[l] = og_args[f];
		l++;
	}
	new_args[l] = NULL;
}

/* Function: run_command
   Description: This function is called at the end of
     my while-loop in my main() function.  After I have
     gotten all of the necessary information in main(),
     I call this function, which then calls the
     necessary function needed to execute the user's
     command.    
*/ 

void run_command(int command, char **args, char **sec_args, int loc, int args_size) {
	if(command == 0) {
		loc = get_output_loc(args, 0);
		execute_file_redirection(args[0], sec_args, loc);
	} else if(command == 1) {
		loc = get_output_loc(args, 1);
		execute_pipe_redirection(args[0], sec_args, loc);
	} else if(command == 2) {
		execute_simple_command(args[0], sec_args, args_size);
	}
}

/* Function: remove_newlines
   Description: This function is called after I have
     gotten all of the arguments from parse_command_line
     in my main() function.  I call this function to
     remove any newline characters that could be at the
     end of the strings in my args array.    
*/ 

void remove_newlines(char **args) {
	int m;
	for(m = 0 ; args[m] != NULL ; m++) {
		char *position;
		if((position=strchr(args[m], '\n')) != NULL) {
    		*position = '\0';
    	}
    }
}