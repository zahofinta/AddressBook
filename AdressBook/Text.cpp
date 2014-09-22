
#include "Text.h"

Text::Text(){};

Text::~Text(){};

Text::Text(const string& value)
{
 text=value;
 set_content(value);
}

Text::Text(string& value)
{
		set_text(value);
		set_content(value);
}

void Text::set_text(string& value)
{
		text=value;

}

string Text ::get_text()
{
 return text;
}
void Text::serialize(ofstream& writer)
{
		write_int_to_file(text.size(), writer);
		writer.write(text.data(), text.size());
}
void Text::deserialize(ifstream& reader){
		int s = read_int_from_file(reader);
		char* text_array = new char[s+1];
		reader.read(text_array, s);
		text_array[s] = '\0';
		text = text_array;
		set_content(text);
}
