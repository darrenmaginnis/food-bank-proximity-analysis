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

bool getNextRes(ifstream &f, int offset, Location &loc)
{
	
	double easting, northing;
	try
	{
			for(int i = 0; i < offset; i++)
			{
				f >> easting >> northing;		
			}
			loc = Location(easting,northing);
	}
	catch(...)
	{
		return false;
	}

	return true;
}

// Function name   : CalcDistace
// Description     : Calculation of Distance between Locations
// Return type     : inline double 
// Argument        : Location a
// Argument        : Location b

inline double CalcDistance(Location a, Location b){
	return abs( sqrt( ( pow( ( b.Easting - a.Easting ), 2 ) ) + ( pow( ( b.Northing - a.Northing ), 2 ) ) ) );
} 

inline double CalcSquareDistance(Location a, Location b){
	return pow( ( b.Easting - a.Easting ), 2 ) + pow( ( b.Northing - a.Northing ), 2 );
} 

#endif //__HELPERMETHODS_H__