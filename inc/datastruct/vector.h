/*
Date: 06 Feb 2023 01:07:29.444491924
File: vector.h

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

Sign:    __VECTOR_H_75B4DE9E8D0BE655A21DFEEB367A2322__
Purpose: Implements a vector api.

Version control
06 Feb 2023 Duncan Camilleri           Initial development
29 Mar 2023 Duncan Camilleri           Moved cvreturn to commons.h

*/

#ifndef __VECTOR_H_75B4DE9E8D0BE655A21DFEEB367A2322__
#define __VECTOR_H_75B4DE9E8D0BE655A21DFEEB367A2322__

//
// MISSING INCLUDES.
//
#if !defined __COMMONS_H_2224725FD5DAE2AC90D80099D5A003C5__
#error "vector.h: missing include - commons.h"
#endif

//
// MACROS
//

// Vector
#define makecvitem(_x)                       ((cvitem)&_x)

//
// TYPES
//

// Vector types
typedef void* cvector;                             // vector
typedef void* cvitem;                              // vector item
typedef const void* ccvector;                      // const vector
typedef const void* ccvitem;                       // const vector item

//
// VECTOR API
//

// Creation/destruction.
cvector cvcreate(uint32_t itemSize);               // construct empty vector
void cvdestroy(cvector* pv);                       // destroy existing vector

// Item management - public api.
uint32_t cvGetCount(ccvector cv);                  // return item count
uint32_t cvGetSize(ccvector cv);                   // return total items
retcode cvReserve(cvector v, uint32_t itemCount);  // total itemCount items
void* cvPushBack(cvector v, cvitem item);          // add to the end
void cvPopBack(cvector v);                         // remove & return last item
void cvClear(cvector v);                           // empty the vector
void cvShrink(cvector v);                          // remove null tail elements
void* cvGetAt(cvector v, uint32_t index);          // get/set item at index
void* cvSetAt(cvector v, uint32_t index, cvitem item);

#endif   // __VECTOR_H_75B4DE9E8D0BE655A21DFEEB367A2322__
