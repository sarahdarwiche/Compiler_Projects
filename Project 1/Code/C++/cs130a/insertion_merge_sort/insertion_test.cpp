#include <iostream>
#include <time.h>
#include <vector>
#include <cstdlib>
#include <fstream>
using namespace std;

void insertion_test(ofstream &file) {
  file << "Running time for insertion sort:\n";
  vector<int> array4;
  vector<int> array5;
  vector<int> array6;
	
  for(int n = 1000; n <=10000; n+= 1000){ //put insertion in seperate file
	file << n;
		
	//increasing insertion sort
	get_increasing_array(array4, n);
    clock_t start_time1 = clock();
    insertion_sort(array4);
    clock_t end_time1 = clock();
    double running_time_increasing = ((double)(end_time1-start_time1))/CLOCKS_PER_SEC;
	file << "\t" << running_time_increasing;	
		
	//decreasing insertion sort
    get_decreasing_array(array5, n);
    clock_t start_time2 = clock();
    insertion_sort(array5);
    clock_t end_time2 = clock();
    double running_time_decreasing = ((double)(end_time2-start_time2))/CLOCKS_PER_SEC;
	file << "\t" << running_time_decreasing;
		
	//random insertion sort
    get_random_array(array6, n);
    clock_t start_time3 = clock();
    insertion_sort(array6);
    clock_t end_time3 = clock();
    double running_time_random = ((double)(end_time3-start_time3))/CLOCKS_PER_SEC;
	file << "\t" << running_time_random << endl;
  }
}