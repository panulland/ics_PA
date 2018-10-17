#include "cpu/instr.h"

static void instr_execute_2op() {
	operand_read(&opr_src);
	opr_dest=alu_xor(opr_dest.val,opr_src.val,data_size);
	operand_write(&opr_dest);
}

make_instr_impl_2op(xor,i,rm,b)
make_instr_impl_2op(xor,i,rm,v)
make_instr_impl_2op(xor,i,rm,bv)
