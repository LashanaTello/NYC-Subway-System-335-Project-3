/*******************************************************************************
  Title          : subway_station_hash.h
  Author         : Lashana Tello
  Created on     : May 3, 2018
  Description    : The interface file for the SubwayStationHash class
  Purpose        : To provide fast access to subway stations in New York City's 
									 subway system
  Usage          : Use to store SubwayStation objects that contain data 
									 pertaining to New York City's subway system
  Build with     : No building 
  Modifications  : 
 
*******************************************************************************/

#ifndef __SUBWAY_STATION_HASH_H__
#define __SUBWAY_STATION_HASH_H__

#include <vector>
#include <string>
#include "hash_entry.cpp"
#include "subway_station.h"
#include "subway_line.h"

/*******************************************************************************

		The SubwayStationHash class is a hash table that stores SubwayStation 
		objects. Its default size is 977 since there are 451 subway stations in 
		New York City. This table uses a division-based hash function to insert 
		SubwayStation objects. This table stores the SubwayStation objects using a 
		vector of HashEntry objects that store SubwayStation objects. 
		SubwayStationHash contains a few methods that answer queries about 
		SubwayStation objects, such as the nearest station or line to given 
		latitude and longitude coordinates and displaying the names of all stations 
		in the table. It also contains a method that helps construct a SubwayLine 
		object by adding stations that serve that particular line to SubwayLine's 
		private vector. 

*******************************************************************************/

const SubwayStation kNotFound;

class SubwayStationHash {
 public:
	//	Creates a SubwayStationHash object whose default size is 977 if an integer
	//	argument is not provided
	explicit SubwayStationHash(int size = 977);

	//	Creates a SubwayStationHash object that is an exact copy of other_table
	SubwayStationHash(const SubwayStationHash& other_table);

	//	Destroys SubwayStationHash object
	~SubwayStationHash();

	//	Inserts station into SubwayStationHash object's table_
	void insert(const SubwayStation& station);

	//	Removes SubwayStation object whose name is station_name from table_
	void remove(const std::string& station_name);

	//	Removes all SubwayStation objects from table_
	void clear();

	//	Returns an unmodifiable reference to a SubwayStation object if it exists
	//	in this SubwayStationHash object. If it does not exist, returns kNotFound
	const SubwayStation& find(const std::string& station_name) const;

	//	Returns SubwayStationHash object's current_size_ member
	int size() const;

	//	Helps build SubwayLine object by adding SubwayStation objects to
	//	SubwayLine's private vector
	void add_stations_to_line(SubwayLine& a_line) const;

	//	Returns a vector that contains the names of every station in this 
	//	SubwayStationHash object
	std::vector<std::string> all_stations() const;

	//	Returns a vector that contains the name(s) of the closest station(s) to
	//	the given latitude and longitude corrdinates
	std::vector<std::string> nearest_station(const double& latitude, 
																					 const double& longitude) const;

	//	Changes lv to reflect the integer value of the closest subway lines to the
	//	given latitude and longitude coordinates
	void nearest_line(const double& latitude, const double& longitude,
										unsigned long& lv) const;

 private:
	//	Vector that stores SubwayStation objects
	std::vector< HashEntry<SubwayStation> > table_;
	
	//	An integer representing how many SubwayStation objects are in table_
	int current_size_;

	//	Returns an integer that is the index in table_ at which the SubwayStation
	//	object whose name is station_name will be inserted. Finds a position for
	//	the SubwayStation object in table_
	unsigned int find_pos(const std::string& station_name) const;

	//	Returns an integer that is the index in table_ at which the SubwayStation
	//	object whose name is station_name will be inserted
	int hash(std::string station_name) const;

	//	Returns a very large integer value representing station_name
	long long encode(const std::string station_name) const;

	//	When table_ becomes half full, increases table_'s capacity more than two
	//	times its current capacity and rehashes all of its entries into table_
	void rehash();
};

#endif

