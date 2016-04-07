#include <iostream>
#include <time.h>
#include <vector>
#include <cstdlib>
#include <fstream>
using namespace std;

void merge_test(ofstream &file) {  
  file << "Running time for merge sort:\n";
  
  vector<int> array1;
  vector<int> array2;
  vector<int> array3;
    
  for(int n = 1000; n <= 10000; n += 1000){
    file <<  n; //format for excell
		
	//increasing merge sort
	get_increasing_array(array1, n);
    clock_t start_time1 = clock();
    merge_Sort(array1);
    clock_t end_time1 = clock();
    double running_time_increasing = ((double)(end_time1-start_time1))/CLOCKS_PER_SEC;
	file << "\t" << running_time_increasing; 
		
    //decreasing merge sort
    get_decreasing_array(array2, n);
    clock_t start_time2 = clock();
    merge_Sort(array2);
    clock_t end_time2 = clock();
    double running_time_decreasing = ((double)(end_time2-start_time2))/CLOCKS_PER_SEC;
	file << "\t" << running_time_decreasing;
		
   //random merge sort
   get_random_array(array3, n);
   clock_t start_time3 = clock();
   merge_Sort(array3);
   clock_t end_time3 = clock();
   double running_time_random = ((double)(end_time3-start_time3))/CLOCKS_PER_SEC;
   file << "\t" << running_time_random << endl;
	}
}