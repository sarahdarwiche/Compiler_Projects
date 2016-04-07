#include <stdio.h>
#include <stdlib.h>

void odd_or_even(int num){
  int result;
  result = num % 2;
  if(result == 0){
    printf("%d is an even number\n", num);
  }
  else{
    printf("%d is an odd number\n", num);
   }
}
void no_div(int num){
  int result;
  result = num % 2;
  if(result == 0){
    printf("%d is an even number\n", num);
  }
  else{
    printf("%d is an odd number\n", num);
   }
}
void int_to_hex(int num){

}
void int_to_binary(int num){

}

int main(int argc, char* argv[]){
  int a, b, c, d, e;
  a = 1;
  b = 2;
  c = 3;
  d = 4;
  e = 5;
  
  odd_or_even(a);
  odd_or_even(b);
  odd_or_even(c);
  odd_or_even(d);
  odd_or_even(e);
  
  return 0;
}