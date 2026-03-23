/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
DPA 8150:  Project One:  Nuke Nodes, Image Operators
/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

Compiling with GCC:
An example GCC file is included to view as a simpler example of compiling just one plug-in node using the GNU C Compiler (gcc).
(Nuke recommends for Nuke 11 a certain version of gcc that is older than on SoC machines.  There's a flag to ignore this need essentially).


Makefile:
Use the Makefile by typing "make", though, and it will build all that are included in it using similar gcc attritbutes.
When using the Makefile, each .cpp creates in intermediate .os file when built and final libary .so when built and linked.
(Running "make clean" will clean up those files, leaving just the .cpp files, if you're trying to clean-up your folder.)


Setup:
Make sure to edit menu.py as needed and place in your ~/.nuke directory.  (ls -a shows hidden folders).
Make sure to copy all .so files when built to ~/.nuke directory.


Discussion:
Add.cpp should suffice as an example of a basic, single image (unary) operator.
SimpleBlur.cpp should suffice as an example of checking nearby pixels as would be needed to implement a "filter."
AddInputs.cpp should suffice as an example of implementing a two-image input ("binary") operator.
