#include "cpu/instr.h"

make_instr_func(lgdt) {
    OPERAND opr_src;
    opr_src.data_size = 32;
    int len = 1;
    len += modrm_rm(eip+1,&opr_src);
    operand_read(&opr_src);
    OPERAND i1,i2;
    i1.data_size = 32;
    i2.data_size = 16;
    i1.sreg=i2.sreg=SREG_CS;
    i1.type=i2.type=OPR_IMM;
    i1.addr=opr_src.mem_addr.disp + 2;
    i2.addr=opr_src.mem_addr.disp;
    operand_read(&i1);
    operand_read(&i2);
    cpu.gdtr.base=i1.val;
    cpu.gdtr.limit=i2.val;
    printf("%x %x %x %x %x\n",opr_src.val,opr_src.mem_addr.base,opr_src.mem_addr.disp,opr_src.mem_addr.index,opr_src.mem_addr.scale);
    print_asm_1("lgdt","",len + 1,&opr_src);
    return len; 
}