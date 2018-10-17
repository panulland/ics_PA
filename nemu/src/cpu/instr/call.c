#include"cpu/instr.h"

make_instr_func(call_near) {
	OPERAND rel;
	rel.type = OPR_IMM;
	rel.sreg = SREG_CS;
	rel.data_size = data_size;
	rel.addr = eip + 1;

	operand_read(&rel);

	OPERAND stack;
	stack.type = OPR_REG;
	stack.data_size=data_size;
	stack.addr=0x4;
	cpu.esp=cpu.esp-4;
	oprand_write(cpu.eip);

	int offset = sign_ext(rel.val,data_size);
	print_asm_1("call","",2,&rel);



	cpu.eip += offset;
	return 1 + data_size / 8;
}
