#include "cpu/instr.h"

static void instr_execute_2op() {
	operand_read(&opr_src);
	opr_dest.val=alu_and(opr_dest.val,opr_src.val,data_size);
	operand_write(&opr_dest);
}

make_instr_impl_2op(and,i,rm,b)
make_instr_impl_2op(and,i,rm,v)
make_instr_impl_2op(and,i,rm,bv)
