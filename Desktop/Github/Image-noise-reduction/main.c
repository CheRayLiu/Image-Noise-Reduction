#include <stdio.h>
#include <stdlib.h>
#include "filter.h"

extern double getTime(int flag);
int main(int argc, char* argv[]  ) 
{
  if (argc < 5){
      printf("Usage: ./denoise input.ppm output.ppm N F\n");
      return 0;
    } /*Prints Usage if # of argument is wrong*/
  /*Obtain input bounds */
  int width, height,max;
  int n = atoi(argv[3]);
  char f = argv[4][0];
  char buffer[10];
  FILE *old_file;
  old_file = fopen(argv[1],"rb");
  if (old_file == NULL){
    printf("Could not read specified file");
    return 0;
  }
  
  fscanf(old_file, "%s %d %d %d", buffer, &width, &height, &max);
  /*printf( "%d %d %d \n", width,height,max);*/
  
  fclose(old_file);

  printf("Reading file %s\n", argv[1] );
  double time = getTime(1);
  RGB *read = readPPM(argv[1], &width, &height,&max);
  time = getTime(1)-time ;
  printf("*** %s read in  %1.e seconds\n\n", argv[1],time);

  filter type;
  if (f == 'A')
  {
     type = MEAN;
     printf("Processing %d x %d using %d x %d window and mean filter\n",width, height,n, n ); 
  }

  else if (f== 'M')
  {
    type = MEDIAN; 
    printf("Processing %d x %d using %d x %d window and median filter\n",width, height,n, n ); 
  }

  time = getTime(1);
  RGB *filter = denoiseImage(width, height, read, n, type);
  time = getTime(1)- time;
  printf("*** image processed in %.1e seconds\n\n", time);


  printf("Writing file %s\n", argv[2]);
  time = getTime(1);
  writePPM(argv[2], width, height, max, filter);
  time = getTime(1) -time;
  printf("*** %s written in %.1e seconds\n\n", argv[2],time);

  
  

  return 0;
}    