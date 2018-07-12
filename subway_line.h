/*******************************************************************************
  Title          : subway_line.h
  Author         : Lashana Tello
  Created on     : May 3, 2018
  Description    : The interface file for the SubwayLine class
  Purpose        : To provide a means of representing a train line in New York 
									 City's subway system
  Usage          : Use to store data pertaining to New York City's subway system
  Build with     : No building 
  Modifications  : 
 
*******************************************************************************/

#ifndef __SUBWAY_LINE_H__
#define __SUBWAY_LINE_H__

#include <vector>
#include <string>
#include "subway_station.h"

/*******************************************************************************

		The SubwayLine class represents a train line in New York City's subway 
		system. A train line has its own unique route, meaning it stops at many 
		different subway stations. So in its private section, a SubwayLine object 
		contains a vector storing all the SubwayStation objects that it stops at. 
		The order of the SubwayStation objects in the container does not correspond 
		to the order in which the train line stops at each station. Also in private,
		the SubwayLine class contains a string that tells you the name of the line, 
		(such as "A", "B", or "SIR"), an unsigned long 32-bit mask, which is the 
		unique integer representation of the line. The bitmask is created using the 
		line's string name to get its corresponding LineValue, and its LineValue 
		will be the number of times a single 1 is shifted to the left in a 32-bit 
		mask.  Additionally, the identifier_ member of all SubwayStation objects in 
		SubwayLine's vector contains the SubwayLine's identifier_ member. Meaning, 
		the bit representing a specific SubwayLine in SubwayStation's identifier_ 
		member is set to 1. There are 26 train lines in New York City. 

*******************************************************************************/

class SubwayLine {
 public:
	//	Default constructor for SubwayLine object
	SubwayLine();

	//	Constructor for SubwayLine object
	SubwayLine(std::string line_name, unsigned long identifier);

	//	Creates SubwayLine object that is an exact copy of other_subway_line
	SubwayLine(const SubwayLine& other_subway_line);

	//	Destroys SubwayLine object
	~SubwayLine();

	//	Returns a reference to a SubwayLine obejct that is an exact copy of
	//	other_subway_line
	SubwayLine& operator=(const SubwayLine& other_subway_line);

	//	Returns SubwayLine's identifier_ member
	unsigned long get_identifier() const;

	//	Adds station to SubwayLine's stops_ member
	void add_station(const SubwayStation& station);

	//	Returns SubwayLine's line_name_ member
	std::string get_line_name() const;

	//	Returns SubwayLine's stops_ member
	std::vector<SubwayStation> get_stations() const;

 private:
	//	String representing the name of this subway line
	std::string line_name_;

	//	Unique 32-bit mask that is the integer representation of this subway line
	unsigned long identifier_;

	//	Vector of all stations that this subway line stops at. The order of the
	//	stations in the container does not correspond to the real life order that
	//	the subway line stops at these stations
	std::vector<SubwayStation> stops_;
};

#endif

