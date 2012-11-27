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
int results[4] = {0}; // 0 = 0 to 1 km, 1 = > 1 to 2 km, 2 = > 2 to 5 km, 3 = > 5 km
void processSlave();
void processMaster();
void CommonLogic();


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
		
		// start
		CommonLogic();

		if(instance == 0) 
			processMaster();
		else
			processSlave();
		
		//shutdown
		return MPI_Finalize();
	}
	return EXIT_FAILURE;
}

// Function name   : processSlave
// Description     : Slave process sends info to the mastet process
// Return type     : void

void processSlave(){

}


// Function name   : processMaster
// Description     : Master process collects info from the slaves
// Return type     : void

void processMaster(){	

}


// Function name   : CommonLogic
// Description     : Logic common to all proccesses
// Return type     : void 

void CommonLogic(){


	//Read in all foodbank locations
	vector<Location> foodBanks = readFile("foodbanks.dat");

	//Open the residences.dat
	ifstream residence("residences.dat");

	//read in the fist location
	Location loc;


	vector<Location>::const_iterator IT;

	if( getNextLocation( residence, instance + 1, loc ) ) 
	{
		double closest = (double)INT_MAX;//set number realy high
		for( IT = foodBanks.begin(); IT != foodBanks.end(); ++IT )
		{
			double distance = CalcDistance( *IT, loc ) / 1000.0;
			double closest = min(closest, distance);
			
		}		
		if(closest < 1)
			{
				results[0]++;
			}
			else if( closest < 2 )
			{
				results[1]++;
			}
			else if( closest < 5 )
			{
				results[2]++;
			}
			else
			{
				results[3]++;
			}
	}
	int i = 0;
	//for each location after
	while( getNextLocation( residence, poolSize, loc ) && ++i < 10000 )
	{
		for( IT = foodBanks.begin(); IT != foodBanks.end(); ++IT )
		{
			double distance = CalcDistance( *IT, loc );
			if(distance < 1)
			{
				results[0]++;
			}
			else if( distance < 2 )
			{
				results[1]++;
			}
			else if( distance < 5 )
			{
				results[2]++;
			}
			else
			{
				results[3]++;
			}
		}
	}

}