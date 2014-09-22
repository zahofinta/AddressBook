
#ifndef Text_h
#define Text_h
#include <iostream>
#include <string>
#include <vector>
#include "Serializable.h"
#include "functions.h"
#include <fstream>
#include "SearchObject.h"
using namespace std;

class Text:public Serializable, public SearchObject
{
private:
		string text;
public:
		Text();
		~Text();
		Text(string&);
		Text(const string&);
		void set_text(string&);
		string get_text();
		void serialize(ofstream&);
		void deserialize(ifstream&);
};
#endif