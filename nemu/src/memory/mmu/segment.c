#include "cpu/cpu.h"
#include "memory/memory.h"

// return the linear address from the virtual address and segment selector
uint32_t segment_translate(uint32_t offset, uint8_t sreg) {
	uint32_t ret = 0;
	ret = offset + cpu.segReg[sreg].base;
	/* TODO: perform segment translation from virtual address to linear address
	 * by reading the invisible part of the segment register 'sreg'
	 */
	return ret;
}

// load the invisible part of a segment register
void load_sreg(uint8_t sreg) {
	SegDesc s;
	s.val[0] = s.val[1] = 0;
	memcpy(&s, hw_mem + cpu.gdtr.base + cpu.segReg[sreg].index * 8, 8);
	printf("%x %x\n",s.val[0],s.val[1]);
	printf("%x %x %x %x\n",s.limit_15_0,s.base_15_0,s.type,s.base_31_24);
	cpu.segReg[sreg].base = (s.base_15_0) + (s.base_23_16 << 16) + (s.base_31_24 << 24);
	cpu.segReg[sreg].limit = (s.limit_15_0) + (s.limit_19_16 << 16);
	cpu.segReg[sreg].type = s.type;
	cpu.segReg[sreg].soft_use = s.soft_use;
	cpu.segReg[sreg].privilege_level = s.privilege_level;
	printf("%x\n",cpu.segReg[sreg].base);
	//assert(cpu.segReg[sreg].base = 0);
	assert(s.granularity=0);
	/* TODO: load the invisibile part of the segment register 'sreg' by reading the GDT.
	 * The visible part of 'sreg' should be assigned by mov or ljmp already.
	 */
}
