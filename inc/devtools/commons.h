/*
Date: 29 Mar 2023 21:58:40.032678969
File: commons.h

Copyright Notice
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

Sign:    __COMMONS_H_2224725FD5DAE2AC90D80099D5A003C5__
Purpose: Common structures/macros useful across multiple projects.

Version control
29 Mar 2023 Duncan Camilleri           Initial development
30 Mar 2023 Duncan Camilleri           Function pointer types: comparator
*/

#ifndef __COMMONS_H_2224725FD5DAE2AC90D80099D5A003C5__
#define __COMMONS_H_2224725FD5DAE2AC90D80099D5A003C5__

//
// INCLUDES
//
#if !defined _INTTYPES_H
#error "commons.h: missing include - inttypes.h"
#endif

//
// Generic types.
//
#define nul                                  ((void*)0)
#define null                                 nul

//
// Generic structures.
//

// Generic return code.
typedef enum {
   cvfail = 0x00,
   cvsuccess = 0x01
} retcode;

//
// Useful function pointer types
//
// Comparator function to compare a with b.
// Expected return values:
//    -1:   a < b
//    1:    a > b
//    0:    a == b
typedef int8_t (*comparator)(void* a, void* b);

#endif   // __COMMONS_H_2224725FD5DAE2AC90D80099D5A003C5__

