#include"cpu/instr.h"

make_instr_func(call_near) {
	OPERAND rel;
	rel.type = OPR_IMM;
	rel.sreg = SREG_CS;
	rel.data_size = data_size;
	rel.addr = eip + 1;

	operand_read(&rel);

	int offset = sign_ext(rel.val,data_size);
	printf("%d\n",rel.val);
	print_asm_1("call","",2,&rel);



	cpu.eip += offset;
	return 1 + data_size / 8;
}
