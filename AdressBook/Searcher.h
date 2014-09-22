#ifndef Searcher_h
#define Searcher_h
#include "contact.h"
#include <vector>
#include <sstream>
#include <string>
using namespace std;
class Searcher
{ 
private:
		vector<Contact*>* AddressBook;
public:
		Searcher(vector<Contact*>*);
		~Searcher();
		void simple_search(const char*);
		void search_by_field(const char*, const char*, const char*);
		/*void add_contact(Contact *);
		void remove_contact(Contact*);*/
		vector<Contact*>* get_addressbook();
		string return_adrress_book_info();

};
#endif