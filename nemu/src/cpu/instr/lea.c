#include "cpu/instr.h"

make_instr_func(lea) {
	OPERAND m,r;

	m.data_size=r.data_size=data_size;

	int len=1;
	len += modrm_r_rm(eip+1,&r,&m);

	r.val=m.addr;
	operand_write(&r);

	print_asm_2("lea","",3,&m,&r);

	return len;
}
