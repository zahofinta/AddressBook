#ifndef Type_h
#define  Type_h
#include "PhoneNumber.h"
#include "Email.h"
#include "date.h"
#include "Text.h"
#include "Date_.h"
#include <string>
#include <vector>
#include <map>
#include <fstream>
class Type :public Serializable
{
private:
	vector<Email*> emails;
	vector<Text*> texts;
	vector<PhoneNumber*> phones;
	vector<Date_*> dates;

public:
	Type();
	~Type();
	void add_email(const string&);
	void add_text(const string&);
	void add_phone_number(const string&);
	void add_date(date*, const string&);
	vector<Email*>& get_email_type();
	vector<Date_*>& get_date_type();
	vector<Text*>& get_text_type();
	vector<PhoneNumber*>& get_phonenumber_type();
	void print_existing_fields();
	void serialize(ofstream&);
	void deserialize(ifstream&);
};
#endif