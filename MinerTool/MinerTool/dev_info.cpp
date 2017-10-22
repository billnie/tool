#include "stdafx.h"
#include "dev_info.h"

bool dev_status::parseFromPTree(boost::property_tree::ptree&  pItem) {
	Code = pItem.get<std::string>("Code");
	Description = pItem.get<std::string>("Description");
	Msg = pItem.get<std::string>("Msg");
	STATUS = pItem.get<std::string>("STATUS");
	When = pItem.get<int>("When");
	return TRUE;
}

bool dev_item::parseFromPTree(boost::property_tree::ptree&  pItem) {
	ASC = pItem.get<std::string>("ASC");
	Name = pItem.get<std::string>("Name");
	Enabled = pItem.get<std::string>("Enabled");
	Status = pItem.get<std::string>("Status");
	ID = pItem.get<int>("ID");
	MHSav = pItem.get<double>("MHSav");
	MHS5s = pItem.get<double>("MHS5s");
	MHS1m = pItem.get<double>("MHS1m");
	MHS5m = pItem.get<double>("MHS5m");
	MHS15m = pItem.get<double>("MHS15m");
	Accepted = pItem.get<int>("Accepted");
	Rejected = pItem.get<int>("Rejected");
	HardwareErrors = pItem.get<int>("HardwareErrors");
	DeviceElapsed = pItem.get<int>("DeviceElapsed");
	temperature = pItem.get<double>("temperature");
	return TRUE;
}