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
	SegDesc *s = cpu.segReg[sreg].index * 8 + cpu.gdtr.base;
	cpu.segReg[sreg].base = s->base_15_0 + s->base_23_16 << 16 + s->base_31_24 << 24;
	cpu.segReg[sreg].limit = s->limit_15_0 + s->limit_19_16 << 16;
	/* TODO: load the invisibile part of the segment register 'sreg' by reading the GDT.
	 * The visible part of 'sreg' should be assigned by mov or ljmp already.
	 */
}
