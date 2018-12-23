#include "common.h"
#include "memory.h"
#include "x86/memory.h"
#include <string.h>

#define VMEM_ADDR 0xa0000
#define SCR_SIZE (320 * 200)
#define NR_PT ((SCR_SIZE + PT_SIZE - 1) / PT_SIZE)  // number of page tables to cover the vmem


PDE* get_updir();

void create_video_mapping() {
	
	/* TODO: create an identical mapping from virtual memory area
	 * [0xa0000, 0xa0000 + SCR_SIZE) to physical memeory area
	 * [0xa0000, 0xa0000 + SCR_SIZE) for user program. You may define
	 * some page tables to create this mapping.
	 */

	//panic("please implement me");
	PDE *pdir = get_updir();
	pdir->present = 1;
	//pdir += KOFFSET / PT_SIZE;
	//pdir->present = 1;
	PTE *ptable = (PTE *)((uint32_t)pdir->page_frame);
	for(uint32_t i = 0; i < NR_PT; i++) {
		uint32_t page = 0xa0 + i;
		PTE* pte;
		pte = ptable + page;
		pte->present = 1;
		pte->page_frame = page & 0xfffff;
	}
}

void video_mapping_write_test() {
	int i;
	uint32_t *buf = (void *)VMEM_ADDR;
	for(i = 0; i < SCR_SIZE / 4; i ++) {
		buf[i] = i;
	}
}

void video_mapping_read_test() {
	int i;
	uint32_t *buf = (void *)VMEM_ADDR;
	for(i = 0; i < SCR_SIZE / 4; i ++) {
		assert(buf[i] == i);
	}
}

void video_mapping_clear() {
	memset((void *)VMEM_ADDR, 0, SCR_SIZE);
}

