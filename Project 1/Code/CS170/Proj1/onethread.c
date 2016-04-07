#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/*
 * program to find the product of a matrix
 * which forks off a single thread to do the matrix computation
 */

char* Usage = "usage: my_matrix_multiply -a a_matrix_file.txt -b b_matrix_file.txt -t thread_count";
#define ARGS "a:b:t:"

#define RAND() (drand48()) /* basic Linux random number generator */

struct matrix
{
	int rows;
	int columns;
	double* data_array;
};

/*
 * data type definition for arguments passed to thread
 */
struct arg_struct
{
	int id;			    /* sequential thread ID */
	struct matrix *A;	/* A matrix */
	struct matrix *B;	/* B matrix */
	struct matrix *C;	/* C matrix holds the product */
};

/*
 * data type definition for results passed back from threads
 */
struct result_struct
{
	struct matrix *C; //I think?? not sure what would be here if we pass c in already
};

void *MatrixThread(void *arg)
{
	int i;
	int j;
	int k;
	int sum;
	int my_id;
	struct matrix *A;	
	struct matrix *B;	
	struct matrix *C;
	struct arg_struct *my_args;
	//int my_size;
	//double *my_data;
	struct result_struct *result;
	
	
	printf("matrix thread running\n");
	fflush(stdout);

	//unmarshal the arguments (A, B, and C matrix)
	my_args = (struct arg_struct *)arg;
	result = (struct result_struct *)malloc(sizeof(struct result_struct));
	if(result == NULL) {
		exit(1);
	}

	my_id = my_args->id;
	A = my_args->A;
	B = my_args->B;
	C = my_args->C;
	

	/*
	 * free the arg structure since it isn't needed any more
	 */
	free(my_args);
	
	//do error checking


	////do matrix multiply of A * B putting result in C
	for(i=0; i < A->rows; i++) {
		for(j=0; j < B->columns; j++) {
			sum=0;
           for(k=0;k<A->columns;k++){ //can use a->columns or b->rows
               sum=sum+A[i][k]*B[k][j];
            }
           C->C_data_array[i][j]=sum;
		}
	}

	result->matrix = C;
	printf("matrix thread done, returning\n");
	fflush(stdout);

	return((void *)result);
}

void printMatrix(struct matrix* matrix) {
  int i, j;
  for(i=0; i<matrix->rows; i++) {
    for(j=0; j<matrix->columns; j++) {
      printf("%lf  ", matrix->data_array[i][j]);
    }
    printf("\n");
  }
}


int main(int argc, char **argv)
{
	int my_id;
	struct arg_struct *args;
	pthread_t thread_id;
	struct result_struct *result;
	int err;
	struct matrix* A;
	struct matrix* B;
	struct matrix* C;
	
	//read in A matrix
	
	//read in B matrix
	
	//allocate C matrix (of the correct size)
	 C = (struct matrix*)malloc(sizeof(struct matrix));
     int C_data_array[A->rows][B->columns];
     C->data = &(C_data_array[0][0]);
	
	//allocate a thread_args structure
	args = (struct arg_struct *)malloc(sizeof(struct arg_struct));
	if(args == NULL) {
		exit(1);
	}
	//fill in the fields of the thread_args structure
	my_id = args->id;
	
	//pthread_create a thread that takes the thread_args structure
	printf("main thread forking matrix thread\n");
	fflush(stdout);
	err = pthread_create(&thread_id, NULL, SumThread, (void *)args);
	if(err != 0) {
		fprintf(stderr,"pthread create failed\n");
		exit(1);
	}
	printf("main thread running after matrix thread created, about to call join\n");
	fflush(stdout);

	
	//pthread_join with that thread
	err = pthread_join(thread_id,(void **)&result);
	if(err != 0) {
		fprintf(stderr,"pthread_join failed\n");
		exit(1);
	}
	printf("main thread joined with matrix thread\n");
	fflush(stdout);
	
	//print out the C matrix
	printMatrix(C);
	
	//free A, B, and C matrix 
	//free result?
	free(A);
	free(B);
	free(C);
	
	
	//exit
	return(0);


}
