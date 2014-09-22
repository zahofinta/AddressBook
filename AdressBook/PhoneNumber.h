#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Serializable.h"
#include "functions.h"
#include "SearchObject.h"
using namespace std;

class PhoneNumber:public Serializable, public SearchObject
{
private:
string phone;
public:
		PhoneNumber();
		~PhoneNumber();
		PhoneNumber(string&);
		PhoneNumber(const string&);
		void set_phone(string&);
		string get_phone();
		void serialize(ofstream&);
		void deserialize(ifstream&);
		
};