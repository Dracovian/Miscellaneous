#!/bin/sh

 # Set our current directory to the Build directory.
cd Build

# Remove any previous compilation.
rm -f MUSE

# Run the make command on the Makefile.dist file.
make -f Makefile.dist

# Configure our sources.
./configure --disable-dependency-tracking

# Make the MUSE interpreter.
make

# Cleanup the build directory
make -f Makefile.am clean
