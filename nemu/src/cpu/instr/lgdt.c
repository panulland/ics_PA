#include "cpu/instr.h"

make_instr_func(lgdt) {
    OPERAND opr_src;
    opr_src.data_size=data_size;
    opr_src.type = OPR_IMM; 
	opr_src.sreg = SREG_CS; 
	opr_src.addr = eip + 2;
    operand_read(&opr_src);
    print_asm_1("lgdt","",6,&opr_src);
    OPERAND i1,i2;
    printf("%x\n",opr_src.val);
    i1.data_size=16;
    i1.type=OPR_IMM;
    i1.sreg=SREG_CS;
    i1.addr=opr_src.val;
    i2.data_size=32;
    i2.type=OPR_IMM;
    i2.sreg=SREG_CS;
    i2.addr=opr_src.val+3;
    operand_read(&i1);
    operand_read(&i2);
    cpu.gdtr.limit=i1.val;
    cpu.gdtr.base=i2.val;
    return 6; 
}