#include "memory/cache.h"

init_cache() {
	for(int i=0;i < 1024;i++) {
		cache[i].valid = 0;
	}
}
