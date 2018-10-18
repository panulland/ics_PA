#include "cpu/instr.h"

static void instr_execute_1op() {
	OPERAND opr_dest;
	opr_dest.type=OPR_MEM;
	opr_dest.addr=cpu.esp;
	opr_dest.data_size=data_size;
	operand_read(&opr_dest);
	opr_src.val=opr_dest.val;
	cpu.esp+=4;
	operand_write(&opr_src);
}

make_instr_impl_1op(pop,r,v)
