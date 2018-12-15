#include "cpu/instr.h"

make_instr_func(int_) {
    OPERAND i;
    i.data_size = 8;
    i.type = OPR_IMM;
    i.sreg = SREG_CS;
    i.addr = cpu.eip + 1;
    operand_read(&i);
    print_asm_1("int","",2,&i);
    return 2;
}