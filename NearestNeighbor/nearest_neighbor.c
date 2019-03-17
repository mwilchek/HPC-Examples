#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#ifndef NUMBER_OF_POINTS
#define NUMBER_OF_POINTS 100
#endif

typedef struct { //struct to hold coordinates for each ordered-pair.
  double x,y;
} points;




int main(int argc, char **argv)
{

  srand(time(NULL));
  int *index_array = (int*) malloc(NUMBER_OF_POINTS * sizeof( int ));
  if (index_array == NULL ) { puts("Cannot Allocate Result Array.");exit(1);}
  points *p = (points*) malloc(NUMBER_OF_POINTS * sizeof(points));
  if (p == NULL ) { puts("Cannot Allocate points.");exit(1);}

// Comment out printf's to get speed up.
 
// Populate plane with points and write locations of points.
  FILE *locationsFile;
  if (NULL != (locationsFile = fopen ("locations.txt","w"))){
    for (int i = 0 ; i < NUMBER_OF_POINTS ; i++){
      p[i].x = rand()/(double)RAND_MAX;    
      p[i].y = rand()/(double)RAND_MAX;    
      fprintf(locationsFile,"%d %f %f \n",i,p[i].x,p[i].y);
    }
    fclose(locationsFile);
  }



// Find nearest neighbor iand w
  FILE *distancesFile;
  if (NULL != (distancesFile = fopen ("distances.txt","w"))){

  for (int i = 0 ; i < NUMBER_OF_POINTS ; i++){
    double previous = 2;// Initial reference point out at 'infinity'.
    double distance = 0;// Initial reference point as close as self.
    for (int j = 0 ; j < NUMBER_OF_POINTS ; j++){
      if ( j != i ){
	distance = (p[i].y-p[j].y)*(p[i].y-p[j].y);
	fprintf(distancesFile,"%f\n",distance);
        if ( distance < previous ){ 
           previous = distance;
           index_array[i] = j;
        }
      } 
    }
  }
    fclose(distancesFile);
  }


  
// Write out indices of nearest neighbor to ith point.
  FILE *resultFile;
  if (NULL != (resultFile = fopen ("NearestResults.txt","w"))) {
    for (int i = 0 ; i < NUMBER_OF_POINTS ; i++){
      fprintf(resultFile,"%d\n",index_array[i]);
    }
    fclose(resultFile);
  }


// This section basically writes out a crude gnuplot script, lines.gp, which can be called using you guessed it -- gnuplot.
  FILE *linesFile;
  if( NULL != (linesFile = fopen ("lines.gp","w"))){
    fprintf(linesFile,"reset\n");
    fprintf(linesFile,"set title '100 Points' \n");
    for (int i = 0 ; i < NUMBER_OF_POINTS ; i++){
      fprintf(linesFile,"set arrow from %f,%f to %f,%f\n",p[i].x,p[i].y,p[index_array[i]].x,p[index_array[i]].y);
     }

    fprintf(linesFile,"set grid\n");
    fprintf(linesFile,"pl [0:1] [0:1]  'locations.txt' using 2:3:(2*($1+1)) pt 7 ps 2 ti ''\n");
     fclose(linesFile);
  }

// Clean up allocated memory
  free(index_array);
  free(p);
  return 0;
}
