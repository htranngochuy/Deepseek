#include "kernel.h"


void rmsnorm(
    registers_format *reg
) { 
   for (int i=0; i<N_TOKEN; i++) {
    float sum_i_x = 0.0f; 
    for (int j=0; j<D_MODEL; j++) {
        float i_A_fp32 = bf16_to_fp32(reg->local_i_x_A[i][j]);
        reg->i_x_A[i][j] = i_A_fp32;
        sum_i_x += i_A_fp32 * i_A_fp32;
    }
    float rms = sqrtf(sum_i_x / D_MODEL + NORM_EPS); 
    for (int j=0; j<D_MODEL; j++) {
        float i_A_fp32 = reg->i_x_A[i][j];
        float w_norm_fp32 = bf16_to_fp32(reg->local_w_norm[i][j]);
        reg->i_x_A_nga[i][j] = (i_A_fp32 / rms) * w_norm_fp32;
        reg->o_nx[i][j] = fp32_to_bf16(reg->i_x_A_nga[i][j]);
    }
   }
}