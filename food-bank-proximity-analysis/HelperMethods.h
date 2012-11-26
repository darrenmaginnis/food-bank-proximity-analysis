#ifndef __HELPERMETHODS_H__
#define __HELPERMETHODS_H__

#include <iostream>
#include <fstream>
#include <cmath>
#include "Location.h"

using namespace std;

void readFile()
{
		// Read and process the input data
		double foodBanks = 0;
		ifstream in("foodbank.dat");
		while(in>>foodBanks)
		{
		
		}
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