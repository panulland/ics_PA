#include "cpu/instr.h"

static void instr_execute_1op() {
	operand_read(&opr_src);
	if(opr_src.type==OPR_IMM&&opr_src.data_size==8)
	{
		opr_src.val=sign_ext(opr_src.val,8)&(0xFFFFFFFF>>(32-data_size));
	}
	OPERAND opr_dest;
	opr_dest.data_size=data_size;
	opr_dest.type = OPR_MEM;
	opr_dest.sreg = SREG_DS;
	cpu.esp -= 4;
	opr_dest.addr = cpu.esp;
	opr_dest.val = opr_src.val;
	operand_write(&opr_dest);
}

make_instr_impl_1op(push,r,v)
make_instr_impl_1op(push,rm,v)
make_instr_impl_1op(push,i,v)
make_instr_impl_1op(push,i,b)
