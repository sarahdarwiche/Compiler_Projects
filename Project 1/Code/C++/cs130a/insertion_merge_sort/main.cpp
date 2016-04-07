#include <iostream>
#include <time.h>
#include <vector>
#include <cstdlib>
#include <fstream>
#include "utilities.cpp"
#include "insertion_sort.cpp"
#include "merge.cpp"
#include "merge_test.cpp"
#include "insertion_test.cpp"

using namespace std;

int main (int argc, char* argv[]) {
 
  ofstream file;     
  file.open("testing.txt");
  
  merge_test(file);
  insertion_test(file);
  
  //close file
  file.close();
  return 0;
 };