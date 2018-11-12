#include "memory/cache.h"
#include "memory/memory.h"

void init_cache() {
	for(int i=0;i < 1024;i++) {
		cache[i].valid = 0;
		cache[i].tag = 0;
	}
}

uint32_t cache_read(paddr_t paddr, size_t len) {
	return hw_mem_read(paddr,len);
	uint32_t num = (paddr << 20 >> 25) * 8;
	uint32_t tag = paddr >> 12;
	uint32_t addr = paddr << 27 >> 27;
	if(addr+len>32) {
		size_t len1=32-addr;
		size_t len2=len-len1;
		switch(len) {
			case 2:return (cache_read(paddr,1)<<8) + cache_read(paddr+1,1);
			case 4:return (cache_read(paddr,len1)<<len2) + cache_read(paddr+len1,len2);
		}
	}
	uint32_t res = 0;
	for(int i=0; i < 8; i++) {
		if(cache[num + i].tag == tag && cache[num + i].valid == 1) {
			switch(len) {
				case 1:return cache[num + i].data[addr];
				       break;
				case 2:res += cache[num + i].data[addr]<<8;
				       res += cache[num + i].data[addr + 1];
				       return res;
				       break;
				case 3:res += cache[num + i].data[addr]<<16;
				       res += cache[num + i].data[addr+1]<<8;
				       res += cache[num + i].data[addr+2];
				case 4:res += cache[num + i].data[addr]<<24;
				       res += cache[num + i].data[addr + 1]<<16;
				       res += cache[num + i].data[addr + 2]<<8;
				       res += cache[num + i].data[addr + 3];
				       return res;
				       break;
			}
						
		}
	}
	for(int i=0; i < 8; i++) {
		if(cache[num + i].valid == 0) {
			cache[num + i].valid = 1;
			cache[num + i].tag = tag;
			for(int j=0;j<32;j++) {
				cache[num+i].data[j]=hw_mem[paddr-addr+j];
			}
			return hw_mem_read(paddr,len);
		}
	}
	cache[num].tag=tag;
	for(int j=0;j<32;j++) {
		cache[num].data[j]=hw_mem[paddr-addr+j];
	}
	return hw_mem_write(paddr,len);
}

void cache_write(paddr_t paddr, size_t len, uint32_t data) {
	uint32_t num = (paddr << 20 >> 25) * 8;
	uint32_t tag = paddr >> 12;
	uint32_t addr = paddr << 27 >> 27;
	if(addr+len>32) {
		size_t len1=32-addr;
		size_t len2=len-len1;
		switch(len) {
			case 2:cache_write(paddr,1,data>>8);
			       cache_write(paddr+1,1,data<<24>>24);
			       return;
			case 4:cache_write(paddr,len1,data>>(len2*8));
			       cache_write(paddr,len2,data<<(32-len2*8)>>(32-len2*8));
			       return;
		}
	}
	for(int i=0; i < 8;i++) {
		if(cache[num + i].tag == tag && cache[num + i].valid == 1) {
			for(int j=0;j<len;j++) {
				cache[num + i].data[addr+j] = data >> (8*(len - 1 -j));
			hw_mem_write(paddr,len,data);
			return;
		}
	}
	hw_mem_write(paddr,len,data);
	return;
}
