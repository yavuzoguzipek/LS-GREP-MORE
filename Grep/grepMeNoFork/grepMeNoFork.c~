/*#########################################*/
/*			  			                   */
/*          YAVUZ OGUZ IPEK		           */
/*							 	           */
/*		   grepMeNoFork.c		           */
/* Compile: gcc grepMeNoFork.c             */
/* Run: ./a.out -file.txt word_1 word_2... */
/*#########################################*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define USAGEERR -1

int search(char * fileName, char * word, int size);

/*--------------------------------------------------------------------------------*/
/*Fuction Name   :   "usage"                                                      */
/*Parameters     :  1- int   argc  : Holds the number of the program parameters   */
/*                  2- char* argv[]: Holds program parameters as character arrays */
/*Description    :   Checks for valid number of command-line arguments            */
/*--------------------------------------------------------------------------------*/ 

static inline int usage(int argc,char* argv[]){

  if (  argc < 3  ){ 
  		fprintf(stderr,"Usage: </path/to/%s> <-file.txt> <words>\n", argv[0]);
  		return USAGEERR;  // for wrong Argument
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
	char **  words;	// Searched words
	int i,	totalWord;		// to keep total words 
	FILE *  File;

	if( (File = fopen(&argv[ 1 ][ 1 ], "r")) == NULL){
		printf("Cannot find or open '%s'\n", &argv[1][1]);
		return 1;  // to detect for  file error
	}
	fclose(File);
	totalWord = argc - 2;		// total words 
	words = &argv[2];	// Searched words
	
	for(i = 0; i < totalWord; ++i)
		printf(" %s : %d\n",  words[ i ],	search( &argv[ 1 ][ 1 ], words[ i ], strlen( words[ i ] ) ) );
	
	time2 = gettimeofday( &now2 , NULL);
	endOfCode = (double) now2.tv_usec/1.0e4 ;    // end of program
    printf("Time : [%.4lf] \n", endOfCode - startOfCode);   // calculating time

	return 0;
}

int search(char * fileName, char * word, int size){

	FILE *  File = fopen(fileName, "r"); // to open file
	char Buffer;
	int i, counter = 0;
	
	while( fscanf(File, "%c", &Buffer) != EOF ){	// scannig file
		for(i = 0; i < size && Buffer == word[i] && fscanf(File, "%c", &Buffer) != EOF; ++i)	
			if(i == size - 1)
				++counter; // if find word
	}
	
	fclose(File);  // to close file
	return counter;
}
