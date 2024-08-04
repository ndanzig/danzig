#include <stdio.h>

int main()
{
  long int dim1, dim2;
  int i=0, j=0;

  int *array1; 
  int **array2; 

  printf("let's make a 1-D array. Enter the size: "  ); //like cout
  scanf("%d",&dim1 );//like cin>>dim1;

  array1= new int[dim1];//allocate memory to the array pointer
  for(;i<dim1;i++)//put some values into the array
       array1[i]=i;
 
  printf("\nSuccess!! "  );
  printf("\nThe values in your 1-D array are: "  );
  for(i=0;i<dim1;i++)
    printf("\nPlace %d has value: %d", i, array1[i] );
  
  printf("\nDeleting!! "  );
  delete array1; //delete the memory (not the pointer)

 start2d:  //label for the goto
  printf("\nNow, let's make a 2-D array. Enter first dimension: "  );
  scanf("%d",&dim1 );
  printf("\nEnter second dimension: "  );
  scanf("%d",&dim2 );
 
  if ( dim1 * dim2 >  1000000  ) 
    {
      printf("\nAre you crazy? You asked for %d mb of memory. Choose a smaller amount\n", dim1 * dim2 * 4 / (1024 * 1024) );
      goto start2d; //really using goto is bad, but I want you to see an example of it
    }
  
  array2 = new int*[dim1]; //create an array of pointers 
  
  for( i=0;i<dim1;i++)
    array2[i] = new int[dim2]; //have each pointer point to an array
  
  printf("\nSuccess!! "  );
  
  for( i=0;i<dim1;i++)
    {
      for(j=0;j<dim2;j++)
	array2[i][j]=i; //assign values to the array
    }
  
  
  printf("\nThe values in your 2-D array are: \n"  );
  for(i=0;i<dim1;i++)
    {
      for(j=0;j<dim2;j++)
	printf("%d  ", array2[i][j]);
      printf("\n");
    }
  
  printf("\nDeleting!! \n"  );
  //delete everything I created with "new"
  for(i=0;i<dim1;i++)
    delete array2[i]; //delete each array
  
  delete array2; //delete the array of pointers
  
  return 1;
}
