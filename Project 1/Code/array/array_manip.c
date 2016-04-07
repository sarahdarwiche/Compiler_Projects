#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdbool.h"
#include "array_manip.h"


//string is null terminated
void reverse ( char* string ) {
	char* begin;
	char* end;
	int length;
	int c;
	char temp;
	
	printf( "Original String is: %s \n", string );
	
	length = strlen(string) ;
	begin  = string;
    end    = begin + length -1 ;
		
   while (end > begin)
   {        
      temp   = *begin;
      *begin= *end;
      *end = temp;
 
      begin++;
      end--;
   }
	printf( "Reversed String is: %s \n", string );
	
}

void palindrome( char* string){
	int length;
	char* start;
	char* end;
	int success = 0;
	
	length = strlen(string);
	start = string;
	end = string + length - 1;
	
	while( end > start){
		if( *start != *end ){
		  success = -1;
	      break;
	     }
		end--;
		start++;
	}
	
	if(success == 0) printf("%s is a palindrome!\n", string);
	else
		printf("%s is NOT a palindrome!\n", string);
}

void fill_spaces(char* string, char c){
	int i;
	int length;
	
	length = strlen(string);
	
	printf( "Unfilled String is: %s \n", string);
	
	for( int i = 0; i < length; i++){
	 	if(string[i] == ' ') string[i] = c;
	}
	
	printf( "Filled String is: %s \n", string);
}

void swap_no_temp(int a, int b){
  printf("a was %d before swap \n" , a);
  printf("b was %d before swap \n" , b);
  
  a = a + b;
  b = a - b;
  a = a - b;
  
  printf("a is now %d \n" , a);
  printf("b is now %d \n" , b);
  
}

int multiply_without_mult(int a, int b){
  int result;
  int i;
  
  result = 0;
  
  for(i = 0; i < b; i++){
  	result = result + a;
  }
   
  return result;
}
struct countIndex {
   int count;
   int index;
};
//We can augment the count array by storing not just counts but also the index of the first time you encountered the 
//character e.g. (3, 26) for ‘a’ meaning that ‘a’ got counted 3 times and the first time it was seen is at position 26. 
//So when it comes to finding the first non-repeater, we just have to scan the count array, instead of the string. 
//Following is C implementation of the extended approach that traverses the input string only once. O(n)
void unique_char(char* string){
 
  int i;
  int length;
  char unique;
  bool all_unique = true;
  struct countIndex *count = (struct countIndex *)calloc(sizeof(struct countIndex), 256); //calloc initializes mem to 0
  length = strlen(string);
  
  
  //for(i=0; i<length; i++){
  for(i=0; *(string+i); i++){
   count[string[i]].count++; //needs to be fixed 
   //count[*(string+i)].count++;
   if(count[*(string+i)].count == 1) count[*(string+i)].index = i;  
  }
  
  for(i=0; i<256; i++){
    if(count[i].count == 1) unique = string[count[i].index];
    if(count[i].count > 1) all_unique = false;
      
  }
  printf("First unique char in string %s is %c \n", string, unique);
  if(all_unique == true) printf("All characters are unique in string %s \n", string); 
}


int main(int argc, char* argv[]){
  
  char sentence1[] = "Hello world blah blah.";
  reverse(sentence1);
  
  char sentence2[] = "Hello world blah blah.";
  fill_spaces(sentence2, 'a' );
  
  int a = 4;
  int b = 7;
  swap_no_temp(a,b);
  
  int result;
  
  result = multiply_without_mult(a,b);
  printf("Result of %d * %d is %d \n", a, b, result);
  
  palindrome("racecar");
  palindrome("hello");
  
  unique_char("google");
  unique_char("gole");
  
  
  return 0;
}