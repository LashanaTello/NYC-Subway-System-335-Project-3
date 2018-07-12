/*******************************************************************************
  Title          : subway_station.cpp
  Author         : Lashana Tello
  Created on     : May 3, 2018
  Description    : The implementation file for the SubwayStation class
  Purpose        : To provide a means of representing a subway station in New 
									 York City
  Usage          : Use to store data pertaining to New York City's subway system
  Build with     : No building 
  Modifications  : 
 
*******************************************************************************/

#include "subway_station.h"

SubwayStation::SubwayStation() : entrance_indices_(), station_name_(""), 
    identifier_(0UL), station_latitude_(0), station_longitude_(0) 
{
}

SubwayStation::SubwayStation(std::vector<unsigned int> indices_of_entrances, 
														 std::string name, unsigned long identifier,
														 double latitude, double longitude) : 
    entrance_indices_(indices_of_entrances), station_name_(name), 
    identifier_(identifier), station_latitude_(latitude), 
    station_longitude_(longitude)
{
}

SubwayStation::SubwayStation(const SubwayStation& other_station) {
	entrance_indices_ = other_station.entrance_indices_;
	station_name_ = other_station.station_name_;
	identifier_ = other_station.identifier_;
	station_latitude_ = other_station.station_latitude_;
	station_longitude_ = other_station.station_longitude_;
}

SubwayStation::~SubwayStation() 
{
}

SubwayStation& SubwayStation::operator=(const SubwayStation& other_station) {
	entrance_indices_ = other_station.entrance_indices_;
	station_name_ = other_station.station_name_;
	identifier_ = other_station.identifier_;
	station_latitude_ = other_station.station_latitude_;
	station_longitude_ = other_station.station_longitude_;
	return *this;
}

unsigned long SubwayStation::get_identifier() const {
	return identifier_;
}

std::string SubwayStation::get_station_name() const {
	return station_name_;
}

void SubwayStation::get_coordinates(double& lat, double& lon) const {
	lat = station_latitude_;
	lon = station_longitude_;
}

std::vector<unsigned int> SubwayStation::get_entrance_positions() const {
	return entrance_indices_;
}

bool SubwayStation::contains_line(const unsigned long& other_line) const {
	if ((identifier_ & other_line) == other_line) {
		return true;
	}
	return false;
}
