#include "cpu/instr.h"

make_instr_impl_1op(push,r,v);

make_instr_func(push) {
	OPERAND r;

	int len=1;

	r.data_size=data_size;
	r.type=OPR_REG;
	r.addr=opcode&0x7;

	operand_read(&r);

	return len;
}
