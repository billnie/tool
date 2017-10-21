#pragma once
#include <string>  
#include <sstream>  
#include <vector>  
using namespace std;
class dev_item {
public:
	string ASC;
	string Name;
	string Enabled;
	int temperature;
};
class dev_status {
public:
	string STATUS;
	string Code;
	string Description;
	string Msg;
	int When;
};
class dev_info
{
public:
	dev_info() {

	}
	~dev_info() {

	}
public:
	static std::string INDEX;
	static std::string DEVS;
	static std::string STATUS;
	static std::string id;
	vector<dev_item> items;
	vector<dev_status>status;
private:

public:	
};

