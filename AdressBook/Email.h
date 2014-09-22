
#ifndef email_h
#define email_h
#include <string>
#include <vector>
#include <iostream>
#include "Serializable.h"
#include "functions.h"
#include "SearchObject.h"

using namespace std;
class Email : public Serializable, public SearchObject
{
private:
		string email;
public:
		Email();
		~Email();
		Email(string&);
		Email(const string&);
		void set_email(string&);
		string get_email();
		void serialize(ofstream&);
		void deserialize(ifstream&);
};
#endif