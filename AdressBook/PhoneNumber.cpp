#include "PhoneNumber.h"

PhoneNumber::PhoneNumber(){};

PhoneNumber::~PhoneNumber(){};

PhoneNumber::PhoneNumber(const string& value)
{
	phone = value;
	set_content(value);
}

PhoneNumber::PhoneNumber(string& value)
{
	set_phone(value);
	set_content(value);
}

void PhoneNumber::set_phone(string& value)
{
	phone = value;

}
string PhoneNumber::get_phone()
{
	return phone;
}
void PhoneNumber::serialize(ofstream& writer)
{
	write_int_to_file(phone.size(), writer);
	writer.write(phone.data(), phone.size());
}
void PhoneNumber::deserialize(ifstream& reader)
{
	int s = read_int_from_file(reader);
	char * phone_number = new char[s + 1];
	reader.read(phone_number, s);
	phone_number[s] = '\0';
	phone = phone_number;
	set_content(phone);
}


