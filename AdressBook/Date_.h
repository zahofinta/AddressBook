#ifndef Date__h
#define Date__h
#include <iostream>
#include "date.h"
#include <vector>
#include <fstream>
#include "SearchObject.h"
using namespace std;

class Date_:public Serializable, public SearchObject
{
private:
		date* current_date;
		string field_name;
public:
		Date_();
		~Date_();
		Date_(date*&);
		Date_(date*&, const string&);
		void set_date(date*&);
		date* get_date();
		void set_field_name(const string&);
		string get_field_name();
		string to_string();
		void serialize(ofstream&);
		void deserialize(ifstream&);
};
#endif