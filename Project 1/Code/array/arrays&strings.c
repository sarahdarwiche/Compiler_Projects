#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//string is null terminated
void reverse ( char* string ) {
	int forward_ctr;
	int backward_ctr;
	int string_len;
	char* forward_val;
	char* reverse_val;
	char* temp_val;
	
	string_len = strlen(string);
	forward_ctr = 0;
	backward_ctr = string_len;
	
	forward_val = string[0];
	reverse_val = string[string_len];
	
	if( (forward_ctr <= string_len/2) && (backward_ctr <= strlen/2) ){
		
		temp_val = forward_val;
		forward_val = reverse_val;
		reverse_val = temp;
		
		forward_ctr++;
		backward_ctr--;
	}
}

void test_reverse( char* string ){
	printf( "Original String is: %s \n", string );
	printf( "Reversed String is: %s \n", reverse(string) );
}

int unique( char* string ){
  return 0;
}

int permutation(char* string1, char* string2){
  return 0;
}

void replace_spaces(char* string, char* new_space){
}

int main(int argc, char* argv[]){
  
  char* sentence = "Hello world."
  test_reverse(sentence);
  
  
  return 0;
}