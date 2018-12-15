#include "cpu/instr.h"

make_instr_func(lgdt) {
    OPERAND opr_src;
    opr_src.data_size=48;
    int len = 1;
    len += modrm_rm(eip+1,&opr_src);
    operand_read(&opr_src);
    printf("%x\n",opr_src.val);
    print_asm_1("lgdt","",len + 1,&opr_src);
    cpu.gdtr.base=opr_src.val << 16 >> 16;
    cpu.gdtr.limit=opr_src.val >> 32;
    return len; 
}