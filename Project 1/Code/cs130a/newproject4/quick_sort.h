#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <vector>
#include <assert.h>
using namespace std;

void quick_sort(vector<int> &array);
void quicksort(vector<int> &array, int i, int k);
int partition(vector <int> &array, int left, int right);
   
#endif