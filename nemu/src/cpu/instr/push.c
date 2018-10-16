#include "cpu/instr.h"

make_instr_impl_1op(push,r,v);

make_instr_func(push) {
	OPERAND r;

	int len=1;

	r.type=OPR_REG;
	reg.addr=eip+1;
	reg.data_size=data_size;

	esp = esp - 4;
}
