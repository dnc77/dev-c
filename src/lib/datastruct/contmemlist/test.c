/*
Date: 28 Nov 2023 14:20:17.537241475
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

Sign:    __TEST_C_CAFB06E6A33A1460EC8E7BC13EC9016A__
Purpose: Tests for contmemlist.c.

Version control
28 Nov 2023 Duncan Camilleri           Initial development
*/

#include <stdio.h>
#include <inttypes.h>
#include <memory.h>
#include <commons.h>
#include <testfaze.h>
#include <contmemlist.h>

//
// MACROS
//

//
// TEST CASES
//

// Tests creation and destruction of a vector.
bool testCreate(TFSuite pTest)
{
   // Create the contiguous memory list.
   memlist cml = cmlcreate(null, 0, 512);
   if (false == tfzassert(pTest, cml != null, true, false)) {
      return false;
   }

   // Ensure we cannot get an item at index 0 when nothing was requested.
   if (false == tfzassert_ptr(pTest, cmlGet(cml, 0), null, false)) {
      cmldestroy(&cml);
   }
   
   // Destroy it and ensure that nothing is left...
   cmldestroy(&cml);
   return tfzassert_ptr(pTest, cml, null, false);
}

// Tests addition of items...
bool testAdd(TFSuite pTest)
{
   // Create the vector with a value.
   memlist cml = cmlcreate("ABCD", 4, 4);
   if (false == tfzassert(pTest, cml != null, true, false)) {
      return false;
   }

   // Ensure first item added...
   CMLBuffer buf;
   memlistitem cmli = cmlGet(cml, 0);
   if (!createCMLBuffer(cmli, &buf, false)) {
      cmldestroy(&cml);
      return false;
   }

   // Ensure we have the item; and of the right size..
   if (!tfzassert_buf(pTest, "ABCD", 4, buf.mpData, 4, false)) {
      destroyCMLBuffer(&buf);
      cmldestroy(&cml);
      return false;
   }
   if (!tfzassert_ui32(pTest, 4, buf.mSize, false)) {
      destroyCMLBuffer(&buf);
      cmldestroy(&cml);
      return false;
   }

   // Free up buffer.
   destroyCMLBuffer(&buf);

   // Add another item using cmlAdd.
   if (!cmlAdd(&cmli, "EFG", 3)) {
      cmldestroy(&cml);
      return false;
   }

   // Get a persistent buffer this time.
   cmli = cmlGet(cml, 1);
   if (!createCMLBuffer(cmli, &buf, true)) {
      cmldestroy(&cml);
      return false;
   }

   // Ensure we have the item; and of the right size..
   if (!tfzassert_buf(pTest, "EFG", 3, buf.mpData, 3, false)) {
      destroyCMLBuffer(&buf);
      cmldestroy(&cml);
      return false;
   }
   if (!tfzassert_ui32(pTest, 3, buf.mSize, false)) {
      destroyCMLBuffer(&buf);
      cmldestroy(&cml);
      return false;
   }

   // Success.
   destroyCMLBuffer(&buf);
   cmldestroy(&cml);
   return true;
}

void runTests()
{
   // Test suite.
   TFSuite tfz = tfzCreate("contmemlist tests");
   if (!tfz) {
      printf("alloc() fail!\n");
      return;
   }

   // Individual tests.
   testCreate(tfz);
   testAdd(tfz);

   // Show results.
   tfzShowResults(tfz);
   tfzDestroy(&tfz);
}

int main(int argc, char** argv)
{
   runTests();

   return 0;
}

