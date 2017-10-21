#pragma once
#include <string>  
#include <sstream>  
#include <vector>  
using namespace std;
class dev_item {
public:
	string ASC;
};
class dev_info
{
public:
	dev_info() {
		index_ = 0;
	}
	~dev_info() {

	}
public:
	static std::string INDEX;
	static std::string DEVS;
	static std::string STATUS;
	static std::string id;

private:
	int index_;
	std::string to_;
	std::string from_;
	std::string msg_;

public:
	dev_info(int index, const std::string& to, const std::string& from, const std::string& msg)
	{
		index_ = index;
		to_ = to;
		from_ = from;
		msg_ = msg;
	}
	int index()
	{
		return index_;
	}
	std::string to()
	{
		return to_;
	}
	std::string from()
	{
		return from_;
	}
	std::string msg()
	{
		return msg_;
	}

};

