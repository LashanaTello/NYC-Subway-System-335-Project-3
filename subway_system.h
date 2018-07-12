/*******************************************************************************
  Title          : subway_system.h
  Author         : Lashana Tello
  Created on     : May 3, 2018
  Description    : The interface file for the SubwaySystem class
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

#ifndef __SUBWAY_SYSTEM_H__
#define __SUBWAY_SYSTEM_H__

#include "subway_entrance.h"
#include "subway_station_hash.h"
#include "subway_line_hash.h"
#include <utility>
#include <vector>
#include <string>

/*******************************************************************************

		The SubwaySystem class acts as database for the New York City subway system. 
		It encapsulates a vector that stores pairs of Entrance objects and an 
		index, a SubwayStationHash object, and a SubwayLineHash object. The vector 
		represents disjoint sets of Entrance objects. Meaning, the vector is 
		a bunch of parent trees of entrances. The parent entrance’s second pair 
		value will always be negative and reflects how many entrances are in its 
		set, including itself. All other entrances that are not parents are 
		children, and their second pair value will always be a positive integer, 
		which is the index of its parent in the vector. The vector is used to 
		create SubwayStation objects, and SubwayStation objects are used to create 
		SubwayLine objects. The SubwayStationHash object is a hash table that 
		provides fast access to all SubwayStation objects. The SubwayLineHash object 
		is a hash table that provides fast access to SubwayLine objects. When a 
		SubwaySystem object is created, all Entrance objects must be added to it 
		first, and then the method make_subway_system must be called to create the 
		SubwayStation objects, the SubwayLine objects, the SubwayStationHash object, 
		and the SubwayLineHash object. SubwaySystem uses the enumerated type 
		LineValue that is defined in the Entrance class's header file. 
		There are 451 subway stations and 26 train lines in New York City. 

*******************************************************************************/

class SubwaySystem {
 public:
	//	Default constructor for SubwaySystem object
	SubwaySystem();

	//	Destroys SubwaySystem object
	~SubwaySystem();

	//	Adds entrance to SubwaySystem's entrances_ member
	void add(const Entrance& entrance);

	//	Creates subway system database
	void make_subway_system();

	//	Displays all the station names of the stations that the train line whose 
	//	name is line_name stops at
	void list_line_stations(std::string& line_name);

	//	Displays all the stations in the subway system
	void list_all_stations() const;

	//	Displays all the entrances that make up the station named name_of_station
	void list_entrances(const std::string& name_of_station) const;

	//	Displays the closest station(s) to the given latitude and longitude point
	void nearest_station(const double& latitude, const double& longitude) const;

	//	Displays the closest train line(s) to the given latitude and longitude 
	//	point
	void nearest_line(const double& latitude, const double& longitude) const;

	//	Displays the closest entrance to the given latitude and longitude point
	void nearest_entrance(const double& latitude, const double& longitude) const;

	//	Returns the number of entrances in SubwaySystem
	int entrances() const;
	
	//	Returns the number of stations in SubwaySystem
	int stations() const;

 private:
	//	Vector that represents disjoint sets of Entrance objects and is used to
	//	create SubwayStation objects
	//	The pair's first value is an Entrance object and the pair's second value
	//	is the index of the Entrance object's parent
	std::vector< std::pair<Entrance, int> > entrances_;

	//	Hash table that stores SubwayStation objects
	SubwayStationHash station_table_;

	//	Hash table that stores SubwayLine objects
	SubwayLineHash line_table_;

	//	Performs a union on two disjoint sets in entrances_
	//	Whichever root has the deeper tree (whichever set is bigger), is the root
	//	whose tree will be added to
	void unionize(int root1, int root2);

	//	Compresses the parent tree that x is a part of by making each of its 
	//	children point directly to the parent
	void find(int x);

	//	Returns the second value of the pair stored at index x in entrances_
	//	Compresses the parent tree that x is a part of and makes x and all of x's 
	//	parents point directly to the root of the parent tree that x is a part of
	int find(int x, int& count);

	//	Creates all SubwayStation objects and hashes them into station_table_
	void make_stations();

	//	Creates all SubwayLine objects and hashes them into line_table_
	void make_lines();
};

//	Returns true if c1 and c2 are whitespace characters
bool are_spaces(char c1, char c2);

//	Returns the string representation of lv, whose actual type is LineValue but
//	technically, LineValue is an integer so it can be treated as an integer in 
//	some ways
std::string convert_to_string(const int& lv);

#endif

