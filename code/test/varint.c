/// \file varint.c test for variable integer encoding

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "check.h"

#include "variable_int.h"

int main(void) {
  ilr_element_t arr[10];
  size_t size;

  size = ilr_varint_from_size_t(arr, 0xAB);
  CHECK(size == 1);
  CHECK(arr[0] == 0xAB);
  
  size = ilr_varint_from_size_t(arr, 0xFFFF);
  CHECK(size == 2);
  CHECK(arr[0] == 0xFFFF);
  CHECK(arr[1] == 0);

  size = ilr_varint_from_size_t(arr, 0x10000);
  CHECK(size == 2);
  CHECK(arr[0] == 0xFFFF);
  CHECK(arr[1] == 1);

  size = ilr_varint_from_size_t(arr, 0xFFFFFFFF);
  CHECK(size == 3);
  CHECK(arr[0] == 0xFFFF);
  CHECK(arr[1] == 0xFFFF);
  CHECK(arr[2] == 0);

  size = ilr_varint_from_size_t(arr, 0x100000014);
  CHECK(size == 3);
  CHECK(arr[0] == 0xFFFF);
  CHECK(arr[1] == 0xFFFF);
  CHECK(arr[2] == 0x15);

  size = ilr_varint_from_size_t(arr, 0xFFFFFFFFFFFF);
  CHECK(size == 4);
  CHECK(arr[0] == 0xFFFF);
  CHECK(arr[1] == 0xFFFF);
  CHECK(arr[2] == 0xFFFF);
  CHECK(arr[3] == 0);

  size = ilr_varint_from_size_t(arr, 0x100000000CAFE);
  CHECK(size == 4);
  CHECK(arr[0] == 0xFFFF);
  CHECK(arr[1] == 0xFFFF);
  CHECK(arr[2] == 0xFFFF);
  CHECK(arr[3] == 0xCAFF);

  size = ilr_varint_from_size_t(arr, 0xFFFFFFFFFFFFFFFF);
  CHECK(size == 5);
  CHECK(arr[0] == 0xFFFF);
  CHECK(arr[1] == 0xFFFF);
  CHECK(arr[2] == 0xFFFF);
  CHECK(arr[3] == 0xFFFF);
  CHECK(arr[4] == 0);

  arr[0] = 0xCAFE;
  CHECK(ilr_varint_to_size_t(arr, (sizeof(arr) / sizeof(arr[0]))) == 0xCAFE);

  arr[0] = 0xFFFF;
  arr[1] = 1;
  CHECK(ilr_varint_to_size_t(arr, (sizeof(arr) / sizeof(arr[0]))) == 0x10000);

  arr[0] = 0xFFFF;
  arr[1] = 0xFFFF;
  arr[2] = 0XCAFE;
  CHECK(ilr_varint_to_size_t(arr, (sizeof(arr) / sizeof(arr[0]))) == 0x10000CAFD);

  arr[0] = 0xFFFF;
  arr[1] = 0xFFFF;
  arr[2] = 0xFFFF;
  arr[3] = 0;
  CHECK(ilr_varint_to_size_t(arr, (sizeof(arr) / sizeof(arr[0]))) == 0xFFFFFFFFFFFF);

  arr[0] = 0xFFFF;
  arr[1] = 0xFFFF;
  arr[2] = 0xFFFF;
  arr[3] = 1;
  CHECK(ilr_varint_to_size_t(arr, (sizeof(arr) / sizeof(arr[0]))) == 0x1000000000000);

  arr[0] = 0xFFFF;
  arr[1] = 0xFFFF;
  arr[2] = 0xFFFF;
  arr[3] = 0xFFFF;
  arr[4] = 0;
  CHECK(ilr_varint_to_size_t(arr, (sizeof(arr) / sizeof(arr[0]))) == 0xFFFFFFFFFFFFFFFF);

  return check_report();
}

