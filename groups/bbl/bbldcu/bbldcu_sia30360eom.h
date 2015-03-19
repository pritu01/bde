// bbldcu_sia30360eom.h                                               -*-C++-*-
#ifndef INCLUDED_BBLDCU_SIA30360EOM
#define INCLUDED_BBLDCU_SIA30360EOM

#ifndef INCLUDED_BSLS_IDENT
#include <bsls_ident.h>
#endif
BSLS_IDENT("$Id: $")

//@PURPOSE: Provide support for the SIA 30/360 end-of-month convention.
//
//@CLASSES:
//  bbldcu::Sia30360eom: SIA 30/360 eom convention stateless functions
//
//@DESCRIPTION: This component provides a 'struct', 'bbldcu::Sia30360eom',
// that defines a suite of date-related functions, which can be used to compute
// the day-count and year-fraction between two dates as prescribed by the
// Standard Industry Association (SIA) 30/360 convention with end of month
// (eom) adjustments.  In this convention (also known as "US 30/360" or just
// "30/360"), each year is assumed to have 12 months and 360 days, each month
// consisting of exactly 30 days.  Special end-of-month rule adjustments *are*
// made to account for the last day of February.  Note that in this convention,
// the second date (D2) may or may not be adjusted depending on the first date
// (D1).
//
///SIA-30/360-eom Day-Count Algorithm
///----------------------------------
// Given 'beginDate' and 'endDate' let:
//
// Ye =  year of earlier date           Yl =  year of later date
// Me = month of earlier date           Ml = month of later date
// De =   day of earlier date           Dl =   day of later date
//
//   o If Dl is the last day of February (29 in a leap year, else 28)
//     and De is the last day of February, change Dl to 30.
//
//   o If De is the last day of February, change De to 30.
//
//   o If Dl is 31 and De is 30 or 31, change Dl to 30.
//
//   o If De is 31, change De to 30.
//
// daysDiff ::= sign(endDate - beginDate) *
//                                   (Yl - Ye) * 360 + (Ml - Me) * 30 + Dl - De
//..
// Ref: Standard Securities Calculation Methods (1996) ISBN 1-882936-01-9.
//
///Usage
///-----
// This section illustrates intended use of this component.
//
///Example 1: Computing Day-Count and Year-Fraction
///- - - - - - - - - - - - - - - - - - - - - - - -
// The following snippets of code illustrate how to use 'bbldcu_Sia30360eom'
// methods.  First, create two 'bdlt::Dates' 'd1' and 'd2':
//..
//  const bdlt::Date d1(2004,  9, 30);
//  const bdlt::Date d2(2004, 12, 31);
//..
// Then, compute the day-count between these two dates:
//..
//  const int daysDiff = bbldcu::Sia30360eom::daysDiff(d1, d2);
//  assert(90 == daysDiff);
//..
// Finally, compute the year-fraction between these two dates:
//..
//  const double yearsDiff = bbldcu::Sia30360eom::yearsDiff(d1, d2);
//  assert(0.25 == yearsDiff);
//..

#ifndef INCLUDED_BBLSCM_VERSION
#include <bblscm_version.h>
#endif

namespace BloombergLP {

namespace bdlt {

class Date;

}  // close namespace bdlt

namespace bbldcu {

                           // ==================
                           // struct Sia30360eom
                           // ==================

struct Sia30360eom {
    // This 'struct' provides a namespace for a suite of pure functions that
    // compute values based on dates according to the SIA 30/360 end-of-month
    // convention.

    // CLASS METHODS
    static int daysDiff(const bdlt::Date& beginDate,
                        const bdlt::Date& endDate);
        // Return the number of days between the specified 'beginDate' and
        // 'endDate' according to the SIA 30/360 end-of-month convention.  If
        // 'beginDate <= endDate', then the result is non-negative.  Note that
        // reversing the order of 'beginDate' and 'endDate' negates the result.

    static double yearsDiff(const bdlt::Date& beginDate,
                            const bdlt::Date& endDate);
        // Return the number of years between the specified 'beginDate' and
        // 'endDate' according to the SIA 30/360 end-of-month convention.  If
        // 'beginDate <= endDate', then the result is non-negative.  Note that
        // reversing the order of 'beginDate' and 'endDate' negates the result;
        // specifically '|yearsDiff(b, e) + yearsDiff(e, b)| <= 1.0e-15'.
};

}  // close package namespace
}  // close enterprise namespace

#endif

// ----------------------------------------------------------------------------
// Copyright 2015 Bloomberg Finance L.P.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ----------------------------- END-OF-FILE ----------------------------------