#include "cpu/instr.h"

static void instr_execute_2op() {
	operand_read(&opr_src);
	operand_read(&opr_dest);
	uint32_t tmp = opr_dest.val;	
	opr_dest.val = alu_and (opr_dest.val,opr_src.val,data_size);
	opr_dest.val = tmp;
	cpu.eflags.CF = 0;
	cpu.eflags.OF = 0;
}

make_instr_impl_2op(test,r,rm,v)
