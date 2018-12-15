#include "cpu/instr.h"
#include "cpu/intr.h"

make_instr_func(int_) {
    OPERAND i;
    i.data_size = 8;
    i.type = OPR_IMM;
    i.sreg = SREG_CS;
    i.addr = cpu.eip + 1;
    operand_read(&i);
    print_asm_1("int","",2,&i);
    raise_sw_intr(i.val);
    return 0;
}

make_instr_func(iret) {
    OPERAND m;
    m.data_size = data_size;
    m.type = OPR_MEM;
    m.sreg = SREG_ES;
    m.addr = cpu.esp;
    operand_read(&m);
    cpu.eip = m.val;
    cpu.esp += 4;
    m.addr = cpu.esp;
    operand_read(&m);
    cpu.cs.val = m.val;
    cpu.esp += 4;
    m.addr = cpu.esp;
    operand_read(&m);
    cpu.eflags.val = m.val;
    print_asm_0("iret","",1);
    return 0;
}