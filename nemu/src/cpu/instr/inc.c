#include "cpu/instr.h"

static void instr_execute_1op() {
	opr_dest.val ++;
	operand_write(&opr_dest);
	printf("%d\n",opr_dest.val);
}

make_instr_impl_1op(inc,rm,v)
make_instr_impl_1op(inc,r,v)
