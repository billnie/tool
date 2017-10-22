#pragma once
#include <string>  
#include <sstream>  
#include <vector>  
#include <boost/property_tree/ptree.hpp>  

using namespace std;
class dev_item {
public:
	string ASC;
	string Name;
	int ID;
	string Enabled;
	string Status;
	int MHSav;
	int MHS5s;
	int MHS1m;
	int MHS5m;
	int MHS15m;
	int Accepted;
	int Rejected;
	int HardwareErrors;
	int DeviceElapsed;
	int temperature;

	bool parseFromPTree(boost::property_tree::ptree  &pItem);
};
class dev_status {
public:
	string STATUS;
	string Code;
	string Description;
	string Msg;
	int When;

	bool parseFromPTree(boost::property_tree::ptree  &pItem);
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
};

