#include "cpu/instr.h"

static void instr_execute_1op() {
	opr_dest.val--;
}

make_instr_impl_1op(dec,rm,v)
