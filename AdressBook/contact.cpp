#include "contact.h"
#include "functions.h"
//#include "date.h"
//#include <vector>
//#include <string.h>
#include <iostream>
//#include <string>

int Contact::id_counter = 0;
Contact::Contact()
{
	contact_properties = NULL;
}
Contact::Contact(Type* values)
{
	set_unique_id();
	set_contact_properties(values);

}
Contact::~Contact()
{
	delete contact_properties;
}
void Contact::set_unique_id()
{
	unique_id = id_counter++;
}
void Contact::set_contact_properties(Type* values)
{
	if (values != NULL)
		contact_properties = values;
}
Type* Contact::get_contact_properties()
{
	return contact_properties;
}

int Contact::get_unique_id()
{
	return unique_id;
}

//v address book chetem mapa s konfiguraciqta, podavame go kato argument na searchera i contacta vuv funkciite v koito im trqbva
//a imenno full_info() i konstruktora na searcher \moge bi\

string Contact::full_info()
{
	string to_return;
	stringstream buffer;
	buffer << "--------------------------------------------\n";
	buffer << "Contact: " << unique_id << endl;
	buffer << "--------------------------------------------\n";
	buffer << "Name and comments:\n";
	buffer << "--------------------------------------------\n";
	for (int i = 0; i < get_contact_properties()->get_text_type().size(); i++)
	{
		buffer << get_contact_properties()->get_text_type()[i]->get_text() << endl;
	}
	buffer << "--------------------------------------------\n";
	buffer << "E-mails:\n";
	buffer << "--------------------------------------------\n";
	for (int i = 0; i < get_contact_properties()->get_email_type().size(); i++)
	{
		buffer << get_contact_properties()->get_email_type()[i]->get_email() << endl;
	}
	buffer << "--------------------------------------------\n";
	buffer << "Phone numbers:\n";
	buffer << "--------------------------------------------\n";
	for (int i = 0; i < get_contact_properties()->get_phonenumber_type().size(); i++)
	{

		buffer << get_contact_properties()->get_phonenumber_type()[i]->get_phone() << endl;
	}
	
	buffer << "--------------------------------------------\n";
	buffer << "Important dates:\n";
	buffer << "--------------------------------------------\n";
	for (int i = 0; i < get_contact_properties()->get_date_type().size(); i++)
	{
		buffer << get_contact_properties()->get_date_type()[i]->to_string() << endl;
	}
	buffer << "--------------------------------------------\n";
	to_return = buffer.str();
	return to_return;
}
void Contact::serialize(ofstream& writer)
{
	write_int_to_file(get_unique_id(), writer);
	get_contact_properties()->serialize(writer);
}
void Contact::deserialize(ifstream& reader)
{
	unique_id = read_int_from_file(reader);
	if (contact_properties == NULL)
		contact_properties = new Type();
	get_contact_properties()->deserialize(reader);
}
string Contact::get_name(){
	vector<Text*> *v = &get_contact_properties()->get_text_type();
	for (int i = 0; get_contact_properties()->get_text_type().size(); i++)
	{
		if (v->at(i)->get_text().find_first_of("Name") != string::npos)
		{
			return v->at(i)->get_text();
		}
	}
}
date* Contact::get_birthday(){
	vector<Date_*> *v = &get_contact_properties()->get_date_type();
	for (int i = 0; get_contact_properties()->get_date_type().size(); i++)
	{
		if (v->at(i)->to_string().find_first_of("Birthday") != string::npos)
		{
			return v->at(i)->get_date();
		}
	}
	return NULL;
}