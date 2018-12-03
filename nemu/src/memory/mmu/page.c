#include "cpu/cpu.h"
#include "memory/memory.h"

// translate from linear address to physical address
paddr_t page_translate(laddr_t laddr) {
#ifndef TLB_ENABLED
	//printf("\nPlease implement page_translate()\n");
	//assert(0);
	uint32_t dir = laddr >> 22;
	uint32_t page = laddr << 10 >> 22;
	uint32_t offset = laddr << 20 >> 20;
	PDE pde;
	PTE pte;
	memcpy(&pde.val, hw_mem + ((cpu.cr3.pdbr << 12) + dir * 4), 4);
	assert(pde.present == 1);
	memcpy(&pte.val, hw_mem + ((pde.page_frame << 12) + page * 4), 4);
	assert(pte.present == 1);
	printf("laddr %x\ndir %x\npage %x\noffset %x\n",laddr,dir,page,offset);
	return (pte.page_frame << 12) + offset;
#else	
	return tlb_read(laddr) | (laddr & PAGE_MASK);;
#endif
}
