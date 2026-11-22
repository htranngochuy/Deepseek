#include <stdio.h>
#include <stdlib.h>
#include <string.h>
<<<<<<< HEAD
#include <stdint.h>
#include <math.h>
#include <ctype.h>
#include "data_type.h"
#include "config.h"
#include "data_struct.h"
#include "load.h"
#include "store.h"
#include "kernel.h"

static RAB_format RAB;
static WTB_format WTB;
static registers_format REG;
static bf16 golden[N_TOKEN][D_MODEL];

// Doc gia tri
static long load_hex(const char *path, bf16 *dst, long max_n)
{
    FILE *fp = fopen(path, "r");
    if (!fp) { perror(path); exit(1); }

    long n = 0;
    char tok[64];
    while (n < max_n && fscanf(fp, " %63s", tok) == 1) {
        size_t len = strlen(tok);
        if (len > 0 && tok[len - 1] == ',') tok[len - 1] = '\0';
        if (strchr(tok, '.') || tok[0] == '-') {
            dst[n++] = fp32_to_bf16(strtof(tok, NULL));   
        } else {
            dst[n++].bits = (uint16_t)strtoul(tok, NULL, 16); 
        }
    }
    fclose(fp);
    return n;
}

int main()
{
    const char *in_file  = "data/attn.hc_pre.y.txt";
    const char *w_file   = "data/w_norm.txt";
    const char *ref_file = "data/attn.norm.out.txt";
    const char *out_file = "data/out_C.txt";

    long all = (long)N_TOKEN * D_MODEL;

    // Doc du lieu 
    if (load_hex(in_file, (bf16 *)RAB.i_x_A, all) < all ||
        load_hex(ref_file, (bf16 *)golden, all) < all) {
        printf("Loi file input\n");
        return 1;
    }

    long nw = load_hex(w_file, (bf16 *)WTB.w_norm, all);
    if (nw == D_MODEL) {
        for (int t = 1; t < N_TOKEN; t++)
            memcpy(WTB.w_norm[t], WTB.w_norm[0], sizeof WTB.w_norm[0]);
    } else if (nw < all) {
        printf("Loi file w_norm\n");
        return 1;
    } 

    // Chay RMsnorm 
    REG.norm_eps = NORM_EPS;
    for (int t = 0; t < N_TOKEN; t++) {
        load_local_w_norm(&WTB, &REG, t);
        load_local_i_x_A(&RAB, &REG, t);
        rmsnorm(&REG);
        store_o_nx(&RAB, &REG, t);
    }

    // So sanh golden 
    long exact = 0;
    for (int t = 0; t < N_TOKEN; t++) {
        for (int j = 0; j < D_MODEL; j++) {
            float val_c = bf16_to_fp32(RAB.o_nx[t][j]);
            float val_g = bf16_to_fp32(golden[t][j]);
                if (fabsf(val_c - val_g) <= 1e-5f) {
                    exact++; 
                }
        }
    }

    printf("So sanh %ld phan tu:\n", all);
    printf("  Khop 100%%  : %ld (%.2f%%)\n", exact, 100.0 * exact / all);

    // Ghi ket qua ra file
    FILE *fo = fopen(out_file, "w");
    if (!fo) { perror(out_file); return 1; }
    for (int t = 0; t < N_TOKEN; t++)
        for (int j = 0; j < D_MODEL; j++)
            fprintf(fo, "%04x\n", RAB.o_nx[t][j].bits);
    fclose(fo);

}
=======
#include <math.h>
#include "data_structure.h"
#include "load.h"
#include "kernel.h"
#include "config.h"

static DDR4_format DDR4;               
static RAB_format RAB;
static registers_format REG;
 
int main()
{
    
    srand(1);
    for (int t = 0; t < N_TOKEN; t++)
        for (int i = 0; i < N_HC; i++)
            for (int j = 0; j < D_MODEL; j++)
                DDR4.i_x[t][i][j] = fp32_to_bf16((float)(rand() % 100) / 10.0f);
 
    for (int i = 0; i < N_TOKEN; i += RAB_TOKENS) {
        load_gl_x_i(&DDR4, &RAB, i);                      
 
        for (int t = 0; t < RAB_TOKENS; t++) {
            load_lc_x_i(&RAB, &REG, t);                     
            flatten(&REG);                                  
            rmsnorm(&REG);                             
        }
    }
    for (int i=0; i<4; i++) {
        printf ("%.6f ", REG.y_i[i]);
    }
    printf("\n");
    return 0;
}
>>>>>>> 4b6ee2877c8efc94c98b57b271a9b984f1392cdc
