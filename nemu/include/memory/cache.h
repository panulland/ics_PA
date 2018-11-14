#ifndef __CACHE_H_
#define __CACHE_H_

#include"nemu.h"

typedef struct {
	int valid;
	uint32_t tag;
	uint8_t data[64];
} CacheLine;

CacheLine cache[1024];

void init_cache();

uint32_t cache_read(paddr_t paddr, size_t len);

void cache_write(paddr_t paddr, size_t len, uint32_t data);

#endif
