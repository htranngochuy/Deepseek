#ifndef DATA_STRUCT_H 
#define DATA_STRUCT_H 

#include "data_type.h"
#include "config.h"

typedef struct {
    bf16 i_x_A[N_TOKEN][D_MODEL];
    bf16 o_nx[N_TOKEN][D_MODEL]; 
} RAB_format;

typedef struct {
    bf16 w_norm[N_TOKEN][D_MODEL];
} WTB_format; 

typedef struct {
    bf16 local_i_x_A[N_TOKEN][D_MODEL]; // RAB -> thanh ghi 
    float i_x_A[N_TOKEN][D_MODEL];  // Cast sang fp32 
    float sum_xi_squared; 
    float i_x_A_nga[N_TOKEN][D_MODEL]; // output RMSnorm 
    bf16 local_w_norm[N_TOKEN][D_MODEL]; // WTB -> thanh ghi 
    bf16 o_nx[N_TOKEN][D_MODEL]; // output toàn khối 
    float norm_eps;
} registers_format;

#endif