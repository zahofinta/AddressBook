#include "Date_.h"
Date_::Date_(){
	current_date = new date();
	set_content(current_date->to_string());
};
Date_::~Date_()
{
	delete current_date;
}
Date_::Date_(date*& value)
{
	set_date(value);
	set_content(current_date->to_string());
}
Date_::Date_(date*& value, const string& field_name) 
{
	set_date(value);
	set_field_name(field_name);
}
void Date_::set_field_name(const string& field_name){
	this->field_name = field_name;
}
string Date_::get_field_name()
{
	return field_name;
}
void Date_::set_date(date*& value)
{
	current_date = value;
}
date* Date_::get_date()
{
	return current_date;
}
void Date_::serialize(ofstream& writer)
{
	int size = field_name.size();
	if (field_name[size - 1] != ':' && field_name[size - 2] != ':'){
		field_name += ":";
		size = field_name.size();
	}
	write_int_to_file(size, writer);
	writer.write(field_name.data(), size);
	current_date->serialize(writer);
}
void Date_::deserialize(ifstream& reader)
{
	int size = read_int_from_file(reader);
	char* to_read = new char[size + 1];
	reader.read(to_read, size);
	to_read[size] = '\0';
	field_name = to_read;
	current_date->deserialize(reader);
	set_content(current_date->to_string());
}
string Date_::to_string(){
	return field_name + ": " + current_date->to_string();
}


