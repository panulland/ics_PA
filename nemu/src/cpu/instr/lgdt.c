#include "cpu/instr.h"

make_instr_func(lgdt) {
    OPERAND opr_src;
    opr_src.data_size = 32;
    int len = 1;
    len += modrm_rm(eip+1,&opr_src);
    operand_read(&opr_src);
    printf("%x %x %x\n",opr_src.val,opr_src.mem_addr.base,opr_src.mem_addr.disp);
    print_asm_1("lgdt","",len + 1,&opr_src);
    return len; 
}