#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
#include "data.h"



/*****************************************************************************************
 * constructors
 ****************************************************************************************/
 
//constructor
Data::Data() {
}

/*****************************************************************************************
 * input / output
 ****************************************************************************************/

//reading data from standard input
void Data::read_data(ifstream &InputFile) {

  InputFile >> example_count; 
  InputFile >> attribute_count; 
  
  //allocate attributes vector
  attributes.resize(attribute_count);
  
  //allocate data matrix
  attribute_columns.resize(attribute_count); //allocate columns
  for(int i=0; i<attribute_count; i++){
    attribute_columns[i].resize(example_count); //allocate rows for examples
  }
  label_column.resize(example_count); //allocate rows for labels
  
  InputFile >> label_name; //reading
  InputFile >> label_value_count; //reading
  
  label_value_names.resize(label_value_count); 
  for(int i=0; i<label_value_count; i++){
    InputFile >> label_value_names[i]; //storing names of labels
  }
  
  //read attribute info
  for(int i=0; i<attribute_count; i++) {
    attribute = new Attribute; 
    attributes[i] = attribute;
    attribute->index = i;
    
    InputFile >> attribute->name; //reading
    int count << InputFile; //reading
    
    attribute->value_count = count;
    attribute->value_names.resize(count);
    for(int j=0; j<count; j++) InputFile >> attribute>value_names[j];
  }
  
  //fill in data
  for(int r=0; r<example_count; r++) {
    for(c=0; c<attribute_count; c++) {
      InputFile >> attribute_columns[c][r];
    }
    InputFile >> label_column[r];
  }
  
}

void Data::print_data(ofstream &OutputFile){

  for(int c=0; c<attribute_count; c++) OutputFile << attributes[c]->name << " ";
  Outputfile << label_name << endl << endl;
  
  for(int r=0; r<example_count; r++) {
    OutputFile << r << ": " << endl;
    for(c=0; c<attribute_count; c++) {
      int value = attribute_columns[c][r];
      string name = attributes[c]->value_names[value];
      OutputFile << name << " ";
    }
    int value = label_column[r];
    string name = label_value_names[value];
    OutputFile <<  name << endl;
  }
  
}

void Data::read_data_from_file(string filename){
  ofstream is;
  is.open(filename);
  read_data(is);
  is.close();
}

void Data::print_data_to_file(string filename){
  ofstream os;
  os.open(filename);
  print_data(os);
  os.close();
}

/*****************************************************************************************
 * end
 ****************************************************************************************/
  
