#ifndef KERNEL_H
#define KERNEL_H
 
#include <math.h>
<<<<<<< HEAD
#include "data_struct.h"
#include "data_type.h"
#include "config.h"


=======
#include "data_structure.h"
#include "data_type.h"
 
/* Convert the register's bf16 input to a flat fp32 array. */
void flatten(
    registers_format *reg
);
 
/* y_i = gamma * x / sqrt(mean(x^2) + EPS), stored as fp32. */
>>>>>>> 4b6ee2877c8efc94c98b57b271a9b984f1392cdc
void rmsnorm(
    registers_format *reg
);

#endif