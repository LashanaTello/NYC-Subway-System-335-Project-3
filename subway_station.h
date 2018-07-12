/*******************************************************************************
  Title          : subway_station.h
  Author         : Lashana Tello
  Created on     : May 3, 2018
  Description    : The interface file for the SubwayStation class
  Purpose        : To provide a means of representing a subway station in New 
									 York City
  Usage          : Use to store data pertaining to New York City's subway system
  Build with     : No building 
  Modifications  : 
 
*******************************************************************************/

#ifndef __SUBWAY_STATION_H__
#define __SUBWAY_STATION_H__

#include <vector>
#include <string>

/*******************************************************************************

		The SubwayStation class represents a set that contains entrances 
		(Entrance objects) that make up a station. The SubwayStation class doesn't 
		store actual Entrance objects; it's more like a tool used by another class, 
		SubwaySystem. SubwayStation contains a vector that stores the indices of 
		the entrances that make up the station. The actual Entrance objects are 
		stored in SubwaySystem's private vector. SubwayStation's identifier_ member 
		is equal to the line_identifier_ member of the Entrance objects that form 
		the station (all Entrance objects that make up a SubwayStation have 
		identical line_identifier_ members). SubwayStation's station_latitude_ and 
		station_longitude_ members are the centroid coordinates of each of its 
		Entrance object locations. There are 451 total subway station in 
		New York City.

*******************************************************************************/

class SubwayStation {
 public:
	//	Default constructor for SubwayStation object
	SubwayStation();

	//	Constructor for SubwayStation object
	SubwayStation(std::vector<unsigned int> indices_of_entrances, 
								std::string name, unsigned long identifier, double latitude,
								double longitude);

	//	Makes this SubwayStation object an exact copy of other_station
	SubwayStation(const SubwayStation& other_station);

	//	Destructor for SubwayStation object
	~SubwayStation();

	//	Returns a reference to a SubwayStation object that is an exact copy of
	//	other_station
	SubwayStation& operator=(const SubwayStation& other_station);

	//	Returns SubwayStation object's identifier_ member
	unsigned long get_identifier() const;

	//	Returns SubwayStation object's station_name_ member
	std::string get_station_name() const;

	//	Sets lat equal to SubwayStation object's station_latitude_ member and
	//	sets lon equal to SubwayStation object's station_longitude_ member
	void get_coordinates(double& lat, double& lon) const;

	//	Returns a vector containing the indicies of SubwayStation object's 
	//	entrances in SubwaySystem's vector of entrances
	std::vector<unsigned int> get_entrance_positions() const;

	//	Returns true if this SubwayStation object serves the subway line(s) 
	//	represented by other_line
	bool contains_line(const unsigned long& other_line) const;

	

 private:
	//	Vector that stores the index of each Entrance object that makes up
	//	this station. The indicies reference SubwaySystem's vector of
	//	Entrance objects
	std::vector<unsigned int> entrance_indices_;

	//	The name of the station, which is the name of one of its entrances
	std::string station_name_;

	//	A 32-bit mask that represents the line(s) that this station serves
	unsigned long identifier_;

	//	The latitude of the centroid of SubwayStation object's entrances and exits
	double station_latitude_;

	//	The longitude of the centroid of SubwayStation object's entrances and 
	//	exits
	double station_longitude_;
};

#endif

