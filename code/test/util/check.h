/// \file check.h test check routines

#ifndef TEST_UTIL_CHECK_H
#define TEST_UTIL_CHECK_H

/// Report if condition is false
///
/// \param label print "Failed: <label>"
/// \param expresion boolean value to check
void check(const char * label, bool expression);

/// Shorthand for printing the expression we are checking
#define CHECK(X) check(#X, (X))

/// Report if any tests are failing
/// \return 0 on sucess, and non-zero integer otherwise
int check_report(void);

#endif // TEST_UTIL_CHECK_H
