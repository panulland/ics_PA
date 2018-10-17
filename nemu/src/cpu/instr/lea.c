#include "cpu/instr.h"

make_instr_func(lea) {
	OPERAND m,r;

	m.data_size=r.data_size=data_size;

	int len=1;
	len += modrm_r_rm(eip+1,&m,&r);

	r.val=m.addr;
	operand_write(&r);

	prinr_asm_1("lea","",2,&m,&r);

	return len;
}
