#include"cpu/instr.h"

static void instr_execute_2op() {
	operand_read (&opr_src);
	opr_dest.val=alu_sub(opr_src.val,opr_dest.val,data_size);
	operand_write(&opr_dest);
}

make_instr_impl_2op(sub,i,rm,b)
make_instr_impl_2op(sub,i,rm,v)
make_instr_impl_2op(sub,i,rm,bv)
