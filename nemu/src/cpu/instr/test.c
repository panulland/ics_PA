#include "cpu/instr.h"

static void instr_execute_2op() {
	operand_read(&opr_read);
	opr_dest.val = opr_src.val & opr_dest.val;
	cpu.eflags.CF = 0;
	cpu.eflags.OF = 0;
}

make_instr_impl_2op(test,r,rm,v)
