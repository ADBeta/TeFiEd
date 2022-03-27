/* 
	TeFiEd - "TeeFeed"
	Text File Editor - lightweight and simple generic library.
	Designed for small/medium text files with low speed modifications

	See documentation file(s) for information and examples
	
	Version 0.99
	Written by ADBeta
	Last Modified 26 Mar 2022
*/

/* IMPLIMENTATION NOTES */
/*
	All functions of type int only return the exit status of the function.
	None of them will automatically end the program. This can/will cause
	segmentation faults and/or corruted data if done improperly, but I
	prefered the idea of allowing freedom than hard-coding exit states.
	
	> Be especially cautious on read() and write() calls because they could
	cause seg faults and other bad failures. 

	When finished with the data read from the file, it is possible, and 
	recommended to use the flush() function to clear the vector from RAM

*/

#ifndef FILE_SYSTEM_HANDLER_H
#define FILE_SYSTEM_HANDLER_H

#include <fstream>
#include <string>
#include <vector>

class TeFiEd {
	public:
	//Constructor passes filename to class
	TeFiEd(const char*);
	
	/* Configuration variables */
	#define MAX_RAM_BYTES 2097152 //2MB 	
	#define MAX_STRING_SIZE 50
	
	/** Low level File Functions **/
	//Flushes and shrinks vector
	void flush();
	
	//Compute and return the size in bytes used by the ram vector
	unsigned long getRAMBytes();
	
	/** Basic I/O Functions **/
	//Read all text until RAM Limit into vector
	int read();
	//TODO Test function. prints vector
	void print();
	//Overwrites the file with the RAM vector
	int overwrite();
	//Writes the RAM vector out to a referenced file object
	int writeTo(TeFiEd &);
	
	/** High Level Edit Functions **/
	//Appends a line of text to the end of the vector
	int appendLine(const std::string);
	//Appends a string the the end of a line, at index
	int appendString(unsigned int, const std::string);
	
	//Inserts a line of text into the vector at index
	int insertLine(unsigned int, const std::string);
	//Inserts a string of text, line index and start pos index
	int insertString(unsigned int, unsigned int, const std::string);
	
	//Remov ethe specified line from vector
	int removeLine(unsigned int);
	
	private:
	const char* m_filename; //Filename as char array
	std::fstream m_file; //fsteam object of file
	std::vector<std::string> m_ramfile; //File RAM vector	
	
	//Reset flags/bits then close the file
	void resetAndClose();
	
	//Perform sanity checks on input string and if it will exceed max size
	int sanitiseInputString(std::string, size_t);
};

#endif
