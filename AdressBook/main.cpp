//#include <string.h>
//#include <vector>
#include "contact.h"
//#include <string>
//#include "contact.cpp"
//#include "Searcher.h"
#include "AddressBook.h"
//#include "AddressBook.cpp"
//#include "date.h"
#include <iostream>
#include <algorithm>
using namespace std;
void show_menu(){
		cout<<"1. View all contacts\n";
		cout<<"2. Simple search\n";
		cout<<"3. Search by field\n";
		cout<<"4. Add contact\n";
		cout<<"5. Remove contact\n";
		cout<<"6. Edit contact\n";
		cout<<"7. Sort contacts by name\n";
		cout<<"8. Sort by birthdate\n";
		cout<<"9. Exit\n";
}
bool compare_contacts_by_name(Contact*& c1, Contact*& c2)
{

	return (c1->get_name()).compare(c2->get_name()) < 0;

}
bool compare_contacts_by_date(Contact*& c1, Contact*& c2)
{
	cout << (*c2->get_birthday()).to_string();
	return c1->get_birthday()->operator<(*c2->get_birthday());
}


int main ()
{
		AddressBook ab;
		ifstream reader("contacts.txt", ios::binary);
		ab.deserialize(reader);
		int max_id = 0;
		for(int i = 0; i<ab.get_contacts()->size(); i++){
				if(ab.get_contacts()->at(i)->get_unique_id() > max_id){
						max_id = ab.get_contacts()->at(i)->get_unique_id();
				}
		}
		Contact::id_counter = max_id+1;
		show_menu();
		int choice;
		do{
			cout << "Enter your choice please: ";
			cin >> choice;
			if (choice == 1){
				system("cls");
				ab.print_address_book();
			}
			else if (choice == 2){
				system("cls");
				ab.make_simple_search();
			}
			else if (choice == 3){
				system("cls");
				ab.make_search_by_field();
			}
			else if (choice == 4){
				system("cls");
				Type* t = new Type();
				cout << "Enter contact's name: ";
				string name;
				string prefix = "Name: ";
				cin.ignore();
				cin.clear();
				getline(cin, name);
				prefix += name;
				name = prefix;
				
				string phone;
				cout << "Enter contact's phone: ";
				cin.clear();
				getline(cin, phone, '\n');
				prefix = "Mobile: ";
				prefix += phone;
				phone = prefix;

				t->add_phone_number(phone);
				t->add_text(name);
				Contact* c = new Contact(t);
				ab.add_contact(c);
				ofstream writer("contacts.txt", ios::binary|ios::out);
				ab.serialize(writer);
				writer.close();
			}
			else if (choice == 5){
				for (int i = 0; i < ab.get_contacts()->size(); i++){
					vector<Text*> t = ab.get_contacts()->at(i)->get_contact_properties()->get_text_type();
					for (int j = 0; j < t.size(); j++){
						if (t[j]->get_text().find_first_of("Name:") != string::npos)
							cout << i + 1 << ". " << t[j]->get_text() << endl;
					}
				}
				cout << "Enter the number of contact you want to delete: ";
				int number;
				do{
					cin >> number;
					if (number<1 || number>ab.get_contacts()->size()){
						cout << "Wrong number! Please try again: ";
					}
				} while (number<1 || number>ab.get_contacts()->size());
				number--;
				ab.get_contacts()->erase(ab.get_contacts()->begin()+number);
				ofstream writer("contacts.txt", ios::binary|ios::out);
				ab.serialize(writer);
				writer.close();
			}
			else if (choice == 6){
				for (int i = 0; i < ab.get_contacts()->size(); i++){
					vector<Text*> t = ab.get_contacts()->at(i)->get_contact_properties()->get_text_type();
					for (int j = 0; j < t.size(); j++){
						if (t[j]->get_text().find_first_of("Name:") != string::npos)
							cout << i + 1 <<". "<< t[j]->get_text() << endl;
					}
				}
				cout << "Enter the number of contact you want to edit: ";
				int number;
				do{
					cin >> number;
					if (number<1 || number>ab.get_contacts()->size()){
						cout << "Wrong number! Please try again: ";
					}
				} while (number<1 || number>ab.get_contacts()->size());
				number--;
				ab.edit_contact(ab.get_contacts()->at(number));
				ofstream writer("contacts.txt", ios::binary|ios::out);
				ab.serialize(writer);
				writer.close();
			}
			else if (choice == 7){
				sort(ab.get_contacts()->begin(), ab.get_contacts()->end(), compare_contacts_by_name);
				//ab.sort_contacts_by_name();
				string filename;
				cin >> filename;
				ofstream sorted_by_name_stream(filename.data(), ios::out);
				for (int i = 0; i < ab.get_contacts()->size(); i++){
					sorted_by_name_stream.write(ab.get_contacts()->at(i)->full_info().data(), ab.get_contacts()->at(i)->full_info().size());
				}
				sorted_by_name_stream.close();
			}
			else if (choice == 8){
					
				sort(ab.get_contacts()->begin(), ab.get_contacts()->end(), compare_contacts_by_date);
				string filename;
				cin >> filename;
				ofstream sorted_by_name_stream(filename.data(), ios::out);
				for (int i = 0; i < ab.get_contacts()->size(); i++){
					sorted_by_name_stream.write(ab.get_contacts()->at(i)->full_info().data(), ab.get_contacts()->at(i)->full_info().size());
				}
				sorted_by_name_stream.close();
			}
			if (choice != 9){
				show_menu();
			}
		}
		while (choice != 9);
		//ab.print_address_book();
	
	

		system("pause");
}


