/*******************************************************************************
  Title          : subway_line_hash.h
  Author         : Lashana Tello
  Created on     : May 3, 2018
  Description    : The interface file for SubwayLineHash class
  Purpose        : To provide fast access to train lines in New York City's 
									 subway system
  Usage          : Use to store SubwayLine objects that contain data 
									 pertaining to New York City's subway system
  Build with     : No building 
  Modifications  : 
 
*******************************************************************************/

#ifndef __SUBWAY_LINE_HASH_H__
#define __SUBWAY_LINE_HASH_H__

#include <vector>
#include <string>
#include "hash_entry.cpp"
#include "subway_line.h"

/*******************************************************************************

		The SubwayLineHash class is a hash table that stores SubwayLine objects. 
		Its default size is 59 since there are 26 subway lines in New York City. 
		This table uses a division-based hash function to insert SubwayLine objects. 
		This table stores the SubwayLine objects using a vector of HashEntry objects 
		that store SubwayLine objects.

*******************************************************************************/

const SubwayLine kNonexistent;

class SubwayLineHash {
 public:
	//	Creates a SubwayLineHash object whose default size is 59 if an integer
	//	argument is not provided
	explicit SubwayLineHash(int size = 59);

	//	Creates a SubwayLineHash object that is an exact copy of other_table
	SubwayLineHash(const SubwayLineHash& other_table);

	//	Destroys SubwayLineHash object
	~SubwayLineHash();

	//	Inserts line into SubwayLineHash object's table_
	void insert(const SubwayLine& line);

	//	Removes SubwayLine object whose name is line_name from table_
	void remove(const std::string& line_name);

	//	Removes all SubwayLine objects from table_
	void clear();

	//	Returns an unmodifiable reference to a SubwayLine object if it exists
	//	in this SubwayLineHash object. If it does not exist, returns kNonexistent
	const SubwayLine& find(const std::string& line_name) const;

	//	Returns SubwayLineHash object's current_size_ member
	int size() const;

 private:
	//	Vector that stores SubwayLine objects
	std::vector< HashEntry<SubwayLine> > table_;
	
	//	An integer representing how many SubwayLine objects are in table_
	int current_size_;

	//	Returns an integer that is the index in table_ at which the SubwayLine
	//	object whose name is line_name will be inserted. Finds a position for
	//	the SubwayLine object in table_
	unsigned int find_pos(const std::string& line_name) const;

	//	Returns an integer that is the index in table_ at which the SubwayLine
	//	object whose name is line_name will be inserted
	int hash(const std::string line_name) const;

	//	Returns a very large integer value representing line_name
	long long encode(const std::string line_name) const;

	//	When table_ becomes half full, increases table_'s capacity more than two
	//	times its current capacity and rehashes all of its entries into table_
	void rehash();
};

#endif

