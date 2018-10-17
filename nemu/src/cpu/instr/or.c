#include "cpu/instr.h"

static void instr_execute_2op() {
	operand_read (&opr_src);
	opr_dest.val = alu_sub(opr_dest.val,opr_src.val,data_size);
	operand_read(&opr_dest);
}

make_instr_impl_2op(or,i,rm,b)
make_instr_impl_2op(or,i,rm,v)
make_instr_impl_2op(or,i,rm,bv)
