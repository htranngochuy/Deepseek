#include "store.h"
#include <string.h>

void store_o_nx(
    RAB_format *RAB, 
    registers_format *registers,
    int token_id
) {
    memcpy(
        RAB->o_nx[token_id],
        registers->o_nx,  
        sizeof(RAB->o_nx[token_id]));
} 
