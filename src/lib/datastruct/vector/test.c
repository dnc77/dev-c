/*
Date: 30 Mar 2023 13:14:40.923903409
File: test.c

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

Sign:    __TEST_C_002729CC5D198D90EC0798318742753A__
Purpose: Tests for vector.c.

Version control
30 Mar 2023 Duncan Camilleri           Initial development
*/

#include <stdio.h>
#include <inttypes.h>
#include <commons.h>
#include <testfaze.h>
#include <vector.h>

//
// MACROS
//

// Borrowed alloc units from vector.c.
#define VECTOR_DEFAULT_ALLOCUNITS            8

//
// TEST CASES
//

// Tests creation and destruction of a vector.
bool testCreate(TFSuite pTest)
{
   // Create the vector.
   cvector cv = cvcreate(sizeof(int));
   if (!cv) return false;

   // Destroy it and ensure that nothing is left...
   cvdestroy(&cv);
   return tfzassert_ptr(pTest, cv, 0, false);
}

// Tests the expansion of vector items when adding items beyond end...
bool testBufferGrowth(TFSuite pTest)
{
   // Create the vector.
   cvector cv = cvcreate(sizeof(int));
   if (!cv) return false;

   // Add items to the vector.
   for (int n = 0; n < VECTOR_DEFAULT_ALLOCUNITS; ++n) {
      cvPushBack(cv, makecvitem(n));
   }

   // Ensure correct current total (VECTOR_DEFAULT_ALLOCUNITS).
   uint32_t currentTotal = cvGetSize(cv);
   uint32_t currentItems = cvGetCount(cv);
   if (false == tfzassert_ui32(
      pTest, currentTotal, VECTOR_DEFAULT_ALLOCUNITS, false)
   ) {
      cvdestroy(&cv);
      return false;
   }

   // Adding an extra item should extend the buffer.
   uint32_t newItem = VECTOR_DEFAULT_ALLOCUNITS + 1;
   uint32_t* pNewItem = cvPushBack(cv, makecvitem(newItem));

   // Ensure item being added is the item being returned (confirm it's added).
   if (false ==
      tfzassert_ui32(pTest, *pNewItem, VECTOR_DEFAULT_ALLOCUNITS + 1, false)
   ) {
      cvdestroy(&cv);
      return false;
   }

   // Ensure totals match up as well.
   currentTotal = cvGetSize(cv);
   currentItems = cvGetCount(cv);
   if (false == tfzassert_ui32(pTest, currentTotal,
      VECTOR_DEFAULT_ALLOCUNITS * 2, false)
   ) {
      cvdestroy(&cv);
      return false;
   }

   if (false == tfzassert_ui32(pTest, currentItems,
      VECTOR_DEFAULT_ALLOCUNITS + 1, false)
   ) {
      cvdestroy(&cv);
      return false;
   }

   // Success.
   cvdestroy(&cv);
   return true;
}

// Test shrinking of vector.
bool testShrink(TFSuite pTest)
{
   // Create the vector.
   cvector cv = cvcreate(sizeof(int));
   if (!cv) return false;

   // Add items to the vector - ensure there is space.
   for (int n = 0; n < 20; ++n) {
      cvPushBack(cv, makecvitem(n));
   }

   // Ensure all items are created and total space is in line with our
   // expectations.
   if (false == tfzassert_ui32(pTest, cvGetCount(cv), 20, false)) {
      cvdestroy(&cv);
      return false;
   }
   if (false == tfzassert_ui32(pTest, cvGetSize(cv),
         20 + (20 % VECTOR_DEFAULT_ALLOCUNITS), false)) {
      cvdestroy(&cv);
      return false;
   }

   // Shrink. Ensure shrink will shrink with modulo of alloc units.
   cvShrink(cv);
   if (false == tfzassert_ui32(pTest, cvGetCount(cv), 20, false)) {
      cvdestroy(&cv);
      return false;
   }
   if (false == tfzassert_ui32(pTest, cvGetSize(cv),
         20 + (20 % VECTOR_DEFAULT_ALLOCUNITS), false)) {
      cvdestroy(&cv);
      return false;
   }

   // Pop all items and shrink.
   for (int n = 0; n < 20; ++n) {
      cvPopBack(cv);
   }

   // Ensure all vector container elements present but empty/unused.
   if (false == tfzassert_ui32(pTest, cvGetCount(cv), 0, false)) {
      cvdestroy(&cv);
      return false;
   }
   if (false == tfzassert_ui32(pTest, cvGetSize(cv),
         20 + (20 % VECTOR_DEFAULT_ALLOCUNITS), false)) {
      cvdestroy(&cv);
      return false;
   }

   // Shrink and check that no utilized space remains...
   cvShrink(cv);
   if (false == tfzassert_ui32(pTest, cvGetSize(cv), 0, false)) {
      cvdestroy(&cv);
      return false;
   }

   // Success.
   cvdestroy(&cv);
   return true;
}

void runTests()
{
   // Test suite.
   TFSuite tfz = tfzCreate("cvector tests");
   if (!tfz) {
      printf("alloc() fail!\n");
      return;
   }

   // Individual tests.
   testCreate(tfz);
   testBufferGrowth(tfz);
   testShrink(tfz);

   // Show results.
   tfzShowResults(tfz);
   tfzDestroy(&tfz);
}

int main(int argc, char** argv)
{
   runTests();

   return 0;
}

