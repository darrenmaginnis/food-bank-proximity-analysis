#ifndef __HELPERMETHODS_H__
#define __HELPERMETHODS_H__

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include "Location.h"

using namespace std;

//DataSet type
typedef struct {
	int processRank;
	// 0 = 0 to 1 km, 1 = > 1 to 2 km, 2 = > 2 to 5 km, 3 = > 5 km
	int count[4];
	double freq[4];
} DataSet;



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
	catch(exception ex)
	{
		cerr << ex.what() << endl;
		return false;
	}

	return true;
}

void printResults(int numProcs, DataSet data[])
{
	cout << "Proximity of Residential Addresses to Foodbanks in Toronto" << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << "Number of processes: " << numProcs;
	cout << "Elapsed Time in Seconds: ";
	for(int i = 0; i <= numProcs; i++)
	{
		cout << "Process #" << i+1 << "for 3333" << " addresses..." << endl;
		cout << "Nearest Foodbank(km) \t # of Addresses \t % of Addresses" << endl;
		cout << "-------------------- \t -------------- \t --------------" << endl;
		cout << "0 - 1 \t" << /*first address value*/"" << data[i].freq[0] << endl;
		cout << "1 - 2 \t" << /*first address value*/"" << data[i].freq[1] << endl;
		cout << "2 - 5 \t" << /*first address value*/"" << data[i].freq[2] << endl;
		cout << " > 5 \t"  << /*first address value*/"" << data[i].freq[3] << endl;

		cout << "Aggregate results for all 10000 addresses..." << endl;
		cout << "Nearest Foodbank(km) \t # of Addresses \t % of Addresses" << endl;
		cout << "-------------------- \t -------------- \t --------------" << endl;
		cout << "0 - 1 \t" << /*first address value*/"" << data[i].freq[0] << endl;
		cout << "1 - 2 \t" << /*first address value*/"" << data[i].freq[1] << endl;
		cout << "2 - 5 \t" << /*first address value*/"" << data[i].freq[2] << endl;
		cout << " > 5 \t"  << /*first address value*/"" << data[i].freq[3] << endl;
		
	}

}

// Function name   : CalcSquareDistance
// Description     : Calculation of Squared Distance between Locations, this method is faster for comparing 2 distances as it doesn't need to get the squareroot
// Return type     : inline double 
// Argument        : Location a
// Argument        : Location b

inline double CalcSquareDistance(Location a, Location b){
	return pow( ( b.Easting - a.Easting ), 2 ) + pow( ( b.Northing - a.Northing ), 2 );
} 


// Function name   : createDataSetType
// Description     : Creates the DataType for sending the DataSet over MPI comunication
// Return type     : MPI_Datatype 

MPI_Datatype createDataSetType()
{
	// Set-up the arguments for the call to the datatype constructor
	MPI_Datatype newType;

	int blocklens[] = { 5, 4 };	// 5 ints, 4 doubles
	MPI_Datatype oldTypes[] = {MPI_INT , MPI_DOUBLE };

	MPI_Aint indices[2];

	indices[0] = 0;
	MPI_Type_extent(MPI_INT, &indices[1]);
	indices[1] *= 5;

	// Call the datatype constructor
	MPI_Type_struct(9, blocklens, indices, oldTypes, &newType);

	// Commit the new datatype
	MPI_Type_commit(&newType);

	// Return the new datatype
	return newType;
}

#endif //__HELPERMETHODS_H__