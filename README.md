# Hxdump

A simple program to output raw byte values of a file to standard output. Inspired by hexdump linux utility.

## Compilation

Clone the repo if not already: `git clone https://github.com/m-enes/hxdump.git`. \
Go into repo directory: `cd hxdump`. \
Create bin directory: `mkdir bin`. \
Compile the source code: `gcc -Wall -Wextra -Wpedantic hxdump.c -o bin/hxdump`. \
Go into bin directory: `cd bin`. \
Create or copy a file into the bin directory. \
Run the program: `./hxdump <filename>`, replace `<filename>` with the name of the file you want to read in the bin directory.
