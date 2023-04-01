/*
Date: 06 Feb 2023 01:07:29.427012568
File: vector.c

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

Sign:    __VECTOR_C_3A0A3068C02B12CCC156B01E85D834FD__
Purpose: Implements a vector api.

Version control
06 Feb 2023 Duncan Camilleri           Initial development
21 Mar 2023 Duncan Camilleri           extendBuffer() newItemCount increment fix
29 Mar 2023 Duncan Camilleri           cvreturn and nul to commons.h (retcode)
30 Mar 2023 Duncan Camilleri           testfaze using bool commons type
30 Mar 2023 Duncan Camilleri           tests pulled out from library source
31 Mar 2023 Duncan Camilleri           Introduced cvEmplaceBack
31 Mar 2023 Duncan Camilleri           cvPushBack fail return correct to null
31 Mar 2023 Duncan Camilleri           Renamed return codes to exclude cv prefix
31 Mar 2023 Duncan Camilleri           cvEmplaceBack() did not update item count
31 Mar 2023 Duncan Camilleri           Fixed cvShrink realloc() misuse
02 Apr 2023 Duncan Camilleri           Fixed cvEmplaceBack() returning bad addr
*/

//
// INCLUDES
//
#include <inttypes.h>
#include <memory.h>
#include <malloc.h>

#include <commons.h>
#include <vector.h>

//
// MACROS
//
#define VECTOR_DEFAULT_ALLOCUNITS            8

//
// STRUCTS
//

typedef struct _vector {
   uint32_t mItemSize;                             // size per item - duh
   uint32_t mItemCount;                            // number of items
   uint32_t mTotalCount;                           // all items (incl. blanks) 

   uint32_t mItemsPerAlloc;                        // items to alloc each time
   void* mpData;
} vector;

//
// CREATION/DESTRUCTION.
//

// Create a new vector. Initially the vector will be empty. No memory will
// be allocated unless necessary.
cvector cvcreate(uint32_t itemSize)
{
   // Allocate vector for now.
   vector* pv = (vector*)malloc(sizeof(vector));
   if (!pv) return nul;
   memset(pv, 0, sizeof(vector));

   // Initialize.
   pv->mItemSize = itemSize;
   pv->mItemCount = 0;
   pv->mTotalCount = 0;
   pv->mItemsPerAlloc = VECTOR_DEFAULT_ALLOCUNITS;
   pv->mpData = nul;

   // Done.
   return (cvector)pv;
}

// Destroy existing vector.
void cvdestroy(cvector* pv)
{
   if (nul == pv) return;
   if (nul == (*pv)) return;

   // Free data first.
   vector* v = (vector*)*pv;
   if (v->mpData) {
      free(v->mpData);
      v->mpData = nul;
   }

   free(*pv);
   *pv = 0;
}

//
// Private API - Memory allocation.
//

// extend is used by extendBuffer to extend by the number of items specified
// the memory buffer allocated for data in the vector. This will be rounded to
// the default number of allocation units of the vector.
retcode extend(vector* pv, uint32_t byItemCount)
{
   uint32_t newSize = (pv->mTotalCount + byItemCount) * pv->mItemSize;
   void* pBuf = realloc(pv->mpData, newSize);
   if (!pBuf) return fail;

   // Clean up and update data.
   pv->mpData = pBuf;
   memset(pv->mpData + (pv->mItemSize * pv->mTotalCount),
      0 , pv->mItemSize * byItemCount
   );
   pv->mTotalCount += byItemCount;

   // Done.
   return success;
}

// extendBuffer extends the buffer to ensure newItemCount items can be stored in
// the vector when this is greater than 0. When it's 0, the buffer is
// extended by mItemsPerAlloc items if there are no more free items available
// (ie. mTotalCount == mItemCount). The buffer is always incremented in
// mItemsPerAlloc chunks (using %).
// If the number of items requested is already a factor that's manageable by the
// vector, nothing will be allocated and everything stays as is.
retcode extendBuffer(vector* pv, uint32_t newItemCount)
{
   // Add a new set of blank items to the end of the vector buffer.
   if (newItemCount == 0) {
      if (pv->mTotalCount > pv->mItemCount)
         return success;

      return extend(pv, pv->mItemsPerAlloc);
   }

   // Specific item count specified. Do not do anything if the item count
   // requested is already containable within the vector.
   if (newItemCount <= pv->mTotalCount) {
      return success;
   }

   // We need to allocate more items.
   newItemCount += (pv->mItemsPerAlloc - (newItemCount % pv->mItemsPerAlloc));
   return extend(pv, newItemCount - pv->mTotalCount);
}

//
// Item management - public api.
//

// Returns the number of valid items in the vector.
uint32_t cvGetCount(ccvector cv)
{
   // Access vector.
   const vector* pv = (const vector*)cv;
   return (pv ? pv->mItemCount : 0);
}

// Returns the total number of items in the vector (valid or invalid).
uint32_t cvGetSize(ccvector cv)
{
   // Access vector.
   const vector* pv = (const vector*)cv;
   return (pv ? pv->mTotalCount : 0);
}

// Reserve itemCount items in the vector. This ensures that the vector can
// hold that amount of items. If there is no space to store such items, it
// is allocated ensuring rounding is as per vector's items per allocation
// value.
retcode cvReserve(cvector v, uint32_t itemCount)
{
   // Access vector.
   vector* pv = (vector*)v;
   if (!pv) return fail;

   return extendBuffer(pv, itemCount);
}

// Creates item at end and returns location of item. Will return null if it
// fails! Caller expected to fill item up to the size defined originally.
// This will be provided in pSize.
void* cvEmplaceBack(cvector v, uint32_t* pSize)
{
   // Access vector.
   vector* pv = (vector*)v;
   if (!pv) return null;

   // Allocate space if need be.
   if (fail == extendBuffer(pv, pv->mItemCount + 1))
      return null;

   // Provide the size (if user asks for it).
   if (pSize) *pSize = pv->mItemSize;

   // Return the empty item.
   void* dest = (pv->mpData + (pv->mItemCount * pv->mItemSize));
   pv->mItemCount++;
   return dest;
}

// Adds an item after the last item added. Returns a pointer to the item.
void* cvPushBack(cvector v, cvitem item)
{
   // Access vector.
   vector* pv = (vector*)v;
   if (!pv) return null;
   // ...and item.
   if (!item) return null;

   // Allocate space if need be.
   if (fail == extendBuffer(pv, pv->mItemCount + 1))
      return null;

   // Copy the item.
   void* dest = (pv->mpData + (pv->mItemCount * pv->mItemSize));
   memcpy(dest, item, pv->mItemSize);
   pv->mItemCount++;

   // Done.
   return dest;
}

// Removes (blanks) last item.
void cvPopBack(cvector v)
{
   // Access vector.
   vector* pv = (vector*)v;
   if (!pv) return;

   // Are there any items?
   if (!pv->mpData || pv->mItemCount == 0) return;

   // Clear last item buffer.
   pv->mItemCount--;
   memset(pv->mpData + (pv->mItemSize * pv->mItemCount), 0 , pv->mItemSize);
}

// Removes all items from the vector. Items will be blanked out. To completely
// free up the vector, cvShrink() can be called after.
void cvClear(cvector v)
{
   // Access vector.
   vector* pv = (vector*)v;
   if (!pv) return;

   // Just clear all the buffer.
   memset(pv->mpData, 0, pv->mItemSize * pv->mItemCount);
   pv->mItemCount = 0;
}

// Removes trailing blank items from the vector. Note, that empty items in the
// middle will not be removed. This is to preserve indexes and speed.
void cvShrink(cvector v)
{
   // Access vector.
   vector* pv = (vector*)v;
   if (!pv) return;
   if (!pv->mpData) return;

   // If we don't have enough memory allocated, there is nothing to shrink.
   // Note, in this case shrink will not allocate any memory. Just shrink.
   uint32_t newTotal = 0;
   if (pv->mItemCount > 0) {
      newTotal = (pv->mItemCount + (pv->mItemsPerAlloc -
         (pv->mItemCount % pv->mItemsPerAlloc))
      );
   }

   if (pv->mTotalCount <= newTotal)
      return;

   // Reallocate.
   if (newTotal > 0) {
      void* pBuf = realloc(pv->mpData, newTotal * pv->mItemSize);
      if (!pBuf) return;

      // Set buffer.
      pv->mpData = pBuf;
   } else {
      free(pv->mpData);
      pv->mpData = nul;
   }

   // Since we are only shrinking, there is no memory to clear. Item count is
   // untouched but we freed unused memory up to and rounded by items per alloc.
   pv->mTotalCount = newTotal;
}

// Get item at index. If no item exists, nul is returned.
void* cvGetAt(cvector v, uint32_t index)
{
   // Access vector.
   vector* pv = (vector*)v;
   if (!pv) return nul;
   if (!pv->mpData) return nul;

   // Check index validity.
   if (index >= pv->mItemCount) return nul;

   // Return item.
   return (void*)(pv->mpData + (pv->mItemSize * index));
}

// Sets the item at index and returns it back. To pass an item of the specified
// itemSize, use makecvitem(item). To access an item from a cvitem, use
// makeitem(cvitem). 
void* cvSetAt(cvector v, uint32_t index, cvitem item)
{
   // Access vector.
   vector* pv = (vector*)v;
   if (!pv) return nul;
   if (!pv->mpData) return nul;

   // Check index validity.
   if (index >= pv->mItemCount) return nul;

   // Copy item.
   void* vItem = (pv->mpData + (pv->mItemSize * index));
   memcpy(vItem, item, pv->mItemSize);
   return vItem;
}
