#pragma once
#include <string>  
#include <sstream>  
#include <vector>  
using namespace std;
class miner_status {
	std::string STATUS;
	UINT64		When;
	UINT32		Code;
	std::string Msg;
	std::string Description;
};
class miner_pool {
	UINT32		POOL;
	std::string	URL;
	std::string	Status;
	UINT32		Priority;
	UINT32		Quota;
	std::string	LongPoll;
	UINT32		Getworks;
	UINT32		Accepted;
	UINT32		Rejected;
	UINT32		Works;
	UINT32		Discarded;
	UINT32		Stale;
	UINT32		GetFailures;
	UINT32		RemoteFailures;
	std::string	User;
	std::string	Passwd;
	UINT64		LastShareTime;
	UINT32		Diff1Shares;
	std::string	ProxyType;
	std::string	Proxy;
	UINT32		DifficultyAccepted;
	UINT32		DifficultyRejected;
	UINT32		DifficultyStale;
	UINT32		LastShareDifficulty;
	BOOL		HasStratum;
	BOOL		StratumActive;
	std::string	StratumURL;
	BOOL		HasGBT;
	UINT32		BestShare;
	UINT32		PoolRejected;
	UINT32		PoolStale;
	UINT32		BadWork;
};

class miner_info
{
public:
	vector<miner_status> status;
	vector<miner_pool> pools;
	miner_info();
	~miner_info();
};

