# dev-c - C Libraries and Projects

## Copyright notice
```Copyright Notice
This document is protected by the GNU General Public License v3.0.

This allows for commercial use, modification, distribution, patent and private
use of this software only when the GNU General Public License v3.0 and this
copyright notice are both attached in their original form.

For developer and author protection, the GPL clearly explains that there is no
warranty for this free software and that any source code alterations are to be
shown clearly to identify the original author as well as any subsequent changes
made and by who.

For any questions or ideas, please contact:
github:  https://github(dot)com/dnc77
email:   dnc77(at)hotmail(dot)com
web:     http://www(dot)dnc77(dot)com

Copyright (C) 2023 Duncan Camilleri, All rights reserved.
End of Copyright Notice
```

## Content summary

This is a small C library that comprises or may comprise of libraries that can aid in development as well as software.
We tried to keep dependencies to a minimum so that one may have the option of porting out easily individual tools from this development tree.
Please always maintain copyright attribution and version information in case of re-use.

Thank you.

### Top level folders:
* `inc`                       : definitions (include files)
* `src`                       : source files
* `lib`                       : compiled libraries (post compilation only)

### Top level categories:
* `devtools`                  : general development assists

### projects:
* `src/lib/devtools/logger`   : a simple logger
* `src/lib/devtools/testfaze` : a very basic test case utility

### Usage Notes:
1. Use Makefiles to compile all libraries by going to `/src/lib` and running `make` from there.


### Compilation Notes:
*  This repository has been compiled and linked using the following 
   1. gcc (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0
   2. GNU ld (GNU Binutils for Ubuntu) 2.34

