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
void processSlave();
void processMaster();


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
// Description     : 
// Return type     : void

void processSlave(){

	readFile("foodbanks.dat");
}


// Function name   : processMaster
// Description     : 
// Return type     :  void

void processMaster(){	
	readFile("foodbanks.dat");

}