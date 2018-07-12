/*******************************************************************************
  Title          : subway_entrance.cpp
  Author         : Lashana Tello
  Created on     : May 3, 2018
  Description    : The implementation file for the Entrance class
  Purpose        : To provide a means of representing an entrance in New York
                   City's subway system
  Usage          : Use to store data pertaining to New York City's subway system
  Build with     : No building 
  Modifications  : 
 
*******************************************************************************/

#include "subway_entrance.h"


Entrance::Entrance() : id_(0), url_(""), name_(""), latitude_(0), longitude_(0),
    line_identifier_(0UL)
{
}

Entrance::Entrance(int id, std::string url, std::string name, double latitude,
									 double longitude, std::vector<std::string> lines) : 
    id_(id), url_(url), name_(name), latitude_(latitude), longitude_(longitude),
    line_identifier_(0UL) {

	unsigned long mask;
	for (auto& i : lines) {
		mask = 1UL << get_linevalue(i);
		line_identifier_ |= mask;
		mask &= 0UL;
	}
}

Entrance::Entrance(const Entrance& other_entrance) {
	id_ = other_entrance.id_;
	url_ = other_entrance.url_;
	name_ = other_entrance.name_;
	latitude_ = other_entrance.latitude_;
	longitude_ = other_entrance.longitude_;
	line_identifier_ = other_entrance.line_identifier_;
}
	
Entrance::~Entrance()
{
}

Entrance& Entrance::operator=(const Entrance& other_entrance) {
	id_ = other_entrance.id_;
	url_ = other_entrance.url_;
	name_ = other_entrance.name_;
	latitude_ = other_entrance.latitude_;
	longitude_ = other_entrance.longitude_;
	line_identifier_ = other_entrance.line_identifier_;
	return *this;
}

unsigned long Entrance::get_identifier() const {
	return line_identifier_;
}

	
void Entrance::get_coordinates(double& lat, double& lon) const {
	lat = latitude_;
	lon = longitude_;
}

	
std::string Entrance::get_entrance_name() const {
	return name_;
}

bool Entrance::same_line(const unsigned long& other_line) const {
	if ((line_identifier_ & other_line) == line_identifier_) {
		return true;
	}
	return false;
}

LineValue get_linevalue(const std::string& line_name) {
	if (line_name == "A") {
		return A;
	} else if (line_name == "B") {
		return B;
	} else if (line_name == "C") {
		return C;
	} else if (line_name == "D") {
		return D;
	} else if (line_name == "E") {
		return E;
	} else if (line_name == "F") {
		return F;
	} else if (line_name == "G") {
		return G;
	} else if (line_name == "H") {
		return H;
	} else if (line_name == "J") {
		return J;
	} else if (line_name == "L") {
		return L;
	} else if (line_name == "M") {
		return M;
	} else if (line_name == "N") {
		return N;
	} else if (line_name == "Q") {
		return Q;
	} else if (line_name == "R") {
		return R;
	} else if (line_name == "S") {
		return S;
	} else if (line_name == "Z") {
		return Z;
	} else if (line_name == "1") {
		return ONE;
	} else if (line_name == "2") {
		return TWO;
	} else if (line_name == "3") {
		return THREE;
	} else if (line_name == "4") {
		return FOUR;
	} else if (line_name == "5") {
		return FIVE;
	} else if (line_name == "6") {
		return SIX;
	} else if (line_name == "7") {
		return SEVEN;
	} else if (line_name == "SIR") {
		return SIR;
	} else if (line_name == "FS") {
		return FS;
	} else if (line_name == "GS") {
		return GS;
	}
	return DEFAULT;
}
