#include "load.h"
<<<<<<< HEAD
#include <string.h>

void load_local_i_x_A(
    RAB_format *RAB, 
    registers_format *registers,
    int token_id
) {
    memcpy(
        registers->local_i_x_A, 
        RAB->i_x_A[token_id], 
        sizeof(registers->local_i_x_A));
}

void load_local_w_norm(
    WTB_format *WTB, 
    registers_format *registers,
    int token_id 
) {
    memcpy(
        registers->local_w_norm, 
        WTB->w_norm[token_id], 
        sizeof(registers->local_w_norm));
}
=======

void load_gl_x_i (DDR4_format *DDR4, RAB_format *RAB, int base_token) {
    memcpy(RAB->i_x, DDR4->i_x[base_token], sizeof RAB->i_x);
}

void load_lc_x_i (RAB_format *RAB, registers_format *regs, int token_id) {
    memcpy(regs->x_i, RAB->i_x[token_id], sizeof(bf16) * N_HC * D_MODEL);
}
>>>>>>> 4b6ee2877c8efc94c98b57b271a9b984f1392cdc
