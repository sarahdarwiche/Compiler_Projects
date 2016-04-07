#include <iostream>
#include <cstdlib>
#include <string.h>
#include <vector>
#include "ArraysandStrings.h"


void all_unique(std::string input ){
  


}
void reverse(std::string input ){
  
  int length = input.length();
  char temp;
  
  for(int i = 0, j = input.length()-1; i <= (length-1 )/2 ; i++, j--) {
    
    temp = input[i];
    input[i] = input[j];
    input[j] = temp;
    
  }
 
  std::cout << input << std::endl;
}

int main( int argc, char* argv[]) {
	reverse("what");

  return 0;
}