#include <unistd.h> //???
#include <std.lib>
#include <stdio.h>
#include < pthread.h >

#define RAND() (drand48()) /* basic Linux random number generator */

struct matrix
{
	int rows;
	int columns;
	double* data;
};

struct matrix* simple_matrix_multiply(struct matrix* a, struct matrix* b){

    struct matrix* c;
    int i;
    int j;
    int sum;
    
    c = (struct matrix*)malloc(sizeof(struct matrix));
    int c_data_array[a->rows][b->columns];
    c->data = &(c_data_array[0][0]);
    
	//assuring correctness
	if(a->columns != b->rows){
	 printf("Error product not defined.");
	 return 0;
	}
	
	for(i=0; i < a->rows; i++) {
		for(j=0; j < b->columns; j++) {
			sum=0;
           for(k=0;k<a->columns;k++){ //can use a->columns or b->rows
               sum=sum+a[i][k]*b[k][j];
            }
           c->c_data_array[i][j]=sum;
		}
	}
	
	return c;
};
int main(int argc, char **argv)
{

	struct matrix* a;
	struct matrix* b;
	struct matrix* c;
	int thread_count;
	
	
	//allocate two matrices of fairly large size
	a = (struct matrix*)malloc(sizeof(struct matrix));
	b = (struct matrix*)malloc(sizeof(struct matrix));
	
	//malloc correct array size based on rows and cols
	int a_data_array[a->rows][a->columns];
	int b_data_array[b->rows][b->columns];
	a->data = &(a_data_array[0][0]);
	b->data = &(b_data_array[0][0]);
	
	//fill in matrices with random numbers
	for(i=0; i < a->rows; i++) {
		for(j=0; j < a->columns; j++) {
			a->a_data_array[i*a->columns+j] = RAND();
		}
	}
	
	for(i=0; i < b->rows; i++) {
		for(j=0; j < b->columns; j++) {
			b->b_data_array[i*b->columns+j] = RAND();
		}
	}
	
	//call matrix multiply to get the product
	c = simple_matrix_multiply(a,b);

	//free the matrices and the product
	free(a);
	free(b);
	free(c);
	return(0);
}
