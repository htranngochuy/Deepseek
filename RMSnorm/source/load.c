#include "load.h"
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
