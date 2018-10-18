#include "cpu/instr.h"

static void instr_execute_1op() {
	OPERAND opr_dest;
	opr_dest.type=OPR_REG;
	opr_dest.addr=0x4;
	opr_dest.data_size=data_size;
	operand_read(&opr_dest);
	opr_src.val=opr_dest.val;
	cpu.esp+=4;
	operand_read(&opr_src);
}

make_instr_impl_1op(pop,r,v)
