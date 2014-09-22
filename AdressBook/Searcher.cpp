#include "Searcher.h"
#include <iostream>
using namespace std;

Searcher::Searcher(vector<Contact*>* AB)
{
	AddressBook = AB;
}

Searcher::~Searcher()
{
	while (!AddressBook->empty())
	{
		delete AddressBook->back();
		AddressBook->pop_back();
	}

	delete AddressBook;
}
void Searcher::simple_search(const char* value)
{
	bool found = false;
	cout << "--------------------------------------------\n";
	cout << "Simple search results:\n";
	cout << "--------------------------------------------\n";
	for (int i = 0; i < AddressBook->size(); i++)
	{
		Contact* current_contact = AddressBook->at(i);

		vector<Date_*> dates = current_contact->get_contact_properties()->get_date_type();
		vector<Email*> emails = current_contact->get_contact_properties()->get_email_type();
		vector<Text*> texts = current_contact->get_contact_properties()->get_text_type();
		vector<PhoneNumber*> phones = current_contact->get_contact_properties()->get_phonenumber_type();

		bool finded = false;

		for (int i = 0; i < dates.size(); i++){
			if (!finded && strstr(dates[i]->get_date()->to_string().data(), value) != NULL){
				finded = true;
				cout << current_contact->full_info();
				found = true;
			}
		}

		for (int i = 0; i < emails.size(); i++){
			if (!finded && strstr(emails[i]->get_email().data(), value) != NULL){
				finded = true;
				found = true;
				cout << current_contact->full_info();
			}
		}

		for (int i = 0; i < texts.size(); i++){
			if (!finded && strstr(texts[i]->get_text().data(), value) != NULL){
				finded = true;
				found = true;
				cout << current_contact->full_info();
			}
		}

		for (int i = 0; i < phones.size(); i++){
			if (!finded && strstr(phones[i]->get_phone().data(), value) != NULL){
				finded = true;
				found = true;
				cout << current_contact->full_info();
			}
		}
	}
	if (!found){
		cout << "Nothig found!\n";
		cout << "--------------------------------------------\n";
	}
	
}

void Searcher::search_by_field(const char* field, const char* type, const char* value)
{
	bool found = false;
	cout << "--------------------------------------------\n";
	cout << "Search by field results:\n";
	cout << "--------------------------------------------\n";
	for (int i = 0; i < AddressBook->size(); i++)
	{
		Contact* current_contact = AddressBook->at(i);
		vector<SearchObject*> search_vector;
		if (strcmp(type, "Text") == 0){
			for (int i = 0; i < current_contact->get_contact_properties()->get_text_type().size(); i++){
				search_vector.push_back(current_contact->get_contact_properties()->get_text_type()[i]);
			}
		}
		if (strcmp(type, "Phone") == 0)
		{
			for (int i = 0; i < current_contact->get_contact_properties()->get_phonenumber_type().size(); i++){
				search_vector.push_back(current_contact->get_contact_properties()->get_phonenumber_type()[i]);
			}
		}
		if (strcmp(type, "Email") == 0)
		{
			for (int i = 0; i < current_contact->get_contact_properties()->get_email_type().size(); i++){
				search_vector.push_back(current_contact->get_contact_properties()->get_email_type()[i]);
			}
		}
		if (strcmp(type, "Date") == 0)
		{
			for (int i = 0; i < current_contact->get_contact_properties()->get_date_type().size(); i++){
				search_vector.push_back(current_contact->get_contact_properties()->get_date_type()[i]);
			}
		}
		
		for (int i = 0; i < search_vector.size(); i++){
			if (strstr(search_vector[i]->get_content().data(), field) != NULL && strstr(search_vector[i]->get_content().data(), value)){
				cout << current_contact->full_info();
				found = true;
				break;
			}
		}
	}
	if (!found){
		cout << "Nothing found!\n";
		cout << "--------------------------------------------\n";
	}
}
/*void Searcher::add_contact(Contact * contact)
{

AddressBook->push_back(contact);

}
void Searcher::remove_contact(Contact *contact)
{
for(int i=0;i<AddressBook->size();i++)
{
if(AddressBook->at(i)==contact)
{
AddressBook->erase(AddressBook->begin()+i);
}

}
}*/
vector<Contact*>* Searcher::get_addressbook()
{
	return AddressBook;
}
string Searcher::return_adrress_book_info()
{
	string to_return = "";
	stringstream buffer;
	bool buffer_used = false;
	for (int i = 0; i < AddressBook->size(); i++){
		buffer << get_addressbook()->at(i)->full_info();
		buffer_used = true;
	}
	if(buffer_used)
		to_return = buffer.str();
	return to_return;
}