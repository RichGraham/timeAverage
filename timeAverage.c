/*
  Reads in a list of files which comprise of two columns: time and quantity to be averaged
  Then computes the average of the 2nd column

  Usage : timeAverage [int expected averge] [list of files]
  Aug 2016 
*/


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//#include <time.h>

//#include "/Users/rsgraham/recipes_c-ansi/recipes/nrutil.h"
//#include "/Users/rsgraham/recipes_c-ansi/misc/nrutil.c"


#define MAX_NUM_FILES 75
#define MAX_NUM_POINTS 5000


int main(int argc, char *argv[] )
{
  long nPoints[MAX_NUM_FILES+1]={0}, currentFilePoints=0;
  double time[MAX_NUM_FILES][MAX_NUM_POINTS]={{0.0}};
  double yStored[MAX_NUM_FILES][MAX_NUM_POINTS]={{0.0}};
  double y_average;
  double timeValue, yValue;

  int i,j;//,j,k, skip=20, OUTLFLAG=0, currentFilePoints, ignore;
  
  FILE *inFilePtr;


  // check correct number of arguments
  if(argc<3){
    fprintf(stderr,"Expected a list of at least two files!!!\n");
    fprintf(stderr,"Usage: timeAverage [list of files]\n");
    exit(EXIT_FAILURE);
  }

  if(argc>MAX_NUM_FILES){
    fprintf(stderr,"We can't have more than %d files!!!\n",MAX_NUM_FILES);
    exit(EXIT_FAILURE);
  }
 
  
  
  fprintf(stderr,"Given %d files\n\n",argc-1);
  
 

  
  //______Read in all the data____
  for(i=1; i<=argc-1; i++) {
    if( ( inFilePtr = fopen( argv[i] , "r") ) == NULL ){
      fprintf(stderr,"Can't open file %s\n",argv[i]);
      exit(EXIT_FAILURE);
    }

    fprintf(stderr,"File %d open %s\n",i, argv[i] );

    //__________________Parse through the file_________________________
    currentFilePoints=0;
    while( !feof( inFilePtr )){
      fscanf(inFilePtr,"%le %le",&timeValue,&yValue);
      //fprintf(stderr,"%f %f\n", timeValue, yValue);
      currentFilePoints++;
      time[i][currentFilePoints] = timeValue;
      yStored[i][currentFilePoints] = yValue;
      //fprintf(stderr,"%f %f\n", time[i][currentFilePoints], yStored[i][currentFilePoints]);
    }

    currentFilePoints--;
    fprintf(stderr,"Found %ld points\n\n",currentFilePoints);
    
    if(currentFilePoints>MAX_NUM_POINTS){
      fprintf(stderr,"We can't have more than %d points in a file!!!\n",MAX_NUM_POINTS);
      exit(EXIT_FAILURE);
    }
  
    nPoints[i] = currentFilePoints;

    fclose(inFilePtr);
  }


  //Find the shortest file
  currentFilePoints = 10e5;
  for(i=1; i<=argc-1; i++) {
    //printf("%ld %ld\n",currentFilePoints, nPoints[i]);
    if( nPoints[i] <currentFilePoints ) currentFilePoints=nPoints[i];
  }

  fprintf(stderr,"Going to average over first %ld points\n",currentFilePoints);
  
  //______Check that times in all files agree_______
  for(i=1; i<=argc-2; i++) {



    
    


    //loop over all lines of the file
    for(j=1; j<=currentFilePoints ; j++){

      //Do all time values agree?
      if( fabs(  time[i][j] - time[i+1][j]  )    >    1e-7){
	fprintf(stderr,"Times at point %d in files %s and %s are different: %lf %lf\n",j,argv[i],argv[i+1],
	       time[i][j] ,time[i+1][j]);
	exit( EXIT_FAILURE);
      }
      
    }//loop over all lines of the file (j)
  

  }//loop over all files to perform checks


  
  //______Make the average___
  //loop over all lines of the file
  for(j=1; j<=currentFilePoints ; j++){
    y_average = 0.0;

    for(i=1; i<=argc-1; i++) {   
      y_average += yStored[i][j];      
    }//loop over all files (i) to perform average
    printf("%lf %lf\n",time[1][j], y_average/(argc-1));

  }//loop over all lines of the files
  
    
  
  return 0;
  
}
