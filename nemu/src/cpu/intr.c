#include "cpu/intr.h"
#include "cpu/instr.h"
#include "memory/memory.h"


void raise_intr(uint8_t intr_no) {
#ifdef IA32_INTR
	GateDesc gate;
	printf("%x %x\n",cpu.idtr.base,cpu.idtr.limit);
	memcpy(&gate, hw_mem + cpu.idtr.base + intr_no * 8, 8);
	assert(0);
	printf("%x %x",gate.val[0],gate.val[1]);
	assert(0);
	cpu.esp -= 4;
	OPERAND temp;
	temp.data_size = data_size;
	temp.type = OPR_MEM;
	temp.sreg = SREG_ES;
	temp.val = cpu.eflags.val;
	temp.addr = cpu.esp;
	operand_write(&temp);
	cpu.esp -= 4;
	temp.addr = cpu.esp;
	temp.val = cpu.cs.val;
	operand_write(&temp);
	cpu.esp -= 4;
	temp.addr = cpu.esp;
	temp.val = cpu.eip;
	operand_write(&temp);
	printf("%x\n",cpu.eip);
	cpu.eip = gate.offset_15_0 + (gate.offset_31_16 << 16);
#endif
}

void raise_sw_intr(uint8_t intr_no) {
	// return address is the next instruction
	cpu.eip += 2;
	raise_intr(intr_no);
}
