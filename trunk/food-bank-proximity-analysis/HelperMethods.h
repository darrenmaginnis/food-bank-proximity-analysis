#ifndef __HELPERMETHODS_H__
#define __HELPERMETHODS_H__

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "Location.h"

using namespace std;

vector<Location> readFile(string fName)
{

		vector<Location> loc;
		// Read and process the input data
		double foodBanks,east,north = 0;
		ifstream in(fName);
		while(in>>east>>north)
		{
			loc.push_back(Location(east,north));

		}

		return loc;
}


// Function name   : CalcDistace
// Description     : Calculation of Distance between Locations
// Return type     : inline double 
// Argument        : Location a
// Argument        : Location b

inline double CalcDistace(Location a, Location b){
	return abs( sqrt( ( pow( ( b.Easting - a.Easting ), 2 ) ) + ( pow( ( b.Northing - a.Northing ), 2 ) ) ) );
} 
#endif //__HELPERMETHODS_H__