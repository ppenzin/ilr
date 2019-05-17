#ifndef VERIFY_H
#define VERIFY_H

namespace test {
  /// Record a test result
  bool record(bool result);

  template <typename T>
  /// Verify that value matches expected, trigger report failure if not matching
  bool verify(T value, T expected) {
    return record(value == expected);
  }

  /// Report verification -- return 0 if success, print a message and return non-0 status if failed
  int report();

} // namespace test

#endif // VERIFY_H
