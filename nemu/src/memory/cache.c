#include "memory/cache.h"

void init_cache() {
	for(int i=0;i < 1024;i++) {
		cache[i].valid = 0;
	}
}
