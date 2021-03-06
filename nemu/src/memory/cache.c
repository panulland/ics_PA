#include "memory/cache.h"
#include "memory/memory.h"
#include <memory.h>
#include <stdio.h>

void init_cache() {
	for(int i=0;i < 1024;i++) {
		cache[i].valid = 0;
		cache[i].tag = 0;
	}
}

uint32_t cache_read(paddr_t paddr, size_t len) {
	uint32_t num = (paddr << 19 >> 25) * 8;
	uint32_t tag = paddr >> 13;
	uint32_t addr = paddr << 26 >> 26;
	if(addr+len>64) {
		size_t len1=64-addr;
		size_t len2=len-len1;
		switch(len) {
			case 2:return (cache_read(paddr,1)) + (cache_read(paddr+1,1)<<8);
			case 4:return cache_read(paddr,len1) + (cache_read(paddr+len1,len2)<<(len1*8));
		}
	}
	uint32_t res = 0;
	for(int i=0; i < 8; i++) {
		if(cache[num + i].tag == tag && cache[num + i].valid == 1) {
			memcpy(&res,cache[num+i].data+addr,len);
			return res;		
		}
	}
	for(int i=0; i < 8; i++) {
		if(cache[num + i].valid == 0) {
			cache[num + i].valid = 1;
			cache[num + i].tag = tag;
			for(int j=0;j<64;j++) {
				cache[num+i].data[j]=hw_mem[paddr-addr+j];
			}
			return hw_mem_read(paddr,len);
		}
	}
	cache[num].tag=tag;
	for(int j=0;j<64;j++) {
		cache[num].data[j]=hw_mem[paddr-addr+j];
	}
	return hw_mem_read(paddr,len);
}

void cache_write(paddr_t paddr, size_t len, uint32_t data) {
	uint32_t num = (paddr << 19 >> 25) * 8;
	uint32_t tag = paddr >> 13;
	uint32_t addr = paddr << 26 >> 26;
	if(addr+len>64) {
		size_t len1=64-addr;
		size_t len2=len-len1;
		switch(len) {
			case 2:cache_write(paddr,1,data<<24>>24);
			       cache_write(paddr+1,1,data>>8);
			       return;
			case 4:cache_write(paddr,len1,data<<(32-len1*8)>>(32-len1*8));
			       cache_write(paddr+len1,len2,data>>(len1*8));
			       return;
		}
	}
	for(int i=0; i < 8;i++) {
		if(cache[num + i].tag == tag && cache[num + i].valid == 1) {
			memcpy(cache[num+i].data+addr,&data,len);
			hw_mem_write(paddr,len,data);
			return;
		}
	}
	hw_mem_write(paddr,len,data);
	return;
}
