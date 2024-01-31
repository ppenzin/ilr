#include <stdbool.h>
#include <stdio.h>

static bool all_passed = true;

void check(const char * label, bool expression) {
  if (!expression) {
    printf("Failed: %s\n", label);
    all_passed = false;
  }
}

int check_report(void) {
  return (!all_passed);
}

