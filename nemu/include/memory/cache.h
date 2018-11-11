#ifndef __CACHE_H_
#define __CACHE_H_

struct CacheLine {
	int valid;
	int tag;
	char data[64];
};

init_cache();

uint32_t cache_read(paddr_t paddr, size_t len, CacheLine* cache);

void cache_write(paddr_t paddr, size_t len, uint32_t data, CacheLine* cache);
