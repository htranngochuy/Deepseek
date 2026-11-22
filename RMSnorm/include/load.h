<<<<<<< HEAD
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
=======
#ifndef LOAD_H
#define LOAD_H

#include <stdint.h>
#include "data_structure.h" 

void load_gl_x_i (
    DDR4_format *DDR4, 
    RAB_format *RAB, 
    int base_token);

void load_lc_x_i (
    RAB_format *RAB, 
    registers_format *regs, 
    int token_id); 

#endif 
>>>>>>> 4b6ee2877c8efc94c98b57b271a9b984f1392cdc
