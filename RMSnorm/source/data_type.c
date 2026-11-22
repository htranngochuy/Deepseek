#include "data_type.h"

float bf16_to_fp32(bf16 b) {
    uint32_t sign = ((uint32_t)(b.bits & 0x8000)) << 16;
    uint32_t exponent = ((uint32_t)(b.bits & 0x7F80)) << 16;
    uint32_t mantissa = ((uint32_t)(b.bits & 0x007F)) << 16;
    uint32_t fp32_bits = sign | exponent | mantissa;
    float result;
    memcpy(&result, &fp32_bits, sizeof(result));
    return result;
}
 

<<<<<<< HEAD
bf16 fp32_to_bf16(float f)
{
    /*uint32_t fp32_bits;
=======
bf16 fp32_to_bf16(float f) {
    uint32_t fp32_bits;
>>>>>>> 4b6ee2877c8efc94c98b57b271a9b984f1392cdc
    memcpy(&fp32_bits, &f, sizeof(fp32_bits));
    uint16_t sign = (fp32_bits & 0x80000000u) >> 16;      
    uint16_t expo = (fp32_bits & 0x7F800000u) >> 16;      
    uint16_t mant = (fp32_bits & 0x007F0000u) >> 16;      
<<<<<<< HEAD
    bf16 b = { (uint16_t)(sign | expo | mant) }; */ 
    uint32_t u;
    memcpy(&u, &f, sizeof u);
    if ((u & 0x7FFFFFFFu) > 0x7F800000u)           
        u |= 0x00400000u;
    else
        u += 0x7FFFu + ((u >> 16) & 1u);           
    bf16 b = { (uint16_t)(u >> 16) }; 
    return b;
}
=======
    bf16 b = { (uint16_t)(sign | expo | mant) };
    return b;
}
>>>>>>> 4b6ee2877c8efc94c98b57b271a9b984f1392cdc
