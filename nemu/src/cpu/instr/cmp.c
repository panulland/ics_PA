#include "cpu/instr.h"
#include "cpu/alu.h"

static void instr_execute_2op() {
	operand_read (&opr_src);
	opr_dest.val = alu_sub(opr_src.val,opr_dest.val,data_size);
}

make_instr_impl_2op(cmp,i,rm,bv)
