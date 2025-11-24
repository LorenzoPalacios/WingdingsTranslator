#include "wdanalysis.h"

#include <stdio.h>

#include "..\myclib\include\myclib.h"
#include "..\wdtranslator\wdtranslator.h"

typedef char **str_array;
typedef const char *const *const const_str_array;

typedef void (*wd_chr_analysis_f)(FILE *, const char *);

/* - INTERNAL - */

static inline void print_str_bytes(FILE *const out, const char *str) {
  if (*str != '\0') {
    for (; *(str + 1) != '\0'; str++)
      fprintf(out, "%hhu ", (byte)*str);
    fprintf(out, "%hhu", (byte)*str);
  }
}

static inline void print_str_byte_sum(FILE *const out, const char *str) {
  long long sum = 0;
  for (; *str != '\0'; str++)
    sum += (byte)*str;
  fprintf(out, "%lld", sum);
}

/* - FUNCTIONS - */

static const wd_chr_analysis_f FUNCS[] = {print_str_bytes, print_str_byte_sum};

void print_wd_details(FILE *const out, const WD_ANALYSIS_FLAGS flags) {
  const_str_array requested_wd =
      (flags & WDAF_SORTED) ? SORTED_WINGDINGS : WINGDINGS;
  for (size_t i = 0; i < NUM_WINGDINGS; i++) {
    const_wd_char wd_chr = requested_wd[i];
    fprintf(out, "%s", wd_chr);
    for (size_t i = 1; (1 << i) <= flags; i++) {
      if ((1 << i) & flags) {
        fputs(", ", out);
        FUNCS[i - 1](out, wd_chr);
      }
    }
    fputc('\n', out);
  }
}

int main(void) {
  FILE *out = fopen("out.txt", "w");
  print_wd_details(out, WDAF_BYTES | WDAF_BYTE_SUM);
  return 0;
}
