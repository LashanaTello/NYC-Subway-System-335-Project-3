# Project: NYC Subway System Recreation
## CSCI 335

This project can be viewed [here](http://www.compsci.hunter.cuny.edu/~sweiss/course_materials/csci335/assignments/project3.pdf).

### Description
The goal of this project was to attempt to recreate New York City's subway system using NYC Open Data's data about New York City's subway entrances. Using the subway entrances, I had to create subway stations, and then create subway train lines using the subway stations. The subway stations for a line are not ordered correctly in this project.

This project can be used to:
- get the closest subway stations to a user-given latitude and longitude
- get the closest subway entrances to a user-given latitude and longitude
- get the closest subway lines to a user-given latitude and longitude
- get all the entrances at a particular subway station
- get all the stations that serve a particular train line
- get all the subway stations 

(_**Note**: The [NYC Open Data file](./subway_entrances_cleaned.csv) used to create this project is not the same as the one you will export from NYC Open Data's page for [subway entrances](https://data.cityofnewyork.us/Transportation/Subway-Entrances/drex-xx56/data). This file was tweaked in order for its content to be read and stored more easily and efficiently._)

This project is useful for New Yorkers who take the subway. It can help them navigate New York City. It can definitely use a lot of improvements if it will be used for official NYC transportation software.

### How To Use
Download the zip file for this repository. Open a terminal and go to the directory containing all the project files in this zip. Type "make all" to compile the project. Type "./project3 subway_entrances_cleaned.csv name_of_file_with_commands_in_it" to run the project. The "name_of_file_with_commands_in_it" file will contain commands and their arguments, which the user wants to search for. In this repository, there are three files each named "commandfile" with an integer from one to three at the end. You can use these to test the program or see what the output would be. You can create your own command file using the guidelines listed in the [assignment in Section 4.3](http://www.compsci.hunter.cuny.edu/~sweiss/course_materials/csci335/assignments/project3.pdf#subsection.4.3).
