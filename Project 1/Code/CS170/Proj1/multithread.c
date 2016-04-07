#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>

double CTimer() {
	struct timeval tm;

	gettimeofday(&tm,NULL);
	return((double)tm.tv_sec + (double)(tm.tv_usec/1000000.0));
}



char* Usage = "usage: my_matrix_multiply -a a_matrix_file.txt -b b_matrix_file.txt -t thread_count";
#define ARGS "a:b:t:"
typedef enum {
  COMMAND, FILE_ERR, FIRSTLINE, DIMENS, NOMATCH
} Error_Type;

struct matrix {
  int rows;
  int columns;
  double* data;
};

struct arg_struct {
  int id;
  int starting_i;
  int size;
  struct matrix* A;
  struct matrix* B;
  struct matrix* C;
};

void printMatrix(double* matrix, int row, int col);
void readFile(char* file_A, char* file_B, struct matrix* a, struct matrix* b);
void InputError(Error_Type err, char* str);


void* ComputeRows(void* arg) {
  int i; // current row
  int j; // current col (in A), also the current row (in B)
  int b; // current col (in B)
  double sum;

  struct arg_struct* my_args;
  int start_index;
  int end_index;
  struct matrix* A;
  struct matrix* B;
  struct matrix* C;

  // Unpack
  my_args = (struct arg_struct*) arg;
  start_index = my_args->starting_i;
  end_index = start_index + my_args->size;
  A = my_args->A;
  B = my_args->B;
  C = my_args->C;
  free(my_args);

  // Compute result matrix
  for(i = start_index; i < end_index; i++) { // For each row in A
    for(b=0; b < B->columns; b++) {// For each col in B
      // Get the sum of multiples
      sum = 0;
      for(j = 0; j < A->columns; j++) {
        sum += A->data[i*A->columns+j] * B->data[j*B->columns+b];
      }
      // Set the result
      C->data[i*C->columns+b] = sum;
    }
  }
  return NULL;
}

int main(int argc, char** argv) {
  int c;
  int i;
  int j;
  int thread_count;
  char* file_A;
  char* file_B;
  struct matrix* A;
  struct matrix* B;
  struct matrix* C;
  int err;
  pthread_t* thread_ids;
  int id;
  int extra;
  int range_size;
  int* result;
  int index;
  int t;
  struct arg_struct* args;
   double start_time;
  double end_time;
  double total_time;
  
  start_time = CTimer();

  // Get arguments
  while((c = getopt(argc, argv, ARGS)) != EOF) {
    switch(c) {
      case 'a': // Matrix A
        file_A = optarg;
        break;
      case 'b': // Matrix B
        file_B = optarg;
        break;
      case 't': // Thread count
        thread_count = atoi(optarg);
        break;
      default:
        InputError(COMMAND, optarg);
    }
  }

  if(thread_count <= 0) {
    InputError(COMMAND, NULL);
  }

  // Allocate A and B and fill the matrices
  A = (struct matrix*) malloc(sizeof(struct matrix));
  B = (struct matrix*) malloc(sizeof(struct matrix));
  readFile(file_A, file_B, A, B);

  // Allocate C
  C = (struct matrix*) malloc(sizeof(struct matrix));
  C->rows = A->rows;
  C->columns = B->columns;
  C->data = (double*) malloc(C->rows*C->columns*sizeof(double));

  /* divide the rows of the C matrix up by the number of threads
   * make sure that each row belongs to exactly one thread 
   * (taking care of the case where the number of threads does not divide the number of rows evenly)
   */
  
  thread_ids = (pthread_t *)malloc(sizeof(pthread_t)*thread_count);
  extra = A->rows % thread_count;
  range_size = A->rows/thread_count;
  
  index = 0;
  for(t=0; t < thread_count; t++) {
    
    //allocate an argument structure for each thread
    args = (struct arg_struct *)malloc(sizeof(struct arg_struct));
    args->starting_i = index;
    
    //fill it in with that threads specific information and pointers to the A,B, and C matrix
    args->id = (t+1);
    args->size = range_size;
    if(extra != 0){
      args->size++;
      index++;
      extra--;
    }
    
    args->A = A;
    args->B = B;
    args->C = C;
    
    //printf("main thread creating matrix thread %d\n", t+1);
    //fflush(stdout);
    
    //spawn each thread using pthread_create
    err = pthread_create(&(thread_ids[t]), NULL, ComputeRows, (void *)args);
    //printf("main thread has created matrix thread %d\n", t+1);
    index += range_size;
  }
  
  //printf("main thread about to create %d matrix threads\n", thread_count);
  //fflush(stdout);
  
  for(t=0; t < thread_count; t++) {
    //printf("main thread about to join with matrix thread %d\n",t+1);
    //fflush(stdout);
    //join with each thread using pthread_join
    err = pthread_join(thread_ids[t],(void **)&result);
    //printf("main thread joined with matrix thread %d\n",t+1);
    //fflush(stdout);
  }

  //printMatrix(C->data, C->rows, C->columns);

  free(C);
  end_time = CTimer();
  total_time = end_time - start_time;
  printf("program took %f amount of time\n", total_time);
  return 0;
}

/* Prints the given matrix to stdout
 * In the same format as input. Comments separate each row. */
void printMatrix(double* matrix, int row, int col) {
  int i, j;
  printf("%d %d\n", row, col);
  for(i=0; i<row; i++) {
    printf("# Row %d\n", i);
    for(j=0; j<col; j++) {
      printf("%lf\n", matrix[i*col+j]);
    }
  }
}

/* Takes in a filenames, opens the files, allocates matrices, reads into matrices.
 * Ignores all comments starting with '#'.
 * The first line that is not a comment is the matrix dimensions. */
void readFile(char* file_A, char* file_B, struct matrix* A, struct matrix* B) {
  FILE *ifpA, *ifpB;
  char buff[1000];
  int i;
  int j;
  int success;
  char* ptr;

  ifpA = fopen(file_A, "r");
  if(ifpA == NULL) {
    InputError(FILE_ERR, file_A);
  }
  ifpB = fopen(file_B, "r");
  if(ifpB == NULL) {
    InputError(FILE_ERR, file_B);
  }

  // Get matrix dimensions
  while(fgets(buff, 1000, ifpA)!=NULL) {
    if(buff[0] == '#') continue;
    else if(sscanf(buff, "%d %d \n", &(A->rows), &(A->columns)) != 2) {
      InputError(FIRSTLINE, file_A);
    }
    else break;
  }
  while(fgets(buff, 1000, ifpB)!=NULL) {
    if(buff[0] == '#') continue;
    if(sscanf(buff, "%d %d \n", &(B->rows), &(B->columns)) != 2) {
      InputError(FIRSTLINE, file_B);
    }
    else break;
  }

  // Compare the dimensions, check for multiplication possibility
  if(A->columns != B->rows) {
    InputError(DIMENS, NULL);
  }

  // Allocate both matrices
  A->data = (double*) malloc(A->rows*A->columns*sizeof(double));
  B->data = (double*) malloc(B->rows*B->columns*sizeof(double));

  // Go through A file line by line
  for(i=0; i<A->rows; i++) {
    for(j=0; j<A->columns; j++) {
      success = 0;
      while(fgets(buff, 1000, ifpA)!=NULL) {
	// Remove spaces and look at first word
	ptr = strtok(buff, " ");
	if(ptr[0] == '#' || ptr[0] == '\n')
	  continue;
	else if(sscanf(ptr, "%lf\n", &(A->data[i*A->columns+j])) != 1)
	  InputError(NOMATCH, file_A);
	else {
	  success = 1;
	  break;
	}
      }
      if(!success) InputError(NOMATCH, file_A);
    }
  }

  // Go through B file line by line
  for(i=0; i<B->rows; i++) {
    for(j=0; j<B->columns; j++) {
      success = 0;
      while(fgets(buff, 1000, ifpB) != NULL) {
	ptr = strtok(buff, " ");
	if(ptr[0] == '#' || ptr[0] == '\n')
	  continue;
	if(sscanf(ptr, "%lf\n", &(B->data[i*B->columns+j])) != 1)
	  InputError(NOMATCH, file_B);
	else {
	  success = 1;
	  break;
	}
      }
      if(!success) InputError(NOMATCH, file_B);
    }
  }
  fclose(ifpA);
  fclose(ifpB);
}

/* Controls error messages using Error_Type.
 * Takes in a string value to utilize in error message. */
void InputError(Error_Type err, char* str) {
  switch(err) {
    case COMMAND:
      fprintf(stderr, "unrecognized command %s\n", str);
      fprintf(stderr, "usage: %s", Usage);
      exit(1);
      break;
    case FILE_ERR:
      fprintf(stderr, "Cannot open input file %s\n", str);
      exit(1);
      break;
    case FIRSTLINE:
      fprintf(stderr, "Improper format for matrix dimens of %s\n", str);
      exit(1);
      break;
    case DIMENS:
      fprintf(stderr, "Matrix dimensions do not allow matrix multiplication\n");
      exit(1);
      break;
    case NOMATCH:
      fprintf(stderr, "File data does not match matrix dimensions given in %s\n", str);
      exit(1);
      break;
  }
}