/*******************************************************************************
  Title          : subway_station_hash.cpp
  Author         : Lashana Tello
  Created on     : May 3, 2018
  Description    : The implementation file for the SubwayStationHash class
  Purpose        : To provide fast access to subway stations in New York City's 
									 subway system
  Usage          : Use to store SubwayStation objects that contain data 
									 pertaining to New York City's subway system
  Build with     : No building 
  Modifications  : 
 
*******************************************************************************/

#include "subway_station_hash.h"
#include "haversine.h"
#include <ctype.h>
#include <iostream>


SubwayStationHash::SubwayStationHash(int size) :
    table_(size, HashEntry<SubwayStation>(SubwayStation())), current_size_(0)
{
} 

SubwayStationHash::SubwayStationHash(const SubwayStationHash& other_table) {
	table_ = other_table.table_;
	current_size_ = other_table.current_size_;
}

SubwayStationHash::~SubwayStationHash()
{
}

void SubwayStationHash::insert(const SubwayStation& station) {
	unsigned int position = find_pos(station.get_station_name());
	if (table_[position].active()) {
		return;
	}
	HashEntry<SubwayStation> entry(station, ACTIVE);
	table_[position] = entry;
	if (((unsigned)++current_size_) > (table_.size() / 2)) {
		rehash();
	}
}

void SubwayStationHash::remove(const std::string& station_name) {
	int position = hash(station_name);
	if (table_[position].active()) {
		table_[position].status = DELETED;
	}
}

void SubwayStationHash::clear() {
	for (auto& entry : table_) {
		entry.status = DELETED;
	}
}

const SubwayStation& SubwayStationHash::find(const std::string& station_name) 
    const {
	std::string lower_name = station_name;
	for (char& c : lower_name) {
		c = tolower(c);
	}
	unsigned int position = find_pos(lower_name);
	if (table_[position].active()) {
		return table_[position].data;
	}
	return kNotFound;
}

int SubwayStationHash::size() const {
	return current_size_;
}

void SubwayStationHash::add_stations_to_line(SubwayLine& a_line) const {
	for (auto& entry : table_) {
		if (entry.active()) {
			SubwayStation s(entry.data);
			if (s.contains_line(a_line.get_identifier())) {
				a_line.add_station(entry.data);
			}
		}
	}
}

std::vector<std::string> SubwayStationHash::all_stations() const {
	std::vector<std::string> stations;
	for (auto& entry : table_) {
		if (entry.active()) {
			SubwayStation s = entry.data;
			stations.push_back(s.get_station_name());
		}
	}
	return stations;
}

std::vector<std::string> SubwayStationHash::nearest_station(
    const double& latitude, const double& longitude) const {

	std::vector<std::string> station_names;
	SubwayStation s = table_[0].data;
	double lat, lon;
	s.get_coordinates(lat, lon);
	double distance;
	double smallest_distance = haversine(latitude, longitude, lat, lon);
	station_names.push_back(s.get_station_name());

	for (unsigned int i = 1; i < table_.size(); ++i) {
		if (table_[i].active()) {
			s = table_[i].data;
			s.get_coordinates(lat, lon);
			distance = haversine(latitude, longitude, lat, lon);
			if (distance < smallest_distance) {
				smallest_distance = distance;
				station_names.clear();
				station_names.push_back(s.get_station_name());
			} else if (distance == smallest_distance) {
				station_names.push_back(s.get_station_name());
			}
		}
	}
	return station_names;
}

void SubwayStationHash::nearest_line(const double& latitude,
																		 const double& longitude,
																		 unsigned long& lv) const {
	SubwayStation s = table_[0].data;
	double lat, lon;
	s.get_coordinates(lat, lon);
	double distance;
	double smallest_distance = haversine(latitude, longitude, lat, lon);
	lv |= s.get_identifier();

	for (unsigned int i = 1; i < table_.size(); ++i) {
		if (table_[i].active()) {
			s = table_[i].data;
			s.get_coordinates(lat, lon);
			distance = haversine(latitude, longitude, lat, lon);
			if (distance < smallest_distance) {
				smallest_distance = distance;
				lv &= 0UL;
				lv |= s.get_identifier();
			} else if (distance == smallest_distance) {
				lv |= s.get_identifier();
			}
		}
	}
}

/*******************************************************************************

																		PRIVATE

*******************************************************************************/

unsigned int SubwayStationHash::find_pos(const std::string& station_name) const
{
	int offset = 1;
	unsigned int pos = hash(station_name);
	SubwayStation s(table_[pos].data);
	std::string name_of_station = s.get_station_name();
	for (char& c : name_of_station) {
		c = tolower(c);
	}
	while (table_[pos].status != EMPTY && name_of_station != station_name) {
		pos += offset;
		offset += 2;
		if (pos >= table_.size()) {
			pos -= table_.size();
		}
		s = table_[pos].data;
		name_of_station = s.get_station_name();
		for (char& c : name_of_station) {
			c = tolower(c);
		}
	}
	return pos;
}

int SubwayStationHash::hash(std::string station_name) const {
	for (char& c : station_name) {
		c = tolower(c);
	}
	long long value = encode(station_name);
	return (value % table_.size());
}

long long SubwayStationHash::encode(const std::string station_name) const {
	long long value = 0;
	for (unsigned int i = 0; i < station_name.length(); ++i) {
		if ((i % 2) == 0) {
			value = station_name[i] + (38 * value);
		}
	}
	return value;
}

void SubwayStationHash::rehash() {
	std::vector< HashEntry<SubwayStation> > old_table = table_;
	current_size_ = 0;
	table_.resize(1973);
	for (auto& entry : table_) {
		entry.status = EMPTY;
	}
	for (auto& entry : old_table) {
		if (entry.active()) {
			insert(entry.data);
		}
	}
}
