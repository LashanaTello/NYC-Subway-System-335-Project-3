/*******************************************************************************
  Title          : subway_line_hash.cpp
  Author         : Lashana Tello
  Created on     : May 3, 2018
  Description    : The implementation file for the SubwayLineHash class
  Purpose        : To provide fast access to train lines in New York City's 
									 subway system
  Usage          : Use to store SubwayLine objects that contain data 
									 pertaining to New York City's subway system
  Build with     : No building 
  Modifications  : 
 
*******************************************************************************/

#include "subway_line_hash.h"
#include <iostream>

SubwayLineHash::SubwayLineHash(int size) :
    table_(size, HashEntry<SubwayLine>(SubwayLine())), current_size_(0)
{
}

SubwayLineHash::SubwayLineHash(const SubwayLineHash& other_table) {
	table_ = other_table.table_;
	current_size_ = other_table.current_size_;
}

SubwayLineHash::~SubwayLineHash()
{
}

void SubwayLineHash::insert(const SubwayLine& line) {
	int position = find_pos(line.get_line_name());
	if (table_[position].active()) {
		return;
	}

	HashEntry<SubwayLine> entry(line, ACTIVE);
	table_[position] = entry;
	if (((unsigned)++current_size_) > (table_.size() / 2)) {
		rehash();
	}
}

void SubwayLineHash::remove(const std::string& line_name) {
	int position = hash(line_name);
	if (table_[position].active()) {
		table_[position].status = DELETED;
	}
}

void SubwayLineHash::clear() {
	for (auto& entry : table_) {
		entry.status = DELETED;
	}
}

const SubwayLine& SubwayLineHash::find(const std::string& line_name) const {
	int position = find_pos(line_name);
	if (table_[position].active()) {
		return table_[position].data;
	}
	return kNonexistent;
}

int SubwayLineHash::size() const {
	return current_size_;
}

/*******************************************************************************

																		PRIVATE

*******************************************************************************/

unsigned int SubwayLineHash::find_pos(const std::string& line_name) const {
	int offset = 1;
	unsigned int pos = hash(line_name);
	SubwayLine line(table_[pos].data);

	while ((table_[pos].status != EMPTY) && (line.get_line_name() != line_name)) {
		pos += offset;
		offset += 2;
		if (pos >= table_.size()) {
			pos -= table_.size();
		}
		line = table_[pos].data;
	}
	return pos;
}

int SubwayLineHash::hash(const std::string line_name) const {
	long long value = encode(line_name);
	return (value % table_.size());
}

long long SubwayLineHash::encode(const std::string line_name) const {
	long long value = 0;
	for (unsigned int i = 0; i < line_name.length(); ++i) {
		value = line_name[i] + (25 * value);	//	25 symbols are used to name lines
	}
	return value;
}

void SubwayLineHash::rehash() {
	std::vector< HashEntry<SubwayLine> > old_table = table_;
	current_size_ = 0;
	table_.resize(127);

	for (auto& entry : table_) {
		entry.status = EMPTY;
	}

	for (auto& entry : old_table) {
		if (entry.active()) {
			insert(entry.data);
		}
	}
}


