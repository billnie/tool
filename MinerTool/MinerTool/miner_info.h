#pragma once
#include <string>  
#include <sstream>  
#include <vector>  
using namespace std;
class miner_status {

};
class miner_pool {

};

class miner_info
{
public:
	vector<miner_status> status;
	vector<miner_pool> pools;
	miner_info();
	~miner_info();
};

