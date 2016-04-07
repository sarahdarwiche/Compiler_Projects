#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include "utilities.h"
#include "insertion_sort.h"
#include "merge.h"
#include "bubble_sort.h"
#include "quick_sort.h"

using namespace std;

int main (int argc, char* argv[]) {

  int test_count;
  cin >> test_count; //read number of test cases
  
  vector< vector<int> > test_cases(test_count);
  
  vector< vector<int> > test_cases_bubble(test_count);
  vector< vector<int> > test_cases_insertion(test_count);
  vector< vector<int> > test_cases_quick(test_count);
  vector< vector<int> > test_cases_merge(test_count);
  
  
  int i;
  for(i = 0; i < test_count; i++) { //iterate over test cases
     
    int input_size, current_int;
    cin >> input_size; 
    
    for( int j = 0; j < input_size; j++) {

    cin >> current_int;
    test_cases[i].push_back(current_int);
    
    }
}
    test_cases_bubble = test_cases;
    test_cases_insertion = test_cases;
    test_cases_quick = test_cases;
    test_cases_merge = test_cases;
 
    for(i = 0; i < test_count; i++) { //iterate over test cases {
   //printing solution of tests
    cout << "Case #" << (i + 1) << ":" << endl;
    
    cout << "Bubble Sort:" << endl;
    bubble_sort(test_cases_bubble[i]);
    
    
    cout << "Insertion Sort:"  << endl;
    insertion_sort(test_cases_insertion[i]);
   
    
    cout << "Quick Sort:" << endl;
    quick_sort(test_cases_quick[i]);
    
    
    cout << "Merge Sort:" << endl;
    merge_sort(test_cases_merge[i]);
    
  }
 
};