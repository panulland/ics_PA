#include "cpu/instr.h"

static void instr_execute_1op() {
	opr_dest.type = OPR_REG;
	opr_dest.addr = 0x4;
	operand_read(&opr_src);
	//cpu.esp=cpu.esp-4;
	opr_dest.val = opr_src.val;
	operand_write(&opr_dest);
}

make_instr_impl_1op(push,r,v)
