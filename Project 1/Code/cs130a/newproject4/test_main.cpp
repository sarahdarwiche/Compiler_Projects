#include <iostream>
#include <time.h>
#include <vector>
#include <cstdlib>
#include <fstream>
#include "utilities.h"
#include "insertion_sort.h"
#include "merge.h"
#include "bubble_sort.h"
#include "quick_sort.h"

using namespace std;


//returns time in milli seconds
double get_insertion_sort_time(vector<int> &array) {
  clock_t start_time = clock();
  insertion_sort(array);
  clock_t end_time = clock();
  return ((double)1000*(end_time-start_time))/CLOCKS_PER_SEC;
}

//returns time in milli seconds
double get_merge_sort_time(vector<int> &array) {
  clock_t start_time = clock();
  merge_sort(array);
  clock_t end_time = clock();
  return ((double)1000*(end_time-start_time))/CLOCKS_PER_SEC;
}

//returns time in milli seconds
double get_bubble_sort_time(vector<int> &array) {
  clock_t start_time = clock();
  insertion_sort(array);
  clock_t end_time = clock();
  return ((double)1000*(end_time-start_time))/CLOCKS_PER_SEC;
}

//returns time in milli seconds
double get_quick_sort_time(vector<int> &array) {
  clock_t start_time = clock();
  insertion_sort(array);
  clock_t end_time = clock();
  return ((double)1000*(end_time-start_time))/CLOCKS_PER_SEC;
}


void output_insertion_sort_file(string fname, int start, int end, int inc) {

  ofstream file;     
  file.open(fname);
  
  vector<int> array;
  double running_time;
    
  for(int n = start; n <= end; n+= inc) {
    file << n;
	
    get_increasing_array(array, n);
    file << "\t " << get_insertion_sort_time(array);
    array.clear();

    get_decreasing_array(array, n);
    file << "\t " << get_insertion_sort_time(array);
    array.clear();

    get_random_array(array, n);   
    file << "\t" << get_insertion_sort_time(array);
    array.clear();
		
	file << endl;
  }
	
  file.close(); 
  
}

void output_merge_sort_file(string fname, int start, int end, int inc) {

  ofstream file;     
  file.open(fname);
  
  vector<int> array;
  double running_time;
    
  for(int n = start; n <= end; n+= inc) {
    file << n;
	
    get_increasing_array(array, n);
    file << "\t" << get_merge_sort_time(array);
    array.clear();

    get_decreasing_array(array, n);
    file << "\t" << get_merge_sort_time(array);
    array.clear();

    get_random_array(array, n);   
    file << "\t" << get_merge_sort_time(array);
    array.clear();
		
	file << endl;
  }
	
  file.close(); 
  
}

void output_bubble_sort_file(string fname, int start, int end, int inc) {

  ofstream file;     
  file.open(fname);
  
  vector<int> array;
  double running_time;
    
  for(int n = start; n <= end; n+= inc) {
    file << n;
	
    get_increasing_array(array, n);
    file << "\t" << get_bubble_sort_time(array);
    array.clear();

    get_decreasing_array(array, n);
    file << "\t" << get_bubble_sort_time(array);
    array.clear();

    get_random_array(array, n);   
    file << "\t" << get_bubble_sort_time(array);
    array.clear();
		
	file << endl;
  }
	
  file.close(); 
  
}

void output_quick_sort_file(string fname, int start, int end, int inc) {

  ofstream file;     
  file.open(fname);
  
  
  vector<int> array;
  double running_time;
    
  for(int n = start; n <= end; n+= inc) {
    file << n;
	
    get_increasing_array(array, n);
    file << "\t" << get_quick_sort_time(array);
    array.clear();

    get_decreasing_array(array, n);
    file << "\t" << get_quick_sort_time(array);
    array.clear();

    get_random_array(array, n);   
    file << "\t" << get_quick_sort_time(array);
    array.clear();
		
	file << endl;
  }
	
  file.close(); 
  
}




int main (int argc, char* argv[]) {
  
  cout << "Starting insertion sort...";
  cout.flush();
  output_insertion_sort_file("insertion.txt",1000,10000,500);
  cout << "done." << endl;
  
  cout << "Starting merge sort...";
  cout.flush();
  output_merge_sort_file("merge.txt",1000,10000,500);
  cout << "done." << endl;
  
  cout << "Starting bubble sort...";
  cout.flush();
  output_bubble_sort_file("bubble.txt",1000,10000,500);
  cout << "done." << endl;
  
  cout << "Starting quick sort...";
  cout.flush();
  output_quick_sort_file("quick.txt",1000,10000,500);
  cout << "done." << endl;
  
  /*vector<int> array;
  get_increasing_array(array, 10);
  print_array(array);
  merge_sort(array);
  
  vector<int> array1;
  get_decreasing_array(array1, 20);
  print_array(array1);
  merge_sort(array1);
  
  vector<int> array2;
  get_random_array(array2, 30);
  print_array(array2);
  merge_sort(array2);*/
  
 
};