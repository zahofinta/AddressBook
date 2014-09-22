#ifndef date_h
#define date_h
#include <string>
#include "Serializable.h"
#include "functions.h"
using namespace std;
class date:public Serializable
{
private:
		int day;
		int month;
		int year;

public:
		date();
		date(int,int,int);
		date(date & );
		bool is_leap();
		bool operator>(date & );
		bool operator<( date &);
		bool operator>=(date &);
		bool operator<=(date &);
		bool operator==(date &);
		bool operator!=(date &);
		date operator++();
		date operator--();
		int operator-(date &);
		int get_day();
		int get_month();
		int get_year();
		void set_day(int);
		void set_month(int);
		void set_year(int); 
		string to_string();
		string to_string(char);
		void serialize(ofstream &);
		void deserialize(ifstream &);
		
};

#endif