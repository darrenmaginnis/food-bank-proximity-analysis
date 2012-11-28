#ifndef __HELPERMETHODS_H__
#define __HELPERMETHODS_H__

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include "Location.h"

using namespace std;

vector<Location> readFile(string fName)
{

		vector<Location> loc;
		// Read and process the input data
		double east,north = 0;
		ifstream in(fName);
		setprecision(3);
		while(in>>east>>north)
		{
			loc.push_back(Location(east,north));
		}

		return loc;
}



// Function name   : getNextLocation
// Description     : sets loc as the next location from offset and returns true if sucessful
// Return type     : bool 
// Argument        : IN ifstream &f
// Argument        : IN int offset
// Argument        : OUT Location &loc

bool getNextLocation(ifstream &f, int offset, Location &loc)
{
	
	double easting = 0.0, northing = 0.0;
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

//inline double CalcDistance(Location a, Location b){
//	return abs( sqrt( ( pow( ( b.Easting - a.Easting ), 2 ) ) + ( pow( ( b.Northing - a.Northing ), 2 ) ) ) );
//} 



// Function name   : CalcSquareDistance
// Description     : Calculation of Squared Distance between Locations, this method is faster for comparing 2 distances as it doesn't need to get the squareroot
// Return type     : inline double 
// Argument        : Location a
// Argument        : Location b

inline double CalcSquareDistance(Location a, Location b){
	return pow( ( b.Easting - a.Easting ), 2 ) + pow( ( b.Northing - a.Northing ), 2 );
} 


struct DataSet{
	// 0 = 0 to 1 km, 1 = > 1 to 2 km, 2 = > 2 to 5 km, 3 = > 5 km
	int count[4];
	double freq[4];
};

#endif //__HELPERMETHODS_H__