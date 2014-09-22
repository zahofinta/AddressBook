#include "AddressBook.h"
#include "contact.h"


date* AddressBook::to_date(string d)
{
	date* todate;
	int day = atoi(d.substr(0, 2).data());
	int month = atoi(d.substr(3, 2).data());
	int year = atoi(d.substr(5, 4).data());
	todate = new date(day, month, year);
	return todate;
}


AddressBook::AddressBook(){
	contacts = new vector<Contact*>();
	search = new Searcher(contacts);
	ifstream reader("cfgfile.txt");
	parse(reader);
}

AddressBook::~AddressBook()
{
	while (!contacts->empty())
	{
		Contact* p = contacts->back();
		contacts->pop_back();
		delete p;
	}

	delete search;
}

vector<Contact*>* AddressBook::get_contacts()
{
	return contacts;
}

void AddressBook::add_contact(Contact * c)
{
	contacts->push_back(c);
	//ofstream writer(filename.data(), ios::binary | ios::out);
	//serialize(writer);
	//writer.close();
	//add to file
}
void AddressBook::remove_contact(Contact * c)
{
	for (int i = 0; i < contacts->size(); i++)
	{
		if (c == contacts->at(i))
		{
			contacts->erase(contacts->begin() + i);

		}
	}
	ofstream writer(filename.data(), ios::binary | ios::out);
	serialize(writer);
	writer.close();
	// erase from file
}
void AddressBook::edit_contact(Contact * c)
{
	cout << "1. Add new field\n";
	cout << "2. Edit existing field\n";
	cout << "3. Delete field\n";

	map<string, int> enabled_to_add;
	for (map<string, string*>::const_iterator it = cfg.begin(); it != cfg.end(); it++)
	{
		enabled_to_add[it->first] = atoi(it->second[1].data());
	}
	int choice;
	cin >> choice;
	cin.clear();
	cin.ignore();

	int cnt = 1;
	if (choice == 1){

		cout << "The fields supported by the program are: " << endl;

		for (map<string, string*>::const_iterator it = cfg.begin(); it != cfg.end(); it++)
		{
			cout << it->first << endl;
		}

		cout << "Enter the name of the field you want to add: " << endl;

		string name_of_new_field;
		cin >> name_of_new_field;
		cin.clear();
		cin.ignore();
		map<string, string*>::const_iterator it = cfg.find(name_of_new_field);

		if (it != cfg.end()){
			if (atoi(it->second[1].data()) == -1){ 
				help_enter_field(name_of_new_field, it->second[0], c);
			}
			else{
				int possible_adds = atoi(it->second[1].data());
				string type = it->second[0];
				if (type.compare("Email") == 0){
					vector<Email*> v = c->get_contact_properties()->get_email_type();
					for (int i = 0; i<v.size(); i++){
						if (v[i]->get_email().find_first_of(it->first)){
							possible_adds--;
						}
					}
					if (possible_adds > 0){

						cout << "Enter contact's " << it->first << " please: " << endl;

						string to_add;
						getline(cin, to_add);
						cin.clear();

						c->get_contact_properties()->add_email(to_add);
					}
				}
				if (type.compare("Text") == 0){
					vector<Text*> v = c->get_contact_properties()->get_text_type();
					for (int i = 0; i<v.size(); i++){
						if (v[i]->get_text().find_first_of(it->first) != string::npos){
							possible_adds--;
						}
					}
					if (possible_adds > 0){

						cout << "Enter contact's " << it->first << " please: " << endl;
						cin.ignore();

						string to_add;
						getline(cin, to_add);
						cin.clear();

						c->get_contact_properties()->add_text(to_add);
					}
				}
				if (type.compare("PhoneNumber") == 0){
					vector<PhoneNumber*> v = c->get_contact_properties()->get_phonenumber_type();
					for (int i = 0; i<v.size(); i++){
						if (v[i]->get_phone().find_first_of(it->first)){
							possible_adds--;
						}
					}
					if (possible_adds > 0){

						cout << "Enter contact's " << it->first << " please: " << endl;
						cin.ignore();

						string to_add;
						getline(cin, to_add);
						cin.clear();

						c->get_contact_properties()->add_phone_number(to_add);
					}
				}
				if (type.compare("Date") == 0){
					vector<Date_*> v = c->get_contact_properties()->get_date_type();
					for (int i = 0; i<v.size(); i++){
						if (v[i]->get_date()->to_string().find_first_of(it->first) != string::npos){
							possible_adds--;
						}
					}
					if (possible_adds > 0){

						cout << "Enter contact's " << it->first << " please: " << endl;
						cin.ignore();

						string to_add;
						getline(cin, to_add);
						cin.clear();

						date* current_date = to_date(to_add);
						c->get_contact_properties()->add_date(current_date, it->first);

					}
				}
			}

		}
	}
	else if (choice == 2){
		cout << c->full_info() << endl << "-----------------------------------------------------------------\n";
		cout << "Enter  the name of the field you want to edit : " << endl;
		string name_of_new_field;
		cin >> name_of_new_field;
		cout << name_of_new_field << endl;
		map<string, string*>::const_iterator it = cfg.find(name_of_new_field);
		if (it->second[0].compare("Email") == 0){
			vector<Email*> v = c->get_contact_properties()->get_email_type();
			vector<Email*> to_change_only;
			for (int i = 0; i < v.size(); i++){
				if (v[i]->get_email().find(name_of_new_field) != string::npos){
					to_change_only.push_back(v[i]);
				}
			}
			if (to_change_only.size() == 1){
				cout << "Enter the new information:" << endl;
				cin.clear();
				cin.ignore();
				string new_info;
				getline(cin, new_info);
				name_of_new_field.append(":");
				name_of_new_field.append(new_info);
				to_change_only[0]->set_email(name_of_new_field);
			}
			else{
				cout << "Enter the number of " << name_of_new_field << " you want to change:\n";
				for (int i = 0; i < to_change_only.size(); i++){
					cout << i + 1 << ". " << to_change_only[i]->get_email() << endl;
				}
				int index;
				do{
					cin >> index;
					index--;
					if (index < 0 || index >= to_change_only.size()){
						cout << "You entered wrong number, please retry!\n";
					}
				} while (index < 0 || index >= to_change_only.size());

				cout << "Enter the new information:" << endl;
				cin.clear();
				cin.ignore();
				string new_info;
				getline(cin, new_info);
				name_of_new_field.append(":");
				name_of_new_field.append(new_info);
				to_change_only[index]->set_email(name_of_new_field);
			}
		}
		if (it->second[0].compare("Text") == 0){
			vector<Text*> v = c->get_contact_properties()->get_text_type();
			vector<Text*> to_change_only;
			for (int i = 0; i < v.size(); i++){
				if (v[i]->get_text().find(name_of_new_field) != string::npos)
				{
					to_change_only.push_back(v[i]);
				}
			}
			if (to_change_only.size() == 1)
			{
				cout << "Enter the new information:" << endl;
				cin.clear();
				cin.ignore();
				string new_info;
				getline(cin, new_info);
				name_of_new_field.append(":");
				name_of_new_field.append(new_info);
				to_change_only[0]->set_text(name_of_new_field);
			}
			else{
				cout << "Enter the number of " << name_of_new_field << " you want to change:\n";
				for (int i = 0; i < to_change_only.size(); i++){
					cout << i + 1 << ". " << to_change_only[i]->get_text() << endl;
				}
				int index;
				do{
					cin >> index;
					index--;
					if (index < 0 || index >= to_change_only.size()){
						cout << "You entered wrong number, please retry!\n";
					}
				} while (index < 0 || index >= to_change_only.size());

				cout << "Enter the new information:" << endl;
				cin.clear();
				cin.ignore();
				string new_info;
				getline(cin, new_info);
				name_of_new_field.append(":");
				name_of_new_field.append(new_info);
				to_change_only[index]->set_text(name_of_new_field);
			}
		}
		if (it->second[0].compare("Phone") == 0){
			vector<PhoneNumber*> v = c->get_contact_properties()->get_phonenumber_type();
			vector<PhoneNumber*> to_change_only;
			for (int i = 0; i < v.size(); i++){
				if (v[i]->get_phone().find(name_of_new_field) != string::npos)
				{
					to_change_only.push_back(v[i]);
				}
			}
			if (to_change_only.size() == 1)
			{
				cout << "Enter the new information:" << endl;
				cin.clear();
				cin.ignore();
				string new_info;
				getline(cin, new_info);
				name_of_new_field.append(":");
				name_of_new_field.append(new_info);
				to_change_only[0]->set_phone(name_of_new_field);
			}
			else{
				cout << "Enter the number of " << name_of_new_field << " you want to change:\n";
				for (int i = 0; i < to_change_only.size(); i++){
					cout << i + 1 << ". " << to_change_only[i]->get_phone() << endl;
				}
				int index;
				do{
					cin >> index;
					index--;
					if (index < 0 || index >= to_change_only.size()){
						cout << "You entered wrong number, please retry!\n";
					}
				} while (index < 0 || index >= to_change_only.size());

				cout << "Enter the new information:" << endl;
				cin.clear();
				cin.ignore();
				string new_info;
				getline(cin, new_info);
				name_of_new_field.append(":");
				name_of_new_field.append(new_info);
				to_change_only[index]->set_phone(name_of_new_field);
			}
		}
		if (it->second[0].compare("Date") == 0){
			vector<Date_*> v = c->get_contact_properties()->get_date_type();
			vector<Date_*> to_change_only;
			for (int i = 0; i < v.size(); i++){
				if (v[i]->to_string().find(name_of_new_field) != string::npos)
				{
					to_change_only.push_back(v[i]);
				}
			}
			if (to_change_only.size() == 1)
			{
				cout << "Enter the new information:" << endl;
				cin.clear();
				cin.ignore();
				string new_info;
				getline(cin, new_info);
				date* new_date = to_date(new_info);
				to_change_only[0]->set_date(new_date);
			}
			else{
				cout << "Enter the number of " << name_of_new_field << " you want to change:\n";
				for (int i = 0; i < to_change_only.size(); i++){
					cout << i + 1 << ". " << to_change_only[i]->to_string() << endl;
				}
				int index;
				do{
					cin >> index;
					index--;
					if (index < 0 || index >= to_change_only.size()){
						cout << "You entered wrong number, please retry!\n";
					}
				} while (index < 0 || index >= to_change_only.size());

				cout << "Enter the new information:" << endl;
				cin.clear();
				cin.ignore();
				string new_info;
				getline(cin, new_info);
				date* new_date = to_date(new_info);
				to_change_only[index]->set_date(new_date);
			}
		}
	}
	else if (choice == 3){
		cout << "Enter  the name of the field you want to delete : " << endl;
		string name_of_new_field;
		cin >> name_of_new_field;
		cout << name_of_new_field << endl;
		map<string, string*>::const_iterator it = cfg.find(name_of_new_field);
		if (it->second[0].compare("Email") == 0)
		{
			vector<Email*> *v = &(c->get_contact_properties()->get_email_type());
			cout << v->size() << endl;
			if (v->size() == 1)
			{
				v->erase(v->begin());
			}
			else
			{
				cout << "Enter the number of " << name_of_new_field << " you want to delete:\n";
				for (int i = 0; i < v->size(); i++){
					cout << i + 1 << ". " << (*v)[i]->get_email() << endl;
				}
				int index;
				do{
					cin >> index;
					index--;
					if (index < 0 || index >= v->size()){
						cout << "You entered wrong number, please retry!\n";
					}
				} while (index < 0 || index >= v->size());
				v->erase(v->begin() + index);//(v.begin(), v.begin() + index);
				for (int i = 0; i < v->size(); i++){
					//cout << v[i]->get_email() << endl;
				}
				cout << "The information was deleted succesfully  :" << endl;
				cin.clear();
				//cin.ignore();
			}
		}
		if (it->second[0].compare("Phone") == 0)
		{
			vector<PhoneNumber*> *v = &(c->get_contact_properties()->get_phonenumber_type());
			cout << v->size() << endl;
			if (v->size() == 1)
			{
				v->erase(v->begin());
			}
			else
			{
				cout << "Enter the number of " << name_of_new_field << " you want to delete:\n";
				for (int i = 0; i < v->size(); i++){
					cout << i + 1 << ". " << (*v)[i]->get_phone() << endl;
				}
				int index;
				do{
					cin >> index;
					index--;
					if (index < 0 || index >= v->size()){
						cout << "You entered wrong number, please retry!\n";
					}
				} while (index < 0 || index >= v->size());
				v->erase(v->begin() + index);//(v.begin(), v.begin() + index);
				for (int i = 0; i < v->size(); i++){
					//cout << v[i]->get_email() << endl;
				}
				cout << "The information was deleted succesfully  :" << endl;
				cin.clear();

			}

		}
		if (it->second[0].compare("Text") == 0)
		{
			vector<Text*> *v = &(c->get_contact_properties()->get_text_type());
			cout << v->size() << endl;
			if (v->size() == 1)
			{
				v->erase(v->begin());
			}
			else
			{
				cout << "Enter the number of " << name_of_new_field << " you want to delete:\n";
				for (int i = 0; i < v->size(); i++){
					cout << i + 1 << ". " << (*v)[i]->get_text() << endl;
				}
				int index;
				do{
					cin >> index;
					index--;
					if (index < 0 || index >= v->size()){
						cout << "You entered wrong number, please retry!\n";
					}
				} while (index < 0 || index >= v->size());
				v->erase(v->begin() + index);//(v.begin(), v.begin() + index);
				for (int i = 0; i < v->size(); i++){
					//cout << v[i]->get_email() << endl;
				}
				cout << "The information was deleted succesfully  :" << endl;
				cin.clear();
			}
		}
		if (it->second[0].compare("Date") == 0)
		{
			vector<Date_*> *v = &(c->get_contact_properties()->get_date_type());
			cout << v->size() << endl;
			if (v->size() == 1)
			{
				v->erase(v->begin());
			}
			else
			{
				cout << "Enter the number of " << name_of_new_field << " you want to delete:\n";
				for (int i = 0; i < v->size(); i++){
					cout << i + 1 << ". " << (*v)[i]->to_string() << endl;
				}
				int index;
				do{
					cin >> index;
					index--;
					if (index < 0 || index >= v->size()){
						cout << "You entered wrong number, please retry!\n";
					}
				} while (index < 0 || index >= v->size());
				v->erase(v->begin() + index);//(v.begin(), v.begin() + index);
				for (int i = 0; i < v->size(); i++){
					//cout << v[i]->get_email() << endl;
				}
				cout << "The information was deleted succesfully  :" << endl;
				cin.clear();
			}

		}
	}

	else{

	}
}
void AddressBook::make_simple_search()
{
	cout << "Word to search : " << endl;
	string word;
	cin >> word;
	search->simple_search(word.data());
}
void AddressBook::make_search_by_field()
{
	cout << "Choose field : " << endl;
	string field, word;
	cin >> field;
	map<string, string*>::const_iterator it = cfg.find(field);
	string type = it->second[0];
	cout << "Word to search : " << endl;
	cin >> word;
	search->search_by_field(field.data(), type.data(), word.data());
}

void AddressBook::serialize(ofstream & writer)
{
	int size_contacts = get_contacts()->size();
	write_int_to_file(size_contacts, writer);
	for (int i = 0; i < contacts->size(); i++)
	{
		contacts->at(i)->serialize(writer);
	}
}
void AddressBook::deserialize(ifstream& reader)
{
	int size_contacts = read_int_from_file(reader);
	while (contacts != NULL && !contacts->empty())
	{
		delete contacts->back();
		contacts->pop_back();
	}
	if (contacts != NULL)
		delete contacts;
	contacts = new vector<Contact*>();
	for (int i = 0; i < size_contacts; i++){
		Contact * c = new Contact();
		c->deserialize(reader);
		add_contact(c);
	}
}

void AddressBook::print_address_book()
{
	cout << search->return_adrress_book_info() << endl;
}
string AddressBook::get_filename()
{
	return filename;
}
map<string, string*> AddressBook::get_map()
{
	return cfg;
}
void AddressBook::load(){
	ifstream  reader(filename.data(), ios::binary);
	deserialize(reader);
	reader.close();
}
void AddressBook::parse(ifstream & reader)
{
	string id, eq, val, cnt;
	while (reader >> id >> eq >> val >> cnt)
	{
		if (id[0] == '#') continue;
		if (eq != "=") cout << " Error " << endl;
		string* to_add = new string[2];
		to_add[0] = val;
		to_add[1] = cnt;
		cfg[id] = to_add;
	}

	/*for (map<string, string*>::const_iterator it = cfg.begin(); it != cfg.end(); it++)
	{
	cout << it->first << " = " << it->second[0] << " " << it->second[1] << endl;
	}*/

}

void AddressBook::help_enter_field(string& name_of_new_field, string& to_compare, Contact*& c)
{
	cout << "Enter contact's " << name_of_new_field << " please: \n";
	//cin.ignore();


	string to_add;
	getline(cin, to_add);
	//cout << to_add << endl;
	cin.clear();
	//cin.ignore();
	if (to_compare.compare("Date") != 0){
		name_of_new_field.append(": ");
		name_of_new_field.append(to_add);
	}

	to_add = name_of_new_field;
	//cin.ignore();

	if (to_compare.compare("Email") == 0){
		c->get_contact_properties()->add_email(to_add);
	}
	if (to_compare.compare("Phone") == 0){
		c->get_contact_properties()->add_phone_number(to_add);
	}
	if (to_compare.compare("Date") == 0){
		date* current_date = to_date(to_add);
		c->get_contact_properties()->add_date(current_date, name_of_new_field);
	}
	if (to_compare.compare("Text") == 0){
		c->get_contact_properties()->add_text(to_add);
	}
}

