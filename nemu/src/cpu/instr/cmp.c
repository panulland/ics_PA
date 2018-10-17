#include "cpu/instr.h"

static void instr_execute_2op() {
	operand_read (&opr_src);
	opr_dest.val = alu_sub(opr_dest.val,opr_src.val,data_size);
}

make_instr_impl_2op(cmp,i,rm,b)
make_instr_impl_2op(cmp,i,rm,v)
make_instr_impl_2op(cmp,i,rm,bv)
make_instr_impl_2op(cmp,r,rm,v)
