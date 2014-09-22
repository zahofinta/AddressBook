#ifndef functions_h
#define functions_h
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void write_int_to_file(int, ofstream &);
int read_int_from_file(ifstream& );
vector<string> read_vector_of_strings_from_file(ifstream & );
#endif