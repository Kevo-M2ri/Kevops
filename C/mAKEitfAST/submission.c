#include <stdbool.h>

#include "vectors.h"


bool vector_fma(struct doubleVector * a,
                const struct doubleVector * b,
                const struct doubleVector * c) {
  int length = a->length;
  double * a_data = a->data;
  double * b_data = b->data;
  double * c_data = c->data;

  if (b->length != length || c->length != length) {
    return false;
  }

  int i = 0; // define i to avoid redefining
  int limit = length - (length % 4);
  for (; i < limit; i += 4) {
      __asm__ volatile (
        "movsd (%0), %%ymm0\n"
        "movsd (%1), %%ymm1\n"
        "movsd (%2), %%ymm2\n"
        "vfmadd231sd %%ymm0, %%ymm1,  %%ymm2\n"
        "vmovupd %%ymm2, 0(%0)\n"
      :
      : "r" (a_data), "r" (b_data), "r" (c_data)
      : "ymm0", "ymm1", "ymm2", "memory"
    );
    // pointer advancement by 32 bits
    a_data +=4;
    b_data +=4;
    c_data +=4;
  }

  //any remaining elements 1 by 1 processing (tail loop)
  for (; i < length; ++i) {
    __asm__ volatile (
      "movsd 0(%0), %%xmm0\n"
      "movsd 0(%1), %%xmm1\n"
      "movsd 0(%2), %%xmm2\n"
      "vfmadd231sd %%xmm0, %%xmm1, %%xmm2\n"
      "movsd %%xmm2, 0(%0)\n"
      :
      : "r" (a_data), "r" (b_data), "r" (c_data)
      : "xmm0", "xmm1", "xmm2", "memory"
    );
    
    // Advance pointers by 8 bytes
    a_data += 1;
    b_data += 1;
    c_data += 1;
  }

  return true;
}
