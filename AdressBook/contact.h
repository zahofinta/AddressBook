//#include <fstream>
//#include "functions.cpp"
//#include <string.h>
//using namespace std;
#ifndef contact_h
#define contact_h
#include <sstream>
#include <vector>
//#include "date.h"
#include "serializable.h"
#include "Type.h"


class Contact : public Serializable
{
private:
    int unique_id;	
		Type* contact_properties;
public:
		static int id_counter;
		Contact();
		Contact(Type*);
		~Contact();
		void set_unique_id();
		int get_unique_id();
		string full_info();
		void serialize(ofstream &);
		void deserialize(ifstream &);
		void set_contact_properties(Type*);
		Type* get_contact_properties();
		string get_name();
		date* get_birthday();

};
#endif