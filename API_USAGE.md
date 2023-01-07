** THIS IS UNFINISHED AND ISN'T FINAL **

The first step to using TeFiEd is to declare an object.
	TeFiEd Object("filename.ext");	
	
	/** Configuration Functions ***********************************************/
	//Sets the verbose flag. See API_USAGE for notes
	void setVerbose(bool verb) { this->verbose = verb; }
	
	//Sets the maximum -BYTES- the file can have until failsafe triggers.	
	void setByteLimit(size_t bytes) { this->MAX_RAM_BYTES = bytes; }
	
	//Sets the maximum number of -CHARS- a line can have before failsafe.
	void setStringLimit(size_t chars) { this->MAX_STRING_SIZE = chars; }
	
	/** File Metadata getters *************************************************/
	//Return the filename string (converted from const char* to string)
	std::string filename();
	
	//Scan the vector and return the number of bytes used. (Can be slow)
	size_t bytes();
	
	//Return number of elements in the vector, which is 1:1 for lines of output
	size_t lines();
	
	/** Basic Functions *******************************************************/
	//Reads input file into the RAM file (vector)
	int read();
	
	//Return the line string at the passed index
	std::string getLine(size_t);
	
	//Overwrite the original file with the RAM file
	int overwrite();
	
	//Writes the RAM file out to another TeFiEd Object. See API_USAGE for notes.
	//TODO
	int writeTo(TeFiEd &);
	
	//Deletes all the data in the RAM File, and shrinks the vector to save space
	void flush();
	
	/** File Editing Functions ************************************************/
	//Appends a string to the end of the RAM File
	int appendString(const std::string);
	
	//Append a string onto the end of a specific line
	int appendToLine(const std::string, size_t line);
	
	//Inserts a line of text into the vector at index.
	int insertString(const std::string, size_t index);
	
	//Inserts a string of text, line index and start pos index.
	int insertToLine(const std::string, size_t line, size_t pos);
	
	//Remove the specified line from RAM File.
	int removeLine(size_t line);
	
