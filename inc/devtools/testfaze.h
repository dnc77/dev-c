/*
Date: 07 Feb 2023 21:35:02.371782234
File: testfaze.h

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

Sign:    __TESTFAZE_H_98A3BB4CC58CB174077E14BC6AA65023__
Purpose:

Version control
07 Feb 2023 Duncan Camilleri           Initial development
30 Mar 2023 Duncan Camilleri           Use commons bool 'type'
31 Mar 2023 Duncan Camilleri           Introduced most basic assert (bool)
*/

#ifndef __TESTFAZE_H_98A3BB4CC58CB174077E14BC6AA65023__
#define __TESTFAZE_H_98A3BB4CC58CB174077E14BC6AA65023__

// Missing includes.
#ifndef _INTTYPES_H
#error "testfaze.h requires inttypes.h."
#elif !defined __COMMONS_H_2224725FD5DAE2AC90D80099D5A003C5__
#error "testfaze.h requires commons.h."
#endif

//
// TYPES
//
typedef void* TFSuite;


//
// FUNCTION DEFINITIONS
//

//
// Construct/Destruct
//
TFSuite tfzCreate(const char* const pName);
void tfzDestroy(TFSuite* ptfs);

//
// Metrics
//

// Show test results as recorded in the metrics by tfzToMetric.
void tfzShowResults(TFSuite suite);

//
// Assertions.
// These are the main assertion functions called within the test framework.
// Parameters are generally as follows:
// suite          :  The test faze instance.
// res            :  The result obtained.
// exp            :  The expected result.
// noMetric       :  Does not consider running test for metrics purposes.
//                   This should default to false; meaning that the running
//                   test will be assessed within the testing framework of
//                   choice.
//

bool tfzassert(TFSuite suite, bool res, bool exp, uint8_t noMetric);
bool tfzassert_ui8(TFSuite suite,
   uint8_t res, uint8_t exp, uint8_t noMetric);
bool tfzassert_ui16(TFSuite suite,
   uint16_t res, uint16_t exp, uint8_t noMetric);
bool tfzassert_ui32(TFSuite suite,
   uint32_t res, uint32_t exp, uint8_t noMetric);
bool tfzassert_ptr(TFSuite suite,
   void* res, void* exp, uint8_t noMetric);
// TODO: Deprecated. Use tfzassert_buf instead.
// bool tfzassert_str(TFSuite suite,
//    const char* const res, const char* const exp, uint8_t noMetric);
bool tfzassert_buf(TFSuite suite,
   const void* const res, uint32_t resSize,
   const void* const exp, uint32_t expSize,
   uint8_t noMetric);

#endif   // __TESTFAZE_H_98A3BB4CC58CB174077E14BC6AA65023__
