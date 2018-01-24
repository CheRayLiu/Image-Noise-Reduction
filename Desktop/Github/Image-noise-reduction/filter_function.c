#include <stdio.h>
#include <stdlib.h>
#include "filter.h"

RGB *readPPM(const char *file, int *width, int *height, int *max){
	char  buffer[5] ;// buffers that will store the type, size and max 
	RGB *img = malloc( sizeof(RGB)*(*width)*(*height));
	FILE *fp;
	fp  = fopen(file,"rb");
	fscanf(fp, "%s", buffer);
	
	int *data = malloc(3*sizeof(int)*(*width)*(*height));
	int *p= data;
	int i =0;
	while (!feof (fp))
    {  
      
      fscanf (fp, "%d", data);
      data++;    
    }
    p++; p++; p++;
    for (int i=0; i<(*height); i++)
    {
    	for (int j=0; j<(*width); j++)
    	{
    		img[i*(*width)+j].r=(unsigned char)(*p);
    		p++;
    		img[i*(*width)+j].g=(unsigned char)(*p);
    		p++;
    		img[i*(*width)+j].b=(unsigned char)(*p);
    		p++;
    		
    	}

    }
    
    fclose(fp);
	return img;
}

/* writePPM writes an image into a file.
   Input:
      file   name of the file
      width  width of the image
      height height of the image
      max    largest RGB value
      image  pointer to an array of size width*height with RGB values
*/
void writePPM(const char *file, int width, int height, int max,
              const RGB *image){
	FILE *fp;
	fp = fopen(file,"wb");
	fputs( "P3", fp );
	fputs( "\n", fp );
	fprintf(fp, "%d %d",width,height);
	fputs( "\n", fp );
	fprintf(fp, "%d ",max );
	fputs( "\n", fp );
		for (int i=0; i<(height); i++)
    {
    	for (int j=0; j<(width); j++)
    	{
    		
    		fprintf(fp, "%d %d %d ",image[width*i+j].r,image[width*i+j].g,image[width*i+j].b );
    		
    	}
    	fputs( "\n", fp );

    }
  	
    fclose(fp);
}

/* Function to sort an array using insertion sort*/
int findMedian(int *arr, int n)
{
   int i, key, j;
   for (i = 1; i < n; i++)
   {
       key = arr[i];
       j = i-1;
       while (j >= 0 && arr[j] > key)
       {
           arr[j+1] = arr[j];
           j = j-1;
       }
       arr[j+1] = key;
   }
   if(n%2==0) {
        // if there is an even number of elements, return mean of the two elements in the middle
   		
        return((arr[n/2] + arr[n/2 - 1]) / 2);
    } else {
        // else return the element in the middle
        
        return arr[n/2];
    }
}
/* denoiseImage applies filtering to an image.
   Input:
      width  width of the image
      height height of the image
      max    largest RGB value
      image  pointer to an array of size width*height with RGB values
      n      size of filtering window
      f      type of filtering: MEAN or MEDIAN

   denoiseImage returns a pointer to an arrary of size width*height containing the new image.
*/

RGB *denoiseImage(int width, int height, const RGB *image, int n, filter f)

{RGB *newimg = malloc( sizeof(RGB)*(width)*(height));
	

	if ( f == MEAN)
		{	
			for (int row=0; row<height; row++)
		    {
		    		for (int column=0; column<width; column++)
		    		{	int sumr=0;
		    			int sumg=0;
		    			int sumb=0;
		    			int count=0;
		    		    for (int i=row-(n/2); i<row+(n/2)+1; i++)
    					{
	    							for (int j=column-(n/2); j<column+(n/2)+1; j++)
			    						{ 
			    							
			    							if ((j > -1 && j < height) && (i > -1 && i < height) )
				    						{   
				    							sumr+=image[i*width+j].r;
								    			sumg+=image[i*width+j].g;
								    			sumb+=image[i*width+j].b;
								    			count+=1;

				    						}
	    		
	    								}
	    						
    	   				}		
    	   				
    	   				newimg[row*(width)+column].r=sumr/count;
    					newimg[row*(width)+column].g=sumg/count;
    					newimg[row*(width)+column].b=sumb/count;	
    	   				
		    		}
		 	}

			return newimg;
		 }
	if ( f == MEDIAN)
		{	int print = 0;
			
			for (int row=0; row<height; row++)
		    {
		    		for (int column=0; column<width; column++)

		    		{	
						int data_r[n*n];
						int data_g[n*n];
						int data_b[n*n];
						int count=0;

		    				for (int i=row-(n/2); i<row+(n/2)+1; i++)
    						{
    							
								for (int j=column-(n/2); j<column+(n/2)+1; j++)
					    			{
					    				if  (((i) > -1 && (i) < height)&&((j) > -1 && (j) < height))
					    					{
					    									
							    				data_r[count]=image[i*width+j].r;
											    data_g[count]=image[i*width+j].g;
											    data_b[count]=image[i*width+j].b;
											    count+=1;	
				    						}
		    						}
							}
						newimg[row*(width)+column].r=findMedian(data_r, count);
						newimg[row*(width)+column].g=findMedian(data_g, count);
						newimg[row*(width)+column].b=findMedian(data_b, count);
		    		}
		 	}
		 return newimg;
		}
} 
