#include "Type.h"
Type::Type()
{

}
Type::~Type()
{
	while (!texts.empty())
	{
		Text* p = texts.back();
		texts.pop_back();
		delete p;
	}
	while (!emails.empty())
	{
		Email* p = emails.back();
		emails.pop_back();
		delete p;
	}
	while (!phones.empty())
	{
		PhoneNumber* p = phones.back();
		phones.pop_back();
		delete p;
	}
	while (!dates.empty())
	{

		Date_* p = dates.back();
		dates.pop_back();
		delete p;
	}

}
void Type::add_email(const string & email)
{
	emails.push_back(new Email(email));
}
void Type::add_phone_number(const string & phone)
{
	phones.push_back(new PhoneNumber(phone));
}
void Type::add_text(const string & text)
{
	texts.push_back(new Text(text));
}
void Type::add_date(date* current_date, const string& date_description)
{
	dates.push_back(new Date_(current_date, date_description));
}

vector<Email*>& Type::get_email_type()
{
	return emails;
}
vector<Date_*>& Type::get_date_type()
{
	return dates;
}
vector<Text*>& Type::get_text_type()
{
	return texts;
}
vector<PhoneNumber*>& Type::get_phonenumber_type()
{
	return phones;
}
void Type::print_existing_fields(){
	for (int i = 0; i < texts.size(); i++)
	{

	}
}
void Type::serialize(ofstream& writer)
{
	write_int_to_file(texts.size(), writer);
	for (int i = 0; i < texts.size(); i++)
	{
		texts[i]->serialize(writer);
	}
	write_int_to_file(emails.size(), writer);
	for (int i = 0; i < emails.size(); i++)
	{
		emails[i]->serialize(writer);
	}
	write_int_to_file(phones.size(), writer);
	for (int i = 0; i < phones.size(); i++)
	{
		phones[i]->serialize(writer);
	}
	write_int_to_file(dates.size(), writer);
	for (int i = 0; i < dates.size(); i++)
	{
		dates[i]->serialize(writer);
	}
}
void Type::deserialize(ifstream& reader)
{
	int s = read_int_from_file(reader);
	for (int i = 0; i < s; i++)
	{
		Text * t = new Text();
		t->deserialize(reader);
		texts.push_back(t);
	}
	s = read_int_from_file(reader);
	for (int i = 0; i < s; i++)
	{
		Email * e = new Email();
		e->deserialize(reader);
		emails.push_back(e);
	}
	s = read_int_from_file(reader);
	for (int i = 0; i < s; i++)
	{
		PhoneNumber * p = new PhoneNumber();
		p->deserialize(reader);
		phones.push_back(p);
	}
	s = read_int_from_file(reader);
	for (int i = 0; i < s; i++)
	{
		Date_ * d = new Date_();
		d->deserialize(reader);
		dates.push_back(d);
	}
}

