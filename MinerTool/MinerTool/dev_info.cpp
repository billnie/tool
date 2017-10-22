#include "stdafx.h"
#include "dev_info.h"


bool dev_status::parseFromPTree(boost::property_tree::ptree  &pItem) {
	Code = pItem.get<std::string>("Code");
	Description = pItem.get<std::string>("Description");
	Msg = pItem.get<std::string>("Msg");
	STATUS = pItem.get<std::string>("STATUS");
	When = pItem.get<double>("When");
	return TRUE;
}

bool dev_item::parseFromPTree(boost::property_tree::ptree  &pItem) {
	ASC = pItem.get<std::string>("ASC");
	Name = pItem.get<std::string>("Name");
	Enabled = pItem.get<std::string>("Enabled");
	Status = pItem.get<std::string>("Status");
	ID = pItem.get<int>("ID");
	MHSav = pItem.get<int>("MHSav");
	MHS5s = pItem.get<int>("MHS5s");
	MHS1m = pItem.get<int>("MHS1m");
	MHS5m = pItem.get<int>("MHS5m");
	MHS15m = pItem.get<int>("MHS15m");
	Accepted = pItem.get<int>("Accepted");
	Rejected = pItem.get<int>("Rejected");
	HardwareErrors = pItem.get<int>("HardwareErrors");
	DeviceElapsed = pItem.get<int>("DeviceElapsed");
	temperature = pItem.get<int>("temperature");
	return TRUE;
}
