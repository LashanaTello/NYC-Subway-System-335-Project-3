/*******************************************************************************
  Title          : subway_line.cpp
  Author         : Lashana Tello
  Created on     : May 3, 2018
  Description    : The implementation file for the SubwayLine class
  Purpose        : To provide a means of representing a train line in New York 
									 City's subway system
  Usage          : Use to store data pertaining to New York City's subway system
  Build with     : No building 
  Modifications  : 
 
*******************************************************************************/

#include "subway_line.h"

SubwayLine::SubwayLine() : line_name_(""), identifier_(0UL), stops_() {
}

SubwayLine::SubwayLine(std::string line_name, unsigned long identifier) : 
    line_name_(line_name), identifier_(identifier), stops_() {
}

SubwayLine::SubwayLine(const SubwayLine& other_subway_line) {
	line_name_ = other_subway_line.line_name_;
	identifier_ = other_subway_line.identifier_;
	stops_ = other_subway_line.stops_;
}

SubwayLine::~SubwayLine()
{
}

SubwayLine& SubwayLine::operator=(const SubwayLine& other_subway_line) {
	line_name_ = other_subway_line.line_name_;
	identifier_ = other_subway_line.identifier_;
	stops_ = other_subway_line.stops_;
	return *this;
}

unsigned long SubwayLine::get_identifier() const {
	return identifier_;
}

void SubwayLine::add_station(const SubwayStation& station) {
	stops_.push_back(station);
}

std::string SubwayLine::get_line_name() const {
	return line_name_;
}

std::vector<SubwayStation> SubwayLine::get_stations() const {
	return stops_;
}
