/*#########################################*/
/*						                   */
/*       YAVUZ OGUZ IPEK		           */
/*							 	           */
/*		   grepMeFork.c			           */
/* Compile: gcc grepMeFork.c               */
/* Run: ./a.out -file.txt word_1 word_2 ...*/
/*#########################################*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>
#define USAGEERR -1

int search(char * fileName, char * word);

/*--------------------------------------------------------------------------------*/
/*Fuction Name   :   "usage"                                                      */
/*Parameters     :  1- int   argc  : Holds the number of the program parameters   */
/*                  2- char* argv[]: Holds program parameters as character arrays */
/*Description    :   Checks for valid number of command-line arguments            */
/*--------------------------------------------------------------------------------*/ 
static inline int usage(int argc, char* argv[]){

  if ( argc < 3  ){  
  		fprintf(stderr,"Usage: </path/to/%s> <-file.txt> <words>\n",argv[0]);
  		return USAGEERR;		// for wrong Argument  
  }
        return 1;
}

int main(int argc, char** argv){

	if( usage(argc, argv) == USAGEERR )
    	return USAGEERR;  // for wrong Argument

	int time, time2; 
	double startOfCode, endOfCode;	
	struct timeval now, now2;   // to calculate time of program
    time = gettimeofday(&now, NULL);   // to calculate time of program
    startOfCode = (double) now.tv_usec / 1.0e4;   // beginning of program
	char ** words;	// Searched words
	int  i = 0, totalWord;	// to keep total words 
	pid_t Parent, Child;	// Process id of child 
	FILE *  File;

	if( (File = fopen(&argv[ 1 ][ 1 ], "r")) == NULL){
		printf("Cannot find or open '%s'\n", &argv[1][1]);
		return 1;  // to detect for  file error
	}
	fclose(File);	  	
	totalWord = argc - 2;	// total words 
	words = &argv[2];	// Searched words
	Parent = getpid();

	do{
		Child = fork();
		if(Child == -1){  		// Error check 
			printf("Failed  fork!\n");
			return 1;
		}
	
		if(Child == 0) { // If process is a child , searching word  in file
			printf(" %s => %d pid: %d ppid: %d\n", words[i], search( &argv[1][1], words[i]), getpid(), getppid() );
			break;
		}
	
		++i;
	}while(i < totalWord);
	
	do{  	// Wait for children 
		while( ( Child = wait(NULL) ) == -1 && ( errno == EINTR ) )
			;
	}while(Child > 0);
	
	if( Parent == getpid() ) {  // If process is parent 
		printf("Main Process id : %d\n",  getpid());
		time2 = gettimeofday( &now2 , NULL);
		endOfCode = (double) now2.tv_usec/1.0e4 ;    // end of program
    	printf("Time : [%.4lf] \n", endOfCode - startOfCode);   // calculating time
	}

	return 0;
}

int search(char * fileName, char * word){
	FILE * File = fopen(fileName, "r"); // to open file
	int i, length = strlen(word), counter = 0;
	char Buffer;
	
	while( fscanf(File, "%c", &Buffer) != EOF ){// scannig file
		for(i = 0;	i < length && Buffer == word[i] && fscanf(File, "%c", &Buffer) != EOF; ++i)			
			if(i == length - 1)
				++counter;   // if find word
	}	
	fclose(File);  // to close file
	return counter;
}
