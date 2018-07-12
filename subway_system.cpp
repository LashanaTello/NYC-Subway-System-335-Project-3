/*******************************************************************************
  Title          : subway_system.cpp
  Author         : Lashana Tello
  Created on     : May 3, 2018
  Description    : The implementation file for the SubwaySystem class
  Purpose        : To provide a means of representing New York City's subway 
									 system
  Usage          : To serve as a database of New York City's subway system and 
									 allow user to query about the subway system, such as, the 
									 closest subway stations, subway entrances, and subway lines 
									 to a user-given latitude and longitude, all the entrances at 
									 a particular station, all the stations that serve a 
									 particular train line, and all the subway stations
  Build with     : No building 
  Modifications  : 
 
*******************************************************************************/

#include "subway_system.h"
#include "subway_station.h"
#include "subway_station_hash.h"
#include "subway_line_hash.h"
#include "haversine.h"
#include <stdlib.h>
#include <algorithm>
#include <iomanip>
#include <iostream>

SubwaySystem::SubwaySystem() : entrances_(), station_table_(), line_table_()
{
}

SubwaySystem::~SubwaySystem()
{
}

void SubwaySystem::add(const Entrance& entrance) {
	std::pair<Entrance, int> entrance_set(entrance, -1);
	double lat1, lat2, lon1, lon2;
	entrance.get_coordinates(lat1, lon1);
	entrances_.push_back(entrance_set);

	for (unsigned int i = 0; i < entrances_.size() - 1; ++i) {
		Entrance e(entrances_[i].first);
		e.get_coordinates(lat2, lon2);
		if (entrance.same_line(e.get_identifier())) {
			if (0.28 >= haversine(lat1, lon1, lat2, lon2)) {
				unionize(i, entrances_.size() - 1);
				return;
			}
		}
	}
}

void SubwaySystem::make_subway_system() {
	make_stations();
	make_lines();
}

void SubwaySystem::list_line_stations(std::string& line_name) {
	for (char& c : line_name) {
		c = toupper(c);
	}
	LineValue lv = get_linevalue(line_name);
	if (lv == DEFAULT) {
		std::cout << "Line named '" << line_name << "' does not exist" << std::endl;
	} else {
		SubwayLine line = line_table_.find(line_name);
		std::vector<SubwayStation> line_stations = line.get_stations();

		std::cout << "Stations serving Line " << line_name << ":" << std::endl;
		for (auto& i : line_stations) {
			SubwayStation s(i);
			std::cout << s.get_station_name() << std::endl;
		}
	}
	std::cout << std::endl;
}

void SubwaySystem::list_all_stations() const {
	std::vector<std::string> stations = station_table_.all_stations();
	std::cout << "All stations:" << std::endl;
	for (auto& name : stations) {
		std::cout << name << std::endl;
	}
	std::cout << std::endl;
}

void SubwaySystem::list_entrances(const std::string& name_of_station) const {
	//	eliminate extra spaces in name_of_station
	std::string station_name = name_of_station;
	station_name.erase(std::unique(station_name.begin(), station_name.end(),
																 are_spaces), station_name.end());
	

	SubwayStation s(station_table_.find(station_name));
	if (s.get_station_name() == "") {
		std::cout << "Station '" << station_name << "' does not exist" << std::endl;
	} else {
		std::vector<unsigned int> entrance_indices = s.get_entrance_positions();

		std::cout << "The entrances for station '" << station_name << "' are:";
		std::cout << std::endl;

		for (auto& i : entrance_indices) {
			Entrance e(entrances_[i].first);
			std::string name = e.get_entrance_name();
			if (name[name.length() - 1] != ')') {
				std::cout << name << std::endl;
			}
		}
	}
	std::cout << std::endl;
}

void SubwaySystem::nearest_station(const double& latitude, 
																	 const double& longitude) const {

	std::vector<std::string> names = station_table_.nearest_station(latitude,
																																	longitude);

	std::cout << "Stations nearest to " << std::setprecision(12) << latitude;
	std::cout << ", " << std::setprecision(12) << longitude << ":";
	std::cout << std::endl;

	for (auto& i : names) {
		std::cout << i << std::endl;
	}
	std::cout << std::endl;
}

void SubwaySystem::nearest_line(const double& latitude, const double& longitude)
																const {
	unsigned long line_mask = 0UL;
	station_table_.nearest_line(latitude, longitude, line_mask);

	std::cout << "Nearest lines to " << std::setprecision(12) << latitude;
	std::cout << ", " << std::setprecision(12) << longitude << ":";
	std::cout << std::endl;
	for (int i = A; i < DEFAULT; ++i) {
		unsigned long mask = 1UL << i;
		if ((line_mask & mask) == mask) {
			std::cout << convert_to_string(i) << std::endl;
		}
	}
	std::cout << std::endl;
}

void SubwaySystem::nearest_entrance(const double& latitude,
																		const double& longitude) const {
	std::vector<std::string> entrance_names;
	Entrance e = entrances_[0].first;
	double lat, lon;
	e.get_coordinates(lat, lon);
	double distance;
	double smallest_distance = haversine(latitude, longitude, lat, lon);
	entrance_names.push_back(e.get_entrance_name());

	for (unsigned int i = 1; i < entrances_.size(); ++i) {
		e = entrances_[i].first;
		e.get_coordinates(lat, lon);
		distance = haversine(latitude, longitude, lat, lon);
		if (distance < smallest_distance) {
			smallest_distance = distance;
			entrance_names.clear();
			entrance_names.push_back(e.get_entrance_name());
		} else if (distance == smallest_distance) {
			entrance_names.push_back(e.get_entrance_name());
		}
	}

	std::cout << "Nearest entrances to " << std::setprecision(12) << latitude;
	std::cout << ", " << std::setprecision(12) << longitude << ":";
	std::cout << std::endl;
	for (auto& i : entrance_names) {
		std::cout << i << std::endl;
	}
	std::cout << std::endl;
}

int SubwaySystem::entrances() const {
	return entrances_.size();
}

int SubwaySystem::stations() const {
	return station_table_.size();
}

/*******************************************************************************

																		PRIVATE

*******************************************************************************/

void SubwaySystem::unionize(int root1, int root2) {
	if ((unsigned)root1 >= entrances_.size() || 
			(unsigned)root2 >= entrances_.size()) {
		return;
	}
	if (root1 != root2) {
		if(entrances_[root2].second < entrances_[root1].second) {
			// root2 is deeper
			if (entrances_[root1].second > 0) {
				entrances_[root2].second = root1;
			} else {
				entrances_[root2].second += entrances_[root1].second;
				entrances_[root1].second = root2;
			}
		}
		else {
			// root1 is deeper
			if (entrances_[root2].second > 0) {
				entrances_[root1].second = root2;
			} else {
				entrances_[root1].second += entrances_[root2].second;
				entrances_[root2].second = root1;
			}
		}
	}
}

void SubwaySystem::find(int x) {
	int count = 0;
	find(x, count);
}

//	if find(x, count) is called just once, it means that x  pointed directly to
//	its parent
//	every call above one (meaning, count is greater than 1) represents a child
//	that isn't directly connected to its parent
//	When the parent of x is found, it will point directly to it but the parent's
//	second member will not reflect the total number of kids it has, which is why
//	parent's second member must be updated
int SubwaySystem::find(int x, int& count) {
	if ((unsigned)x >= entrances_.size()) {
		return entrances_.size();
	}
	if (entrances_[x].second < 0) {
		//	change the parent's second value to reflect the number of children it 
		//	has
		if (count > 1) {
			while (count != 1) {
				--entrances_[x].second;
				--count;
			}
		}
		return x;
	} else {
		++count;	//	count keeps track of how many times find(x, count) is called
		return entrances_[x].second = find(entrances_[x].second, count);
	}
}

void SubwaySystem::make_stations() {
	//	make all children point directly to their parent
	for (unsigned int i = 0; i < entrances_.size(); ++i) {
		find(i);
	}

	for (unsigned int i = 0; i < entrances_.size(); ++i) {
		if (entrances_[i].second < 0) {	//	entrances_[i] is a root
			std::vector<unsigned int> indices;
			indices.push_back(i);
			Entrance e1(entrances_[i].first);
			std::string station_name = e1.get_entrance_name();
			unsigned long line_value = e1.get_identifier();
			double lat, lon;
			e1.get_coordinates(lat, lon);

			if (entrances_[i].second < -1) {
				int children = entrances_[i].second + 1;
				for (unsigned int j = i + 1; j < entrances_.size(); ++j) {
					if (entrances_[j].second == (signed)i) {
						indices.push_back(j);	//	add index of child
						double latitude, longitude;
						Entrance e2(entrances_[j].first);
						e2.get_coordinates(latitude, longitude);
						lat += latitude;	//	do this to calculate centroid
						lon += longitude;
						++children;
					}
					if (children == 0) {	//	stop when all children found
						break;
					}
				}
				//	calculate centroid value of station
				lat = lat / (abs(entrances_[i].second));
				lon = lon / (abs(entrances_[i].second));
			}
			SubwayStation station(indices, station_name, line_value, lat, lon);
			station_table_.insert(station);
		}
	}
}

void SubwaySystem::make_lines() {
	for (int i = A; i < DEFAULT; ++i) {
		unsigned long mask = 1UL << i;
		SubwayLine a_line(convert_to_string(i), mask);
		station_table_.add_stations_to_line(a_line);
		line_table_.insert(a_line);
	}
}

bool are_spaces(char c1, char c2) {
	return ((c1 == c2) && (c1 == ' '));
}

std::string convert_to_string(const int& lv) {
	std::string name_of_line;
	switch (lv) {
		case A:
			name_of_line = "A";
			break;
		case B:
			name_of_line = "B";
			break;
		case C:
			name_of_line = "C";
			break;
		case D:
			name_of_line = "D";
			break;
		case E:
			name_of_line = "E";
			break;
		case F:
			name_of_line = "F";
			break;
		case G:
			name_of_line = "G";
			break;
		case H:
			name_of_line = "H";
			break;
		case J:
			name_of_line = "J";
			break;
		case L:
			name_of_line = "L";
			break;
		case M:
			name_of_line = "M";
			break;
		case N:
			name_of_line = "N";
			break;
		case Q:
			name_of_line = "Q";
			break;
		case R:
			name_of_line = "R";
			break;
		case S:
			name_of_line = "S";
			break;
		case Z:
			name_of_line = "Z";
			break;
		case ONE:
			name_of_line = "1";
			break;
		case TWO:
			name_of_line = "2";
			break;
		case THREE:
			name_of_line = "3";
			break;
		case FOUR:
			name_of_line = "4";
			break;
		case FIVE:
			name_of_line = "5";
			break;
		case SIX:
			name_of_line = "6";
			break;
		case SEVEN:
			name_of_line = "7";
			break;
		case SIR:
			name_of_line = "SIR";
			break;
		case FS:
			name_of_line = "FS";
			break;
		case GS:
			name_of_line = "GS";
			break;
		default:
			name_of_line = "";
			break;
	}
	return name_of_line;
}

