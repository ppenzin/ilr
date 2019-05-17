#include "test/verify.h"

#include <vector>
#include <iostream>

using namespace std;

static vector<bool> results;

bool test::record(bool result) {
  results.push_back(result);
  return result;
}

int test::report() {
  // Anything ran?
  if (results.size() == 0) {
    cout << "No tests ran." << endl;
    return 1;
  }

  // Find failed tests
  vector<unsigned> inds;
  for (unsigned i = 0; i < results.size(); ++i) {
    if (!results[i])
      inds.push_back(i+1);
  }

  cout << inds.size() << " out of " << results.size()
       << " tests failed." << endl;
  if (inds.size() && (inds.size() != results.size())) {
    bool start = false;
    cout << "Test #s: ";
    for (auto i : inds) {
       if (start)
         cout << ", ";
       cout << i;
       start = true;
    }
    cout << "." << endl;
  }

  return inds.size();
}

