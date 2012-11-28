/*
 * Program: CPA2-6
 * Course: INFO-5083
 * Professor: Tony Haworth
 * Project: Food Bank Proximity Analysis
 * Due Date: Wed., November 28th, 2012 @ 7:00 p.m.
 * 
 * Author Darren Maginnis 0026561
 * Author Ryan Johnston 0068199
 * 
 * Description: an application using MPI to generate statistics about the proximity of residential 
 *				addresses in the City of Toronto to the available Food Banks.
 */


#include<iostream>
#include <fstream>
#include <mpi.h>
#include "HelperMethods.h"


using namespace std;
int poolSize, instance;
DataSet commonLogic();


// Function name   : main
// Description     : Main Application entry
// Return type     : int
// Argument        : int argc
// Argument        : char *argv[]

int main(int argc, char *argv[])
{
	//Initialize MPI
	if( MPI_Init(&argc, &argv) == MPI_SUCCESS )
	{
		//Obtain the instance and the poolsize
		MPI_Comm_size(MPI_COMM_WORLD, &poolSize);
		MPI_Comm_rank(MPI_COMM_WORLD, &instance);
		
		DataSet processResults = commonLogic();

		// Create a derived type
		MPI_Datatype dataSetType = createDataSetType();
		DataSet* allResults = new DataSet[poolSize];
		
		MPI_Gather(&processResults, 1, dataSetType, //send info
			allResults, 1, dataSetType, //recieve info
			0, MPI_COMM_WORLD); //world info

		if(instance == 0) {
			printResults(poolSize, allResults);
		}

		//clean up
		delete[] allResults;
		
		// Free the recType
		MPI_Type_free(&dataSetType);

		//shutdown
		return MPI_Finalize();
	}
	return EXIT_FAILURE;
}



// Function name   : CommonLogic
// Description     : Logic common to all proccesses
// Return type     : void 

DataSet commonLogic(){
	DataSet results; 
	//record counter
	int count = 0;
	//Read in all foodbank locations
	vector<Location> foodBanks = readFile("foodbanks.dat");

	//Open the residences.dat
	ifstream residence("residences.dat");

	vector<Location>::const_iterator IT;
	Location loc;

	//read in the fist location
	if( getNextLocation( residence, instance + 1, loc ) ) 
	{
		++count;
		double closest = (double)INT_MAX;//set number realy high
		for( IT = foodBanks.begin(); IT != foodBanks.end(); ++IT )
			closest = min(closest, CalcSquareDistance( *IT, loc ));

		closest = (sqrt(closest) / 1000.0); // calc the acual distance

		if(closest < 1)
			++results.count[0];
		else if( closest < 2 )
			++results.count[1];
		else if( closest < 5 )
			++results.count[2];
		else
			++results.count[3];
	}
	//for each location after first
	while( getNextLocation( residence, poolSize, loc ) &&  count <= 10000 ) //TODO: Remove the && ++i < 10000 to run full dataset
	{
		++count;
		double closest = (double)INT_MAX;//set number realy high
		for( IT = foodBanks.begin(); IT != foodBanks.end(); ++IT )
			closest = min(closest, CalcSquareDistance( *IT, loc ));

		closest = (sqrt(closest) / 1000.0); // calc the acual distance

		if(closest < 1)
			++results.count[0];
		else if( closest < 2 )
			++results.count[1];
		else if( closest < 5 )
			++results.count[2];
		else
			++results.count[3];
	}
	//calc the freq
	results.freq[0] = results.count[0] / ((double)count);
	results.freq[1] = results.count[1] / ((double)count);
	results.freq[2] = results.count[2] / ((double)count);
	results.freq[3] = results.count[3] / ((double)count);

	return results;
}