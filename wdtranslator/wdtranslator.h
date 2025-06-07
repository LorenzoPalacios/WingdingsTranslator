#ifndef WD_TRANSLATOR
#define WD_TRANSLATOR

#include <limits.h>
#include <stddef.h>

#include "../myclib/str/str.h"

/* - DEFINITIONS - */

#define IS_SMALL_WD(wd_chr) \
  ((wd_chr)[3] == WD_TERM_2 || (wd_chr)[3] == WD_TERM_3)

#define IS_MEDIUM_WD(wd_chr) ((wd_chr)[5] == WD_TERM_1)

#define IS_LARGE_WD(wd_chr) ((wd_chr)[6] == WD_TERM_2)

/* - ENUMS - */

typedef enum : char {
  WD_BEGIN_1 = -16,
  WD_BEGIN_2 = -30,
  WD_BEGIN_3 = -32,
} WD_BEGIN_BYTE;

typedef enum : char {
  WD_TERM_1 = -114,
  WD_TERM_2 = -80,
  WD_TERM_3 = -75,
} WD_END_BYTE;

typedef enum : size_t {
  WD_SIZE_SMALL = sizeof("🙰"),
  WD_SIZE_MEDIUM = sizeof("✏︎"),
  WD_SIZE_LARGE = sizeof("👓︎"),
} WD_SIZE;

/* - TYPES - */

typedef const char *const wd_container[];

typedef char *wd_char;
typedef const char *const const_wd_char;

/* - FUNCTIONS - */

const_wd_char ascii_char_to_wd_char(char ascii);

[[nodiscard]]
string ascii_str_to_wd_str(const char *ascii);

const_wd_char *search_for_wd(const_wd_char);

const_wd_char *search_sorted_wd(const_wd_char);

[[nodiscard]]
string wd_str_to_ascii_str(const char *wd_str);

char wd_char_to_ascii_char(const_wd_char);

#endif
