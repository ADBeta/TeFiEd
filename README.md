# TeFiEd
**Te**xt**Fi**le**Ed**itor  
<b>ADBeta (c) 2023</b>  

TeFiEd - pronounced TeeFeed - is a low-overhead file manager and editor,  
it is intended to be the backend for a text editor, game engine, or any other  
application that requires outputting standard ASCII text to a file. (Unicdoe  
should work but it hasn't been tested yet. See #TODO).  

The API for this library is designed with ease of use, while still having high  
levels of functionality. The internal 'RAM file' can be written to a seperate  
file, or overwrite itself. This is ideal for some niche uses such as logging,  
creating backups of text upon write, etc.  

The speed of this library has been optimised for a happy medium, in return for  
having a much simpler and RAM Safer <vector> based structure.  

## Usage
TeFiEd is designed to be simple and flexible for any use, in order to use this  
library copy TeFiEd.h and TeFiEd.cpp into your projects directory and include  
TeFiEd.h in your source files.  

The first step to using TeFiEd is to declare an object and pass the filename.  
`TeFiEd file("filename.extension");`  

You can do this via pointers too, if you wish to declare a TeFiEd object, but  
do not want to immediately give it a file to open.  
```
//Global space
TeFiEd *file;

void setFile() {
	file = new TeFiEd("filename.txt");
}
```

<b>Please note, you must file.read() before performing any other functions. Failure  
to do this will cause a segmentation fault.</b>  
	
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

<b>File Metadata Getters</b>  
To get the filename of the TeFiEd object. This converts the native char* type  
into a std::string.  
`file.filename();`  

Scan the whole vector and return how many bytes are being used. The speed of this  
depends on the size of the RAM file.  
`file.bytes();`  

Return how many lines the file has, this is the same value as there are elements  
in the vector.  
`file.lines();`  

<b>General Use Functions</b>  
To read the file from filename into the RAM vector, call read(). This will return  
non-zero upon error. A return of 1 indicates a general failure, and will print an  
error message.  
`file.read();`  

To get the string held at line n, call getLine(n). The first index is 1, this is  
done as it makes more sense in the context of a text editor. A request for n=0  
will simply return n=1 to avoid crashing or segfaults.  
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
	
<b>File Editing Functions</b>  
Append a string to the end of the RAM vector. Returns error status.  
`file.appendString(const std::string);`  

Append a string onto the end of a specific line. Returns error status.  
`file.appendToLine(const std::string, size_t line);`  
	
Inserts a line of text into the vector at index line. Returns error status.  
`file.insertString(const std::string, size_t index);`  
	
Inserts a string to the vector at line index and start pos index.  
`file.insertToLine(const std::string, size_t line, size_t pos);`  
	
Remove or delete line from the vector. Returns error status.  
`file.removeLine(size_t line);`  
	
## TODO
* Add checksum function, to detect changes to the file, and to output  
a file checksum without external programs.  
* Refactor some interal checks such as .isOpen() for more safeties  
* Add full unicode support - std::strings and size don't support > 8bit chars  
* Do write out speed tests, e.g. Bytes Per Second (avg) and 1024 byte speed.  
* Add Find Search and Replace functons to the library.  
* Add a file validity checker instead of Read() in some situations  
* file.create() call instead of write then read, which can be confusing  
* Make destructor more cleanup oriented.  
* Change how error messages are called and how they work.  

## Changelog
* 2.5 - Initial release.  
* 2.6 - Cleared up some logic problems  
* 2.8 - Added -hasChanged- flag, to make overwrite or writeTo not waste time by  
 writing to IO if nothing needs to be changed  
* 2.9 - Added some extra features to the object (eg filename print and TODO  
* *** - Added a testing branch to test and play around with the features and  
functions of the library.  
* 3.0 - Changed how a lot of the functions work in order to make a simpler API  
and less bloated sub-system
* 3.0.1 - Added better usage notes, merged API_USAGE.md

## Licence
This software is under the GPL (GPL3.0), please see LICENCE for information  
