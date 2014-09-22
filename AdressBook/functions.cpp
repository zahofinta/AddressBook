#include "functions.h"
#include <iostream>
using namespace std;
void  write_int_to_file(int p, ofstream& writer){

		//writer.open(filename,ios::binary);
		if(!writer.good()){ cout << "Error opening the file!\n";}
		writer.write((const char*)&p,sizeof(int));
		//unsigned int cur_pos=writer.tellp();
		//cout << cur_pos << endl;
}

int read_int_from_file(ifstream& reader){
		int p;
		if(!reader.good()){cout << "Error"<<endl;}
		reader.read((char*)&p ,sizeof(int) );
		return p;
}
vector<string> read_vector_of_strings_from_file(ifstream & reader)
{
		int len=read_int_from_file(reader);
		vector<string> read_phone_nums_and_emails(len);
		if(!reader.good()) { cout << "Error"<<endl;}
		for(int i=0;i<len;i++)
		{
				int p=read_int_from_file(reader);
				char* readed = new char[p+1];
				reader.read((char*)readed,p);
				readed[p] = '\0';
				read_phone_nums_and_emails.push_back(readed);
		}
		return read_phone_nums_and_emails;
}
