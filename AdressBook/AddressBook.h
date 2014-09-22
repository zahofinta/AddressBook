#ifndef AddressBook_h
#define AddressBook_h
#include <vector>
#include "contact.h"
#include "Searcher.h"
#include "Serializable.h"
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;
class AddressBook:public Serializable
{
private:
		vector<Contact*>* contacts;
		Searcher* search;
		string filename;
		map<string,string*> cfg;
		void parse(ifstream&);
		date* to_date(string);
		void help_enter_field(string&, string&, Contact*&);
public:
		AddressBook();
		~AddressBook();
		vector<Contact*>* get_contacts();
		void add_contact( Contact*);
		void remove_contact(Contact *);
		void make_simple_search();
		void make_search_by_field();
		void edit_contact(Contact *);
		void serialize(ofstream &);
		void deserialize(ifstream &);
		void print_address_book();
		void load();
		string get_filename();
		map<string,string*> get_map();
		
};

#endif