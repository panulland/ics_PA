#include "common.h"
#include "memory.h"
#include "x86/memory.h"
#include <string.h>

#define VMEM_ADDR 0xa0000
#define SCR_SIZE (320 * 200)
#define NR_PT ((SCR_SIZE + PT_SIZE - 1) / PT_SIZE)  // number of page tables to cover the vmem

PDE* get_updir();
PDE kpdir[NR_PDE] align_to_page;				// kernel page directory
PTE kptable[PHY_MEM / PAGE_SIZE] align_to_page;		// kernel page tables

void create_video_mapping() {
	
	/* TODO: create an identical mapping from virtual memory area
	 * [0xa0000, 0xa0000 + SCR_SIZE) to physical memeory area
	 * [0xa0000, 0xa0000 + SCR_SIZE) for user program. You may define
	 * some page tables to create this mapping.
	 */

	//panic("please implement me");
	PDE *pdir = (PDE *)va_to_pa(kpdir);
	PTE *ptable = (PTE *)va_to_pa(kptable);
	pdir->present = 1;
	for(int i = 0; i < SCR_SIZE; i++) {
		uint32_t addr = VMEM_ADDR + i;
		uint32_t page = addr << 10 >> 22;
		PTE* pte;
		pte = ptable + (pdir->page_frame << 12) + page;
		pte->present = 1;
		pte->page_frame = addr >> 20;
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

