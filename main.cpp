/*******************************************************************************
  Title          : main.cpp
  Author         : Lashana Tello
  Created on     : May 3, 2018
  Description    : Given two input files from the command line (the first is a
									 csv document containing an NYC subway entrance and its 
									 information on each line from the NYC OpenData project and 
									 the other is a list of commands to execute with one command 
									 on each line), a SubwaySystem object will be created and each 
									 entrance from the subway file will be inserted into the 
									 SubwaySystem object. The SubwaySystem object's 
									 make_subway_system method will then be called to create the 
									 subway system and will then execute each command in the 
									 command file. A Command object is used to parse the file
									 containing the list of commands, and get each command and its
									 arguments from each line. The arguments are then given to the
									 SubwaySystem object method that corresponds to each command
									 and the command is executed.
  Purpose        : To store and use the contents of a New York City subway 
									 entrances file to create New York City's subway system in an
									 object that represents a database and answer specific user
									 queries pertaining to the database
  Usage          : When running, provide two input files, the NYC Subway 
									 entrances file and a file with a list of commands, 
									 respectively
  Build with     : g++ -std=c++11 -o main main.cpp subway_entrance.cpp 
									 subway_station.cpp subway_line.cpp subway_station_hash.cpp 
									 subway_line_hash.cpp subway_system.cpp command.o
  Modifications  : 
 
*******************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "subway_entrance.h"
#include "subway_system.h"
#include "command.h"

int main(int argc, char* argv[]) {
/*
	ifstream subway_file;
	subway_file.open("subway_entrances_cleaned.csv");

	SubwaySystem subway_system;
	int entrance_id;
	double latitude, longitude;
	string website, name, a_line, data;
	vector<string> train_lines;
	//bool end_of_file = false;
	//int b = 1;
	string sq;

	while (subway_file.is_open()) {
		getline(subway_file, a_line);
		//cout << "MAKING ENTRANCE " << b << endl;

		if (subway_file.eof()) {
			break;
		}

		unsigned int start = 0, count = 1;
		for (unsigned int i = 0; i < a_line.length(); ++i) {
			if (a_line[i] == ',') {
				data = a_line.substr(start, i - start);
				if (count != 3) {
					istringstream ss1(data);
					if (1 == count) {
						ss1 >> entrance_id;
						//cout << entrance_id << endl;
					} else if (2 == count) {
						ss1 >> website;
						//cout << website << endl;
					} else if (4 == count) {
						unsigned int begin = 7;
						for (unsigned int j = 7; j < data.length(); ++j) {
							if (data[j] == ' ') {
								istringstream ss2(data.substr(begin, j - begin));
								ss2 >> longitude;
								//cout << longitude << endl;
								begin = j + 1;
							} else if (j == data.length() - 1) {
								istringstream ss2(data.substr(begin));
								ss2 >> latitude;
								//cout << latitude << endl;
							}
						} //end for
					} //end else count 4
				} else {
					name = data;
					//cout << name << endl;
				}
				start = i + 1;
				++count;
			} else if (i == a_line.length() - 1) {
				data = a_line.substr(start);
				if (data.length() == 1 || data == "SIR" || data == "FS") {
					//cout << "Single line: " << data << endl;
					train_lines.push_back(data);
				} else {
					//cout << "Several lines: ";
					unsigned int begin = 0;
					for (unsigned int k = 0; k < data.length(); ++k) {
						if (data[k] == '-') {
							sq = data.substr(begin, k - begin);
							//cout << sq << " ";
							train_lines.push_back(sq);
							begin = k + 1;
						} else if (k == data.length() - 1) {
							sq = data.substr(begin);
							//cout << sq << endl;
							train_lines.push_back(sq);
						}
					}//end for
				}
			}//end length else
		} //end first if

		Entrance entrance(entrance_id, website, name, latitude, longitude, train_lines);
		train_lines.clear();
		//cout << entrance.get_identifier() << endl;
		subway_system.add(entrance);
	}//end file while

	//subway_system.show();
		
	//cout << subway_system.count() << endl;

	subway_system.make_subway_system();
	//subway_system.show2();
	cout << subway_system.stations() << endl;
	//subway_system.list_all_stations();
	//cout << endl;
*/
	if(3 == argc) {
		std::ifstream subway_file;
		std::ifstream command_file;
		subway_file.open(argv[1]);
		command_file.open(argv[2]);
		if (subway_file.fail()) {
			std::cerr << "Unable to open subway file: " << argv[1] << std::endl;
			exit(1);
		}
		if (command_file.fail()) {
			std::cerr << "Unable to open commands file: " << argv[2] << std::endl;
			exit(1);
		}

		SubwaySystem subway_system;
		int entrance_id;
		double latitude, longitude;
		std::string website, name, a_line, data;
		std::vector<std::string> train_lines;

		while (subway_file.is_open()) {
			std::getline(subway_file, a_line);

			if (subway_file.eof()) {
				break;
			}

			unsigned int start = 0, count = 1;
			for (unsigned int i = 0; i < a_line.length(); ++i) {
				if (a_line[i] == ',') {
					data = a_line.substr(start, i - start);
					if (count != 3) {
						std::istringstream ss1(data);
						if (1 == count) {
							ss1 >> entrance_id;
						} else if (2 == count) {
							ss1 >> website;
						} else if (4 == count) {
							unsigned int begin = 7;
							for (unsigned int j = 7; j < data.length(); ++j) {
								if (data[j] == ' ') {
									std::istringstream ss2(data.substr(begin, j - begin));
									ss2 >> longitude;
									begin = j + 1;
								} else if (j == data.length() - 1) {
									std::istringstream ss2(data.substr(begin));
									ss2 >> latitude;
								}
							}
						}
					} else {
						name = data;
					}
					start = i + 1;
					++count;
				} else if (i == a_line.length() - 1) {
					data = a_line.substr(start);
					if (data.length() == 1 || data == "SIR" || data == "FS") {
						train_lines.push_back(data);
					} else {
						unsigned int begin = 0;
						for (unsigned int k = 0; k < data.length(); ++k) {
							if (data[k] == '-') {
								train_lines.push_back(data.substr(begin, k - begin));
								begin = k + 1;
							} else if (k == data.length() - 1) {
								train_lines.push_back(data.substr(begin));
							}
						}
					}
				}
			}

			Entrance entrance(entrance_id, website, name, latitude, longitude,
												train_lines);
			train_lines.clear();
			subway_system.add(entrance);
		}
		subway_system.make_subway_system();


		Command command;
    std::string station_name, identifier;
    bool result;

		while (!command_file.eof()) {
			if (!command.get_next(command_file)) {
				if (!command_file.eof()) {
					std::cerr << "Could not get next command.\n";
				}
				return 1;
			}
			command.get_args(identifier, station_name, longitude, latitude, result);

			switch (command.type_of()) {
				case list_line_stations_cmmd:
					subway_system.list_line_stations(identifier);
					break;
				case list_all_stations_cmmd:
					subway_system.list_all_stations();
					break;
				case list_entrances_cmmd:
					subway_system.list_entrances(station_name);
					break;
				case nearest_station_cmmd:
					subway_system.nearest_station(latitude, longitude);
					break;
				case nearest_lines_cmmd:
					subway_system.nearest_line(latitude, longitude);
					break;
				case nearest_entrance_cmmd:
					subway_system.nearest_entrance(latitude, longitude);
					break;
				case bad_cmmd:
					std::cout << "Invalid command" << std::endl;
					break;
				default:
					break;
			}
		}

		subway_file.close();
		command_file.close();
	} else if (3 < argc) {
		std::cerr << "ERROR: Too many arguments provided. ";
		std::cerr << "You must provide one input file and one command file, ";
		std::cerr << "respectively." << std::endl;
		exit(1);
	} else {
		std::cerr << "ERROR: Too few arguments. You must provide one input file ";
		std::cerr << "and one command file, respectively" << std::endl;
		exit(1);
	}
	return 0;
}
