#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
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

struct dimens {
  int rows;
  int cols;
};

struct matrix {
  int rows;
  int columns;
  double* data;
};

struct arg_struct {
  int id;
  int starting_i;
  int row_size;
  int starting_j;
  int col_size;
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
  int row_start_index;
  int row_end_index;
  int col_start_index;
  int col_end_index;
  struct matrix* A;
  struct matrix* B;
  struct matrix* C;

  // Unpack
  my_args = (struct arg_struct*) arg;
  row_start_index = my_args->starting_i;
  row_end_index = row_start_index + my_args->row_size;
  col_start_index = my_args->starting_j;
  col_end_index = col_start_index + my_args->col_size;
  A = my_args->A;
  B = my_args->B;
  C = my_args->C;
  free(my_args);

  // Compute result matrix
  for(i = row_start_index; i < row_end_index; i++) { // For each row in A
    for(b = col_start_index; b < col_end_index; b++) {// For each col in B
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
  int row_index;
  int col_index;
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

  // WE DON'T NEED TO USE ALL THE THREADS
  int rows = sqrt(thread_count);
  int cols = sqrt(thread_count);

  int real_thread_count = rows*cols; 
  thread_ids = (pthread_t *)malloc(sizeof(pthread_t)*real_thread_count);

  // The dimens of each sub matrix initially
  int row_range = A->rows / rows;
  int col_range = A->columns / cols;

  struct dimens* dimens_matrix = (struct dimens*) malloc(real_thread_count*sizeof(struct dimens));
  for(i=0; i<real_thread_count; i++) {
    dimens_matrix[i].rows = row_range;
    dimens_matrix[i].cols = col_range;
  }

  // The rows and columns that are currently unaccounted for
  int extra_cols = A->columns % cols;
  int extra_rows = A->rows % rows;

  // Distribute extra columns
  for(j=0; j<extra_cols; j++) {
    for(i=0; i<rows; i++) {
      dimens_matrix[i*cols+j].cols++; 
    }
  }
  // Distribute extra rows
  for(i=0; i<extra_rows; i++) {
    for(j=0; j<cols; j++) {
      dimens_matrix[i*cols+j].rows++; 
    }
  }
  
  row_index = 0;
  for(i=0; i<rows; i++) {
    col_index = 0;
    for(j=0; j<cols; j++) {
      //allocate an argument structure for each thread
      args = (struct arg_struct *)malloc(sizeof(struct arg_struct));
      args->starting_i = row_index;
      args->starting_j = col_index;
      args->id = (i*cols+j)+1;
      //printf("thread %d starting row is %d and start col is %d \n", args->id, row_index, col_index);
      args->row_size = dimens_matrix[i*cols+j].rows;
      args->col_size = dimens_matrix[i*cols+j].cols;
      //printf("thread %d computing %d by %d matrix \n", args->id, args->row_size, args->col_size);

      args->A = A;
      args->B = B;
      args->C = C;

      // Update the column index
      col_index += args->col_size;
      // Update the row index if we're at the last element of the row
      if(j == cols-1) {
        row_index += args->row_size;
      }

      err = pthread_create(&(thread_ids[i*cols+j]), NULL, ComputeRows, (void *)args);
    }
  }
  
  //printf("main thread about to create %d matrix threads\n", thread_count);
  //fflush(stdout);
  int t;
  for(t=0; t < real_thread_count; t++) {
    //printf("main thread about to join with matrix thread %d\n",t+1);
    //fflush(stdout);
    //join with each thread using pthread_join
    err = pthread_join(thread_ids[t],(void **)&result);
    //printf("main thread joined with matrix thread %d\n",t+1);
    //fflush(stdout);
  }
  
  //printMatrix(C->data, C->rows, C->columns);

  free(dimens_matrix);
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