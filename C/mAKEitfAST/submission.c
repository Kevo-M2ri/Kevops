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

  int i = 0;
  int limit4 = length - (length % 4);

  // Process 4 elements at a time
  for (; i < limit4; i += 4) {
    __asm__ volatile (
      "vmovupd (%0), %%ymm0\n\t"
      "vmovupd (%1), %%ymm1\n\t"
      "vmovupd (%2), %%ymm2\n\t"
      "vfmadd231pd %%ymm1, %%ymm2, %%ymm0\n\t"
      "vmovupd %%ymm0, (%0)\n\t"
      :
      : "r" (a_data), "r" (b_data), "r" (c_data)
      : "ymm0", "ymm1", "ymm2", "memory"
    );
    
    a_data += 4;
    b_data += 4;
    c_data += 4;
  }

  // Tail Loop: Handle remaining elements 1 by 1
  for (; i < length; ++i) {
    __asm__ volatile (
      "vmovsd (%0), %%xmm0\n\t"
      "vmovsd (%1), %%xmm1\n\t"
      "vmovsd (%2), %%xmm2\n\t"
      "vfmadd231sd %%xmm1, %%xmm2, %%xmm0\n\t"
      "vmovsd %%xmm0, (%0)\n\t"
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