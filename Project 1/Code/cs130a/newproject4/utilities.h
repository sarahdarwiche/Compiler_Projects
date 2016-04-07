#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;



 
vector<int> read_array(vector<int> &array);
void print_array(vector<int> array);
void get_increasing_array(vector<int> &array, int n) ;
void get_decreasing_array(vector<int> &array, int n);
bool is_increasingly_sorted(vector<int> array);
int my_rand(int n);
void get_random_array(vector<int> &array, int n);
   



#endif