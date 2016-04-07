#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <vector>

using namespace std;

class Attribute {

  public:
  
  int index; //index into attribute vector of data
  string name;
  
  int value_count; //number of values for attribute
  vector<string> value_names; //vector has size equal to value_count
  
  
  //information gain info
  //each of the following vectors has size equal to value_count
  vector<int> positive_counts; //one count per attribute value
  vector<int> negative_counts; //one count per attribute value
  
  
  };

#endif