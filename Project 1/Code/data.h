#ifndef DATA_H
#define DATA_H

#include <vector>

using namespace std;

class Data {

  public:
  
  int attribute_count; //column count
  int example_count; //row count
  
  vector<vector> attribute_columns;
  vector<int> label_column;
  
  //label information
  string label_name;
  int label_value_count;
  vector<string> label_value_names;
  
  //attribute information
  vector<Attribute> attributes;
  
  //methods
  
  read_data(ifstream &InputFile);
  print_data(ofstream &OutputFile);

  read_data_from_file(string filename);
  print_to_file(string filename);
  
  };

#endif

//data file format
//
//example_count attribute_count
//label_name label_value_count value_1_name ... value_n_name
//attribute_name value_count value_1_name ... value_n_name
//...
//
//a0_value a1_value .... am_value label
//...