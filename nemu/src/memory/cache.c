#include "memory/cache.h"
#include "memory/memory.h"

void init_cache() {
	for(int i=0;i < 1024;i++) {
		cache[i].valid = 0;
		cache[i].tag = 0;
		cache[i].data = 0;
	}
}

uint32_t cache_read(paddr_t paddr, size_t len) {
	return hw_mem_read(paddr,len);
	uint32_t num = (paddr << 18 >> 26) * 8;
	uint32_t tag = paddr >> 14;
	//uint32_t addr = paddr << 18 >> 18;
	for(int i=0; i < 8; i++) {
		if(cache[num + i].tag == tag && cache[num + i].valid == 1) {
			return cache[num + i].data;
		}
	}
	for(int i=0; i < 8; i++) {
		if(cache[num + i].valid == 0) {
			cache[num + i].valid = 1;
			cache[num + i].tag = tag;
			cache[num + i].data = hw_mem_read(paddr,len);
			return cache[num + i].data;
		}
	}
	cache[num].tag=tag;
	cache[num].data=hw_mem_read(paddr,len);
	return cache[num].data;
}

void cache_write(paddr_t paddr, size_t len, uint32_t data) {
	uint32_t num = (paddr << 18 >> 26) * 8;
	uint32_t tag = paddr >> 14;
	//uint32_t addr = paddr << 18 >> 18;
	for(int i=0; i < 8;i++) {
		if(cache[num + i].tag == tag && cache[num + i].valid == 1) {
			cache[num + i].data = data;
			hw_mem_write(paddr,len,data);
			return;
		}
	}
	hw_mem_write(paddr,len,data);
	return;
}
