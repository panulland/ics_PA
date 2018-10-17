#include "cpu/instr.h"

make_instr_func(ret_near) {
	OPERAND r,m;
	r.data_size=data_size;
	r.type=OPR_REG;
	r.addr=0x4;
	operand_read(&r);
	m.data_size=data_size;
	m.type=OPR_MEM;
	m.addr=cpu.esp;
	operand_read(&m);
	cpu.eip=m.val;
	cpu.esp+=4;

	print_asm_0("ret","",1);

	return 1 + data_size / 8;
}
