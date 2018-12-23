#include "cpu/cpu.h"
#include "memory/memory.h"

// translate from linear address to physical address
paddr_t page_translate(laddr_t laddr) {
#ifndef TLB_ENABLED
	//printf("\nPlease implement page_translate()\n");
	//assert(0);
	uint32_t dir = laddr >> 22 & 0x3ff;
	uint32_t page = laddr << 10 >> 22;
	uint32_t offset = laddr << 20 >> 20;
	if(dir * 4 > 0x3ff)
	printf("=========");
	PDE pde;
	PTE pte;
	pde.val = paddr_read((cpu.cr3.pdbr << 12) + dir * 4, 4);
	//memcpy(&pde.val, hw_mem + ((cpu.cr3.pdbr << 12) + dir * 4), 4);
	if(pde.present == 0)
		printf("%x\n",laddr);
	assert(pde.present == 1);
	pte.val = paddr_read((pde.page_frame << 12) + page * 4, 4);
	//memcpy(&pte.val, hw_mem + ((pde.page_frame << 12) + page * 4), 4);
	if(pte.present == 0)
	printf("%x\n",laddr);
	assert(pte.present == 1);
	//if(laddr > 0xa0000 && laddr < 0xa0000+320*200)
	//	printf("%x\n",laddr);
	return (pte.page_frame << 12) + offset;
#else	
	return tlb_read(laddr) | (laddr & PAGE_MASK);;
#endif
}
