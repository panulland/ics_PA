#include "cpu/instr.h"

make_instr_funci(lea) {
	OPERAND m,r;

	m.data_size=r.data_size=data_size;

	int len=1;
	len += modrm_r_rm(eip+1,&m,&r);

	r.val=m.addr;
	operand_write(&r);

	return len;
}
