/*******************************************************************************
  Title          : hash_entry.cpp
  Author         : Lashana Tello
  Created on     : May 3, 2018
  Description    : The interface and implementation file for the hash_entry 
									 struct
  Purpose        : To provide a means of representing an entry in a hash table
  Usage          : Use to store hashed objects in a hash table
  Building       : This is a templated struct. Do not build this file. 
  Modifications  : 
 
*******************************************************************************/

#ifndef __HASH_ENTRY__
#define __HASH_ENTRY__

/*******************************************************************************

		The HashEntry struct is to be used to represent an entry in a hash table. 
		When the hash table is constructed, it is to be filled with blank HashEntry 
		objects whose data member is the default constructor for the hashed object, 
		and whose Status member is set to EMPTY. It is templated to work with any 
		type of data. Its data members are data and an enumerated type, Status. 
		Status can be three values: EMPTY, ACTIVE, and DELETED. A HashEntry object 
		(in a hash table) whose Status member is equal to EMPTY means that no 
		hashed object has been inserted into the table at that index. If Status is 
		ACTIVE, then that index is already occupied by another hashed object. If 
		Status is DELETED, then there is no hashed object there anymore because 
		it was deleted. 

*******************************************************************************/

enum Status {
	EMPTY,
	ACTIVE,
	DELETED
};

template <class T>
struct HashEntry {
	T data;
	Status status;

	//	Constructor for HashEntry object
	HashEntry(const T& some_data, const Status currently) {
		data = some_data;
		status = currently;
	}

	//	Constructor for HashEntry object
	HashEntry(const T& some_data) {
		data = some_data;
		status = EMPTY;
	}

	//	Default constructor for HashEntry object
	HashEntry() {
		this->data = T();
		this->status = EMPTY;
	}

	//	Returns true if HashEntry object's status member is equal to ACTIVE
	bool active() const {
		if (status == ACTIVE) {
			return true;
		}
		return false;
	}
};

#endif
