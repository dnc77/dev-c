/*
Date: 27 Nov 2023 09:25:42.566444418
File: contmemlist.h

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

Sign:    __CONTMEMLIST_H_D8E98414C759BAB7F879CB7503C28900__
Purpose: There are times where multiple items of data of varying size need to be
         stored in a contiguous block of memory. Thinking of a linked list with
         data items of varying sizes all stored in the same memory block.
         This is such a list.

Version control
27 Nov 2023 Duncan Camilleri           Initial development
*/


#ifndef __CONTMEMLIST_H_D8E98414C759BAB7F879CB7503C28900__
#define __CONTMEMLIST_H_D8E98414C759BAB7F879CB7503C28900__

//
// TYPES
//

// Structures for external use.
typedef struct _CMLBuffer {
   bool mPersist;                                  // warning: do not change 
   uint32_t mSize;                                 // size of data at mpData
   void* mpData;                                   // note persistence
} CMLBuffer;

// List types.
typedef void* memlist;                             // contiguous memory list
typedef void* memlistitem;                         // a single item in the list

// Creation - (that which is created, needs to be destroyed).
memlist cmlcreate(void* pData, uint32_t size, uint32_t blocksize);
void cmldestroy(memlist* pp);

// Memory management.
// Adds a new item to the list.
// Note: Upon calling add, any non persistent CMLBuffers may become invalid.
// Note also that persistent CMLBuffers use up more memory. 
memlistitem cmlAdd(memlist* ppList, void* pData, uint32_t size);
memlistitem cmlGet(memlist pList, uint32_t index);

// CML Buffers
// CML Buffers fetch the actual data from an memlistitem. They can either be
// persistent (more heavy on resources) or temporary (faster and low resources).
// The catch is that every time a new contiguous memory item is added to the
// list with cmlAdd, a non persistent/temporary CML Buffer may become invalid.
// All CML Buffers should be destroyed cleanly.
bool createCMLBuffer(memlistitem hItem, CMLBuffer* pBuffer, bool persist);
void destroyCMLBuffer(CMLBuffer* pBuffer);

#endif   // __CONTMEMLIST_H_D8E98414C759BAB7F879CB7503C28900__

