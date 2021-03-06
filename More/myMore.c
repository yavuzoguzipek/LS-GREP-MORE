/*----------------------------------------------------------------------------*/
/* Author	:  YAVUZ OĞUZ İPEK                                                */
/* Date		:  April 7th  2013                                                */
/* Program Name  : "myMore.c"                                                 */ 
/* Description   : Displays the contents of the file.                         */
/*                 This code works like more	   				              */
/*----------------------------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#define USAGEERR -1
#define DEFAULT_LINE 24


/*--------------------------------------------------------------------------------*/
/*Fuction Name   :   "usage"                                                      */
/*Parameters     :  1- int   argc  : Holds the number of the program parameters   */
/*                  2- char* argv[]: Holds program parameters as character arrays */
/*Description    :   Checks for valid number of command-line arguments            */
/*--------------------------------------------------------------------------------*/ 

static inline int usage(int argc,char* argv[]){

  if ( ( argc > 3 ) || ( argc < 2 ) ){ 
  		fprintf(stderr,"Usage: </path/to/%s> <Unnecessary Argument>\n",argv[0]);
  		return USAGEERR;
  }
        return 1;
}

/* to detect spcae and enter */
int getCharacter(void); 



int main(int argc,char *argv[])
{
		
	   if( usage(argc, argv) == USAGEERR )
    		return USAGEERR;  // for Unnecessary Argument


       int  i,  LineNumber, flag ;
	   int  inputKeyboard;
       char Line[ 100 ] ; 
	   FILE *inputFromFile;  

	  
	   if( argc == 3 ){   // If the number of lines entered
	  		LineNumber = atoi( argv[ 1 ] );  
			inputFromFile = fopen( argv[ 2 ] , "r" );
			flag = 1;
	   } else {  // for default number of lines 
			LineNumber = DEFAULT_LINE ; 
			inputFromFile = fopen( argv[ 1 ] , "r" );
			flag = 0;
	   }


	   do{  
      	 
	  		for( i = 0 ; i < LineNumber ; ++i ){
      		
				if( fgets( Line, 100, inputFromFile ) == '\0' )
					exit ( 0 ) ;	 // if end of file   	
				printf("%s", Line ); 
			}

			do{
				inputKeyboard =  getCharacter() ;
				switch( inputKeyboard ){
					case '\n':  LineNumber = 1;  // if press enter
						break;
					case ' ':  {	
								if( flag )							
									LineNumber = atoi( argv[ 1 ] );
								else
									LineNumber = DEFAULT_LINE ;
						}break;  // if press space
				}	
		
			//  to detecet only Enter and Space
			}while( ! ( inputKeyboard == '\n' || inputKeyboard == ' ' ) );

		
	  } while( LineNumber );
      fclose( inputFromFile );	  	 
	  return 0;
}


/* Excerpt from the book to detect 'SPACE' directly. ( UNIX SYSTEMS PROGRAMMING )*/
int getCharacter(void)
{
  	int valueOfInput;
  	struct termios oldt;
  	struct termios newt;
  	
	tcgetattr( STDIN_FILENO, &oldt ); 
  	newt = oldt;
  	newt.c_lflag &= ~( ICANON | ECHO ); 
  	tcsetattr( STDIN_FILENO, TCSANOW, &newt ); 
  	valueOfInput = getchar(); 
  	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );  
	return valueOfInput ; 
}

