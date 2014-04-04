#include "brisque.h"

int find_option( int argc, char **argv, const char *option )
{
    for( int i = 1; i < argc; i++ )
        if( strcmp( argv[i], option ) == 0 )
            return i;
    return -1;
}

int read_int( int argc, char **argv, const char *option, int default_value )
{
    int iplace = find_option( argc, argv, option );
    if( iplace >= 0 && iplace < argc-1 )
        return atoi( argv[iplace+1] );
    return default_value;
}

char *read_string( int argc, char **argv, const char *option, char *default_value )
{
    int iplace = find_option( argc, argv, option );
    if( iplace >= 0 && iplace < argc-1 )
        return argv[iplace+1];
    return default_value;
}


int  main(int argc, char** argv)
{
  
    if( find_option( argc, argv, "-h" ) >= 0 )
    {
        printf( "Options:\n" );
        printf( "-t <int> to specify if you want to retrain \n" );
        printf( "-im <filename> to specify the image file  name\n" );
        return 0;
    }
    
  int istrain    = read_int( argc, argv, "-t",1 );
  char *filename = read_string( argc, argv, "-im", NULL );


  float qualityscore;

  if(!istrain)
   trainModel();
  
  qualityscore = computescore(filename);
  cout<<"score in main file is given by:"<<qualityscore<<endl;
}
