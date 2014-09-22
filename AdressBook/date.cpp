#include "date.h"
#include <sstream>
#include<ctime>
#include <iostream>
using namespace std;


date::date(){
		time_t current_time;
		time(&current_time);
		struct tm * now = localtime( & current_time );
		day = now->tm_mday;
		month = now->tm_mon+1;
		year = now->tm_year+1900;
}
date::date(int day, int month, int year){
		set_day(day);
		set_month(month);
		set_year(year);
}
date::date(date& d){
		set_day(d.day);
		set_month(d.month);
		set_year(d.year);
}

bool date::is_leap(){
		if(year%400 == 0) return true;
		else{
				if(year%100 == 0) return false;
				else{
						if(year%4==0) return true;
						return false;
				}
		}
}

bool date:: operator>(date& d){
		if(year>d.year) return true;
		if(year<d.year) return false;
		if(month>d.month) return true;
		if(month<d.month) return false;
		if(day>d.day) return true;
		else return false;
}

bool date::operator<(date& d){
		if(year<d.year) return true;
		 if(year>d.year) return false;
		if(month<d.month) return true;
		 if(month>d.month) return false;
		if(day<d.day) return true;
		else return false;
}

bool date::operator>=(date& d){
		if(year>d.year) return true;
		if(year<d.year) return false;
		if(month>d.month) return true;
		if(month<d.month) return false;
		if(day>=d.day) return true;
		else return false;
}

bool date::operator<=(date& d){
		if(year<d.year) return true;
		if(year>d.year) return false;
		if(month<d.month) return true;
		if(month>d.month) return false;
		if(day<=d.day) return true;
		else return false;
}

bool date::operator==(date& d){
		return year==d.year&&month==d.month&&day==d.day;
}

bool date::operator!=(date& d){
		return !(*this == d);
}

date date::operator++(){
		day++;
		if(month==4||month==6||month==9||month==11){
				if(day == 31){
						day = 1;
						month++;
				}
		}
		else{
				if(month == 2){
						if(is_leap()){
								if(day == 30){
										day = 1;
										month++;
								}
						}
						else{
								if(day == 29){
										day = 1;
										month++;
								}
						}
				}
				else{
						if(day == 32){
								day = 1;
								month++;
								if(month == 13){
										month = 1;
										year++;
								}
						}
				}
		}
		return *this;
}

date date::operator--(){
		day--;
		if(month==2||month==4||month==6||month==8||month==9||month==11||month==1){
				if(day==0){
						month--;
						day=31;
						if(month==0){
								month=12;
								year--;
						}
				}
		}
		else if(month==3)
		{
				if(is_leap()){
						day=29;
						month--;
				}
				else{
						day=28;
						month--;
				}
		}
		else
		{
				day=30;
				month--;
		}
		return *this;
}

int date::operator- (date& d){
		date d1(*this);
		if(d1<d){
				date temp = d;
				d = d1;
				d1 = temp;
		}
		int days_counter = 0;
		while(d<d1)
		{
				++d;
				days_counter++;
		}
		return days_counter;
}

int date::get_day(){
		return day;
}
int date::get_month(){
		return month;
}
int date::get_year(){
		return year;
}
void date::set_day(int value){
		day = value;
}
void date::set_month(int value){
		month = value;
}
void date::set_year(int value){
		year = value;
}
 string date::to_string(){
		stringstream stream;
		if(day<10)
				stream<<0;
		stream<<day<<'.';
		if(month<10)
				stream<<0;
		stream<<month<<'.';
		stream<<year<<'\0';
		string result = stream.str();
		//printf("%s\n", result);
		return result;
}
 string date::to_string(char divider){
		stringstream stream;
		if(day<10)
				stream<<0;
		stream<<day<<divider;
		if(month<10)
				stream<<0;
		stream<<month<<divider;
		stream<<year;
		string res=stream.str();
		return res;
}
 void date::serialize(ofstream & writer)
 {
		 write_int_to_file(day,writer);
		 write_int_to_file(month,writer);
		 write_int_to_file(year,writer);
 }
 void date::deserialize(ifstream & reader)
 {
		 int day=read_int_from_file(reader);
		 int month=read_int_from_file(reader);
		 int year=read_int_from_file(reader);
		 set_day(day);
		 set_month(month);
		 set_year(year);
 }
//da go prenapishem
/*void write_date_to_binary_file(ofstream& writer){
char d = char(day);
char m = char(month);
char* y = make_char_array_from_int(year);
/*int year_to_write = year;
for(int i = 3; i>=0; i--){
y[i] = 0;
y[i] = y[i]|year_to_write;
year_to_write = year_to_write>>8;
}
y[4] = '\0';
char date_to_write[7];
date_to_write[0] = d;
date_to_write[1] = m;
for(int i = 0; i<5; i++){
date_to_write[i+2] = y[i];
}
writer.write(date_to_write, sizeof(date_to_write));
cout<<5<<endl;
delete y;
}
string read_date_from_binary_file(ifstream& reader){

}*/

 

