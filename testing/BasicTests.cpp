/*******************************************************************************
* This is a basic function test for TeFiEd. It opens a file and outputs some
* text to it, this file should be called "BasicTests.txt"
*
* Please see API_USAGE for more notes on how to use this software
*
* ADBeta (c) Nov 2022
*******************************************************************************/
#include "../TeFiEd.h"
#include <iostream>

//Declare the TeFiEd object
TeFiEd Testfile("./BasicTests.txt");

int main() {
	//Enable verbosity
	Testfile.setVerbose(true);
	//Print the filename to aid user finding the file, and to confirm function.
	std::cout << "Filename string is: " << Testfile.filename() << std::endl;
	
	/** Create a file from nothing ********************************************/
	
	//Test appending line
	Testfile.appendString("If you can read this, appendString works!");
	
	//Add some text to the first line, at a specific position
	Testfile.insertToLine(" and insertToLine", 1, 35);
	
	//Write the RAM file out to the actual file and finish
	Testfile.overwrite();
	
	std::cout << "Done writing" << std::endl << std::endl;

	/** Open the file and output the line now *********************************/

	//Open and read in the test file
	if(Testfile.read() != 0) {
		std::cout << "File did not open correctly. exiting" << std::endl;
		return 1;
	}
	
	//Print the first line of the file
	std::cout << Testfile.getLine(1) << std::endl << std::endl;

	std::cout << "Basic Tests Finished!" << std::endl;
		
	return 0;
}
