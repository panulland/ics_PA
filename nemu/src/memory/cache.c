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
	uint32_t num = (paddr << 18 >> 26) * 8;
	uint32_t tag = paddr >> 14;
	uint32_t addr = paddr << 18 >> 18;
	for(int i=0; i < 8; i++) {
		if(cache[num + i].tag == tag && cache[num + i].valid == 1) {
			return cache[num + i].data[addr];
		}
	}
	for(int i=0; i < 8; i++) {
		if(cache[num + i].valid == 0) {
			cache[num + i].valid = 1;
			cache[num + i].tag = tag;
			for(int j=0;j<32;j++) {
				cache[num+i].data[j]=hw_mem[addr+j];
			}
			return cache[num + i].data[0];
		}
	}
	cache[num].tag=tag;
	for(int j=0;j<32;j++) {
		cache[num].data[j]=hw_mem[addr+j];
	}
	return cache[num].data[0];
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
