#include <stdio.h>

/* - ENUMS - */

typedef enum : unsigned char {
  WDAF_BYTES = 1 << 1,
  WDAF_BYTE_SUM = 1 << 2,
  WDAF_SORTED = 1 << 3,
} WD_ANALYSIS_FLAGS;

/* - FUNCTIONS - */

void print_wd_details(FILE *out, WD_ANALYSIS_FLAGS);
