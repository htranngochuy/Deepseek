#ifndef LOAD_H 
#define LOAD_H 

#include "data_type.h"
#include "config.h"
#include "data_struct.h"

void load_local_i_x_A(
    RAB_format *RAB, 
    registers_format *registers,
    int token_id
);

void load_local_w_norm(
    WTB_format *WTB, 
    registers_format *registers,
    int token_id 
);

#endif 
