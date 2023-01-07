# TeFiEd
**Te**xt**Fi**le**Ed**itor  
ADBeta (c) 2023  

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

## TODO
* Add checksum function, to detect changes to the file, and to output  
a file checksum without external programs.  
* Refactor some interal checks such as .isOpen() for more safeties  
* Add full unicode support - std::strings and size don't support > 8bit chars  
* Do write out speed tests, e.g. Bytes Per Second (avg) and 1024 byte speed.  
* Add Find Search and Replace functons to the library.  
* Add a file validity checker instead of Read() in some situations  
* file.create() call instead of write then read, which can be confusing  

## Changerlog
* 2.5 - Initial release.  
* 2.6 - Cleared up some logic problems  
* 2.8 - Added -hasChanged- flag, to make overwrite or writeTo not waste time by  
 writing to IO if nothing needs to be changed  
* 2.9 - Added some extra features to the object (eg filename print and TODO  
* *** - Added a testing branch to test and play around with the features and  
functions of the library.  
* 3.0 - Changed how a lot of the functions work in order to make a simpler API  
and less bloated sub-system

## Licence
This software is under the GPL (GPL3.0), please see LICENCE for information  
