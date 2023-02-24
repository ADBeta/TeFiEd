TeFiEd is designed to be simple and flexible with sensible API calls and functions.

In order to use the library, copy TeFiEd.h and TeFiEd.cpp into the appropriate 
place in your project and include TeFiEd.hpp.

The first step to using TeFiEd is to declare an object and pass the filename.  
```C++
TeFiEd file("filename.extension");`

file.read();
```

You can do this via pointers too, if you wish to declare a TeFiEd object, but  
do not want to immediately give it a file to open.  
```C++
//Global space
TeFiEd *file;

void setFile() {
	file = new TeFiEd("filename.txt");
	
	file.read();
}
```

<b>Please note, you must read the file (`file.read()`) before performing any 
other operations. Failure to do this will cause a segmentation fault.</b>  

----
<b>Configuraton Functions for TeFiEd</b>  
To make TeFiEd Objects verbose, i.e. print detailed information about what is 
going on, you can set the verbosity using this call.  
`file.setVerbose( bool );`
	
To change the maximum number of bytes that the object file can contain before a 
failsafe triggers and ends operation, use this call. (This defaults to 8MB)   
`file.setByteLimit(size_t bytes);`

To change the maximum number of characters a single line can have before a 
failsafe triggers. This is a safety measure. (Defaults to 5000 chars)  
`file.setStringLimit(size_t chars);`

----
<b>File Metadata Getters</b>  
To get the filename of the TeFiEd object. This converts the native char* type
into a std::string.  
`file.filename();`  
Or you can get the native c string version using  
`file.filename_c_str();`

Scan the whole vector and return how many bytes are being used. The speed of this
depends on the size of the RAM file.  
`file.bytes();`

Return how many lines the file has, this is the same value as there are elements
in the vector.  
`file.lines();`

----
<b>General Functions</b>  
To create a blank file. Returns error status.  
`file.create();`

To read the file from filename into the RAM vector, call read(). This will return
non-zero upon error. A return of 1 indicates a general failure, and will print an
error message.  
`file.read();`

Another option to check if the file is open - better option is checking return
status of the read() function - is to call the isOpen function.  
`file.isOpen();`

To get the string held at line n, call getLine(n). The first index is 1, this is
done as it makes more sense in the context of a text editor. Request for line 0
will return a blank string.  
`file.getLine(size_t line);`

TeFiEd has multiple output options, one option is to write the file to itself, 
i.e. to overwrite itself. This does not re-read the file when exectited, as it 
would waste CPU time to assume the user wanted to overwrite then read.  
`file.overwrite();`

Another way to output the RAM file is by writing it out to another TeFiEd object.
This is done by passing the object to the writeTo() method. Please see examples
for more informaton on this.  
`file.writeTo(TeFiEd &);`
	
To safely delete the data from the vector, and reduce the RAM usage. This is not
strictly needed to do before exiting, but it does help the deconstructor to
quickly handle the garbage collection.  
`file.flush();`

----
<b>File Editing Functions</b>  
Convert the line ending type from DOS (\r\n or CR/LF) to Unix (\n or LF), or 
vice versa.  
`file.convertLineEnding(LineEnding type);    //LineEnding::Unix or LineEnding::Unix`

Append a string to the end of the RAM vector. Returns error status.  
`file.append(const std::string);`

Append a string onto the end of a specific line. Returns error status.  
`file.appendLine(size_t line, const std::string);`
	
Inserts a line of text into the vector at index line. Returns error status.  
`file.insert(size_t line, const std::string);`

Remove or delete line from the vector. Returns error status.  
`file.remove(size_t line);`

Get -index- word from the line. There are 2 ways of doing this:  
Pass line No & index, return string - blank when no match.  
Pass string & index, return string - blank when no match.  
`file.getWord(size_t line, unsigned int index);`  
`file.getWord(std::string input, unsigned int index);`

Find the first instance of a string that matches, but can offset the start line.
offset defaults to 1.  
`file.find(std::string search, size_t offset = 1);`

This finds the first instance of a string inside the vector and return its line
index number. Returns 0 if no match is found.  
`file.findFirst(std::string search);`

This finds the first, then next instance of a string on subsequent calls.
Returns 0 when no match is found, and resets to start of the vector when the
search string is different.  
`file.findNex(std::string search);`
