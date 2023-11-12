#ifndef MD5_H
#define MD5_H

#include "stdint.h"
#include "string.h"

/*
 * The basic MD5 functions.
 *
 * E and G are optimized compared to their RFC 1321 definitions for
 * architectures that lack an AND-NOT instruction, just like in Colin Plumb's
 * implementation.
 * E() has been used instead of F() because F() is already defined in the Arduino core
 */
#define E(x, y, z)			((z) ^ ((x) & ((y) ^ (z))))
#define G(x, y, z)			((y) ^ ((z) & ((x) ^ (y))))
#define H(x, y, z)			((x) ^ (y) ^ (z))
#define I(x, y, z)			((y) ^ ((x) | ~(z)))

/*
 * The MD5 transformation for all four rounds.
 */
#define STEP(f, a, b, c, d, x, t, s) \
	(a) += f((b), (c), (d)) + (x) + (t); \
	(a) = (((a) << (s)) | (((a) & 0xffffffff) >> (32 - (s)))); \
	(a) += (b);

/*
 * SET reads 4 input bytes in little-endian byte order and stores them
 * in a properly aligned word in host byte order.
 */
#define SET(n) \
	(ctx->block[(n)] = \
	(uint32_t)ptr[(n) * 4] | \
	((uint32_t)ptr[(n) * 4 + 1] << 8) | \
	((uint32_t)ptr[(n) * 4 + 2] << 16) | \
	((uint32_t)ptr[(n) * 4 + 3] << 24))
#define GET(n) \
	(ctx->block[(n)])

typedef struct
{
  uint32_t lo, hi;
  uint32_t a, b, c, d;
  uint8_t buffer[64];
  uint32_t block[16];
} MD5_CTX;

// public
void MD5_MakeHash(uint8_t *srcArr, uint32_t srcArrSize, uint8_t* destHash);
void MD5_MakeDigest16(const uint8_t *hash, char *digest);
  
#endif // MD5_H