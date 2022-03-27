#include "TeFiEd.hpp"

#include <fstream>
#include <iostream>
#include <string>

//TODO function to report write status and size. 
//TODO simple api config calls (?)
//TODO read verbosity function
//TODO verbosity stuff
//TODO review code for efficiency

TeFiEd::TeFiEd(const char* inputfn) {
	m_filename = inputfn;
}

/** Low Level File Functions **/
void TeFiEd::flush() {
	//Empties out the vector and shrinks its size
	m_ramfile.clear();
	m_ramfile.shrink_to_fit();
}

unsigned long TeFiEd::getRAMBytes() {
	unsigned long byteCount = 0;
	
	//Go through every element in the vector
	unsigned int vectElement = 0;
	while(vectElement < m_ramfile.size()) {
		//For each element, add the string size to the count.
		//NOTE <string>.size() returns number of bytes. it does not natively
		//understand unicode or multi-byte character sets, so this should
		//be a reliable method of getting bytes (as of 2022)
		byteCount += m_ramfile[vectElement].size();
	
		//NOTE Strings do not know about their terminating \n, so add 
		//1 byte to the count after every loop
		//This has been tested to agree with both Thunar and Nautilus 
		//file manager. may need rework later in time
		++byteCount;
	
		++vectElement;
	}
	
	return byteCount;
}

void TeFiEd::resetAndClose() {
	//Private function. resets bit flags and closes the file for the
	//next operation that is done
	
	//Clar flags
	m_file.clear();
	//Seek to 0th byte
	m_file.seekg(0, std::ios::beg);
	//Close file
	m_file.close();
}

/** Basic I/O Functions **/
//Read file into RAM
int TeFiEd::read() {
	//Reads the specified file into a RAM vector, up until certain RAM limit
	//then closes the file for next operation

	//Open file as read
	m_file.open(m_filename, std::ios::in);
	
	//Make sure file is open and exists
	if(m_file.is_open() == 0) {
		std::cerr << "Error: read: Could not open file " << m_filename 
		<< std::endl;
		
		return EXIT_FAILURE;
	}

	//Byte count, same methodology as getRAMBytes.
	unsigned long byteCount = 0;

	//String containing current line of text
	std::string lineStr;
	
	//Get the next line in the stream, unless next line is EOF
	while(m_file.peek() != EOF) {
		//Copy current line string to var
		std::getline(m_file, lineStr);
		
		//Add bytes to RAM byte counter
		byteCount += lineStr.size();
		//Add newline char per loop
		++byteCount;
		
		//Check that the next push won't overflow the size of the file
		if(byteCount > MAX_RAM_BYTES) {
			//Error message
			std::cerr <<
			"Error: read: File exceeds MAX_RAM_BYTES (" << 
			MAX_RAM_BYTES << "). Stopping read at current position." 
			<< std::endl;
			
			//Return error status
			return EXIT_FAILURE;
		}
		
		//if no failure, push string into vector
		m_ramfile.push_back(lineStr);
	}
	
	//Close file for next operation
	resetAndClose();
	//Success
	return EXIT_SUCCESS;
}

void TeFiEd::print() {
	// Print out the vector
	for(std::string n : m_ramfile) {
		std::cout << n << std::endl;
	}
}

int TeFiEd::overwrite() {
	//Open file as output, truncate
	m_file.open(m_filename, std::ios::out | std::ios::trunc);
	
	//Make sure file is open and exists
	if(m_file.is_open() == 0) { 
		std::cerr << "Error: overwrite: Could not create file " << m_filename 
		<< std::endl;
		
		return EXIT_FAILURE;
	}
	
	//Write parent object ram to file
	for(std::string lineStr : m_ramfile) {
		m_file << lineStr << std::endl;
	}
	
	//Close file and clear flags
	resetAndClose();
	
	return EXIT_SUCCESS;
}

//Write RAM into file object passed to it
int TeFiEd::writeTo(TeFiEd &target) {
	//Open file as output, truncate
	target.m_file.open(target.m_filename, std::ios::out | std::ios::trunc);
	
	//Make sure file is open and exists
	if(target.m_file.is_open() == 0) { 
		std::cerr << "Error: writeTo: Could not create file " << 
		target.m_filename << std::endl;
		
		return EXIT_FAILURE;
	}
	
	//Write parent object ram to file
	for(std::string lineStr : this->m_ramfile) {
		target.m_file << lineStr << std::endl;
	}
	
	//Close file and clear flags
	target.resetAndClose();
	
	return EXIT_SUCCESS;
}

/** High Level Edit Functions **/
int TeFiEd::sanitiseInputString(std::string parentFunc, size_t inputSize) {
	//Parent func is given for error message
	
	//Check if input string length for safety
	if(inputSize > MAX_STRING_SIZE) {
		std::cerr <<
		"Error: " << parentFunc << ": " <<
		"input string exceeds MAX_STRING_SIZE (" << MAX_STRING_SIZE 
		<< ")" << std::endl;
		
		return EXIT_FAILURE;
	}
	
	//Check if adding the string to the file will overflow the ram limit
	//NOTE +1 for newline, because this is a line operation
	if((getRAMBytes() + inputSize + 1) > MAX_RAM_BYTES) {
		std::cerr <<
		"Error: " << parentFunc << ": " <<
		"Operation causes file to exceed MAX_RAM_BYTES (" << MAX_RAM_BYTES 
		<< ")" << std::endl;
		
		return EXIT_FAILURE;
	}
	
	//Otherwise exit with pass
	return EXIT_SUCCESS;
}

int TeFiEd::appendLine(const std::string text) {
	//Append string to end of RAM object
	
	//Sanity check string and RAM size
	if(sanitiseInputString("appendLine", text.size()) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}
	
	//push entry to back of the vector
	m_ramfile.push_back(text);
	//Complete
	return EXIT_SUCCESS;
}

int TeFiEd::appendString(unsigned int index, const std::string text) {
	//Decriment index if above 0, vector is 0 indexed but 
	//line number is 1 indexed
	if(index > 0) {
		--index;
	}
	
	//Sanity check string and RAM size
	if(sanitiseInputString("appendLine", text.size()) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}
	
	//append the string in the vector at index given
	m_ramfile[index].append(text);
	
	return EXIT_SUCCESS;
}

int TeFiEd::insertLine(unsigned int index, const std::string text) {
	//Decriment index if above 0, vector is 0 indexed but 
	//line number is 1 indexed
	if(index > 0) {
		--index;
	}
	
	//Sanity check string and RAM size
	if(sanitiseInputString("insertLine", text.size()) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}

	//Make sure that the vector has enough elements to allow the insert
	if(index < m_ramfile.size()) {
		m_ramfile.insert(m_ramfile.begin() + index, text);
	} else {
		//Error message and return fail
		std::cerr << 
		"Error: insertLine: Line " << index + 1 << " does not exist in file." 
		<< std::endl;
		
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}

int TeFiEd::insertString(unsigned int index, unsigned int pos, 
	const std::string text) {
	//Insert a string at the given position	
	
	//Decriment index if above 0, vector is 0 indexed but 
	//line number is 1 indexed
	if(index > 0) --index;
	
	//Decriment pos if above 0
	if(pos > 0) --pos;
	
	//Sanity check string and RAM size
	if(sanitiseInputString("insertString", text.size()) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}

	//Make sure that the vector has enough elements to allow the insert
	if(index < m_ramfile.size()) {
		m_ramfile[index].insert(pos, text);
	} else {
		//Error message and return fail
		std::cerr << 
		"Error: insertString: Line " << index + 1 << " does not exist in file." 
		<< std::endl;
		
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
	
}

int TeFiEd::removeLine(unsigned int index) {
	//Decriment index if above 0, vector is 0 indexed but 
	//line number is 1 indexed
	if(index > 0) {
		--index;
	}
	
	//Make sure that the vector has the correct number of elements
	if(index < m_ramfile.size()) {
		//Erase line specified
		m_ramfile.erase(m_ramfile.begin() + index);
		//Shrink the vector
		m_ramfile.shrink_to_fit();
		
		//Return success
		return EXIT_SUCCESS;
		
	} else {
		//Error message and return error value
		std::cerr << 
		"Error: removeLine: Line " << index + 1  << " does not exist in file." 
		<< std::endl;
		
		return EXIT_FAILURE;
	}

}
