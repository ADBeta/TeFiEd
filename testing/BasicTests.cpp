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
TeFiEd Testfile("BasicTests.txt");

int main() {
	//Enable verbosity
	Testfile.setVerbose(true);
	//Print the filename to aid user finding the file, and to confirm function.
	std::cout << "Filename string is: " << Testfile.filename() << 
	  "\t\t  parent directory is: " << Testfile.parentDir() << std::endl;
	
	/** Create a file from nothing ********************************************/
	//Testfile.create();
	
	//Test appending line
	//Testfile.appendString("If you can read this, appendString works!");
	
	//Add some text to the first line, at a specific position
	//Testfile.insertToLine(" and insertToLine", 1, 35);
	
	//Write the RAM file out to the actual file and finish
	//Testfile.overwrite();
	
	//std::cout << "Done writing" << std::endl << std::endl;

	/** Open the file *********************************************************/
	//Open and read in the test file
	if(Testfile.read() != 0) {
		std::cout << "File did not open correctly. exiting" << std::endl;
		return 1;
	}
	
	//Convert the input file to Unix Line ending style
	Testfile.convertLineEnding(le_Unix);
	
	
	//Go through every word in every line in the file
	/*
	std::string cWord;
	size_t cLine = 1, cIndex = 1;
	
	while( cLine <= Testfile.lines() ) {
		while( (cWord = Testfile.getWord(cLine, cIndex)) != "" ) {
		
			std::cout << cWord << std::endl;
		
			++cIndex;
		}
		
		cIndex = 1;
		++cLine;
	}
	*/
	
	//Find function tests. Find the first line that matches, offset to line 10
	size_t matchLine = Testfile.findLine("TRACK", 10);
	std::cout << "Matched line: " << matchLine << "   " << 
	          Testfile.getLine(matchLine) << std::endl;
	
	//Testfile.overwrite();
	
	//Print the first line of the file
	//std::cout << Testfile.getLine(1) << std::endl << std::endl;

	//std::cout << "Basic Tests Finished!" << std::endl;
	
	return 0;
}
