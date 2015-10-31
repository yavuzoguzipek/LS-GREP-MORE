/*################################*/
/*						          */
/*       YAVUZ OGUZ IPEK		  */
/*							 	  */
/*		   lsNoFork.c    		  */
/*################################*/

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

int printDirectory( const char *path ,  int valueForRecursive );

int main(int argc, const char* argv[]){

	printf("PID\t\t    PATH\n---------------------------------------\n");
    printDirectory( argv[1], 1 );
    return 0;
}


// to find directory and file
int printDirectory( const char *path , int valueForRecursive ){

    struct dirent *direntp = NULL;
    DIR *dirp = NULL;
    size_t pathLenght;
	
    if ( !path )  // to check path
        return -1;

    pathLenght = strlen(path);  

    if ( ( pathLenght > _POSIX_PATH_MAX ) || !path || !pathLenght )
        return -1;

    
    dirp = opendir( path );  /*  to open directory */

    if ( dirp == NULL )  /* if directory does not open*/
        return -1;

    while ( ( direntp = readdir( dirp ) ) != NULL) {  // to read directory
            
        struct stat fstat;
        char PathName[_POSIX_PATH_MAX + 1];

        /* to check lenght of  path nameslimit */
        if ((pathLenght + strlen(direntp->d_name) + 1) > _POSIX_PATH_MAX)
            continue;

        strcpy( PathName, path );
        if ( PathName[ pathLenght - 1 ] != '/' )
            strcat( PathName,  "/" );
        strcat( PathName, direntp->d_name );

		
        /* to pass special  directories. */
        if ( ( strcmp( direntp->d_name, "." ) == 0 ) || ( strcmp( direntp->d_name , ".." ) == 0 ) )
            continue;


        if ( stat( PathName, &fstat ) < 0 )
            continue;
        
        printf( "%d    %s\n", getpid() , PathName );
        if ( valueForRecursive )
            printDirectory( PathName, 1 );
        
    }

    closedir( dirp );    /* to close directory */
    return 0;
}
