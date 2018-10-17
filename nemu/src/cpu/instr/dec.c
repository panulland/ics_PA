#include "cpu/instr.h"

static void instr_execute_1op() {
	opr_dest.val--;
	operand_write(&opr_dest);
}

make_instr_impl_1op(dec,rm,v)
make_instr_impl_1op(dec,r,v)
