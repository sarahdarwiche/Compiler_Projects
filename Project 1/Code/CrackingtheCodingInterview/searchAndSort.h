#ifndef SEARCHANDSORT_H
#define SEARCHANDSORT_H
#include <vector>

/*template <typename Comparable> 
class searchAndSort{
public:*/

//finds the position of target value in a SORTED array
//space and best time =  O(1)
// avg time = worst time = O(log n)
//applications: number guessing game, word lists (phone book)

int mybinarySearch(std::vector<int> , int); //done

int recursiveBinarySearch(std::vector<int> , int);

std::vector<int> fillArray(int , int , std::vector<int> ); //done

//merge sort not working
void mergeAll(std::vector<int> &arrayC, std::vector<int> &temp, int start, int middle, int end);
void recursiveMerge(std::vector<int> , std::vector<int> , int , int );
void mergeMain(std::vector<int> );

//int quickSort(int* S[]);

//int bubbleSort();


#endif