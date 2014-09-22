#ifndef serializable_h
#define serializable_h
#include <fstream>
using namespace std;
class Serializable
{
		virtual void serialize(ofstream &)=0;
		virtual void deserialize(ifstream &) = 0;
};
#endif