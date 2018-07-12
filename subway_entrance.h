/*******************************************************************************
  Title          : subway_entrance.h
  Author         : Lashana Tello
  Created on     : May 3, 2018
  Description    : The interface file for the Entrance class
  Purpose        : To provide a means of representing an entrance in New York
									 City's subway system
  Usage          : Use to store data pertaining to New York City's subway system
  Build with     : No building 
  Modifications  : 
 
*******************************************************************************/

#ifndef __SUBWAY_ENTRANCE_H__
#define __SUBWAY_ENTRANCE_H__

#include <vector>
#include <string>

/*******************************************************************************

		The Entrance class stores information about a single entrance in New 
		York City's subway system. The information stored by the Entrance 
		class comes from a file provided by the Metropolitan Transit Authority 
		(MTA). The file stores all subway station entrances and exits. Its private 
		member variables all store a piece of data from the file. The Entrance
		object must be used with the enumerated type LineValue. LineValue
		is the integer representation of the name of a subway line. For example,
		the A line's corresponding LineValue is A, which is equal to 0. The B line's
		corresponding LineValue is B, which is equal to 1, and so on.

		Entrance's line_identifier_ member is a 32-bit mask that represents
		the subway lines that are accessible from this entrance. The bitmask is 
		created by shifting a 1 a number of times equal to the line's corresponding
		LineValue. For example, the C line's corresponding LineValue is 2. So in
		order to create a bitmask that represents the C line, you would shift a 1
		two times to the left. So the numerical value that represents the C line is
		4 and the bitmask for it is 00000000000000000000000000000100.

		If there is more than one line accessible from an entrance, you would OR the
		bitmask that represents each line. For example, the bitmask representing the
		A line is 00000000000000000000000000000001 since A's LineValue is 0 so you 
		would shift a 1 zero times to the left. To create a bitmask for an entrance 
		that serves the A and C line, you OR each line's bitmask. 
		00000000000000000000000000000100 OR 00000000000000000000000000000001 = 
		00000000000000000000000000000101, and its numerical value is 5. 
		It's easy and fast to get the line's string representation from the bitmask, 
		to add lines to an entrance, to determine if two entrances serve the same 
		line, and to determine if an entrance serves a particular line.

*******************************************************************************/


enum LineValue {
	A = 0,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	J,
	L,
	M,
	N,
	Q,
	R,
	S,
	Z,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	SIR,
	FS,
	GS,
	DEFAULT
};

class Entrance {
 public:
	//	Default constructor for Entrance object
	Entrance();

	//	Creates Entrance object
	//	@param id: the unique identification number of the entrance
	//	@param url:
	//	@param name: will be the name of the Entrance object
	//	@param latitude and longitude: will be the Entrance object's latitude_ and
	//	longitude_ members, respectively
	//	@param lines: contains the string representation of each subway line this
	//	entrance serves
	Entrance(int id, std::string url, std::string name, double latitude, 
					 double longitude, std::vector<std::string> lines);
	
	//	Creates Entrance object that is an exact copy of other_entrance
	Entrance(const Entrance& other_entrance);

	//	Destroys Entrance object
	~Entrance();

	//	Returns reference to Entrance object that is an exact copy of 
	//	other_entrance
	Entrance& operator=(const Entrance& other_entrance);

	//	Returns Entrance object's line_identifier_ member
	unsigned long get_identifier() const;

	//	Sets lat equal to Entrance object's latitude_ member and
	//	sets lon equal to Entrance object's longitude_ member
	void get_coordinates(double& lat, double& lon) const;

	//	Returns Entrance object's name_ member
	std::string get_entrance_name() const;

	//	Returns true if Entrance object's line_identifier_ member is equal to
	//	other_line. Returns false otherwise
	bool same_line(const unsigned long& other_line) const;

 private:
	//	Unique identification number of Entrance object
	int id_;

	//	
	std::string url_;

	//	Name of the entrance
	std::string name_;

	//	Latitude of the entrance's location
	double latitude_;

	//	Longitude of the entrance's location
	double longitude_;

	//	32-bit mask that represents the subway line(s) that are accessible from
	//	this entrance 
	unsigned long line_identifier_;
};

//	Returns the LineValue that corresponds to the name of the subway line as a
//	string
LineValue get_linevalue(const std::string& line_name);

#endif

