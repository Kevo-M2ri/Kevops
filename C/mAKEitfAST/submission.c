#include <stdbool.h>

#include "vectors.h"

bool vector_fma(struct doubleVector * a, const struct doubleVector * b, const struct doubleVector * c) {
  int length = a->length;
  double * a_data = a->data;
  double * b_data = b->data;
  double * c_data = c->data;

  if (b->length != length || c->length != length) {
    return false;
  }

  int i = 0; //avoid defining i everytime
  //Process 16 elements per iteration
  int limit16 = length - (length % 16);
  for (; i < limit16; i += 16) {
    __asm__ volatile (
      // Elements 0-3
      "vmovupd 0(%0), %%ymm0\n"
      "vmovupd 0(%1), %%ymm1\n"
      "vmovupd 0(%2), %%ymm2\n"
      "vfmadd231pd %%ymm1, %%ymm2, %%ymm0\n"
      "vmovupd %%ymm0, 0(%0)\n"

      // Elements 4-7
      "vmovupd 32(%0), %%ymm3\n"
      "vmovupd 32(%1), %%ymm4\n"
      "vmovupd 32(%2), %%ymm5\n"
      "vfmadd231pd %%ymm4, %%ymm5, %%ymm3\n"
      "vmovupd %%ymm3, 32(%0)\n"

      // Element 8-11
      "vmovupd 64(%0), %%ymm6\n"
      "vmovupd 64(%1), %%ymm7\n"
      "vmovupd 64(%2), %%ymm8\n"
      "vfmadd231pd %%ymm7, %%ymm8, %%ymm6\n"
      "vmovupd %%ymm6, 64(%0)\n"

      // Elements 12-15
      "vmovupd 96(%0), %%ymm9\n"
      "vmovupd 96(%1), %%ymm10\n"
      "vmovupd 96(%2), %%ymm11\n"
      "vfmadd231pd %%ymm10, %%ymm11, %%ymm9\n"
      "vmovupd %%ymm9, 96(%0)\n"
      :
      : "r" (a_data), "r" (b_data), "r" (c_data)
      : "ymm0", "ymm1", "ymm2", "ymm3", "ymm4", "ymm5",
        "ymm6", "ymm7", "ymm8", "ymm9", "ymm10", "ymm11", "memory"
    );
    a_data += 16;
    b_data += 16;
    c_data += 16;
  }

  // Process in blocks of 4 for the remaining elements
  int limit4 = length - (length % 4);
  for (; i < limit4; i += 4) {
    __asm__ volatile (
      "vmovupd (%0), %%ymm0\n"
      "vmovupd (%1), %%ymm1\n"
      "vmovupd (%2), %%ymm2\n"
      "vfmadd231pd %%ymm1, %%ymm2, %%ymm0\n"
      "vmovupd %%ymm0, (%0)\n"
      :
      : "r" (a_data), "r" (b_data), "r" (c_data)
      : "ymm0", "ymm1", "ymm2", "memory"
    );
    a_data += 4;
    b_data += 4;
    c_data += 4;
  }

  // Process any final trailing elements 1 by 1
  for (; i < length; ++i) {
    __asm__ volatile (
      "vmovsd (%0), %%xmm0\n"
      "vmovsd (%1), %%xmm1\n"
      "vmovsd (%2), %%xmm2\n"
      "vfmadd231sd %%xmm1, %%xmm2, %%xmm0\n"
      "vmovsd %%xmm0, (%0)\n"
      :
      : "r" (a_data), "r" (b_data), "r" (c_data)
      : "xmm0", "xmm1", "xmm2", "memory"
    );
    a_data += 1;
    b_data += 1;
    c_data += 1;
  }

  return true;
}