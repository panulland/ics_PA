#include "cpu/instr.h"

make_instr_func(ret_near) {
	OPERAND rel;
	OPERAND stack;
	stack.type=OPR_REG;
	stack.data_size=data_size;
	stack.addr=0x4;
	rel.data_size=data_size;
	operand_read(&stack);
	rel.addr=stack.val;
	operand_read(&rel);
	cpu.eip=rel.val;
	cpu.esp+=4;

	print_asm_0("ret","",1);

	return 1 + data_size / 8;
}
