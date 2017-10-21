
#include	"stdafx.h"
#include "dev_pool.h"
string dev_pool::pool2string() {
	string s;
	if (bPrefix) {
		s = prefix.c_str();
	}
	s += url.c_str();
	s += "|";
	s += username.c_str();
	s += "|";
	s += password.c_str();
//	s += "|";
	return s;
}
string dev_pools::jsonpools() {
	string s,ss;
	int i = 1;
	char buf[255] = { 0 };
	vector<dev_pool>::iterator it;
	s = "{";
	for (it = pools.begin(); it != pools.end();) {
		sprintf(buf, "\"Pool%d\":", i);
		s += buf; s += "\"";
		ss= it->pool2string();
		s += ss; s += "\"";
		s += ",";
		it++;	i++;
	}
	s += "\"Frequency\":";
	sprintf(buf, "%d", Frequency);
	s += buf;	s += "}";
	return s;
}