/* Name: Mitchell McPartland
   Instructor: Gregory Benson
   Class: Operating Systems
   Program: usfls (Project 2)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

void usfls();

/* Function: main
   Description: This function simply calls my
     usfls() function and then returns a 0.    
*/ 

int main(int argc, char *argv[]) {
	usfls();
    return 0;
}

/* Function: usfls
   Description: This function makes use of the
     dirent struct in order to correctly list
     the files in the current directory.  I
     declare a directory stream called dir. I
     use strcmp() to only print out the files
     that do not start with a '.'.  I use the
     opendir() function to open the current
     directory.  Then, I iterate through
     each file in the current directory,
     printing out only the files that do not
     begin with a period. 
*/ 

void usfls() {
	DIR *dir;
	struct dirent *d_pointer;
	char *file_name;
	dir = opendir(".");
	while((d_pointer = readdir(dir)) != NULL) {
        if (!strcmp(d_pointer->d_name, ".") || !strcmp(d_pointer->d_name, "..")) {
        } else {
            file_name = d_pointer->d_name;
            if(file_name[0] != '.') {
            	printf("%s\n", file_name);
            }
        }
    }
    closedir(dir);
}