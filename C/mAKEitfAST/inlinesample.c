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

  int limit = length - (length % 16);
  for (int i = 0; i < limit; i += 16) {
      __asm__ volatile (
        "movsd (%0), %%ymm0\n"
        "movsd (%1), %%ymm1\n"
        "movsd (%2), %%ymm2\n"
        "vfmadd231sd %%ymm1, %%ymm2,  %%ymm0\n"
        "movsd %%ymm0,  (%0)\n"
        "addq  $32, %0\n"
        "addq  $32, %1\n"
        "addq  $32, %2\n"
        "loop 1b\n"
      : "+r" (a_data), "+r" (b_data), "+r" (c_data), "+c" (length)
      :
      : "memory"
    );
  }

  return true;
}
