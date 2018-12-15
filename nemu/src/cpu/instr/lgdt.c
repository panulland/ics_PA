#include "cpu/instr.h"

make_instr_func(lgdt) {
    OPERAND opr_src,rm;
    rm.data_size=32;
    int len = 1;
    len += modrm_rm(eip+1,&rm);
    operand_read(&rm);
    printf("%x\n",rm.val);
    opr_src.data_size=data_size;
    opr_src.type = OPR_IMM; 
	opr_src.sreg = SREG_CS; 
	opr_src.addr = eip + 2;
    operand_read(&opr_src);
    print_asm_1("lgdt","",len,&opr_src);
    uint32_t g1=0;
    uint32_t g2=0;
    memcpy(&g1, hw_mem + opr_src.val, 2);
    memcpy(&g2, hw_mem + opr_src.val + 2, 4);
    cpu.gdtr.base=g2;
    cpu.gdtr.limit=g1;
    return 6; 
}