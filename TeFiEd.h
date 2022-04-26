/* 
	TeFiEd - "TeeFeed"
	Text File Editor - lightweight and simple generic library.
	Designed for small/medium text files with low speed modifications

	See documentation file(s) for information and examples
	
	Version 2.1
	Written by ADBeta
	Last Modified 19 Apr 2022
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
	size_t MAX_RAM_BYTES = 2097152; //2MB 	
	size_t MAX_STRING_SIZE = 250;
	
	bool VERBOSE = false;
	
	/** Low level File Functions **/
	//Flushes and shrinks vector
	void flush();
	//Compute and return the size in bytes used by the ram vector
	size_t bytes();
	//Return number of elements in the vector
	size_t lines();
	
	/** Basic I/O Functions **/
	//Read all text until RAM Limit into vector
	int read();
	//returns the index requested line
	std::string getLine(size_t);
	//Overwrites the file with the RAM vector
	int overwrite();
	//Writes the RAM vector out to a referenced file object
	int writeTo(TeFiEd &);
	
	/** High Level Edit Functions **/
	//Appends a line of text to the end of the vector
	int appendLine(const std::string);
	//Appends a string the the end of a line, at index
	int appendString(const std::string, size_t);
	
	//Inserts a line of text into the vector at index
	int insertLine(const std::string, size_t);
	//Inserts a string of text, line index and start pos index
	int insertString(const std::string, size_t, size_t);
	
	//Remov ethe specified line from vector
	int removeLine(size_t);
	
	private:
	const char* m_filename; //Filename as char array
	std::fstream m_file; //fsteam object of file
	std::vector<std::string> m_ramfile; //File RAM vector	
	
	//Reset flags/bits then close the file
	void resetAndClose();
	
	//Perform sanity checks on input string and if it will exceed max size
	//checkString("string under test", "caller function name");
	int checkString(std::string, std::string);
	
	//Print a standardized error message. Sloppy. Might re-work but works.
	//Three message input
	template <typename T1, typename T2, typename T3>
	void errorMsg(std::string, T1, T2, T3);
	//Two message input
	template <typename T1, typename T2>
	void errorMsg(std::string, T1, T2);
	//One message input
	template <typename T1>
	void errorMsg(std::string, T1);
};

#endif
