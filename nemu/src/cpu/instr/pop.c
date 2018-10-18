#include "cpu/instr.h"

static void instr_execute_1op() {
	opr_dest.type=OPR_MEM;
	opr_dest.addr=cpu.esp;
	opr_dest.data_size=data_size;
	operand_read(&opr_dest);
	cpu.esp += 4;
}
