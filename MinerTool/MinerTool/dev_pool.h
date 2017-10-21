
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
	string pool2string() {
		string s;
		if (bPrefix) {
			s = prefix.c_str();
		}
		s += url.c_str();
		s += "|";
		s = username.c_str();
		s += "|";
		s = password.c_str();
		s += "|";
		return s;
	}
};

class dev_pools {
public:
	int Frequency;
	vector<dev_pool> pools;
	dev_pools() {

	}
	~dev_pools() {

	}
	string jsonpools(){
		string s;
		int i = 1;
		char buf[255] = { 0 };
		vector<dev_pool>::iterator it;
		for (it = pools.begin(); it != pools.end()) {
			sprintf(buf, "Pool%d:", i);
			s += buf;
			s += it->pool2string();
			s += ",";
		}
		s += "Frequency:";
		sprintf(buf, "%d", Frequency);
		s += buf;
		return s;
	}
};