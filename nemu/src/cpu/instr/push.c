#include "cpu/instr.h"

static void instr_execute_1op() {
	operand_read(&opr_src);
	if(opr_src.type==OPR_IMM&&opr_src.data_size==8)
	{
		opr_src.val=sign_ext(opr_src.val,8)&(0xFFFFFFFF>>(32-data_size));
	}
	OPERAND opr_dest;
	opr_dest.data_size=data_size;
	opr_dest.type = OPR_MEM;
	opr_dest.sreg = SREG_ES;
	cpu.esp -= 4;
	opr_dest.addr = cpu.esp;
	opr_dest.val = opr_src.val;
	operand_write(&opr_dest);
}

make_instr_impl_1op(push,r,v)
make_instr_impl_1op(push,rm,v)
make_instr_impl_1op(push,i,v)
make_instr_impl_1op(push,i,b)

make_instr_func(pusha) {
	uint32_t temp;
	temp = cpu.esp;
	OPERAND r,m;
	r.data_size = m.data_size = data_size;
	m.type = OPR_MEM;
	m.sreg = SREG_ES;
	r.type = OPR_REG;
	r.addr = REG_EAX;
	cpu.esp -= 4;
	m.addr = cpu.esp;
	operand_read(&r);
	m.val = r.val;
	operand_write(&m);
	r.addr = REG_ECX;
	cpu.esp -= 4;
	m.addr = cpu.esp;
	operand_read(&r);
	m.val = r.val;
	operand_write(&m);
	r.addr = REG_EDX;
	cpu.esp -= 4;
	m.addr = cpu.esp;
	operand_read(&r);
	m.val = r.val;
	operand_write(&m);
	r.addr = REG_EBX;
	cpu.esp -= 4;
	m.addr = cpu.esp;
	operand_read(&r);
	m.val = r.val;
	operand_write(&m);
	cpu.esp -= 4;
	m.addr = cpu.esp;
	m.val = temp;
	operand_write(&m);
	r.addr = REG_EBP;
	cpu.esp -= 4;
	m.addr = cpu.esp;
	operand_read(&r);
	m.val = r.val;
	operand_write(&m);
	r.addr = REG_ESI;
	cpu.esp -= 4;
	m.addr = cpu.esp;
	operand_read(&r);
	m.val = r.val;
	operand_write(&m);
	r.addr = REG_EDI;
	cpu.esp -= 4;
	m.addr = cpu.esp;
	operand_read(&r);
	m.val = r.val;
	operand_write(&m);
	print_asm_0("pusha","",1);
	return 1;
}
