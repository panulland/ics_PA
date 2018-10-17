#include "cpu/instr.h"

make_instr_func(ret_near) {
	OPERAND stack;
	stack.type=OPR_REG;
	stack.data_size=data_size;
	stack.addr=0x4;
	operand_read(&stack);
	cpu.eip=stack.val;
	cpu.esp+=4;

	print_asm_1("ret","",2,cpu.eip);

	return 1 + data_size / 8;
}
