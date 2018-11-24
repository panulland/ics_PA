#include "cpu/instr.h"

make_instr_func(leave) {
	OPERAND r;
	r.data_size=data_size;
	r.type=OPR_REG;
	r.addr=0x5;
	operand_read(&r);
	OPERAND r2;
	r2.data_size=data_size;
	r2.type=OPR_REG;
	r2.addr=0x4;
	r2.val=r.val;
	operand_write(&r2);

	OPERAND m;
	m.data_size=data_size;
	m.type=OPR_MEM;
	m.sreg=SREG_DS;
	m.addr=cpu.esp;
	operand_read(&m);
	cpu.esp+=4;
	r.val=m.val;
	operand_write(&r);

	print_asm_0("leave","",1);
	return 1;
}

