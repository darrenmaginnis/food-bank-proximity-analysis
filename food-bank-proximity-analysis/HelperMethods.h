#ifndef __HELPERMETHODS_H__
#define __HELPERMETHODS_H__

#include <iostream>
#include <fstream>
#include <cmath>

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
// Description     : Calculation of Distance between Addresses
// Return type     : double 
// Argument        : double aEasting
// Argument        : double aNorthing
// Argument        : double bEasting
// Argument        : double bNorthing

inline double CalcDistace(double aEasting, double aNorthing, double bEasting, double bNorthing){
	return abs( sqrt( ( pow( ( bEasting - aEasting ), 2 ) ) + ( pow( ( bNorthing - aNorthing ), 2 ) ) ) );
} 
#endif //__HELPERMETHODS_H__