
#pragma once
#include <string>  
#include <sstream>  
#include <vector>  
using namespace std;
class dev_pool
{
public:
	string url;
	string password;
	string username;
	string prefix;
	bool bPrefix;

	dev_pool() {
		prefix = "stratum+tcp://";
	}
	~dev_pool() {

	}
	string urlcodestring();
	string pool2string();
};

class dev_pools {
public:
	int Frequency;
	vector<dev_pool> pools;
	dev_pools() {

	}
	~dev_pools() {

	}
	string urlcodestring();
	string jsonpools();
};