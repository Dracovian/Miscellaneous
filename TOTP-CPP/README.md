# TOTP-C++
**Requirements:**

* OpenSSL

* CMake 3.00 or newer

* C++ compiler with C++20 support

# Building for Windows

1. [Download the OpenSSL library for Windows](https://kb.firedaemon.com/support/solutions/articles/4000121705)

2. Grab this repo using Git
    - `git clone https://github.com/Dracovian/TOTP-CPP`

3. Point CMake-GUI to the newly created `TOTP-CPP` folder and then configure OpenSSL paths to wherever you extracted the OpenSSL 1.1.1h library files.

4. Generate the project files for your selected compiler of choice.

# Building for Linux

1. Install the OpenSSL library from your package manager.
    - `libssl-dev` on Debian hosts.

2. Grab this repo using Git
    - `git clone https://github.com/Dracovian/TOTP-CPP`

3. Create a subdirectory to store the project files.
    - `cd TOTP-CPP && mkdir build && cd build`

4. Generate the project files and compile them.
    - `cmake .. && make`

# Credits

[Professor Melissa O'Neill](https://www.cs.hmc.edu/~oneill/index.html) for the C++ PCG code that is used to generate HMAC keys in this program.

[OpenSSL Developers](https://www.openssl.org/) for the library that is used for generating HMAC hashes in this program.

[Matthew Garrett](https://github.com/mjg59) for the base32 code that I adapted from C to C++ for use in this program.

# License
This work is based on PCG and OpenSSL which are licensed under Apache 2.0.

This work is also based on Matthew Garrett's base32 implementation which is licensed under GPL 2.0.


`SPDX-License-Identifier: Apache-2.0 AND GPL-2.0`
