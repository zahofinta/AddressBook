#ifndef SearchObject_h
#define SearchObject_h
class SearchObject{
private:
	string content;
public:
	void set_content(const string& content){
		this->content = content;
	}
	string get_content()
	{
		return content;
	}
};
#endif