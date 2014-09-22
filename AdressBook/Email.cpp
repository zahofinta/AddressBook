#include "Email.h"

Email:: Email(){};

Email:: ~Email(){};
Email::Email(const string & value)
{
		email=value;
		set_content(value);
}

Email::Email(string& value)
{
		set_email(value);
		set_content(value);

}

void Email::set_email(string& value)
{

		email=value;
}

string Email::get_email()
{
		return email;
}
void Email::serialize(ofstream& writer)
{
		write_int_to_file(email.size(), writer);
		writer.write(email.data(), email.size());
}
void Email::deserialize(ifstream& reader){
		int s = read_int_from_file(reader);
		char* email_array = new char[s+1];
		reader.read(email_array, s);
		email_array[s] = '\0';
		email = email_array;
		set_content(email);
}