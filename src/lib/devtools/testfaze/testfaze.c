/*
Date: 07 Feb 2023 21:34:47.314263429
File: testfaze.c

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

Sign:    __TESTFAZE_C_D697C2F76E8D803D399086898B1A66DF__
Purpose: testfaze is a very simple c test case library.

Version control
07 Feb 2023 Duncan Camilleri           Initial development
30 Mar 2023 Duncan Camilleri           Use commons bool 'type'
30 Mar 2023 Duncan Camilleri           Deprecated string assert in favour of buf
*/

#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <inttypes.h>
#include <commons.h>
#include "testfaze.h"

//
// TYPES
//

// Compact testing framework to assist with testing results. One instance of
// this structure represents one test suite. A name can optionally be stored.
typedef struct _testsuite {
   char mName[32];                                 // test suite name
   uint32_t mTotal;                                // total tests taken
   uint32_t mFailed;                               // total failed
} TestFaze;

//
// GLOBALS
//

//
// INTERNALS
//

// Add a test result to the metrics.
void tfzToMetric(TestFaze* pTest, uint8_t success);

//
// CONSTRUCT/DESTRUCT
//

TFSuite tfzCreate(const char* const pName)
{
   // First allocate buffer.
   TestFaze* ptfz = (TestFaze*)malloc(sizeof(TestFaze));
   if (!ptfz) return 0;

   memset(ptfz, 0, sizeof(TestFaze));
   if (pName) strncpy(ptfz->mName, pName, 31);

   // Done.
   return (TFSuite)ptfz;
}

void tfzDestroy(TFSuite* ptfs)
{
   TestFaze** pptfz = (TestFaze**)ptfs;
   if (!pptfz || !*pptfz) return;

   free(*pptfz);
   *pptfz = 0;
}

//
// METRICS
//

// Adds success/fail result to test suite
void tfzToMetric(TestFaze* pTest, uint8_t success)
{
   // Ensure a test suite to hold the metrics exists.
   if (!pTest) return;

   // Increment current test id.
   pTest->mTotal++;

   // When the test was successful, nothing further needs to be done. 
   if (success == true) return;

   // Record failed test.
   pTest->mFailed++;
}

// Displays summary results of test suite.
void tfzShowResults(TFSuite suite)
{
   // Show summary.
   TestFaze* pTest = (TestFaze*)suite;
   double failureRate = 
      ((double)pTest->mFailed / (double)pTest->mTotal) * 100.0;
   if (failureRate > 0) {
      printf("Test Suite: %s\n", pTest->mName);
      printf("   Total tests: %d, Failed: %d, Success rate: %f%%\n",
         pTest->mTotal, pTest->mFailed, 100.0 - failureRate);
   } else {
      printf("Test Suite: %s ok (100%%)\n", pTest->mName);
      return;
   }
}

//
// ASSERTIONS
//

// Performs a test on an unsigned 8 bit integer.
// Parameters: 
//    suite:      the test suite
//    res:        result
//    exp:        expected result
//    noMetric:   true to not add to metric calculation
bool tfzassert_ui8(TFSuite suite,
   uint8_t res, uint8_t exp, uint8_t noMetric)
{
   // Determine success.
   bool success = ((res == exp ) ? true : false);
   if (noMetric) return success;

   // Add result to metrics.
   tfzToMetric((TestFaze*)suite, success);
   return success;
}

// Performs a test on an unsigned 16 bit integer.
// Parameters: 
//    suite:      the test suite
//    res:        result
//    exp:        expected result
//    noMetric:   true to not add to metric calculation
bool tfzassert_ui16(TFSuite suite,
   uint16_t res, uint16_t exp, uint8_t noMetric)
{
   // Determine success.
   bool success = ((res == exp ) ? true : false);
   if (noMetric) return success;

   // Add result to metrics.
   tfzToMetric((TestFaze*)suite, success);
   return success;
}

// Performs a test on an unsigned 32 bit integer.
// Parameters: 
//    suite:      the test suite
//    res:        result
//    exp:        expected result
//    noMetric:   true to not add to metric calculation
uint8_t tfzassert_ui32(TFSuite suite,
   uint32_t res, uint32_t exp, uint8_t noMetric)
{
   // Determine success.
   uint8_t success = ((res == exp ) ? true : false);
   if (noMetric) return success;

   // Add result to metrics.
   tfzToMetric((TestFaze*)suite, success);
   return success;
}

// Performs a test on a pointer.
// Parameters: 
//    suite:      the test suite
//    res:        result
//    exp:        expected result
//    noMetric:   true to not add to metric calculation
bool tfzassert_ptr(TFSuite suite,
   void* res, void* exp, uint8_t noMetric)
{
   // Determine success.
   uint8_t success = ((res == exp ) ? true : false);
   if (noMetric) return success;

   // Add result to metrics.
   tfzToMetric((TestFaze*)suite, success);
   return success;
}

// Performs a test on a string buffer. Not taking into account string length
// and accepting any length. Security red flag - to visit again!
// Parameters: 
//    suite:      the test suite
//    res:        result
//    exp:        expected result
//    noMetric:   true to not add to metric calculation
// TODO: Deprecated: use tszassert_buf instead.
#if 0
bool tfzassert_str(TFSuite suite,
   const char* const res, const char* const exp, uint8_t noMetric)
{
   // Determine success.
   uint8_t success = true;
   if (strcmp(res, exp) != 0) success = false;
   if (noMetric) return success;

   // Add result to metrics.
   tfzToMetric((TestFaze*)suite, success);
   return success;
}
#endif

// Performs a test on a binary buffer.
// Parameters: 
//    suite:      the test suite
//    res:        result
//    resSize:    size of result buffer
//    exp:        expected result
//    expSize:    size of expected result buffer
//    noMetric:   true to not add to metric calculation
bool tfzassert_buf(TFSuite suite,
   const void* const res, uint32_t resSize,
   const void* const exp, uint32_t expSize,
   uint8_t noMetric)
{
   uint8_t success = true;

   // First compare lengths.
   if (resSize != expSize) success = false;

   // Determine success.
   if (true == success && memcmp(res, exp, resSize) != 0)
      success = false;
   if (noMetric) return success;

   // Add result to metrics.
   tfzToMetric((TestFaze*)suite, success);
   return success;
}
