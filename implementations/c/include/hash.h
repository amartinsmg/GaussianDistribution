#ifndef HASH
#define HASH

#include <stdint.h>

int32_t hash32(int32_t x)
{
  x ^= x >> 16;
  x *= 0x7feb352d;
  x ^= x >> 15;
  x *= 0x846ca68d;
  x ^= x >> 16;
  return x;
}

#endif /*HASH*/
