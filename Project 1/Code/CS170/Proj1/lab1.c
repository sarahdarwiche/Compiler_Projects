#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

char* Usage = "usage: my_matrix_multiply -a a_matrix_file.txt -b b_matrix_file.txt -t thread_count";
#define ARGS "a:b:t:"
typedef enum {
  COMMAND, FILE_ERR, FIRSTLINE, DIMENS, NOMATCH
} Error_Type;

double** matrix_B; // The matrix on the right of the computation.
int B_row_count;
int B_col_count;

double** matrix_A; // The matrix on the left of the computation.
int A_row_count;
int A_col_count;

struct arg_struct {
  int i;           // The starting index
  int row_count;   // The number of rows to process
  int col_count;   // The number of columns to process
};

struct result_struct {
  int row_count;   // The number of rows in the result
  double** data;   // Contains the resulting rows
};

void printMatrix(double** matrix, int row, int col);
void readFile(char* file_A, char* file_B);
void InputError(Error_Type err, char* str);

/* The threaded version of matrix multiplication. Takes in an arg_struct.
   Access matrix_A and matrix_B (read-only) to compute. */
void* ComputeRows(void* arg) {
  int p;
  int i; // current row
  int j; // current col (in A), also the current row (in B)
  int b; // current col (in B)
  double sum;

  struct arg_struct* my_args;
  int start_index;
  int row_count;
  int col_count;

  struct result_struct* result;
  double** result_matrix;

  // Unpack
  my_args = (struct arg_struct*) arg;
  start_index = my_args->i;
  row_count = my_args->row_count;
  col_count = my_args->col_count;
  free(my_args);

  // Allocate result matrix
  result = (struct result_struct*) malloc(sizeof(struct result_struct));
  result_matrix = (double**) malloc(row_count*sizeof(double*));
  for(p=0; p<row_count; p++) {
    result_matrix[p] = (double*) malloc(B_col_count*sizeof(double));
  }

  // Compute result matrix
  for(i=start_index; i<row_count; i++) { // For each row in A
    for(b=0; b<B_col_count; b++) {// For each col in B
      // Get the sum of multiples
      sum = 0;
      for(j=0; j<col_count; j++) {
        sum += matrix_A[i][j] * matrix_B[j][b];
      }
      // Set the result
      result_matrix[i][b] = sum;
    }
  }
  result->data = result_matrix;
  result->row_count = row_count;

  return ((void*) result);
}

void testCompute() {
  // TODO Manually set global variables and call ComputeRow
}

int main(int argc, char** argv) {
  int c;
  int i;
  int j;
  int thread_count;
  char* file_A;
  char* file_B;

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

  // The commented section below was Jenny testing the file i/o and compute rows function
  // Still have tested with threads.
  /*
  readFile(file_A, file_B);
  struct arg_struct* args = (struct arg_struct*) malloc(sizeof(struct arg_struct));
  args->i = 0;
  args->row_count = A_row_count;
  args->col_count = A_col_count;
  void* r = ComputeRows((void*)args);
  struct result_struct* res = (struct result_struct*) r;
  printMatrix(res->data, A_row_count, B_col_count);
  */

  // TODO Distribute to threads

  // TODO Get result data from threads

  // TODO Print result to stdout with input format

  return 0;
}

void printMatrix(double** matrix, int row, int col) {
  int i, j;
  for(i=0; i<row; i++) {
    for(j=0; j<col; j++) {
      printf("%lf  ", matrix[i][j]);
    }
    printf("\n");
  }
}

/* Takes in a filenames, opens the files and reads into the global values. */
void readFile(char* file_A, char* file_B) {
  FILE *ifpA, *ifpB;
  char buff[1000];
  int i;
  int j;

  ifpA = fopen(file_A, "r");
  if(ifpA == NULL) {
    InputError(FILE_ERR, file_A);
  }
  ifpB = fopen(file_B, "r");
  if(ifpB == NULL) {
    InputError(FILE_ERR, file_B);
  }

  // Get matrix dimensions
  if(fgets(buff, 1000, ifpA)!=NULL) {
    if(sscanf(buff, "%d %d \n", &A_row_count, &A_col_count) != 2) {
      InputError(FIRSTLINE, file_A);
    }
  }
  if(fgets(buff, 1000, ifpB)!=NULL) {
    if(sscanf(buff, "%d %d \n", &B_row_count, &B_col_count) != 2) {
      InputError(FIRSTLINE, file_B);
    }
  }

  // Compare the dimensions, check for multiplication possibility
  if(A_col_count != B_row_count) {
    InputError(DIMENS, NULL);
  }

  // Allocate both global matrices
  matrix_A = (double**) malloc(A_row_count*sizeof(double*));
  for(i=0; i<A_row_count; i++) {
    matrix_A[i] = (double*) malloc(A_col_count*sizeof(double));
  }
  matrix_B = (double**) malloc(B_row_count*sizeof(double*));
  for(i=0; i<B_row_count; i++) {
    matrix_B[i] = (double*) malloc(B_col_count*sizeof(double));
  }

  // Go through A file line by line
  for(i=0; i<A_row_count; i++) {
    if(fgets(buff, 1000, ifpA)==NULL) InputError(NOMATCH, file_A);
    if(buff[0] != '#') InputError(NOMATCH, file_A);
    for(j=0; j<A_col_count; j++) {
      if(fgets(buff, 1000, ifpA)==NULL) InputError(NOMATCH, file_A);
      if(sscanf(buff, "%lf \n", &(matrix_A[i][j])) != 1) InputError(NOMATCH, file_A);
    }
  }
  // If there is more in the file besides comments, then error
  while(fgets(buff, 1000, ifpA) != NULL) {
    if(buff[0] != '#')
      InputError(NOMATCH, file_A);
  }

  // Go through B file line by line
  for(i=0; i<B_row_count; i++) {
    if(fgets(buff, 1000, ifpB)==NULL) InputError(NOMATCH, file_B);
    if(buff[0] != '#') InputError(NOMATCH, file_B);
    for(j=0; j<B_col_count; j++) {
      if(fgets(buff, 1000, ifpB)==NULL) InputError(NOMATCH, file_B);
      if(sscanf(buff, "%lf \n", &(matrix_B[i][j])) != 1) InputError(NOMATCH, file_B);
    }
  }
  // If there is more in the file besides comments, then error
  while(fgets(buff, 1000, ifpB) != NULL) {
    if(buff[0] != '#')
      InputError(NOMATCH, file_B);
  }
}

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