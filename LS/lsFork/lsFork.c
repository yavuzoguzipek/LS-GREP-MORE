/*################################*/
/*						          */
/*       YAVUZ OGUZ IPEK		  */
/*							 	  */
/*		    lsFork.c    		  */
/*################################*/

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int ShowPid(); // to show pid
int printDirectory(const char *path, int valueForRecursive ); // to show directory


int main(int argc, const char* argv[]){

	printf("PID    PPID\t\tPATH\n---------------------------------------\n");
    printDirectory( argv[1], 1 );
    return 0;
}

int ShowPid(){

    printf("%d   %d", getpid(), getppid() );
    return 1;
}


int printDirectory(const char *path, int valueForRecursive )
{
	int status = 0;
    struct dirent *direntp = NULL;
    DIR *dirp = NULL;
    size_t pathLenght;

    if (!path)  // to check path
        return -1; 

    pathLenght = strlen(path);  

    if ( ( pathLenght > _POSIX_PATH_MAX ) || !path || !pathLenght  )
        return -1;

    dirp = opendir( path );  /*  to open directory */

    if ( dirp == NULL )  /* if directory does not open*/
		return -1; 

    while ( ( direntp = readdir( dirp ) ) != NULL) {  // to read directory
		
        struct stat fstat;
        char PathName[ _POSIX_PATH_MAX + 1 ];

		/* to check lenght of  path nameslimit */
         if ( ( pathLenght + strlen( direntp->d_name) + 1 ) > _POSIX_PATH_MAX )
            continue;

        strcpy( PathName, path );   
		 
        if ( PathName[ pathLenght - 1] != '/' ) 
            strcat( PathName, "/" );  
        strcat( PathName, direntp->d_name );
		
		
        /* to pass special  directories. */
        if ( ( strcmp( direntp->d_name , "." ) == 0 ) || ( strcmp( direntp->d_name, ".." ) == 0 ) )
            continue;

        /* Print only if it is really directory. */
       if ( stat( PathName, &fstat ) < 0 )
            continue;

       if ( S_ISDIR( fstat.st_mode ) ){		// if directory
			
			pid_t pid = fork();	
			if( pid == 0 ){  
				ShowPid(); 
            	printf("   %s\n", PathName );  
            	if ( valueForRecursive )
                	printDirectory( PathName, 1 );     
				exit( 0 );
			}
		    wait( &status );

		} else{   // if  file
		
			if ( valueForRecursive ){   
				ShowPid(); 
				printf("   %s\n", PathName ); 
              	printDirectory( PathName, 1 ); 
			}
		} 
    }  

    closedir(dirp);   /* to close directory */
    return 0;
}
