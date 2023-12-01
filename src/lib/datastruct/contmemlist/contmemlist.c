/*
Date: 27 Nov 2023 08:59:43.073666164
File: CML.c

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

Sign:    __CONTMEMLIST_C_039775AD8D16D72DEB71D9B04D1B9A14__
Purpose: There are times where multiple items of data of varying size need to be
         stored in a contiguous block of memory. Thinking of a linked list with
         data items of varying sizes all stored in the same memory block.
         This is such a list.

Version control
27 Nov 2023 Duncan Camilleri           Initial development
*/

//
// INCLUDES
//
#include <inttypes.h>
#include <memory.h>
#include <malloc.h>

#include <commons.h>
#include <contmemlist.h>

//
// MACROS
//
#define CONTMEMLIST_DEFAULT_BLOCKSIZE              512

//
// STRUCTS
//

// One single item in the list. Yes, it only consists of the size. What follows
// it is the actual data to that amount in size.
// Oh - CMLI stands for contiguous memory list item.
typedef struct _CMLI {
   uint32_t mItemSize;                             // size of item
} CMLI;

// Contiguous memory list represented as a structure.
typedef struct _CML {
   uint32_t mBlockSize;                            // size of one alloc block
   uint64_t mTotalSize;                            // size of whole data
   uint64_t mTotalUsed;                            // used amount of bytes

   CMLI* mpHead;                                   // pointers to head and tail
   CMLI* mpTail;
} CML;

//
// Helper functions
// These are merely convenience and readability tools.
//

// Returns a pointer to the first item in the list.
// Never pass null. This is an internal function.
void* listToFirstItem(memlist ml)
{
   CML* pCML = (CML*)ml;
   
   // No item?
   if (pCML->mTotalSize == sizeof(CML)) {
      return nul;
   }

   // Get first valid item.
   void* pFirst = (void*)ml;
   return pFirst + sizeof(CML);
}

// Returns a pointer to the list item data buffer from a public memlist item.
// Never pass null. This is an internal function.
void* listItemToData(memlistitem mli)
{
   CMLI* pCMLI = (CMLI*)mli;
   void* pData = (void*)mli;
   return pData + pCMLI->mItemSize;
}

// Returns the total list item size (including the header).
// Never pass null. This is an internal function.
uint32_t listItemSize(memlistitem mli)
{
   CMLI* pCMLI = (CMLI*)mli;
   return sizeof(CMLI) + pCMLI->mItemSize;
}

// Returns next item from item.
// Never pass null. This is an internal function.
memlistitem fromItemToNext(memlist ml, memlistitem mli)
{
   CML* pCML = (CML*)ml;
   if (mli >= (memlistitem)pCML->mpTail) return nul;

   return mli + listItemSize(mli);
}

//
// Creation - (that which is created, needs to be destroyed).
//

// Create a new CML. This may optionally take one item as input as well.
// Params:
//    pData          : data being added to the list (can be null)
//    size           : size of data added (0 if null)
//    blocksize      : size of each allocation block (0 defaults to 512)
memlist cmlcreate(void* pData, uint32_t size, uint32_t blocksize)
{
   // Validation.
   if (0 == blocksize) blocksize = CONTMEMLIST_DEFAULT_BLOCKSIZE;
   if (nul == pData && size > 0) return nul;
   if (pData && size == 0) return nul;

   // Get buffer space needed.
   uint32_t sizeNeeded = sizeof(CML);
   if (size > 0) {
      sizeNeeded +=  sizeof(CMLI) + size;
   }

   // Find out the total number of blocks that need to be allocated.
   uint32_t allocsize = blocksize;
   while (sizeNeeded > allocsize) {
      allocsize += blocksize;
   }

   // Alloc!
   void* p = malloc(allocsize);
   if (!p) return nul;
   memset(p, 0, allocsize);

   // Initialize.
   CML* pCML = (CML*)p;
   pCML->mBlockSize = blocksize;
   pCML->mTotalSize = allocsize;
   pCML->mTotalUsed = sizeNeeded;
   if (size == 0) {
      // No input data.
      pCML->mpHead = pCML->mpTail = 0;
   } else {
      // Input data available.
      pCML->mpHead = listToFirstItem((memlist)pCML);
      pCML->mpTail = pCML->mpHead;

      // Populate data to structure.
      void* payload = listItemToData(pCML->mpHead);
      memcpy(payload, pData, size);
      pCML->mpHead->mItemSize = size;
   }

   // Done.
   return (memlist)pCML;
}

// Destroy existing contiguous memory list.
void cmldestroy(memlist* pp)
{
   if (nul == pp || nul == *pp) return;

   free(*pp);
   *pp = 0;
}

//
// Memory management.
//

// Adds a new item and returns a direct pointer to it (as a memlistitem).
// Returns nul if parameters invalid or on failure.
// Note: Calling cmlAdd may invalidate any external CMLBuffers.
memlistitem cmlAdd(memlist* ppList, void* pData, uint32_t size)
{
   // Validation.
   if (nul == pData || size == 0 || !ppList || !*ppList) return nul;
   CML* p = (CML*)*ppList;

   // Get buffer space needed.
   uint32_t sizeNeeded = sizeof(CMLI) + size;
   uint32_t sizeAvail = p->mTotalSize - p->mTotalUsed;
   uint32_t allocsize = 0;
   while (sizeAvail + allocsize < sizeNeeded) {
      allocsize += p->mBlockSize;
   }

   // Realloc buffer?
   if (0 < allocsize) {
      // Try to reallocate larger needed buffer.
      void* pNew = realloc((void*)p, p->mTotalSize + allocsize);
      if (!pNew) {
         return nul;
      }

      // Update input pointer to new structure.
      *ppList = (memlist)pNew;
      p = (CML*)pNew;

      // Update size in header data.
      p->mTotalSize += allocsize;

      // Correct any header pointers (we only store head and tail).
      void* pNewHead = listToFirstItem((memlist)p);
      uint32_t tailToHead = ((void*)p->mpTail) - ((void*)p->mpHead);
      p->mpHead = (CMLI*)pNewHead;
      p->mpTail = (CMLI*)(pNewHead + tailToHead);
   }

   // Ok we have enough buffer data now. All we do is append to end.
   if (!p->mpHead) {
      // No previous head?
      p->mpHead = (CMLI*)listToFirstItem((memlist)p);
      p->mpTail = p->mpHead;
   }

   // Position tail to new item.
   uint32_t currentTailSize = listItemSize((void*)p->mpTail);
   p->mpTail = ((void*)p->mpTail) + currentTailSize;
   p->mpTail->mItemSize = size;
   memcpy(listItemToData((memlistitem)p->mpTail), pData, size);

   // Done!
   return (memlistitem)p->mpTail;
}

// Locates item at a particular index in the list.
memlistitem cmlGet(memlist pList, uint32_t index)
{
   if (!pList || !((CML*)pList)->mpHead) return nul;

   // Get first item.
   uint32_t n = 0;
   memlistitem item = listToFirstItem(pList);
   if (nul == item) return nul;

   // Keep getting until index found or reached max utilized memory.
   while (n < index && item) {
      // Find next item.
      if (n == index) {
         return item;
      }

      // Next item.
      item = fromItemToNext(pList, item);
      ++n;
   }

   // Not found!
   return nul;
}

//
// CML Buffers
// CML Buffers fetch the actual data from a memlistitem. They can either be
// persistent (more heavy on resources) or temporary (faster and low resources).
// The catch is that every time a new contiguous memory item is added to the
// list with cmlAdd, a non persistent/temporary CML Buffer may become invalid.
// All CML Buffers should be destroyed cleanly.
//

// Create a CML Buffer in pBuffer.
bool createCMLBuffer(memlistitem item, CMLBuffer* pBuffer, bool persist)
{
   // Ident item.
   if (!item || !pBuffer) return false;
   CMLI* pItem = (CMLI*)item;

   // Fill buffer.
   pBuffer->mPersist = persist;
   pBuffer->mSize = pItem->mItemSize;
   if (persist) {
      pBuffer->mpData = malloc(pItem->mItemSize);
      if (!pBuffer->mpData) return false;

      memcpy(pBuffer->mpData, listItemToData(item), pBuffer->mSize);
   } else {
      pBuffer->mpData = listItemToData(item);
   }

   // Done!
   return true;
}

// Frees up a CML Buffer if it is a persistent one.
void destroyCMLBuffer(CMLBuffer* pBuffer)
{
   if (!pBuffer || !pBuffer->mpData || !pBuffer->mPersist) return;
   free(pBuffer->mpData);
   pBuffer->mpData = 0;
}
