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
	// 0 = 0 to 1 km, 1 = > 1 to 2 km, 2 = > 2 to 5 km, 3 = > 5 km
	//int total;
	int count[4];
	double freq[4];
} DataSet;




// Function name   : readFile
// Description     : Read in the Entire File
// Return type     : vector<Location> 
// Argument        : string fName

vector<Location> readFile(string fName)
{

		vector<Location> loc;
		// Read and process the input data
		double east,north = 0;
		ifstream in(fName.c_str());
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
	bool success = false;
	double easting = 0.0, northing = 0.0;
	try
	{
		for(int i = 0; i < offset; i++)
		{
			if(f)
				f >> easting >> northing;
			else
				return false;
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


// Function name   : printResults
// Description     : Print out the results
// Return type     : void 
// Argument        : int numProcs
// Argument        : DataSet data[]
// Argument        : double elapsed

void printResults(int numProcs, DataSet data[], double elapsed)
{
	//cout << fixed;
	cout << setprecision (8);
	cout << "Proximity of Residential Addresses to Foodbanks in Toronto" << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << "Number of processes: " << numProcs << endl;
	cout << "Elapsed Time in Seconds: " << elapsed << endl;
	DataSet totals = {0};
	int totalCount = 0;
	for(int i = 0; i < numProcs; i++)
	{
		int count = data[i].count[0] + data[i].count[1] + data[i].count[2] + data[i].count[3];
		cout << "Process #" << i+1 << " for " << count <<" addresses..." << endl;
		cout << "Nearest Foodbank(km) \t # of Addresses \t % of Addresses" << endl;
		cout << "-------------------- \t -------------- \t --------------" << endl;
		cout << "0 - 1 \t\t\t" << data[i].count[0] <<"\t\t\t" << data[i].freq[0] << endl;
		cout << "1 - 2 \t\t\t" << data[i].count[1] <<"\t\t\t" << data[i].freq[1] << endl;
		cout << "2 - 5 \t\t\t" << data[i].count[2] <<"\t\t\t" << data[i].freq[2] << endl;
		cout << " > 5 \t\t\t"  << data[i].count[3] <<"\t\t\t" << data[i].freq[3] << endl;

		totals.count[0] += data[i].count[0];
		totals.count[1] += data[i].count[1];
		totals.count[2] += data[i].count[2];
		totals.count[3] += data[i].count[3];
		totals.freq[0] = ((totals.freq[0] + data[i].freq[0])/ 200 ) * 100;
		totals.freq[1] = ((totals.freq[1] + data[i].freq[1])/ 200 ) * 100;
		totals.freq[2] = ((totals.freq[2] + data[i].freq[2])/ 200 ) * 100;
		totals.freq[3] = ((totals.freq[3] + data[i].freq[3])/ 200 ) * 100;
		totalCount += count;
		
	}
		
		cout << "Aggregate results for all " << totalCount << " addresses..."  << endl;
		cout << "Nearest Foodbank(km) \t # of Addresses \t % of Addresses" << endl;
		cout << "-------------------- \t -------------- \t --------------" << endl;
		cout << "0 - 1 \t\t\t" << totals.count[0] <<"\t\t\t" << totals.freq[0] << endl;
		cout << "1 - 2 \t\t\t" << totals.count[1] <<"\t\t\t" << totals.freq[1] << endl;
		cout << "2 - 5 \t\t\t" << totals.count[2] <<"\t\t\t" << totals.freq[2] << endl;
		cout << " > 5 \t\t\t"  << totals.count[3] <<"\t\t\t" << totals.freq[3] << endl;

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

	int blocklens[] = { 4, 4 };	// 4 ints, 4 doubles
	MPI_Datatype oldTypes[] = {MPI_INT , MPI_DOUBLE };
	MPI_Aint offset[2];

	offset[0] = 0;
	MPI_Type_extent(MPI_INT, &offset[1]);
	offset[1] *= blocklens[0];

	// Call the datatype constructor
	MPI_Type_struct(2, blocklens, offset, oldTypes, &newType);

	// Commit the new datatype
	MPI_Type_commit(&newType);

	// Return the new datatype
	return newType;
}

#endif //__HELPERMETHODS_H__