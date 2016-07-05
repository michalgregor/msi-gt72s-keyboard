# README #

The msi-gt72s-keyboard utility can be used to set the RGB colors for the regions
on an MSI steelseries keyboard. It has been developed for and tested on the
built-in keyboard in MSI GT72S 6QE. It can be used to set full RGB colors for
any of the regions including the logo, the touchpad and the front lights (7
regions all in all). There is no guarantee that it will do anything useful for
other models – it has only been tested with the one.

The tool is inspired by and loosely based on:
https://github.com/bparker06/msi-keyboard
https://github.com/stevelacy/msi-keyboard

## How to Build ##

The source contains CMake makefiles. The customary build procedure is as follows:
```
mkdir build
cd build
cmake ..
make
```

To install:
```
make install
```

## Usage ##

-h: Displays this help.
-c [<region>,]<color>: Sets color for a region (may be used multiple times to set color for multiple regions). If a region is not specified, all regions are colored.
-m <mode>: Sets the mode (either an integer, or one of center (2), centre (2), frontleft (5), frontright (6), left (1), logo (4), middle (2), right (3), touchpad (7))
-cl: Lists all predefined named colors.

## License ##

The msi-gt72s-keyboard utility is covered by the New BSD License:

Copyright (c) 2016, Michal Gregor
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the author nor the names of its contributors may be
	  used to endorse or promote products derived from this software without
	  specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
