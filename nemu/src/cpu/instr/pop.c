#include "cpu/instr.h"

static void instr_execute_1op() {
	OPERAND opr_dest;
	opr_dest.type=OPR_MEM;
	opr_dest.sreg=SREG_ES;
	opr_dest.addr=cpu.esp;
	opr_dest.data_size=data_size;
	operand_read(&opr_dest);
	opr_src.val=opr_dest.val;
	cpu.esp+=4;
	operand_write(&opr_src);
}

make_instr_impl_1op(pop,r,v)

make_instr_func(popa) {
	OPERAND m,r;
	m.data_size = r.data_size = data_size;
	m.type = OPR_MEM;
	r.type = OPR_REG;
	m.sreg = SREG_ES;
	m.addr = cpu.esp;
	print_asm_0("popa","",1);
	operand_read(&m);
	r.addr = REG_EDI;
	r.val = m.val;
	operand_write(&r);
	cpu.esp += 4;
	m.addr = cpu.esp;
	operand_read(&m);
	r.addr = REG_ESI;
	r.val = m.val;
	operand_write(&r);
	cpu.esp += 4;
	m.addr = cpu.esp;
	operand_read(&m);
	r.addr = REG_EBP;
	r.val = m.val;
	operand_write(&r);
	cpu.esp += 8;
	m.addr = cpu.esp;
	operand_read(&m);
	r.addr = REG_EBX;
	r.val = m.val;
	operand_write(&r);
	cpu.esp += 4;
	m.addr = cpu.esp;
	operand_read(&m);
	r.addr = REG_EDX;
	r.val = m.val;
	operand_write(&r);
	cpu.esp += 4;
	m.addr = cpu.esp;
	operand_read(&m);
	r.addr = REG_ECX;
	r.val = m.val;
	operand_write(&r);
	cpu.esp += 4;
	m.addr = cpu.esp;
	operand_read(&m);
	r.addr = REG_EAX;
	r.val = m.val;
	operand_write(&r);
	cpu.esp += 4;
	return 1;
}
