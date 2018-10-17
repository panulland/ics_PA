#include "cpu/instr.h"

static void instr_execute_1op() {
	opr_dest.type = OPR_MEM;
	cpu.esp -= 4;
	opr_dest.addr = cpu.esp;
	opr_dest.data_size=data_size;
	opr_dest.val = cpu.eip;
	operand_write(&opr_dest);
}

make_instr_impl_1op(push,r,v)
make_instr_impl_1op(push,rm,v)
