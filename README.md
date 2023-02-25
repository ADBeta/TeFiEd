# TeFiEd
**Te**xt **Fi**le **Ed**itor  

TeFiEd - pronounced TeeFeed - is a low-overhead file manager and editor library for C++,
it is intended to be paret of the backend for a text editor, game engine, and any other
application that requires outputting standard ASCII text to a file. 
(Unicdoe should work but it hasn't been tested yet. See #TODO).

The API of this library is designed with ease of use in mind, while not compromising
functionality.  
The internal TeFiEd RAM vecotr can be used to overwrite the current file, or write
to a seperate file.

This library is written to be fast, easy and efficient - with sane default guard
conditions and helpful sanity checks.

See the [doc] files for more information on how to use this library.
	
## TODO
* Add checksum function, to detect changes to the file, and to output  
a file checksum without external programs.
* Add full unicode support - std::strings and size don't support > 8bit chars?
* Change how error messages are called and how they work.
* Change isOpen to exists flag and make it more trustworthy
* word count function

## Changelog
* 2.5 - Initial release.
* 3.0.2 - Added a destructor
* 3.0.2 - Added create() and isOpen()
* 3.3.2 - Added a parentDir() function to return the parent directory of the file
* 4.0.1 - Added convertLineEnding() to convert between DOS (CR/LF) and Unix (LF)  
line ending types.
* 4.2.1 - Included getWord() function, returns a string with simple delimitation
* 4.3.2 - Added an overload of getWord that takes a string and index.
* 4.6.0 - Created a replace() function]
* 5.0.0 - Added documentation and altered the API to be easier to understand
* 5.1.0 - Overloaded TeFiEd constructor to support std::strings

## Licence
<b>ADBeta (c) 2023</b>  
This software is under the GPL (GPL3.0), please see LICENCE for information
