#include "cpu/instr.h"

make_instr_func(ret_near) {
	OPERAND m;
	m.data_size=data_size;
	m.type=OPR_MEM;
	m.addr=cpu.esp;
	operand_read(&m);

	cpu.esp += 4;

	print_asm_0("ret","",1);

	return m.val - cpu.eip;
}

make_instr_func(ret_near_imm16) {
	OPERAND m,i;
	m.data_size=data_size;
	m.type=OPR_MEM;
	m.addr=cpu.esp;
	i.data_size=16;
	i.type=OPR_IMM;
	i.sreg=SREG_CS;
	i.addr=eip+1;
	operand_read(&m);
	operand_read(&i);

	cpu.esp += 4;
	cpu.esp += i.val;

	print_asm_1("ret","",3,&i);

	return m.val - cpu.eip;
}
