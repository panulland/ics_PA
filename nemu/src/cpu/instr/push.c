#include "cpu/instr.h"

static void instr_execute_1op() {
	operand_read(&opr_src);
	cpu.esp=cpu.esp-4;
	
}

make_instr_impl_1op(push,r,v)
