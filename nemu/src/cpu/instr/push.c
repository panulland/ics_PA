#include "cpu/instr.h"

make_instr_func(push) {
	OPERAND reg;

	reg.type=OPR_REG;
	reg.addr=eip+1;
	reg.data_size=data_size;

	reg=reg-4;
}
