#include "cpu/instr.h"
#include "device/port_io.h"

make_instr_func(in_b) {
    OPERAND al,dx;
    al.data_size = 8;
    dx.data_size = 16;
    al.type = OPR_REG;
    dx.type = OPR_REG;
    al.addr = REG_AL;
    dx.addr = REG_DX;
    operand_read(&dx);
    print_asm_1("in","",1,&dx);
    al.val = pio_read(dx.val,1);
    operand_write(&al);
    return 1;
}

make_instr_func(in_v) {
    OPERAND r,dx;
    r.data_size = data_size;
    dx.data_size = 16;
    r.type = OPR_REG;
    dx.type = OPR_REG;
    r.addr = REG_EAX;
    dx.addr = REG_DX;
    operand_read(&dx);
    print_asm_1("in","",1,&dx);
    r.val = pio_read(dx.val,data_size / 8);
    operand_write(&r);
    return 1;
}

make_instr_func(out_b) {
    OPERAND r,dx;
    r.data_size = 8;
    dx.data_size = 16;
    r.type = dx.type = OPR_REG;
    r.addr = REG_AL;
    dx.addr = REG_DX;
    operand_read(&r);
    operand_read(&dx);
    pio_write(dx.val, 1, r.val);
    print_asm_1("out","",1,&dx);
    return 1;
}

make_instr_func(out_v) {
    OPERAND r,dx;
    r.data_size = data_size;
    dx.data_size = 16;
    r.type = dx.type = OPR_REG;
    r.addr = REG_EAX;
    dx.addr = REG_DX;
    operand_read(&r);
    operand_read(&dx);
    pio_write(dx.val, data_size / 8, r.val);
    print_asm_1("out","",1,&dx);
    return 1;
}