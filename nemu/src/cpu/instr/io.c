#include "cpu/instr.h"
#include "device/port_io.h"

make_instr_func(in_b) {
    OPERAND al,dx;
    al.data_size = dx.data_size = 8;
    al.type = OPR_REG;
    dx.type = OPR_REG;
    al.addr = REG_AL;
    dx.addr = REG_DX;
    operand_read(&dx);
    al.val = pio_read(dx.val,1);
    operand_write(&al);
    print_asm_0("in","",&dx);
    return 1;
}