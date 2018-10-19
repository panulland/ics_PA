#include"cpu/instr.h"

make_instr_func(call_near) {
	OPERAND rel;
	rel.type = OPR_IMM;
	rel.sreg = SREG_CS;
	rel.data_size = data_size;
	rel.addr = eip + 1;

	operand_read(&rel);
	OPERAND m;
	m.data_size=data_size;
	m.type=OPR_MEM;
	m.val=cpu.eip + 1 + data_size / 8;
	cpu.esp -= 4;
	m.addr=cpu.esp;
	operand_write(&m);

	int offset = sign_ext(rel.val,data_size);
	print_asm_1("call","",1+data_size/8,&rel);

	cpu.eip += offset;
	return 1 + data_size / 8;
}

make_instr_func(call_near_indirect) {
	OPERAND rm;
	rm.data_size=data_size;
	int len = 1;
	len += modrm_rm(eip + 1, &rm);
