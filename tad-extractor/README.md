# TAD Extractor

This program will extract images and other data from tad files.

# Requirements

* CMake 3.00 or newer.

* A C11 compatible compiler such as GCC, Clang, MinGW, or MSVC.

# Usage

`tadextractor.exe {filename} {output directory}`

# How to compile

```
git clone https://github.com/Dracovian/tad-extractor
cd tad-extractor

mkdir build && cd build
cmake ../

make
```

# How to compile on Windows

You can use the CMake GUI application to generate Visual Studio project files.
From there you can open the generated Visual Studio project files in Visual Studio and compile from there.

